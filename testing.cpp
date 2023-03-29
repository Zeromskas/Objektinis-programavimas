#include "mylib.h"

struct Time
{
    string part;
    double duration[5]={0};
};

int main()
{
    vector<Studentas> studentai;
    std::chrono::high_resolution_clock::time_point total_start, total_end;
    std::chrono::high_resolution_clock::time_point start_time, end_time;
    duration<double> dur;

    string filenames[5]{"studentai1k.txt", "studentai10k.txt", "studentai100k.txt", "studentai1M.txt", "studentai10M.txt"};

    Time times[5];
    times[0].part="Nuskaitymas", times[1].part="Dalinimas", times[2].part="Rikiavimas", times[3].part="Išvedimas", times[4].part="Viso";

    int i=0;
    for(auto filename : filenames)
    {
        total_start = high_resolution_clock::now();
        start_time = high_resolution_clock::now();
        failoSkaitymas(studentai, filename);
        end_time = high_resolution_clock::now();
        dur = end_time - start_time;
        times[0].duration[i]=dur.count();
        start_time = high_resolution_clock::now();
        vector<Studentas> studPass = splittinimas(studentai);
        end_time = high_resolution_clock::now();
        dur = end_time - start_time;
        times[1].duration[i] = dur.count();
        studPass.shrink_to_fit();
        studentai.shrink_to_fit();
        start_time = high_resolution_clock::now();
        rikiavimas(studentai, "name");
        rikiavimas(studPass, "name");
        end_time= high_resolution_clock::now();
        dur = end_time - start_time;
        times[2].duration[i] = dur.count();
        start_time = high_resolution_clock::now();
        spausdinimas(studPass, "studPass.txt");
        studPass.clear();
        spausdinimas(studentai, "studFail.txt");
        studentai.clear();
        end_time= high_resolution_clock::now();
        dur = end_time - start_time;
        times[3].duration[i] = dur.count();
        total_end= high_resolution_clock::now();
        dur = total_end - total_start;
        times[4].duration[i] = dur.count();
        i++;
    }

    cout<<"|                  | **1k**    | **10k**  | **100k** | **1M** | **10M** |"<<endl;
    cout<<"|------------------|-----------|----------|----------|--------|---------|"<<endl;
    
    for(int i = 0; i < 5; i++)
    {
        cout << "| **"<<times[i].part<<"** |";
        for(int j=0; j<5; j++)
            cout << " _"<<fixed << setprecision(5-j) << times[i].duration[j] <<"_ |";
        cout<<endl;
    }
    return 0;
}
