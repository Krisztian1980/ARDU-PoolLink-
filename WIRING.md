===============================================================================
                                 ARDU PoolLink
                               MEDENCE VEZÉRLŐ
                            ÖSSZESZERELÉSI ÚTMUTATÓ
                              (Lerch Krisztián)
===============================================================================

1. ALAPKÖTÉSEK (Arduino Nano / Uno)
-------------------------------------------------------------------------------
Tápellátás:
 - Arduino 5V   -> 5V táp
 - Arduino GND  -> Közös föld

FONTOS: Minden eszköznek közös GND-n (földelésen) kell lennie!


2. DS18B20 HŐMÉRŐK (2 DB)
-------------------------------------------------------------------------------
Kollektor szenzor:
 - VCC  -> 5V
 - GND  -> GND
 - DATA -> D2

Medence szenzor:
 - VCC  -> 5V
 - GND  -> GND
 - DATA -> D2 (ugyanarra a buszra!)

Kötelező elem:
 - 4.7 kOhm ellenállás a D2 és az 5V lábak közé kötve (Pull-up).


3. LCD KIJELZŐ (I2C 16x2)
-------------------------------------------------------------------------------
Bekötés:
 - VCC -> 5V
 - GND -> GND
 - SDA -> A4
 - SCL -> A5


4. SZIVATTYÚ RELÉ
-------------------------------------------------------------------------------
Vezérlési oldal bekötése:
 - IN  -> D3
 - VCC -> 5V
 - GND -> GND

Teljesítmény (230V) oldal:
 - COM -> Hálózati fázis bemenet
 - NO  -> Szivattyú fázis kimenet
 - N   -> Közvetlen hálózati nulla

⚠️ FIGYELEM: A 230V-os hálózat szerelése csak villanyszerelői biztonsággal, 
feszültségmentesítés után végezhető!


5. GOMBOK
-------------------------------------------------------------------------------
FEL gomb (UP):
 - Egyik láb -> D4
 - Másik láb -> GND

LE gomb (DOWN):
 - Egyik láb -> D5
 - Másik láb -> GND

FONTOS: Az Arduino belső PULLUP ellenállása van használva a programban, 
ezért külső ellenállás beépítése NEM szükséges!


6. RENDSZER LOGIKAI ELRENDEZÉS
-------------------------------------------------------------------------------
Fizikai elhelyezés:
 - Kollektor szenzor: Tetőn, a napkollektor kimenetnél, hőálló csőben elhelyezve.
 - Medence szenzor:   A visszatérő vízágban, közvetlenül a szűrő után.
 - Relé:              Száraz, védett dobozban, vibrációtól távol.
 - Arduino:           Zárt műanyag dobozban, teljesen páramentes helyen.


7. INDÍTÁSI SORREND
-------------------------------------------------------------------------------
[ LÉPÉS 1 ] - Ellenőrzés
 - Minden GND közösítve van.
 - Nincs rövidzár az áramkörben.
 - A szenzorok megfelelően csatlakoznak.

[ LÉPÉS 2 ] - Táp ráadás
 - Az LCD kijelző felvillan.
 - A "Medence vezérlés" üzenet megjelenik a képernyőn.

[ LÉPÉS 3 ] - Ellenőrzés
 - Mindkét hőmérséklet érték helyesen látszik.
 - Nincs "-127°C"-os hibaüzenet a kijelzőn.


8. BEÁLLÍTÁS ELSŐ INDÍTÁSNÁL
-------------------------------------------------------------------------------
Gyári alapértékek:
 - MEDENCE MAX: 35°C
 - START DIFF:  4°C
 - STOP DIFF:   2°C

Megjegyzés: Ezeket az értékeket a gombok segítségével lehet finomhangolni 
a menüben.


9. TIPIKUS HIBÁK ÉS MEGOLDÁSOK
-------------------------------------------------------------------------------
Hiba: LCD nem működik
 - Ok: Rossz SDA/SCL bekötés vagy hibás I2C cím a kódban.

Hiba: Szenzor -127°C értéket mutat
 - Ok: Hiányzik a 4.7k-s pull-up ellenállás, vagy rossz a D2 bekötés.

Hiba: A relé nem kapcsol
 - Ok: A D3 láb nincs kimenetként definiálva, vagy rossz a relé logikája 
   (Active LOW / HIGH felcserélés).

Hiba: Nincs fűtés, a rendszer nem indul
 - Ok: A START DIFF érték túl magasra van állítva, vagy a két hőmérséklet 
   szenzor fizikailag fel lett cserélve.

 ===============================================================================
              ⚠️ 230V ÉRINTÉSVÉDELMI ÉS BIZTONSÁGI ELŐÍRÁSOK!
===============================================================================

1. ÁLTALÁNOS FIGYELMEZTETÉS
-------------------------------------------------------------------------------
A rendszer 230V hálózati feszültséggel működő berendezést (szivattyú) vezérel 
relén keresztül.

A 230V váltakozó feszültség:
 - Életveszélyes
 - Súlyos áramütést okozhat
 - Tüzet okozhat nem megfelelő kivitelezés esetén

A rendszer telepítése és karbantartása kizárólag megfelelő szakképesítéssel 
rendelkező személy által végezhető!


2. ÉRINTÉSVÉDELMI KÖVETELMÉNYEK
-------------------------------------------------------------------------------
A 230V-os rész kialakításánál az alábbi védelem kötelező:

[ Kettős szigetelés ]
 - Minden vezető rész szigetelt kivitelben legyen
 - Fém ház esetén kötelező a földelés

[ Védőföldelés (PE) ]
 - Minden fém burkolat kötelezően földelve
 - Szivattyú védőföldelése kötelező

[ Áram-védőkapcsoló (FI-relé) ]
 - 30 mA érzékenységű FI-relé használata kötelező
 - Ez életvédelmi alapfeltétel


3. RELÉ ÉS VÁLTÓÁRAM KÖR KIALAKÍTÁSA
-------------------------------------------------------------------------------
A relé csak galvanikusan leválasztott vezérlést végezhet.

Kötelező szabályok:
 - Arduino és 230V hálózat fizikailag el kell legyen választva
 - Relé modul optocsatolt legyen (ajánlott)
 - Vezetékek között megfelelő távolság legyen

Helyes kapcsolás:
 - Fázis (L) megszakítása relén keresztül történik
 - Nulla (N) nem kapcsolható alap esetben
 - Védőföld (PE) soha nem szakítható meg


4. BURKOLAT ÉS SZERELÉSI KÖRNYEZET
-------------------------------------------------------------------------------
Kötelező előírások:
 - 230V-os részek zárt, érintésvédett dobozban legyenek
 - IP65 vagy magasabb védettség kültéren
 - Nedvesség, pára és fröccsenő víz elleni védelem kötelező

Tiltott:
 - Nyitott sorkapocs
 - Szigeteletlen vezeték
 - Ideiglenes kötés kültéren


5. VESZÉLYES ÜZEMI ÁLLAPOTOK
-------------------------------------------------------------------------------
A következő esetek azonnali veszélyhelyzetet jelentenek:
 - Szigetelés sérülése
 - Vizes környezetben nyitott elektronika
 - Földelés hiánya
 - Hibás relé érintkezés (összeégés, beragadás)
 - Túlmelegedett vezetékek

FIGYELEM: Ilyen esetben a rendszert azonnal feszültségmentesíteni kell!


6. KARBANTARTÁS ÉS SZERVIZ
-------------------------------------------------------------------------------
Karbantartás előtt kötelező az alábbi sorrend betartása:
 1. Főkapcsoló lekapcsolása
 2. FI-relé leoldása vagy leválasztás
 3. Feszültségmentesség ellenőrzése műszerrel

Csak ezen lépések elvégzése után kezdhető meg bármilyen szerelési munka!


7. FELELŐSSÉGI NYILATKOZAT
-------------------------------------------------------------------------------
Ez a rendszer prototípus jellegű vezérlőelektronika.
A készítő nem vállal felelősséget:
 - Szakszerűtlen bekötésből eredő károkért
 - Érintésvédelmi előírások megszegésomért
 - Nem megfelelő villamos kivitelezésből eredő balesetekért

A végleges telepítés minden esetben szakember feladata!


8. AJÁNLOTT BIZTONSÁGI KIEGÉSZÍTÉSEK
-------------------------------------------------------------------------------
A rendszer biztonsága jelentősen növelhető az alábbiakkal:
 - FI-relé (30 mA)
 - Kismegszakító külön ágon
 - Túlfeszültség védelem (SPD)
 - IP65 műszerdoboz
 - Sorkapcsos ipari bekötés


9. ÖSSZEFOGLALÁS
-------------------------------------------------------------------------------
A 230V hálózati rész helytelen kivitelezése életveszélyes.
A rendszer csak akkor tekinthető biztonságosnak, ha:
 - Megfelelő szigetelés biztosított
 - FI-relé használva van
 - Relé galvanikusan leválasztott
 - Minden kötés zárt, védett kivitelű

===============================================================================
