#include <fstream>
#include <random>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{

    int studentuKiekis = 1000000;
    int pazymiuKiekis = 15;

    std::string filename = "studentai" + std::to_string(studentuKiekis) + ".txt";

    ofstream out(filename);

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 10);

    out << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė";

    for (int i = 1; i <= pazymiuKiekis; i++)
        out << "ND" << setw(3) << left << i;

    out << "Egzaminas" << endl;

    unique_ptr<ostringstream> oss(new ostringstream());

    for (int i = 1; i <= studentuKiekis; i++)
    {
        (*oss) << "Vardas" << setw(9) << left << i << "Pavardė" << setw(12) << left << i;
        for (int j = 0; j < pazymiuKiekis; j++)
            (*oss) << setw(5) << left << dist(mt);

        (*oss) << dist(mt) << endl;
        if ((i + 1) % 10 == 0 || i == studentuKiekis)
        {
            out << oss->str();
            oss->str("");
        }
        if (i % (studentuKiekis / 100) == 0)
            cout << 100 * i / studentuKiekis << "%" << endl;
    }
}