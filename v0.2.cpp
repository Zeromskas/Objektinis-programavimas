#include "mylib.h"

struct studentas
{
    string vardas, pavarde;
    vector<int> pazymiai;
    int egz = 0;
    double vidurkis = 0;
    double mediana = 0;
};

void vidurkioSkaiciavimas(studentas &temp);
void medianosSkaiciavimas(studentas &temp);
void generuotiAtsitiktinius(vector<studentas> &studentai);
void pildymasKonsoleje(vector<studentas> &studentai);
void spausdinimas(vector<studentas> &studentai);
void failoSkaitymas(vector<studentas> &studentai);
void duomenuIvedimas(studentas &temp);
bool rikiavimoLyginimas(const studentas &a, const studentas &b);

int main()
{
    vector<studentas> studentai;

    int ivedimoTipas = 3;
    while (ivedimoTipas != 0 && ivedimoTipas != 1 && ivedimoTipas != 2)
    {
        cout << "Ar norite duomenis skaityti iš failo (0), įvesti patys (1) ar, kad jie būtų sugeneruoti atsitiktinai (2)?" << endl;
        cin >> ivedimoTipas;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ivedimoTipas = 3;
        }
    }
    if (ivedimoTipas == 0)
        failoSkaitymas(studentai);
    else if (ivedimoTipas == 1)
        pildymasKonsoleje(studentai);
    else if (ivedimoTipas == 2)
        generuotiAtsitiktinius(studentai);

    spausdinimas(studentai);

    for (int i = 0; i < studentai.size(); i++)
        studentai[i].pazymiai.clear();
    studentai.clear();

    return 0;
}

void pildymasKonsoleje(vector<studentas> &studentai)
{
    char testi;
    studentas temp;

    do
    {
        duomenuIvedimas(temp);
        studentai.push_back(temp);
        temp.pazymiai.clear();

        do
        {
            cout << "Ar norite pridėti dar vieną studentą? (t - taip, n - ne) " << endl;
            cin >> testi;
        } while (testi != 't' && testi != 'n');
    } while (testi == 't');
}
void failoSkaitymas(vector<studentas> &studentai)
{
    auto start = high_resolution_clock::now();

    ifstream in("pazymiai.txt");
    if (!in.is_open())
    {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }

    string header;
    getline(in, header);
    int pazymiuKiekis = count(header.begin(), header.end(), 'N');

    studentas temp;
    temp.pazymiai.reserve(pazymiuKiekis);
    int p;
    cout << "Duomenys nuskaitomi..." << endl;
    while (in >> temp.vardas)
    {
        in >> temp.pavarde;
        for (int i = 0; i < pazymiuKiekis; i++)
        {
            in >> p;
            temp.pazymiai.push_back(p);
        }
        in >> temp.egz;
        vidurkioSkaiciavimas(temp);
        medianosSkaiciavimas(temp);
        temp.pazymiai.clear();
        studentai.push_back(temp);
        temp.pazymiai.clear();
    }
    in.close();

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Failas nuskaitytas per " << duration.count() << "ms" << endl;
}
void duomenuIvedimas(studentas &temp)
{
    cout << "Įveskite vardą ir pavardę: " << endl;
    cin >> temp.vardas >> temp.pavarde;

    cout << "Įveskite pažymius (jei daugiau pažymių nėra, įveskite bet kokią raidę):" << endl;

    int p = 0;

    while (cin >> p)
    {
        if (p >= 0 && p <= 10)
        {
            temp.pazymiai.push_back(p);
        }
        else
        {
            cout << "Pažymys turi būti tarp 0 ir 10. Bandykite dar kartą: " << endl;
        }
    }

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "įveskite egzamino pažymį: " << endl;
    cin >> temp.egz;

    while (temp.egz > 10 or temp.egz < 0 or cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Egzamino pažymys turi būti dešimtbalėje sistemoje" << endl;
        cout << "Iveskite egzamino pažymį: " << endl;
        cin >> temp.egz;
    }

    vidurkioSkaiciavimas(temp);
    medianosSkaiciavimas(temp);
    temp.pazymiai.clear();

    cout << "Duomenys įrašyti" << endl;
}
void generuotiAtsitiktinius(vector<studentas> &studentai)
{

    int studentuKiekis = 0;
    int pazymiuKiekis = 0;
    while (true)
    {
        cout << "Kiek studentų norite generuoti?" << endl;
        cin >> studentuKiekis;
        if (cin.fail() || studentuKiekis <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Studentų kiekis turi būti sveikas skaičius, didesnis už 0." << endl;
        }
        else
            break;
    }

    while (true)
    {
        cout << "Kiek pažymių norite generuoti kiekvienam studentui?" << endl;
        cin >> pazymiuKiekis;
        if (cin.fail() || pazymiuKiekis < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pažymių kiekis turi būti teigiamas sveikasis skaičius." << endl;
        }
        else
            break;
    }

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 10);

    cout << "Duomenys generuojami..." << endl;

    studentai.reserve(studentuKiekis);

    studentas temp;
    temp.pazymiai.reserve(pazymiuKiekis);

    for (int i = 0; i < studentuKiekis; i++)
    {
        temp.vardas = "vardas" + to_string(i);
        temp.pavarde = "pavarde" + to_string(i);
        for (int j = 0; j < pazymiuKiekis; j++)
            temp.pazymiai.push_back(dist(mt));
        temp.egz = dist(mt);
        vidurkioSkaiciavimas(temp);
        medianosSkaiciavimas(temp);
        temp.pazymiai.clear();
        studentai.push_back(temp);
        temp.pazymiai.clear();
    }
    cout << "Generavimas baigtas" << endl;
}
void spausdinimas(vector<studentas> &studentai)
{
    // cout << "Prašome palaukti. Sąrašas rikiuojamas..." << endl;
    // sort(studentai.begin(), studentai.end(), rikiavimoLyginimas);

    cout << "Duomenų išvedimas vykdomas..." << endl;
    auto start = high_resolution_clock::now();
    ofstream out("rez.txt");
    out << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė" << setw(18) << left << "Galutinis (Vid.)" << setw(18) << left << "Galutinis (Med.)" << endl
        << "----------------------------------------------------------------" << endl;
    for (int i = 0; i < studentai.size(); i++)
        out << setw(15) << studentai[i].vardas << setw(20) << studentai[i].pavarde << setw(18) << left << setprecision(3) << studentai[i].vidurkis << setw(18) << left << setprecision(3) << studentai[i].mediana << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Duomenys išvesti per " << duration.count() << "ms" << endl;
}
void vidurkioSkaiciavimas(studentas &temp)
{
    double vidurkis = 0;
    if (temp.pazymiai.size() != 0)
    {
        int sum = 0;
        for (int i = 0; i < temp.pazymiai.size(); i++)
            sum = sum + temp.pazymiai[i];
        vidurkis = 1.0 * sum / temp.pazymiai.size();
    }
    temp.vidurkis = vidurkis * 0.4 + temp.egz * 0.6;
}
void medianosSkaiciavimas(studentas &temp)
{
    double mediana = 0;

    if (temp.pazymiai.size() != 0)
    {
        vector<int> pazymiuKopija;
        pazymiuKopija = temp.pazymiai;
        sort(pazymiuKopija.begin(), pazymiuKopija.end());

        if (pazymiuKopija.size() % 2 == 1)
            mediana = pazymiuKopija[(pazymiuKopija.size()) / 2];
        else if (temp.pazymiai.size() % 2 == 0)
            mediana = (pazymiuKopija[(pazymiuKopija.size()) / 2 - 1] + pazymiuKopija[(pazymiuKopija.size()) / 2]) * 1.0 / 2.0;
    }

    temp.mediana = 0.4 * mediana + 0.6 * temp.egz;
}
bool rikiavimoLyginimas(const studentas &a, const studentas &b)
{
    if (a.pavarde == b.pavarde)
        return a.vardas < b.vardas;
    else
        return a.pavarde < b.pavarde;
}