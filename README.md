# v0.5
Perdaryta vietoj vector naudojant list

|                  | **1k**    | **10k**  | **100k** | **1M** | **10M** |
|------------------|-----------|----------|----------|--------|---------|
| **Nuskaitymas**  | _0.01089_ | _0.0470_ | _0.454_  | _4.52_ | _44.3_  |
| **Rikiavimas 1** | _0.00012_ | _0.0010_ | _0.019_  | _0.47_ | _9.2_   |
| **Dalinimas**    | _0.00001_ | _0.0001_ | _0.004_  | _0.09_ | _1.3_   |
| **Rikiavimas 2** | _0.00028_ | _0.0029_ | _0.051_  | _0.95_ | _16.9_  |
| **Išvedimas**    | _0.00214_ | _0.0090_ | _0.117_  | _1.03_ | _9.2_   |
| **Viso**         | _0.01354_ | _0.0602_ | _0.647_  | _7.06_ | _81.0_  |


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

|                  | **1k**    | **10k**  | **100k** | **1M** | **10M** |
|------------------|-----------|----------|----------|--------|---------|
| **Nuskaitymas**  | _0.00919_ | _0.0440_ | _0.354_  | _3.37_ | _34.7_  |
| **Rikiavimas 1** | _0.00015_ | _0.0007_ | _0.007_  | _0.07_ | _0.8_   |
| **Dalinimas**    | _0.00003_ | _0.0002_ | _0.003_  | _0.03_ | _0.4_   |
| **Rikiavimas 2** | _0.00033_ | _0.0025_ | _0.033_  | _0.39_ | _4.6_   |
| **Išvedimas**    | _0.00231_ | _0.0100_ | _0.106_  | _0.79_ | _8.3_   |
| **Viso**         | _0.01219_ | _0.0579_ | _0.506_  | _4.68_ | _49.4_  |
|                  |           |          |          |        |         |
| **Generavimas**  | _0.00599_ | _0.0383_ | _0.381_  | _3.72_ | _35.2_  |

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
