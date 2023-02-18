#include "mylib.h"

struct studentas
{
    string vardas, pavarde;
    vector<int> pazymiai;
    int egz = 0;
    double vidurkis=0;
    double mediana=0;
};

void inputSpausdinimas(studentas &temp);
void vidurkioSkaiciavimas(studentas &temp);
void medianosSkaiciavimas(studentas &temp);
void generuotiAtsitiktinius(vector<studentas> &studentai);
void pildymasKonsoleje(vector<studentas> &studentai);
void spausdinimas(vector<studentas> &studentai);
void failoSkaitymas(vector<studentas> &studentai);
void duomenuIvedimas(studentas &temp);

int main()
{
    vector<studentas> studentai;
    
    int ivedimoTipas=3;
    while (ivedimoTipas != 0 && ivedimoTipas != 1 && ivedimoTipas!=2)
    {
        cout << "Ar norite duomenis skaityti iš failo (0), įvesti patys (1) ar, kad jie būtų sugeneruoti atsitiktinai (2)?" << endl;
        cin >> ivedimoTipas;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    if (ivedimoTipas==0)
        failoSkaitymas(studentai);
    else if (ivedimoTipas == 1)
        pildymasKonsoleje(studentai);
    else if (ivedimoTipas == 2)
        generuotiAtsitiktinius(studentai);
    spausdinimas(studentai);
    return 0;
}

void pildymasKonsoleje(vector<studentas> &studentai)
{
    srand(time(NULL));
    char testi = 't';
    while (testi == 't')
    {
        studentas temp;
        duomenuIvedimas(temp);
        studentai.push_back(temp);
        testi = 'a';
        while (testi != 't' && testi != 'n')
        {
            cout << "Ar norite pridėti dar vieną studentą? (t - taip, n - ne) " << endl;
            cin >> testi;
        }
    }
}

void failoSkaitymas(vector<studentas> &studentai) 
{
    ifstream in("pazymiai.txt");
    
    string header;
    getline(in, header);
    int numGrades = count(header.begin(), header.end(), 'N');

    studentas temp;
    int p;
    while (in >> temp.vardas)
    {
        in>> temp.pavarde;
        for(int i=0; i<numGrades; i++)
        {
            in>>p;
            temp.pazymiai.push_back(p);
        }
        in>>temp.egz;
        vidurkioSkaiciavimas(temp);
        medianosSkaiciavimas(temp);
        studentai.push_back(temp);
        temp.pazymiai.clear();
    }
    if (in.fail())
    {
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout<<"Failas nuskaitytas"<<endl;
    
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

    cout << "Duomenys įrašyti" << endl;
}
void generuotiAtsitiktinius(vector<studentas> &studentai)
{
    int studentuKiekis=0;
    int pazymiuKiekis=0;
    cout<<"Kiek studentų norite generuoti?"<<endl;
    cin>>studentuKiekis;
    cout<<"Kiek pažymių norite generuoti kiekvienam studentui?"<<endl;
    cin>>pazymiuKiekis;

    for (int i = 0; i < studentuKiekis; i++)
    {
        
        studentas temp;
        temp.vardas="vardas"+to_string(i);
        temp.pavarde = "pavarde" + to_string(i);
        for (int j = 0; j < pazymiuKiekis; j++)
            temp.pazymiai.push_back(rand() % 11);
        temp.egz = (double)rand() / RAND_MAX * 10;
        vidurkioSkaiciavimas(temp);
        medianosSkaiciavimas(temp);
        studentai.push_back(temp);
        
    }
}
void spausdinimas(vector<studentas> &studentai)
{
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
                cout << setw(15) << studentai[i].vardas << setw(20) << studentai[i].pavarde<<setprecision(3)<<studentai[i].vidurkis<<endl;
        }
        else if (isvedimoPasirinkimas == 2)
        {
            cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė"
                 << "Galutinis (med)" << endl;
            for (int i = 0; i < studentai.size(); i++)
                cout << setw(15) << studentai[i].vardas << setw(20) << studentai[i].pavarde << setprecision(3) << studentai[i].mediana << endl;
        }
        else if (isvedimoPasirinkimas == 3)
        {
            cout << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė"
                 << "Pažymiai" << endl;
            for (int i = 0; i < studentai.size(); i++)
                inputSpausdinimas(studentai[i]);
        }
        
        else
            cout << "Tokios opcijos nėra" << endl;

        isvedimoPasirinkimas = 4;
    }
}
void inputSpausdinimas(studentas &temp)
{
    cout << setw(15) << temp.vardas << setw(20) << temp.pavarde;
    for (int i = 0; i < temp.pazymiai.size(); i++)
        cout << setw(3) << temp.pazymiai[i];
    if (temp.pazymiai.size() == 0)
        cout << "Pažymių nėra";

    cout << "  Egzaminas:" << setw(5) << temp.egz << endl;
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
    vector<int> pazymiuKopija;
    pazymiuKopija=temp.pazymiai;
    sort(pazymiuKopija.begin(), pazymiuKopija.end());
    double mediana;
    if (pazymiuKopija.size() % 2 == 1)
    {
        mediana = pazymiuKopija[(pazymiuKopija.size()) / 2];
    }
    else if (temp.pazymiai.size() % 2 == 0)
    {
        mediana = (pazymiuKopija[(pazymiuKopija.size()) / 2 - 1] + pazymiuKopija[(pazymiuKopija.size()) / 2]) * 1.0 / 2.0;
    }

    temp.mediana = 0.4 * mediana + 0.6 * temp.egz;
}
