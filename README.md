# 🌞 ARDU PoolLink

### Arduino alapú differenciál medence napkollektor vezérlő

## Projekt bemutatása

Az ARDU PoolLink egy saját fejlesztésű, Arduino alapú differenciál hőmérséklet vezérlő medence napkollektoros rendszerekhez.

A projekt hobbi és kísérleti céllal készült azzal az alapötlettel, hogy a medence vizét csak akkor érdemes a napkollektoron keresztül keringetni, amikor abból ténylegesen hasznos hő nyerhető.

A vezérlő folyamatosan figyeli:

* a napkollektor hőmérsékletét
* valamint a medence vízhőmérsékletét

A két érték különbsége alapján automatikusan kapcsolja a keringető szivattyút.

A projekt jelenleg is fejlesztés alatt áll, nem kereskedelmi termék.
A forráskód és a dokumentáció szabadon felhasználható, módosítható és továbbfejleszthető.

---

# ⚙️ Főbb funkciók

* Differenciál hőmérséklet alapú automatikus vezérlés
* Állítható indítási hőmérséklet különbség
* Állítható leállási hőmérséklet különbség
* Maximális medencehőmérséklet korlátozás
* Automatikus szivattyú vezérlés
* Szenzorhiba figyelés
* Többoldalas LCD információs kijelzés
* Üzemidő statisztikák
* Szivattyú indítás számláló
* Átlagos hőmérséklet különbség számítás
* Medence melegedés követése
* EEPROM alapú beállítás mentés
* Egyszerű kétgombos kezelőfelület

---

# 📟 Kijelzett információk

A rendszer valós időben képes megjeleníteni:

* kollektor hőmérséklet
* medence hőmérséklet
* szivattyú állapot
* üzemidő
* indítások száma
* átlagos differenciál hőmérséklet
* medence teljes melegedése

---

# 🔧 Hardver elemek

A projekt jelenlegi verziója az alábbi főbb elemeket használja:

* Arduino Nano
* DS18B20 hőmérséklet érzékelők
* 16x2 I2C LCD kijelző
* Relé modul
* Nyomógombok
* Tápegység

---

# 🖥 Menü rendszer

A vezérlő egyszerű kétgombos kezelést használ.

Beállítható:

* maximális medence hőmérséklet
* szivattyú indítási differenciál
* szivattyú leállási differenciál

A rendszer külön statisztikai oldalakat is tartalmaz.

---

# 💾 Memória funkciók

A fontosabb beállítások és statisztikai adatok EEPROM memóriába kerülnek mentésre, így áramszünet után sem vesznek el.

---

# ⚠️ FONTOS BIZTONSÁGI FIGYELMEZTETÉS

A projekt hálózati feszültséggel működő berendezéseket kapcsolhat.

A 230V-os hálózati áram életveszélyes lehet!

A projekt építését és használatát kizárólag megfelelő elektromos ismeretekkel rendelkező személy végezze.

Különösen fontos:

* megfelelő érintésvédelem
* biztosítékozás
* galvanikus leválasztás
* megfelelő relék alkalmazása
* szakszerű szerelés

Amennyiben bizonytalan vagy a hálózati szerelésben, mindenképpen kérd villanyszerelő vagy szakember segítségét.

A projekt hobbi és oktatási célból készült.
A forráskód és a kapcsolási megoldások mindenki számára saját felelősségre használhatók fel.

---

# 📖 Projekt állapot

🛠 Fejlesztés alatt

A projekt jelenleg is folyamatos fejlesztés alatt áll.
A kód nem tekinthető véglegesnek vagy hibamentesnek.

Tervezett jövőbeli fejlesztések:

* további védelmi funkciók
* optimalizált menürendszer
* fejlettebb statisztikák
* ventilátor vagy többkörös vezérlés
* adatnaplózás
* WiFi kapcsolat

---

# 🤝 Szabad felhasználás

A projekt célja:

* tanulás
* kísérletezés
* közösségi fejlesztés
* tapasztalatmegosztás

A kód szabadon módosítható és továbbfejleszthető.

---

# 👨‍🔧 Fejlesztő

Lerch Krisztián

Arduino hobby project – 2026
