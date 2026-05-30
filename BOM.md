# 🔧 ARDU PoolLink – Alkatrészlista (BOM)

Az alábbi lista a jelenlegi ARDU PoolLink vezérlő alapverziójához készült.

A projekt hobbi fejlesztés alatt áll, ezért az alkatrészek típusa és kialakítása később még változhat.

---

# 📦 Főbb elektronikai alkatrészek

| Megnevezés                           | Darabszám       | Megjegyzés                |
| ------------------------------------ | --------------- | ------------------------- |
| Arduino Nano                         | 1 db            | ATmega328P alapú          |
| AR-NANO-IOSH                         | 1 db            | Összeszereléshez          |
| DS18B20 vízálló hőmérséklet érzékelő | 2 db            | 1-Wire rendszer           |
| 4.7kΩ ellenállás                     | 1 db            | DS18B20 adatvonal felhúzó |
| 16x2 I2C LCD kijelző                 | 1 db            | PCF8574 I2C modul         |
| RELA-1CH 5V                          | 1 db            | 5V-os vezérlés            |
| 230V kapcsoló (ON/OFF)               | 2 db            | Bekapcsolás               |
| Nyomógomb                            | 2 db            | Menü kezelés              |
| ACDCM-5V-700  230VAC/5V 700mA DC     | 1 db            | Stabil 5V DC              |
| Sorkapocs                            | több db         | Bekötésekhez              |
| Vezetékek                            | szükség szerint | Bekötésekhez              |

---

# ⚡ Hálózati oldali elemek

| Megnevezés                 | Darabszám       | Megjegyzés           |
| -------------------------- | --------------- | -------------------- |
| Keringető szivattyú        | 1 db            | Medence rendszerhez  |
| Biztosíték                 | ajánlott        | Védelemhez           |
| Kapcsoló                   | opcionális      | Főkapcsoló           |
| Hálózati kábel             | szükség szerint | 230V bekötés         |
| Műanyag vagy földelt doboz | 1 db            | Érintésvédelem miatt |

---

# 🛡 Ajánlott védelmek

A biztonság érdekében erősen ajánlott:

* megfelelő biztosítékozás
* FI-relé használata
* galvanikus leválasztás
* megfelelő relé terhelhetőség
* földelés
* nedvesség elleni védelem
* kültéri használat esetén vízálló doboz

---

# 📟 Jelenlegi kijelző funkciók

A rendszer jelenleg képes megjeleníteni:

* kollektor hőmérséklet
* medence hőmérséklet
* szivattyú állapot
* üzemidő
* indítások száma
* átlagos differenciál hőmérséklet
* medence melegedés
* rendszer információk

---

# ⚠️ FIGYELMEZTETÉS

A projekt hálózati feszültséget használhat.

A 230V-os hálózati áram életveszélyes lehet!

A projekt megépítését és használatát kizárólag megfelelő elektromos ismeretekkel rendelkező személy végezze.

Amennyiben nem rendelkezel megfelelő tapasztalattal:

* kérj szakmai segítséget
* bízd villanyszerelőre a hálózati bekötést

A projekt hobbi és oktatási célból készült.
Mindenki kizárólag saját felelősségre használja.

---

# 👨‍🔧 Fejlesztő

Lerch Krisztián

ARDU PoolLink hobby project
