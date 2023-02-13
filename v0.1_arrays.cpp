#include "mylib.h"

struct studentas
{
    string vardas, pavarde;
    int *pazymiai = nullptr;
    int pazymiu_kiekis = 0;
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
    studentas *grupe;
    int n = 1;
    grupe = new studentas[n];
    pildymas(grupe[n - 1]);
    char testi = 'e';
    while (testi != 't' && testi != 'n')
    {
        cout << "Ar norite pridėti dar vieną studentą? (t - taip, n - ne) " << endl;
        cin >> testi;
    }

    while (testi == 't')
    {
        studentas *temp = new studentas[n];
        copy(grupe, grupe + n, temp);
        delete[] grupe;
        grupe = new studentas[n + 1];
        copy(temp, temp + n, grupe);
        delete[] temp;
        n++;
        pildymas(grupe[n - 1]);
        testi = 'e';
        while (testi != 't' && testi != 'n')
        {
            cout << "Ar norite pridėti dar vieną studentą? (t - taip, n - ne) " << endl;
            cin >> testi;
        }
    }

    int t = 4;

    while (t != 0)
    {
        while ((t != 0 && t != 1 && t != 2 && t != 3) || cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Kokius duomenis norite gauti? (Galutinis balas pagal vidurkį - 1; galutinis balas pagal medianą - 2; studentų pažymius - 3; ištrinti duomenis ir išeiti - 0" << endl;
            cin >> t;
        }

        if (t == 0)
            break;

        else if (t == 1)
        {
            cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė"
                 << "Galutinis (vid)" << endl;
            for (int i = 0; i < n; i++)
                vidurkio_spausdinimas(grupe[i]);
        }
        else if (t == 3)
        {
            cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė"
                 << "Pažymiai" << endl;
            for (int i = 0; i < n; i++)
                input_spausdinimas(grupe[i]);
        }
        else if (t == 2)
        {
            cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė"
                 << "Galutinis (med)" << endl;
            for (int i = 0; i < n; i++)
                medianos_spausdinimas(grupe[i]);
        }

        else
            cout << "Tokios opcijos nėra" << endl;

        t = 4;
    }

    delete[] grupe->pazymiai;
    delete[] grupe;
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
        int *pazymiai = nullptr;
        int a = 0;
        int p = 0;

        temp.pazymiai = new int[0];

        while (cin >> p)
        {
            if (p >= 0 && p <= 10)
            {
                pazymiai = new int[a];
                copy(temp.pazymiai, temp.pazymiai + a, pazymiai);
                delete[] temp.pazymiai;
                temp.pazymiai = new int[a + 1];
                copy(pazymiai, pazymiai + a, temp.pazymiai);
                a++;
                temp.pazymiai[a - 1] = p;
                delete[] pazymiai;
            }
            else
            {
                cout << "Pažymys turi būti tarp 0 ir 10. Bandykite dar kartą: " << endl;
            }
        }

        temp.pazymiu_kiekis = a;

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
    {
        generuotiAtsitiktinius(temp);
    }
    cout << "Duomenys įrašyti" << endl;
}

void generuotiAtsitiktinius(studentas &temp)
{

    int kiekis = (double)rand() / RAND_MAX * 20;
    int p;
    temp.pazymiai = new int[kiekis];
    for (int i = 0; i < kiekis; i++)
    {
        p = (double)rand() / RAND_MAX * 10;
        temp.pazymiai[i] = p;
    }
    temp.pazymiu_kiekis = kiekis;
    temp.egz = (double)rand() / RAND_MAX * 10;
}

void input_spausdinimas(studentas &temp)
{
    cout << setw(15) << temp.vardas << setw(20) << temp.pavarde;
    if (temp.pazymiu_kiekis == 0)
        cout << "Pažymių nėra";
    else
        for (int i = 0; i < temp.pazymiu_kiekis; i++)
            cout << setw(3) << temp.pazymiai[i];

    cout << "  Egzaminas:" << setw(5) << temp.egz << endl;
}

void vidurkio_spausdinimas(studentas &temp)
{
    double vidurkis = 0;
    if (temp.pazymiu_kiekis != 0)
    {
        int sum = 0;
        for (int i = 0; i < temp.pazymiu_kiekis; i++)
            sum = sum + temp.pazymiai[i];
        vidurkis = 1.0 * sum / temp.pazymiu_kiekis;
    }
    double galutinis = vidurkis * 0.4 + temp.egz * 0.6;
    cout << setw(15) << left << temp.vardas << setw(20) << left << temp.pavarde;
    cout << setprecision(3) << galutinis << endl;
}
void medianos_spausdinimas(studentas &temp)
{
    int *pazymiai;
    pazymiai = new int[temp.pazymiu_kiekis + 1];
    copy(temp.pazymiai, temp.pazymiai + temp.pazymiu_kiekis, pazymiai);
    pazymiai[temp.pazymiu_kiekis] = temp.egz;
    sort(pazymiai, pazymiai + temp.pazymiu_kiekis + 1);
    cout << setw(15) << left << temp.vardas << setw(20) << left << temp.pavarde;
    if ((temp.pazymiu_kiekis + 1) % 2 == 1)
    {
        cout << pazymiai[(temp.pazymiu_kiekis + 1) / 2];
    }
    else if ((temp.pazymiu_kiekis + 1) % 2 == 0)
    {
        cout << (pazymiai[(temp.pazymiu_kiekis) / 2] + pazymiai[(temp.pazymiu_kiekis) / 2 + 1]) * 1.0 / 2.0;
    }
    cout << endl;
    delete[] pazymiai;
}
