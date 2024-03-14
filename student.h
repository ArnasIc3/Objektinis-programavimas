#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas;
    double galutinis;
};

void Ivedimas(vector<Studentas>& stud, bool randomNames = false, bool randomGrades = false, bool studentCount = false);
void Pasirinkimai(vector<Studentas>& students);
void Spausdinimas(const vector<Studentas>& students, bool Mediana);
bool isNumber(const string& str);
double useMediana(const vector<int>& grades);
void Generacija();

#endif // STUDENT_H
// Path: v0.3/v0.3.cpp