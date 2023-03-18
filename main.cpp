#include "mylib.h"

int main()
{
    deque<Studentas> studentai;
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
    {
        pildymasKonsoleje(studentai);
        start_time = high_resolution_clock::now();
    }
    else if (ivedimoTipas == 2)
        generuotiAtsitiktinius(studentai);

    if (studentai.empty())
        return 0;

    auto start_sort1 = high_resolution_clock::now();
    rikiavimas(studentai, "grade");
    auto stop_sort1 = high_resolution_clock::now();
    duration<double> duration_sort1 = stop_sort1 - start_sort1;
    cout << "Sąrašas surikiuotas per " << duration_sort1.count() << "s" << endl;
    
    deque<Studentas> studPass=splittinimas(studentai);
    studPass.shrink_to_fit();
    studentai.shrink_to_fit();

    auto start_sort2 = high_resolution_clock::now();
    rikiavimas(studentai, "name");
    rikiavimas(studPass, "name");
    auto stop_sort2 = high_resolution_clock::now();
    duration<double> duration_sort2 = stop_sort2 - start_sort2;
    cout << "Sąrašas surikiuotas per " << duration_sort2.count() << "s" << endl;

    auto start_print = high_resolution_clock::now();
    spausdinimas(studPass, "studPass.txt");
    studPass.clear();
    spausdinimas(studentai, "studFail.txt");
    studentai.clear();
    auto stop_print = high_resolution_clock::now();
    duration<double> duration_print = stop_print - start_print;
    cout << "Duomenys išvesti per " << duration_print.count() << "s" << endl;
    

    end_time = high_resolution_clock::now();

    duration<double> total_duration = end_time - start_time;

    cout << "Failo apdorojimas užtruko " << total_duration.count() << "s." << endl;

    return 0;
}
