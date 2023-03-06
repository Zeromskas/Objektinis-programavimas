#include "mylib.h"

int main()
{

    vector<Studentas> studentai;
    std::chrono::high_resolution_clock::time_point start_time, end_time;

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

        while (true)
        {
            try
            {
                system("ls *.txt");
                string filename;
                cout << "Įveskite pažymių failo pavadinimą:" << endl;
                cin >> filename;
                start_time = high_resolution_clock::now();
                failoSkaitymas(studentai, filename);
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

    if (studentai.empty())
        return 0;

    rikiavimas(studentai, "grade");
    vector<Studentas> studPass;
    // vector<Studentas> studFail;
    studPass.reserve(studentai.size() / 2);
    // studFail.reserve(studentai.size() / 2);
    //splittinimas(studentai, studPass, studFail);
    splittinimas(studentai, studPass);
    studPass.shrink_to_fit();
    studentai.shrink_to_fit();
    rikiavimas(studentai, "name");
    rikiavimas(studPass, "name");

    cout << "Pass ";
    spausdinimas(studPass, "studPass.txt");
    studPass.clear();
    cout << "Fail ";
    spausdinimas(studentai, "studFail.txt");

    studentai.clear();
    

    end_time = high_resolution_clock::now();

    duration<double> duration = end_time - start_time;

    cout << "Failo apdorojimas užtruko " << duration.count() << "s." << endl;

    return 0;
}
