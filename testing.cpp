#include "mylib.h"

int main()
{
    vector<Studentas> studentai;
    std::chrono::high_resolution_clock::time_point total_start, total_end;
    std::chrono::high_resolution_clock::time_point start_time, end_time;
    duration<double> dur;
    double duration[5][6];

    string filenames[5]{"studentai1k.txt", "studentai10k.txt", "studentai100k.txt", "studentai1M.txt", "studentai10M.txt"};

    int i=0;
    for(auto filename : filenames)
    {
        total_start = high_resolution_clock::now();
        start_time = high_resolution_clock::now();
        failoSkaitymas(studentai, filename);
        end_time = high_resolution_clock::now();
        if (studentai.empty())
            return 0;
        dur = end_time - start_time;
        duration[i][0] = dur.count();
        start_time = high_resolution_clock::now();
        rikiavimas(studentai, "grade");
        end_time = high_resolution_clock::now();
        dur = end_time - start_time;
        duration[i][1] = dur.count();
        start_time = high_resolution_clock::now();
        vector<Studentas> studPass = splittinimas(studentai);
        end_time = high_resolution_clock::now();
        dur = end_time - start_time;
        duration[i][2] = dur.count();
        studPass.shrink_to_fit();
        studentai.shrink_to_fit();
        start_time = high_resolution_clock::now();
        rikiavimas(studentai, "name");
        rikiavimas(studPass, "name");
        end_time= high_resolution_clock::now();
        dur = end_time - start_time;
        duration[i][3] = dur.count();
        start_time = high_resolution_clock::now();
        spausdinimas(studPass, "studPass.txt");
        studPass.clear();
        spausdinimas(studentai, "studFail.txt");
        studentai.clear();
        end_time= high_resolution_clock::now();
        dur = end_time - start_time;
        duration[i][4] = dur.count();
        total_end= high_resolution_clock::now();
        dur = total_end - total_start;
        duration[i][5] = dur.count();
        i++;
    }

    cout<<"|                  | **1k**    | **10k**  | **100k** | **1M** | **10M** |"<<endl;
    cout<<"|------------------|-----------|----------|----------|--------|---------|"<<endl;
    cout << "| **Nuskaitymas**  | _" << fixed << setprecision(5) << duration[0][0] << "_ | _" << fixed << setprecision(4) << duration[1][0] << "_ | _" << fixed << setprecision(3) << duration[2][0] << "_ | _" << fixed << setprecision(2) << duration[3][0] << "_ | _" << fixed << setprecision(1) << duration[4][0]<<"_ |"<<endl;
    cout << "| **Rikiavimas 1** | _" << fixed << setprecision(5) << duration[0][1] << "_ | _" << fixed << setprecision(4) << duration[1][1] << "_ | _" << fixed << setprecision(3) << duration[2][1] << "_ | _" << fixed << setprecision(2) << duration[3][1] << "_ | _" << fixed << setprecision(1) << duration[4][1] << "_ |" << endl;
    cout << "|  **Dalinimas**   | _" << fixed << setprecision(5) << duration[0][2] << "_ | _" << fixed << setprecision(4) << duration[1][2] << "_ | _" << fixed << setprecision(3) << duration[2][2] << "_ | _" << fixed << setprecision(2) << duration[3][2] << "_ | _" << fixed << setprecision(1) << duration[4][2] << "_ |" << endl;
    cout << "| **Rikiavimas 2** | _" << fixed << setprecision(5) << duration[0][3] << "_ | _" << fixed << setprecision(4) << duration[1][3] << "_ | _" << fixed << setprecision(3) << duration[2][3] << "_ | _" << fixed << setprecision(2) << duration[3][3] << "_ | _" << fixed << setprecision(1) << duration[4][3] << "_ |" << endl;
    cout << "| **Išvedimas**    | _" << fixed << setprecision(5) << duration[0][4] << "_ | _" << fixed << setprecision(4) << duration[1][4] << "_ | _" << fixed << setprecision(3) << duration[2][4] << "_ | _" << fixed << setprecision(2) << duration[3][4] << "_ | _" << fixed << setprecision(1) << duration[4][4] << "_ |" << endl;
    cout << "| **Viso**         | _" << fixed << setprecision(5) << duration[0][5] << "_ | _" << fixed << setprecision(4) << duration[1][5] << "_ | _" << fixed << setprecision(3) << duration[2][5] << "_ | _" << fixed << setprecision(2) << duration[3][5] << "_ | _" << fixed << setprecision(1) << duration[4][5] << "_ |" << endl;
    return 0;
}
