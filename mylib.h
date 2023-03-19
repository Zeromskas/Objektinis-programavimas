#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <list>
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
using std::list;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::duration;
using std::fixed;

struct Studentas
{
    string vardas, pavarde;
    float vidurkis = 0;
    float mediana = 0;
};

struct Pazymiai
{
    list<int> nd;
    int egz = 0;
};

float vidurkioSkaiciavimas(Pazymiai &temp);
float medianosSkaiciavimas(Pazymiai &temp);
void generuotiAtsitiktinius(list<Studentas> &studentai);
void pildymasKonsoleje(list<Studentas> &studentai);
void spausdinimas(list<Studentas> &studentai, string filename);
void failoSkaitymas(list<Studentas> &studentai, string filename);
void duomenuIvedimas(Studentas &temp);
bool compareName(const Studentas &a, const Studentas &b);
bool compareGrade(const Studentas &a, const Studentas &b);

// void splittinimas(list<Studentas> &studentai, list<Studentas> &studPass, list<Studentas> &studFail);
void splittinimas(list<Studentas> &studentai, list<Studentas> &studFail);

void rikiavimas(list<Studentas> &studentai, string sortType);