#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ctime>
#include <fstream>
#include <sstream>

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
    vector<int> sortedGrades = grades;
    sort(sortedGrades.begin(), sortedGrades.end());
    int count = sortedGrades.size();
    if (count % 2 == 0) {
        return (sortedGrades[count / 2 - 1] + sortedGrades[count / 2]) / 2.0;
    }
    else {
        return sortedGrades[count / 2];
    }
}

void Ivedimas(vector<Studentas>& stud, int n, bool randomNames = false, bool randomGrades = false) {
    for (int i = 0; i < n; i++) {
        if (!randomNames) {
            cout << "Iveskite " << i + 1 << " studento varda ir pavarde: ";
            cin >> stud[i].vardas >> stud[i].pavarde;
        }
        else {
            int randIndex = rand() % NUM_NAMES;
            stud[i].vardas = vardai[randIndex];
            stud[i].pavarde = pavardes[randIndex];
        }

        if (randomGrades) {
            int ndCount = rand() % 11;
            for (int j = 0; j < ndCount; j++) {
                stud[i].nd.push_back(rand() % 11);
            }
            stud[i].egzaminas = rand() % 11;
        }
        else {
            string input;
            do {
                cout << "Kiek pazymiu rezultatu turi " << stud[i].vardas << " " << stud[i].pavarde << " :";
                cin >> input;
            } while (!isNumber(input));
            int ndCount = stoi(input);

            for (int j = 0; j < ndCount; j++) {
                do {
                    cout << j + 1 << " balas: ";
                    cin >> input;
                } while (!(isNumber(input) && stoi(input) >= 0 && stoi(input) <= 10));
                stud[i].nd.push_back(stoi(input));
            }

            do {
                cout << "Iveskite " << stud[i].vardas << " " << stud[i].pavarde << " egzamino rezultata: ";
                cin >> input;
            } while (!(isNumber(input) && stoi(input) >= 0 && stoi(input) <= 10));
            stud[i].egzaminas = stoi(input);
        }
    }
}

void Spausdinimas(const vector<Studentas>& stud, bool Mediana) {
    cout << left << setw(15) << "Pavarde" << left << setw(15) << "vardas" << left << setw(15) << "Galutinis " << left << setw(2);
    if (Mediana) {
        cout << "Med.";
    }
    else {
        cout << "Vid.";
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
        cout << "4 - Nuskaityti duomenis is failo kursiokai.txt" << endl; // Add an option to read from a file
        cout << "5 - Baigti programa" << endl;
        cout << " :";
        cin >> choice;

        switch (stoi(choice)) {
            case 1: {
                int n;
                cout << "Iveskite studentu skaiciu: ";
                cin >> n;

                vector<Studentas> students(n);
                bool randomNames = false; // For manual input, randomNames is always false
                bool randomGrades = false; // For manual input, randomGrades is always false
                Ivedimas(students, n, randomNames, randomGrades);

                char calcChoice;
                cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
                cin >> calcChoice;
                bool Mediana = (toupper(calcChoice) == 'M');
                Spausdinimas(students, Mediana);

                break;
            }
            case 2: {
                int n;
                cout << "Iveskite studentu skaiciu: ";
                cin >> n;

                vector<Studentas> students(n);
                bool randomNames = false; // For random generation, randomNames is always false
                bool randomGrades = true; // For random generation, randomGrades is always true
                Ivedimas(students, n, randomNames, randomGrades);

                char calcChoice;
                cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
                cin >> calcChoice;
                bool Mediana = (toupper(calcChoice) == 'M');
                Spausdinimas(students, Mediana);

                break;
            }
            case 3: {
                int n;
                cout << "Iveskite studentu skaiciu: ";
                cin >> n;

                vector<Studentas> students(n);
                bool randomNames = true; // For random generation, randomNames is always true
                bool randomGrades = true; // For random generation, randomGrades is always true
                Ivedimas(students, n, randomNames, randomGrades);

                char calcChoice;
                cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
                cin >> calcChoice;
                bool Mediana = (toupper(calcChoice) == 'M');
                Spausdinimas(students, Mediana);

                break;
            }
            case 4: {
                ifstream infile("kursiokai.txt"); // Open file for reading
                if (!infile) {
                    cerr << "Failo nuskaitymo error." << endl;
                    continue;
                }

                vector<Studentas> students;

                // Read data from the file
                string line;
                while (getline(infile, line)) {
                    istringstream iss(line);
                    Studentas student;
                    iss >> student.vardas >> student.pavarde;
                    int grade;
                    while (iss >> grade) {
                        student.nd.push_back(grade);
                    }
                    // Make sure that egzaminas is also read from the file
                    if (student.nd.size() > 0) {
                        student.egzaminas = student.nd.back();
                        student.nd.pop_back();
                    }
                    students.push_back(student);
                }

                infile.close(); // Close the file

                // Calculate and print results
                char calcChoice;
                cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
                cin >> calcChoice;
                bool Mediana = (toupper(calcChoice) == 'M');
                Spausdinimas(students, Mediana);

                break;
            }
            case 5: {
                return 0; // Exit the program
            }
            default: {
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
                break;
            }
        }

        cout << endl;

        system("pause");
        system("CLS");

    } while (true);

    return 0;
}
