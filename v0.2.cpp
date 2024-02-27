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

using namespace std;

const int NUM_NAMES = 10;

vector<string> vardai = { "Jonas", "Petras", "Algis", "Marius", "Gintaras", "Tomas", "Lukas", "Simas", "Gabrielius", "Olegas" };
vector<string> pavardes = { "Kelmutis", "Kelmutaite", "Dangavicius", "Pieliauskas", "Lukavicius", "Simonavicius", "Skaudavicius", "Juzenas", "Darbavicius", "Stankevicius" };

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas;
    double galutinis;
};

bool isNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

double useMediana(const vector<int>& grades) {
    if (grades.empty()) {
        return 0.0; //Grazinti 0 jei pazymiu sarasas tuscias
    }

    vector<int> sortedGrades = grades;
    sort(sortedGrades.begin(), sortedGrades.end());
    int count = sortedGrades.size();
    if (count >= 2) {
        return (sortedGrades[count / 2 - 1] + sortedGrades[count / 2]) / 2.0;
    } else {
        return sortedGrades[0]; //Grazinti vieninteli pazymi jei pazymiu sarasas turi viena elementa
    }
}

void Ivedimas(vector<Studentas>& stud, bool randomNames = false, bool randomGrades = false, bool studentCount = false) {
    bool moreStudents = true;
    while (moreStudents) {
        Studentas student;

        if (!randomNames && !studentCount) {
            cout << "Iveskite studento varda ir pavarde: ";
            cin >> student.vardas >> student.pavarde;
        }
        else {
            int randIndex = rand() % NUM_NAMES;
            student.vardas = vardai[randIndex];
            student.pavarde = pavardes[randIndex];
        }

        if (randomGrades) {
            int ndCount = rand() % 11;
            for (int j = 0; j < ndCount; j++) {
                student.nd.push_back(rand() % 11);
            }
            student.egzaminas = rand() % 11;
        }
        else {
            string input;
            do {
                cout << "Kiek pazymiu rezultatu turi " << student.vardas << " " << student.pavarde << ": ";
                cin >> input;
            } while (!isNumber(input));
            int ndCount = stoi(input);

            for (int j = 0; j < ndCount; j++) {
                do {
                    cout << j + 1 << " balas: ";
                    cin >> input;
                } while (!(isNumber(input) && stoi(input) >= 0 && stoi(input) <= 10));
                student.nd.push_back(stoi(input));
            }

            do {
                cout << "Iveskite " << student.vardas << " " << student.pavarde << " egzamino rezultata: ";
                cin >> input;
            } while (!(isNumber(input) && stoi(input) >= 0 && stoi(input) <= 10));
            student.egzaminas = stoi(input);
        }

        stud.push_back(student);

        char moreChoice;
        cout << "Ar norite ivesti dar viena studenta? (Y/N): ";
        cin >> moreChoice;
        moreStudents = (moreChoice == 'Y' || moreChoice == 'y');
    }
}

void Spausdinimas(const vector<Studentas>& stud, bool Mediana) {
    cout << left << setw(15) << "Pavarde" << left << setw(15) << "Vardas" << left << setw(15) << "Galutinis ";
    if (Mediana) {
        cout << left << setw(15) << "Med.";
    }
    else {
        cout << left << setw(15) << "Vid.";
    }
    cout << endl;
    cout << "--------------------------------------------" << endl;
    for (const auto& student : stud) {
        double galutinis;
        if (Mediana) {
            galutinis = useMediana(student.nd);
        }
        else {
            double nd_sum = accumulate(student.nd.begin(), student.nd.end(), 0);
            double vidurkis = nd_sum / student.nd.size();
            galutinis = 0.4 * vidurkis + 0.6 * student.egzaminas;
        }
        cout << left << setw(15) << student.pavarde << left << setw(15) << student.vardas << left << setw(15) << fixed << setprecision(2) << galutinis << endl;
    }
}

int main() {
    srand(time(0));

    string choice;
    do {
        cout << "Pasirinkite veiksma: " << endl;
        cout << "1 - Uzpildyti ranka" << endl;
        cout << "2 - Sugeneruoti tik pazymius" << endl;
        cout << "3 - Sugeneruoti pazymius ir vardus" << endl;
        cout << "4 - Nuskaityti duomenis is failo kursiokai.txt" << endl;
        cout << "5 - Baigti programa" << endl;
        cout << " :";
        cin >> choice;
    try{
        switch (stoi(choice)) {
            case 1: {
                vector<Studentas> students;
                Ivedimas(students, false, false);
                char calcChoice;
                cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
                cin >> calcChoice;
                bool Mediana = (toupper(calcChoice) == 'M');
                Spausdinimas(students, Mediana);

                break;
            }
            case 2: {
                vector<Studentas> students;
                Ivedimas(students, false, true);

                char calcChoice;
                cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
                cin >> calcChoice;
                bool Mediana = (toupper(calcChoice) == 'M');
                Spausdinimas(students, Mediana);

                break;
            }
            case 3: {
                vector<Studentas> students;
                Ivedimas(students, true, true, true);

                char calcChoice;
                cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
                cin >> calcChoice;
                bool Mediana = (toupper(calcChoice) == 'M');
                Spausdinimas(students, Mediana);

                break;
            }
            case 4: {
                ifstream fd("kursiokai.txt");
                if (!fd) {
                    cerr << "Failo nuskaitymo error." << endl;
                    continue;
                }
                getline(fd, choice);    //praleisti pirmaja eilute
                vector<Studentas> students;

                string line;
                while (getline(fd, line)) {
                    istringstream iss(line);
                    Studentas student;
                    iss >> student.vardas >> student.pavarde;
                    int grade;
                    while (iss >> grade) {
                        student.nd.push_back(grade);    
                    }
                    // Prideti egzamino pazymi
                    if (student.nd.size() > 0) {
                        student.egzaminas = student.nd.back();
                        student.nd.pop_back();
                    }
                    students.push_back(student);
                }

                fd.close();

                char calcChoice;
                cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
                cin >> calcChoice;
                bool Mediana = (toupper(calcChoice) == 'M');
                Spausdinimas(students, Mediana);

                break;
            }
            case 5: {
                return 0;
            }
            default: {
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
                break;
            }
            }
        }catch (const invalid_argument& e) {
            cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
        }
        system("pause");
        system("cls");
    } while (true);

    return 0;
}