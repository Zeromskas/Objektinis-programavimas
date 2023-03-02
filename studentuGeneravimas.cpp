#include <fstream>
#include <random>
#include <iostream>

using std::cout;
using std::endl;
using std::left;
using std::mt19937;
using std::ofstream;
using std::random_device;
using std::setprecision;
using std::setw;
using std::uniform_int_distribution;

int main()
{

    int studentuKiekis = 10000000;
    int pazymiuKiekis = 7;

    ofstream out("pazymiai.txt");

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 10);

    out << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė";
    for (int i = 1; i <= pazymiuKiekis; i++)
    {
        out << "ND" << setw(3) << left << i;
    }
    out << "Egzaminas" << endl;

    for (int i = 1; i <= studentuKiekis; i++)
    {
        out << "Vardas" << setw(9) << left << i << "Pavardė" << setw(12) << left << i;
        for (int j = 0; j < pazymiuKiekis; j++)
        {
            out << setw(5) << left << dist(mt);
        }
        out << dist(mt) << endl;
        if (i % 100000 == 0)
            cout << 100 * i / studentuKiekis << "%" << endl;
    }
}