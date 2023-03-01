#include "mylib.h"

int main()
{
    vector<Studentas> studentai;

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
        {
            while(true)
            {
                try
                {
                    failoSkaitymas(studentai);
                    break;
                }
                catch (const exception &e)
                {
                    cerr << "Klaida: " << e.what() << endl;
                }
            }
        }
    else if (ivedimoTipas == 1)
        pildymasKonsoleje(studentai);
    else if (ivedimoTipas == 2)
        generuotiAtsitiktinius(studentai);

    if(studentai.size()>0)
        spausdinimas(studentai);

    studentai.clear();

    return 0;
}


