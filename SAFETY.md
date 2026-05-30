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
