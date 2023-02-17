#include "mylib.h"

struct studentas
{
    string vardas, pavarde;
    vector<int> pazymiai;
    int egz = 0;
};

void pildymas(studentas &temp);
void input_spausdinimas(studentas &temp);
void vidurkio_spausdinimas(studentas &temp);
void medianos_spausdinimas(studentas &temp);
void generuotiAtsitiktinius(studentas &temp);

int main()
{
    srand(time(NULL));
    vector<studentas> studentai;
    char testi = 't';
    while (testi == 't')
    {
        studentas temp;

        pildymas(temp);
        studentai.push_back(temp);
        testi = 'a';
        while (testi != 't' && testi != 'n')
        {
            cout << "Ar norite pridėti dar vieną studentą? (t - taip, n - ne) " << endl;
            cin >> testi;
        }
    }

    int isvedimoPasirinkimas = 4;

    while (isvedimoPasirinkimas != 0)
    {
        while ((isvedimoPasirinkimas != 0 && isvedimoPasirinkimas != 1 && isvedimoPasirinkimas != 2 && isvedimoPasirinkimas != 3) || cin.fail())
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Kokius duomenis norite gauti? (Galutinis balas pagal vidurkį - 1; galutinis balas pagal medianą - 2; studentų pažymius - 3; ištrinti duomenis ir išeiti - 0" << endl;
            cin >> isvedimoPasirinkimas;
        }

        if (isvedimoPasirinkimas == 0)
            break;

        else if (isvedimoPasirinkimas == 1)
        {
            cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė"
                 << "Galutinis (vid)" << endl;
            for (int i = 0; i < studentai.size(); i++)
                vidurkio_spausdinimas(studentai[i]);
        }
        else if (isvedimoPasirinkimas == 3)
        {
            cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė"
                 << "Pažymiai" << endl;
            for (int i = 0; i < studentai.size(); i++)
                input_spausdinimas(studentai[i]);
        }
        else if (isvedimoPasirinkimas == 2)
        {
            cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė"
                 << "Galutinis (med)" << endl;
            for (int i = 0; i < studentai.size(); i++)
                medianos_spausdinimas(studentai[i]);
        }

        else
            cout << "Tokios opcijos nėra" << endl;

        isvedimoPasirinkimas = 4;
    }

    return 0;
}

void pildymas(studentas &temp)
{
    cout << "Įveskite vardą ir pavardę: " << endl;
    cin >> temp.vardas >> temp.pavarde;
    int atsitiktinai = 2;
    while (atsitiktinai != 0 && atsitiktinai != 1)
    {
        cout << "Ar norite pažymius įvesti patys (0) ar, kad jie būtų sugeneruoti atsitiktinai (1)?" << endl;
        cin >> atsitiktinai;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if (atsitiktinai == 0)
    {
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
    }
    else if (atsitiktinai == 1)
        generuotiAtsitiktinius(temp);
    cout << "Duomenys įrašyti" << endl;
}
void generuotiAtsitiktinius(studentas &temp)
{

    int kiekis = (double)rand() / RAND_MAX * 20;
    int p;
    for (int i = 0; i < kiekis; i++)
    {
        p = (double)rand() / RAND_MAX * 10;
        temp.pazymiai.push_back(p);
    }
    temp.egz = (double)rand() / RAND_MAX * 10;
}

void input_spausdinimas(studentas &temp)
{
    cout << setw(15) << temp.vardas << setw(20) << temp.pavarde;
    for (int i = 0; i < temp.pazymiai.size(); i++)
        cout << setw(3) << temp.pazymiai[i];
    if (temp.pazymiai.size() == 0)
        cout << "Pažymių nėra";

    cout << "  Egzaminas:" << setw(5) << temp.egz << endl;
}
void vidurkio_spausdinimas(studentas &temp)
{
    double vidurkis = 0;
    if (temp.pazymiai.size() != 0)
    {
        int sum = 0;
        for (int i = 0; i < temp.pazymiai.size(); i++)
            sum = sum + temp.pazymiai[i];
        vidurkis = 1.0 * sum / temp.pazymiai.size();
    }
    double galutinis = vidurkis * 0.4 + temp.egz * 0.6;
    cout << setw(15) << left << temp.vardas << setw(20) << left << temp.pavarde;
    cout << setprecision(3) << galutinis << endl;
}
void medianos_spausdinimas(studentas &temp)
{

    sort(temp.pazymiai.begin(), temp.pazymiai.end());
    cout << setw(15) << left << temp.vardas << setw(20) << left << temp.pavarde;
    double mediana;
    if (temp.pazymiai.size() % 2 == 1)
    {
        mediana = temp.pazymiai[(temp.pazymiai.size()) / 2];
    }
    else if (temp.pazymiai.size() % 2 == 0)
    {
        mediana = (temp.pazymiai[(temp.pazymiai.size()) / 2 - 1] + temp.pazymiai[(temp.pazymiai.size()) / 2]) * 1.0 / 2.0;
    }

    cout << setprecision(3) << 0.4 * mediana + 0.6 * temp.egz << endl;
}
