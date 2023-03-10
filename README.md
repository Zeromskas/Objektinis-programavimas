# v0.4

1. Pridėta studentų pažymių failus generuojanti programa.
2. Pridėtas bendras ir atskirų programos dalių vykdymo laiko skaičiavimas.
3. Patobulinta studentų sarašo rikiavimo funkcija (pridėta galimybė pasirinkti rikiuoti pagal vardus arba pagal galutinius įvertinimus).
4. Pridėta studento sarašo dalinimo į dvi dalis (Pass ir Fail) funkcija.
6. Rezultatas gaunamas kaip 2 atskiri failai ("studPass.txt", "studFail.txt").
7. Optimizuotas RAM naudojimas.

Programos veikimo principas: 
1. Nuskaitomi studentų duomenys iš pasirinkto failo
2. Studentų sąrašas surikiuojamas pagal galutinius pažymius didėjimo tvarka
3. Sąrašas padalinamas į dvi dalis (<5 ir >=5)
4. Abi dalys surikiuojamos pagal vardą ir pavardę
5. Abi dalys išvedamos į atskirus failus

Atliktas programos [greitaveikos testavimas](greitaveikosAtaskaita.txt)

# v0.3

1. Struktūros perkeltos į header failą.
2. Pridėta galimybė pasirinkti duomenų failą iš aplankalo.
3. Naudojamas try-catch atidarinėjant failą.
4. Optimizuotas failo išvedimas, naudojant atskirą stream ir į rez.txt kreipiantis ir rašant duomenis kas dešimtą studentą.
5. Funkcijos perkeltos į atskirą failą "mylib.cpp"
6. Sukurtas MAKEFILE, leidžiantis paleisti programą į konsolę parašius "make"

# v0.2

1. Pridėta galimybė studentų pažymius skaityti iš failo "studentai.txt"
2. Patobulintas atsitiktinių duomenų generavimas naudojant "mt19937"
3. Patobulintas klaidingų įvedimų apdorojimas
4. Optimizuotas RAM naudojimas, apskaičiavus galutinius pažymius ištrinant nebereikalingus pažymius.
5. Duomenys išvedami į failą "rez.txt", bereikalingai neapkraunant konsolės

# v0.1
1.  Programa nuskaito vartotojo įvedamus duomenis: studento vardą ir pavardę.
2.  Leidžia įvesti pažymius ranka, arba generuoti atsitiktinius.
3.  Ranka vedamų pažymių kiekis neribojamas, atsitiktinai generuojant pazymius sugeneruojami 0-20 pažymių. Pažymiai privalo būti dešimtbalėje sistemoje (_0-10_)
4.  Vartotojas, įvedęs visus pažymius, įveda bet kokią raidę ir taip yra sustabdomas pažymių įvedimas.
5.  Duodama įvesti egzamino pažymį (_0-10_) (_privaloma_), prieš tai pasirinkus generavimą atsitiktinai, egzamino pažymys sugeneruojamas atsitiktinai.
6.  Pabaigus pildyti vieno studento pažymius, duodamas pasirinkimas pildyti dar vieno studento duomenis (t) arba baigti pildymą (n) (studentų kiekis neribojamas)
7.  Vartotojui duodamas pasirinkimas gauti 3 rūšių duomenis (_Galutinis balas pagal vidurkį - 1; galutinis balas pagal medianą - 2; studentų pažymius - 3_) arba ištrinti duomenis ir išeiti - _0_. Pasirinkti išvedimą leidžiama neribotą kiekį kartų.

Dvi versijos: 1. naudojant C masyvus 2. naudojant vektorius
