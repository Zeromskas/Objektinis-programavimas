#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <sstream>

using std::cerr;
using std::cin;
using std::copy;
using std::count;
using std::cout;
using std::endl;
using std::exception;
using std::getline;
using std::ifstream;
using std::left;
using std::mt19937;
using std::numeric_limits;
using std::ofstream;
using std::ostringstream;
using std::random_device;
using std::right;
using std::runtime_error;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;
using std::swap;
using std::to_string;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::seconds;

struct Studentas
{
    string vardas, pavarde;
    double vidurkis = 0;
    double mediana = 0;
};

struct Pazymiai
{
    vector<int> nd;
    int egz = 0;
};

double vidurkioSkaiciavimas(Pazymiai &temp);
double medianosSkaiciavimas(Pazymiai &temp);
void generuotiAtsitiktinius(vector<Studentas> &studentai);
void pildymasKonsoleje(vector<Studentas> &studentai);
void spausdinimas(vector<Studentas> &studentai);
void failoSkaitymas(vector<Studentas> &studentai);
void duomenuIvedimas(Studentas &temp);
bool rikiavimoLyginimas(const Studentas &a, const Studentas &b);