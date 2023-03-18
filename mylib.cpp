#include "mylib.h"

void pildymasKonsoleje(deque<Studentas> &studentai)
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

void generuotiAtsitiktinius(deque<Studentas> &studentai)
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


    Studentas temp;
    Pazymiai pazymiai;

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

void failoSkaitymas(deque<Studentas> &studentai, string filename)
{

    auto start = high_resolution_clock::now();

    ifstream in(filename);

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
    duration<double> duration = stop - start;

    cout << studentai.size() << " studentų" << endl;
    cout<< "Failas nuskaitytas per " << duration.count() << "s." << endl;
}
void rikiavimas(deque<Studentas> &studentai, string sortType)
{
    if (sortType == "name")
        sort(studentai.begin(), studentai.end(), compareName);
    if (sortType == "grade")
        sort(studentai.begin(), studentai.end(), compareGrade);
}
void spausdinimas(deque<Studentas> &studentai, string filename)
{
    ofstream out(filename);

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

    out.close();
    studentai.clear();
}

float vidurkioSkaiciavimas(Pazymiai &temp)
{
    float vidurkis = 0;
    if (temp.nd.size() != 0)
    {
        int sum = 0;
        for (int i = 0; i < temp.nd.size(); i++)
            sum = sum + temp.nd[i];
        vidurkis = 1.0 * sum / temp.nd.size();
    }
    return vidurkis * 0.4 + temp.egz * 0.6;
}

float medianosSkaiciavimas(Pazymiai &temp)
{
    float mediana = 0;

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

bool compareName(const Studentas &a, const Studentas &b)
{
    if (a.pavarde == b.pavarde)
        return a.vardas < b.vardas;
    else
        return a.pavarde < b.pavarde;
}

bool compareGrade(const Studentas &a, const Studentas &b)
{
    return a.vidurkis < b.vidurkis;
}

// void splittinimas(deque<Studentas> &studentai, deque<Studentas> &studPass, deque<Studentas> &studFail)
// {
//     auto start = high_resolution_clock::now();
//     for(auto &a : studentai)
//     {
//         if(a.vidurkis<5.0)
//                 studFail.push_back(a);
//         else
//             studPass.push_back(a);
//     }
//     auto stop = high_resolution_clock::now();
//     duration<double> duration = stop - start;
//     cout << "Duomenys padalinti per " << duration.count() << "s" << endl;
//     studentai.clear();
// }

deque<Studentas> splittinimas(deque<Studentas> &studentai)
{
    auto start = high_resolution_clock::now();
    
    int index;
    for(int i = 0; i < studentai.size(); i++)
    {
            if(studentai.at(i).vidurkis>=5)
            {
                index=i;
                break;
            }
    }
    deque<Studentas> temp (studentai.begin() + index, studentai.end());
        // copy(studentai.begin() + index, studentai.end(), std::back_inserter(studPass));
    studentai.resize(studentai.size()-temp.size());

    auto stop = high_resolution_clock::now();
    duration<double> duration = stop - start;
    cout << "Duomenys padalinti per " << duration.count() << "s" << endl;
    
    return temp;
}