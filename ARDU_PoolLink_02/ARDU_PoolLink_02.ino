// ====================================================================================
// DIFFERENCIÁL MEDENCE HŐMÉRSÉKLET VEZÉRLŐ Lerch Krisztián  (ver:02)
// ====================================================================================

#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define ONE_WIRE_BUS 2
#define pumpPin 3
#define BTN_UP 4
#define BTN_DOWN 5

LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// --- EEPROM Memória Címek ---
const int ADDR_TANK_LIMIT = 0;
const int ADDR_START_DT = 4;
const int ADDR_STOP_DT = 8;
const int ADDR_TOTAL_RUN = 12;
const int ADDR_TOTAL_PUMP = 16;

// --- Beállítások és statisztikai változók ---
float tankLimit, startDT, stopDT;
const char buildDate[] = "2026.05.29.";
const char serialNum[] = "Lerch Ver:02";

int menuMode = 0;
uint32_t lastBtnPress = 0;
uint32_t totalRunSeconds = 0;
uint32_t totalPumpSeconds = 0;
uint32_t lastAutoSave = 0;

float tankT = 25.0, collT = 25.0;
float initialTankT = -100.0;
float maxTankT = -100.0;
float tempRise = 0.0;

uint32_t displayTimer = 0;
int displayPage = 0;
uint32_t pumpActiveSeconds = 0;
uint32_t pumpStarts = 0;
bool pumpRunningLastCycle = false;
uint32_t lastStatUpdate = 0;
float diffSum = 0;
uint32_t diffCount = 0;

// --- Időzítők a gombfunkciókhoz ---
uint32_t btnUpTimer = 0;
uint32_t btnDownTimer = 0;
uint32_t resetTimer = 0;
uint32_t sensorErrorTimer = 0;
bool sensorErrorActive = false;

// --- Hosszú gombnyomás kezelés ---
bool longPressHandled = false;

// --- Élettartam adatok mentése az EEPROM-ba ---
void saveLifeStats() {
    uint32_t currentRunSec = millis() / 1000;
    EEPROM.put(ADDR_TOTAL_RUN, totalRunSeconds + currentRunSec);
    EEPROM.put(ADDR_TOTAL_PUMP, totalPumpSeconds + pumpActiveSeconds);
}

void setup(void) {

  EEPROM.get(ADDR_TANK_LIMIT, tankLimit);
  EEPROM.get(ADDR_START_DT, startDT);
  EEPROM.get(ADDR_STOP_DT, stopDT);
  EEPROM.get(ADDR_TOTAL_RUN, totalRunSeconds);
  EEPROM.get(ADDR_TOTAL_PUMP, totalPumpSeconds);

  if (isnan(tankLimit) || tankLimit < 20) tankLimit = 35;
  if (isnan(startDT) || startDT < 2) startDT = 4;
  if (isnan(stopDT) || stopDT < 1) stopDT = 2;

  if (totalRunSeconds == 0xFFFFFFFF) totalRunSeconds = 0;
  if (totalPumpSeconds == 0xFFFFFFFF) totalPumpSeconds = 0;

  sensors.begin();

  lcd.init();
  lcd.backlight();

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  digitalWrite(pumpPin, LOW);
  pinMode(pumpPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print(" ARDU  PoolLink ");

  lcd.setCursor(0, 1);
  lcd.print("Medence vezerles");

  delay(2000);
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(" Szep napot! :) ");

  lcd.setCursor(0, 1);
  lcd.print("Kezdem a munkat!");

  delay(4000);
  lcd.clear();

  lastStatUpdate = millis();
  lastAutoSave = millis();
  displayTimer = millis();
}

void loop(void) {

  uint32_t currentMillis = millis();

  bool btnUpNow = !digitalRead(BTN_UP);
  bool btnDownNow = !digitalRead(BTN_DOWN);

  // --- 1. STATISZTIKA RESET (FEL+LE GOMB 1 MP) ---

  if (btnUpNow && btnDownNow) {

    if (resetTimer == 0) resetTimer = currentMillis;

    if (currentMillis - resetTimer >= 1000) {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("STATISZTIKA");

      lcd.setCursor(0, 1);
      lcd.print("RESET... OK");

      pumpActiveSeconds = 0;
      pumpStarts = 0;
      diffSum = 0;
      diffCount = 0;

      initialTankT = tankT;
      maxTankT = tankT;
      tempRise = 0;

      delay(1500);

      lcd.clear();

      resetTimer = 0;
    }

  } else {

    resetTimer = 0;
  }

  // --- 2. BEÁLLÍTÁSOK RESET (CSAK LE GOMB 1 MP) ---

  if (btnDownNow && !btnUpNow) {

    if (btnDownTimer == 0) btnDownTimer = currentMillis;

    if (currentMillis - btnDownTimer >= 1000) {

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("BEALLITASOK");

      lcd.setCursor(0, 1);
      lcd.print("ALAPHELYZET...OK");

      tankLimit = 35.0;
      startDT = 4.0;
      stopDT = 2.0;

      EEPROM.put(ADDR_TANK_LIMIT, tankLimit);
      EEPROM.put(ADDR_START_DT, startDT);
      EEPROM.put(ADDR_STOP_DT, stopDT);

      delay(1500);

      lcd.clear();

      btnDownTimer = 0;
    }

  } else if (!btnDownNow && btnDownTimer != 0) {

    uint32_t duration = currentMillis - btnDownTimer;

    if (duration < 500 && menuMode > 0 && menuMode <= 3) {

      if (menuMode == 1 && tankLimit > 20) tankLimit -= 1;
      if (menuMode == 2 && startDT > 2) startDT -= 0.5;
      if (menuMode == 3 && stopDT > 1) stopDT -= 0.5;

      lastBtnPress = currentMillis;
    }

    btnDownTimer = 0;
  }

  // --- 3. MENÜ BELÉPÉS ÉS ÉRTÉK MÓDOSÍTÁS (FEL GOMB) ---

  if (btnUpNow && !btnDownNow) {

    if (btnUpTimer == 0) {
      btnUpTimer = currentMillis;
      longPressHandled = false;
    }

    // Hosszú nyomás AZONNAL aktivál
    if (!longPressHandled && (currentMillis - btnUpTimer >= 1000)) {

      menuMode++;

      if (menuMode > 5) menuMode = 0;

      saveLifeStats();

      lcd.clear();

      lastBtnPress = currentMillis;

      longPressHandled = true;
    }

  }
  else if (!btnUpNow && btnUpTimer != 0) {

    uint32_t duration = currentMillis - btnUpTimer;

    // Rövid nyomás
    if (!longPressHandled && duration < 500 && menuMode > 0 && menuMode <= 3) {

      if (menuMode == 1 && tankLimit < 40) tankLimit += 1;
      if (menuMode == 2 && startDT < 10) startDT += 0.5;
      if (menuMode == 3 && stopDT < 5) stopDT += 0.5;

      lastBtnPress = currentMillis;
    }

    btnUpTimer = 0;
  }

  // --- Menü kezelése ---

  if (menuMode > 0) {

    if (currentMillis - lastBtnPress > 10000) {

      EEPROM.put(ADDR_TANK_LIMIT, tankLimit);
      EEPROM.put(ADDR_START_DT, startDT);
      EEPROM.put(ADDR_STOP_DT, stopDT);

      menuMode = 0;

      lcd.clear();
    }

    lcd.setCursor(0, 0);

    if (menuMode == 1) {

      lcd.print("MAX MEDENCE:  ");
      lcd.setCursor(0, 1);
      lcd.print(tankLimit, 1);
      lcd.print(" C     ");
    }

    if (menuMode == 2) {

      lcd.print("START DIFF:   ");
      lcd.setCursor(0, 1);
      lcd.print(startDT, 1);
      lcd.print(" C     ");
    }

    if (menuMode == 3) {

      lcd.print("STOP DIFF:    ");
      lcd.setCursor(0, 1);
      lcd.print(stopDT, 1);
      lcd.print(" C     ");
    }

    if (menuMode == 4) {

      lcd.print("OSSZ. IDO(h): ");

      lcd.setCursor(0,1);

      lcd.print("1:");
      lcd.print((totalPumpSeconds + pumpActiveSeconds) / 3600);

      lcd.print(" 2:");
      lcd.print((totalRunSeconds + (currentMillis/1000)) / 3600);

      lcd.print("h");
    }

    if (menuMode == 5) {

      lcd.print("DATE: ");
      lcd.print(buildDate);

      lcd.setCursor(0,1);
      lcd.print(serialNum);
    }

    return;
  }

  // --- 4. SZENZOROK LEKÉRÉSE ÉS HIBAFIGYELÉS ---

  sensors.requestTemperatures();

  float rawTank = sensors.getTempCByIndex(0);
  float rawColl = sensors.getTempCByIndex(1);

  if (rawTank < -50 || rawColl < -50) {

      if (sensorErrorTimer == 0)
          sensorErrorTimer = currentMillis;

      if (currentMillis - sensorErrorTimer >= 5000) {

          sensorErrorActive = true;

          digitalWrite(pumpPin, LOW);
      }

  } else {

      sensorErrorTimer = 0;
      sensorErrorActive = false;
  }

  if (sensorErrorActive) {

      lcd.setCursor(0, 0);
      lcd.print("SZENZOR HIBA! ");

      lcd.setCursor(0, 1);
      lcd.print("ELLENORIZD!   ");

      return;
  }

  // --- 5. VEZÉRLÉSI LOGIKA ---

  tankT = rawTank;
  collT = rawColl;

  float currentDiff = collT - tankT;

  if (initialTankT < -90) {

      initialTankT = tankT;
      maxTankT = tankT;
  }

  if (tankT > maxTankT)
      maxTankT = tankT;

  tempRise = maxTankT - initialTankT;

  bool isRunningNow = digitalRead(pumpPin);

  // Indítás
  if (!isRunningNow &&
      (currentDiff >= startDT) &&
      (tankT < (tankLimit - 0.2)))
  {
      digitalWrite(pumpPin, HIGH);
  }

  // Leállítás
  else if (isRunningNow &&
           ((currentDiff <= stopDT) ||
            (tankT >= (tankLimit + 0.2))))
  {
      digitalWrite(pumpPin, LOW);
  }

  isRunningNow = digitalRead(pumpPin);

  if (isRunningNow && !pumpRunningLastCycle)
      pumpStarts++;

  pumpRunningLastCycle = isRunningNow;

  if (isRunningNow) {

      if (currentMillis - lastStatUpdate >= 1000) {

          uint32_t secondsPassed =
              (currentMillis - lastStatUpdate) / 1000;

          pumpActiveSeconds += secondsPassed;

          diffSum += (currentDiff * secondsPassed);

          diffCount += secondsPassed;

          lastStatUpdate += (secondsPassed * 1000);
      }

  } else {

      lastStatUpdate = currentMillis;
  }

  // --- 6. KIJELZŐ FRISSÍTÉSE ---

  if (currentMillis - displayTimer > 4000) {

      displayPage++;

      if (displayPage > 2)
          displayPage = 0;

      displayTimer = currentMillis;

      lcd.clear();
  }

  if (displayPage == 0) {

      lcd.setCursor(0, 0);
      lcd.print("S,PANEL:");
      lcd.print(collT, 1);
      lcd.print("C");

      lcd.setCursor(14, 0);
      lcd.print(isRunningNow ? "ON" : "XX");

      lcd.setCursor(0, 1);
      lcd.print("MEDENCE:");
      lcd.print(tankT, 1);
      lcd.print("C");

      // Jobb alsó sarok: OK jelzés
      if (tankT >= tankLimit) {

          lcd.setCursor(14, 1);
          lcd.print("OK");
      }
  }

  else if (displayPage == 1) {

      lcd.setCursor(0, 0);

      lcd.print("UZEMIDO:");
      lcd.print(pumpActiveSeconds / 3600);
      lcd.print("o");

      lcd.print((pumpActiveSeconds % 3600) / 60);
      lcd.print("p");

      lcd.print(pumpActiveSeconds % 60);
      lcd.print("m");

      lcd.setCursor(0, 1);

      lcd.print("SZ,START: ");
      lcd.print(pumpStarts);
      lcd.print("x");
  }

  else {

      lcd.setCursor(0, 0);
      lcd.print("ATLAG H,K,: ");

      if (diffCount > 0) {

          lcd.print(diffSum / diffCount, 1);
          lcd.print("C");

      } else {

          lcd.print("0.0C");
      }

      lcd.setCursor(0, 1);

      lcd.print("MELEGEDES: +");
      lcd.print(tempRise, 1);
      lcd.print("C");
  }

  // --- Automatikus mentés óránként ---

  if (currentMillis - lastAutoSave >= 3600000) {

      saveLifeStats();

      lastAutoSave = currentMillis;
  }
}