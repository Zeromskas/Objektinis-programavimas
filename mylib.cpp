#include "mylib.h"

void pildymasKonsoleje(vector<Studentas> &studentai)
{
    char testi;
    Studentas temp;

    do
    {
        duomenuIvedimas(temp);
        studentai.push_back(temp);

        do
        {
            cout << "Ar norite pridėti dar vieną studentą? (t - taip, n - ne) " << endl;
            cin >> testi;
        } while (testi != 't' && testi != 'n');
    } while (testi == 't');
}

void duomenuIvedimas(Studentas &temp)
{
    cout << "Įveskite vardą ir pavardę: " << endl;
    cin >> temp.vardas >> temp.pavarde;

    cout << "Įveskite pažymius (jei daugiau pažymių nėra, įveskite bet kokią raidę):" << endl;

    Pazymiai pazymiai;

    int p = 0;

    while (cin >> p)
    {
        if (p >= 0 && p <= 10)
        {
            pazymiai.nd.push_back(p);
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
    cin >> pazymiai.egz;

    while (pazymiai.egz > 10 or pazymiai.egz < 0 or cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Egzamino pažymys turi būti dešimtbalėje sistemoje" << endl;
        cout << "Iveskite egzamino pažymį: " << endl;
        cin >> pazymiai.egz;
    }

    temp.vidurkis = vidurkioSkaiciavimas(pazymiai);
    temp.mediana = medianosSkaiciavimas(pazymiai);
    pazymiai.nd.clear();

    cout << "Duomenys įrašyti" << endl;
}

void generuotiAtsitiktinius(vector<Studentas> &studentai)
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

    Studentas temp;
    Pazymiai pazymiai;
    pazymiai.nd.reserve(pazymiuKiekis);

    for (int i = 0; i < studentuKiekis; i++)
    {
        temp.vardas = "vardas" + to_string(i);
        temp.pavarde = "pavarde" + to_string(i);
        for (int j = 0; j < pazymiuKiekis; j++)
            pazymiai.nd.push_back(dist(mt));
        pazymiai.egz = dist(mt);
        temp.vidurkis = vidurkioSkaiciavimas(pazymiai);
        temp.mediana = medianosSkaiciavimas(pazymiai);
        pazymiai.nd.clear();
        studentai.push_back(temp);
    }
    cout << "Generavimas baigtas" << endl;
}

void failoSkaitymas(vector<Studentas> &studentai)
{

    system("ls");
    string failas;
    cout << "Įveskite pažymių failo pavadinimą:" << endl;
    cin >> failas;

    auto start = high_resolution_clock::now();

    ifstream in(failas);

    if (!in.is_open())
    {
        throw runtime_error("Nepavyko atidaryti failo!");
    }

    cout << "Duomenys nuskaitomi..." << endl;

    string line;
    getline(in, line);
    int pazymiuKiekis = count(line.begin(), line.end(), 'N');

    Studentas temp;
    Pazymiai pazymiai;
    pazymiai.nd.reserve(pazymiuKiekis);
    int p;

    while (in >> temp.vardas)
    {
        in >> temp.pavarde;
        for (int i = 0; i < pazymiuKiekis; i++)
        {
            in >> p;
            pazymiai.nd.push_back(p);
        }
        in >> pazymiai.egz;
        temp.vidurkis = vidurkioSkaiciavimas(pazymiai);
        temp.mediana = medianosSkaiciavimas(pazymiai);
        pazymiai.nd.clear();
        studentai.push_back(temp);
    }

    // while (std::getline(in, line))
    // {
    //     std::stringstream ss(line);
    //     ss >> temp.vardas >> temp.pavarde;
    //     for (int i = 0; i < pazymiuKiekis; i++)
    //     {
    //         ss>>p;
    //         pazymiai.nd.push_back(p);
    //     }
    //     ss >> pazymiai.egz;
    //     temp.vidurkis = vidurkioSkaiciavimas(pazymiai);
    //     temp.mediana = medianosSkaiciavimas(pazymiai);
    //     pazymiai.nd.clear();
    //     studentai.push_back(temp);
    // }

    in.close();

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<seconds>(stop - start);
    cout << "Failas nuskaitytas per " << duration.count() << "s. Rasta " << studentai.size() << " studentų" << endl;
}

void spausdinimas(vector<Studentas> &studentai)
{
    cout << "Prašome palaukti. Sąrašas rikiuojamas..." << endl;
    sort(studentai.begin(), studentai.end(), rikiavimoLyginimas);

    cout << "Duomenų išvedimas vykdomas..." << endl;
    auto start = high_resolution_clock::now();
    ofstream out("rez.txt");
    // ostringstream oss;

    // oss << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė" << setw(18) << left << "Galutinis (Vid.)" << setw(18) << left << "Galutinis (Med.)" << endl
    //     << "----------------------------------------------------------------" << endl;
    // out << oss.str();
    // oss.str("");

    // for (int i = 0; i < studentai.size(); i++)
    // {
    //     oss << setw(15) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(18) << left << setprecision(3) << studentai[i].vidurkis << setw(18) << left << setprecision(3) << studentai[i].mediana << endl;
    //     if ((i + 1) / 5 == 0 || i + 1 == studentai.size())
    //     {
    //         out << oss.str();
    //         oss.str("");
    //         oss.reset();
    //     }
    // }

    unique_ptr<ostringstream> oss(new ostringstream());

    (*oss) << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė" << setw(18) << left << "Galutinis (Vid.)" << setw(18) << left << "Galutinis (Med.)" << endl
           << "----------------------------------------------------------------" << endl;
    out << oss->str();
    oss->str("");

    for (int i = 0; i < studentai.size(); i++)
    {
        (*oss) << setw(15) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(18) << left << setprecision(3) << studentai[i].vidurkis << setw(18) << left << setprecision(3) << studentai[i].mediana << endl;
        if ((i + 1) % 10 == 0 || i + 1 == studentai.size())
        {
            out << oss->str();
            oss->str("");
        }
    }

    //
    out.close();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Duomenys išvesti per " << duration.count() << "s" << endl;
}

double vidurkioSkaiciavimas(Pazymiai &temp)
{
    double vidurkis = 0;
    if (temp.nd.size() != 0)
    {
        int sum = 0;
        for (int i = 0; i < temp.nd.size(); i++)
            sum = sum + temp.nd[i];
        vidurkis = 1.0 * sum / temp.nd.size();
    }
    return vidurkis * 0.4 + temp.egz * 0.6;
}

double medianosSkaiciavimas(Pazymiai &temp)
{
    double mediana = 0;

    if (temp.nd.size() != 0)
    {
        sort(temp.nd.begin(), temp.nd.end());

        if (temp.nd.size() % 2 == 1)
            mediana = temp.nd[(temp.nd.size()) / 2];
        else if (temp.nd.size() % 2 == 0)
            mediana = (temp.nd[(temp.nd.size()) / 2 - 1] + temp.nd[(temp.nd.size()) / 2]) * 1.0 / 2.0;
    }

    return 0.4 * mediana + 0.6 * temp.egz;
}

bool rikiavimoLyginimas(const Studentas &a, const Studentas &b)
{
    if (a.pavarde == b.pavarde)
        return a.vardas < b.vardas;
    else
        return a.pavarde < b.pavarde;
}