===============================================================================
                                 ARDU PoolLink
                    DIFFERENCIÁL MEDENCE HŐMÉRSÉKLET VEZÉRLŐ
                         Felhasználói Kézikönyv és Útmutató
===============================================================================

1. KIJELZETT ÉRTÉKEK MAGYARÁZATA
-------------------------------------------------------------------------------
A vezérlő normál üzemmódban 4 másodpercenként automatikusan vált az alábbi 
három információs oldal között:

1. oldal: Hőmérsékletek és állapotok (Főoldal)
 - S,PANEL: A napkollektor (szolár panel) aktuális hőmérséklete Celsius-fokban.
 - MEDENCE: A medence vizének aktuális hőmérséklete Celsius-fokban.
 - ON/XX (Jobb felső sarok): A szivattyú aktuális állapota. Az ON felirat jelzi, 
   ha a keringetés aktív. Az XX jelzi, ha nem aktív.
 - OK (Jobb alsó sarok): Medence célállapota. OK felirat látható, ha a medence 
   vize elérte vagy meghaladta a beállított maximum limitet.

2. oldal: Napi üzemidő statisztika
 - UZEMIDO: A szivattyú futási ideje a legutóbbi statisztikai nullázás, vagy 
   a bekapcsolása óta (óra, perc, másodperc bontásban).
 - SZ,START: A szivattyú elindulásainak száma a legutóbbi nullázás, vagy 
   bekapcsolás óta. Megmutatja a kapcsolási ciklusok gyakoriságát.

3. oldal: Hatékonyság és melegedés
 - ATLAG H,K,: Az átlagos hőkülönbség a panel és a medence között a szivattyú 
   működése alatt. Minél magasabb, annál több hőt szállít a rendszer.
 - MELEGEDES: A medence nettó hőmérséklet-emelkedése a napi indítási 
   bázishoz képest.


2. KEZELÉSI ÚTMUTATÓ ÉS GOMBFUNKCIÓK
-------------------------------------------------------------------------------
Azonnali Menübe lépés és léptetés:
Nyomd meg és tartsd nyomva a FEL gombot. Pontosan 1 másodperc elteltével a 
készülék azonnal (a gomb elengedése nélkül) belép a menübe. Nyomd meg újra, 
1 másodperc elteltével a készülék azonnal (a gomb elengedése nélkül) tovább 
lép a következő menüpontra.

Értékek módosítása a menüben:
 - Növelés: Nyomd meg röviden (fél másodpercnél rövidebb ideig) a FEL gombot.
 - Csökkentés: Nyomd meg röviden (fél másodpercnél rövidebb ideig) a LE gombot.
 - Mentés: Nem szükséges külön gombnyomás. Ha 10 másodpercig nem nyúlsz a 
   készülékhez, az értékek automatikusan elmentődnek az EEPROM memóriába, 
   és a kijelző visszatér a főoldalra.

A menüpontok listája:

[1. menüpont] - MAX MEDENCE
 - Gyári alapérték: 35.0 °C
 - Leírás: A medence maximális megengedett hőfoka. Efelett a szivattyú letilt. 
   (20 és 40 °C között állítható 1°C lépésekben).

[2. menüpont] - START DIFF
 - Gyári alapérték: 4.0 °C
 - Leírás: Indítási hőkülönbség. Ennyivel kell melegebbnek lennie a panelnek 
   az indításhoz. (2 és 10 °C között állítható 0.5°C lépésekben).

[3. menüpont] - STOP DIFF
 - Gyári alapérték: 2.0 °C
 - Leírás: Leállási hőkülönbség. Ha a különbség ez alá csökken, a keringetés 
   leáll. (1 és 5 °C között állítható 0.5°C lépésekben).

[4. menüpont] - OSSZ. IDO (h)
 - Gyári alapérték: -
 - Leírás: Élettartam számláló. 1: Szivattyú összes futott órája, 
   2: Az Arduino kártya teljes üzemideje. (Nem módosítható).

[5. menüpont] - DATE / SN
 - Gyári alapérték: -
 - Leírás: Dátuma és szoftver származása.


3. DIFFERENCIÁL-HISZTERÉZIS MŰKÖDÉSE (START DIFF ÉS STOP DIFF)
-------------------------------------------------------------------------------
A vezérlő alapvető feladata, hogy csak akkor keringesse a vizet, ha a 
napkollektorból valódi hőenergiát tudunk átadni a medencének. A rendszer 
működését két külön határérték, a START DIFF és a STOP DIFF szabályozza. 
Ez a két érték együtt alkotja a differenciál-hiszterézist, amely megakadályozza 
a szivattyú sűrű ki-be kapcsolgatását felhős időben.

START DIFF (Indítási hőkülönbség)
 - Gyári érték: 4.0 °C | Javasolt tartomány: 4.0 °C - 6.0 °C
 - Ez az az érték, amennyivel a kollektornak melegebbnek kell lennie, mint a 
   medence vize, hogy a szivattyú elinduljon. Ha a medence 25 °C-os és a 
   START DIFF 4 °C, a szivattyú csak akkor indul el, ha a kollektor eléri 
   a 29 °C-ot.
 - Túl alacsony értéknél (pl. 2 °C): A szivattyú túl korán elindul. A beáramló 
   hideg medencevíz másodpercek alatt visszahűti a kollektort, a hőkülönbség 
   eltűnik, és a szivattyú azonnal leáll.
 - Túl magas értéknél (pl. 10 °C): A szivattyú nagyon későn (csak tűző napon) 
   indul el. Ezzel rengeteg hasznos energiát veszítünk el.

STOP DIFF (Leállási hőkülönbség)
 - Gyári érték: 2.0 °C | Javasolt tartomány: 1.5 °C - 2.0 °C
 - Amikor a szivattyú dolgozik, folyamatosan hűti a kollektort. A STOP DIFF 
   határozza meg azt a minimális hőkülönbséget, ami alatt a keringetés már 
   nem gazdaságos, vagy ahol már fennáll a veszélye, hogy a medence vize 
   elkezdi fűteni a hideg kollektort (visszahűlés).
 - Ha a medence 25 °C-os és a STOP DIFF 2 °C, a szivattyú mindaddig működik, 
   amíg a kollektor le nem hűl 27 °C-ra. Amint a különbség 2 °C alá csökken, 
   a szivattyú leáll.

ÜZEMI JAVASLAT: A legtöbb házi építésű és gyári medencefűtéshez a START DIFF: 
4.0 °C és STOP DIFF: 2.0 °C párosítás nyújtja a legjobb hatásfokot. Ez a 2 °C-os 
üzemi sáv biztosítja a stabil, tartós szivattyúciklusokat és a kiváló 
élettartamot.


4. INTELLIGENS MAXIMUM LIMIT VÉDELEM
-------------------------------------------------------------------------------
A szivattyú és a relé védelme érdekében a vezérlő egy külön +-0.2 °C-os 
biztonsági sávot használ a medence maximális hőfokának elérésekor is:

 - Lekapcsolás: Ha a medence eléri a beállított határérték + 0.2 °C fokot 
   (pl. 35.0 °C limitnél a 35.2 °C-ot), a szivattyú azonnal leáll, 
   túlmelegedési tiltásba lép, és a főoldal jobb alsó sarkában az OK felirat 
   jelenik meg.
 - Visszakapcsolás: A letiltás mindaddig aktív marad, amíg a medence vissza 
   nem hűl a beállított határérték - 0.2 °C foka alá (pl. 35.0 °C limitnél 
   a 34.8 °C-ra). A visszahűlés fázisa alatt is az OK felirat látható, 
   jelképezve, hogy a medence elérte a kívánt melegséget. Ha 34.8 °C alá 
   esik a hőfok, újra elindul a keringető szivattyú.


5. MANUÁLIS NULLÁZÁSOK (RESET)
-------------------------------------------------------------------------------
JAVASLAT: Javasolt minden nap reggel elindítani és naplementekor lekapcsolni 
az elektronikát! Ezzel a napi statisztikákat is nullázzuk és nem pörög 
feleslegesen a program!

Napi statisztikák törlése bekapcsolt állapotban:
 - Nyomd meg és tartsd nyomva a FEL és LE gombokat egyszerre 1 másodpercig. 
   A kijelzőn a "STATISZTIKA RESET... OK" felirat jelenik meg. Ez nullázza 
   a napi üzemidőt, az indítások számát és a melegedési bázist. A teljes 
   élettartam-számlálót nem érinti.

Gyári értékek visszaállítása:
 - A főoldalon nyomd meg és tartsd nyomva a LE gombot 1 másodpercig. 
   A kijelzőn a "BEALLITASOK ALAPHELYZET...OK" szöveg igazolja a gyári 
   alapértékek (35°C / 4°C / 2°C) visszaállítását.


6. HIBAELHÁRÍTÁSI ÚTMUTATÓ
-------------------------------------------------------------------------------
A kijelzőn a "SZENZOR HIBA! ELLENORIZD!" felirat olvasható
 - Ok: A digitális hőmérők egyike megszakadt, meghibásodott, vagy zárlatos lett 
   (az Arduino -50 °C alatti értéket kapott).
 - Biztonsági reakció: A vezérlő a hiba észlelése után 5 másodperccel leállítja 
   a szivattyút, megelőzve a hibás működést.
 - Megoldás: Ellenőrizd a DS18B20 szenzorok kábelezését és a csatlakozókat. 
   A hiba megszűnése után a vezérlés automatikusan folytatódik.

A szivattyú nem indul el, pedig süt a nap
 - Ellenőrzés 1: Nézd meg a medence aktuális hőmérsékletét és a jobb alsó sarkot. 
   Ha ott OK felirat látható, és a hőmérséklet magasabb, mint a beállított 
   maximum limit + 0.2 °C, a vezérlő túlmelegedési tiltás miatt lekapcsolva 
   tartja a rendszert.
 - Ellenőrzés 2: Várj, amíg a hőkülönbség eléri a START DIFF értéket. 
   Előfordulhat, hogy a panel még nem melegedett fel eléggé a medencéhez képest.


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
