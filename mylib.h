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

using std::cin;
using std::copy;
using std::count;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::left;
using std::mt19937;
using std::numeric_limits;
using std::ofstream;
using std::random_device;
using std::right;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;
using std::swap;
using std::to_string;
using std::uniform_int_distribution;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::seconds;
using std::unique_ptr;
using std::ostringstream;
using std::runtime_error;
using std::exception;
using std::cerr;

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
