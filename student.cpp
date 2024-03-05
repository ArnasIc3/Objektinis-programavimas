#include "student.h"

const int NUM_NAMES = 10;
vector<string> vardai = { "Jonas", "Petras", "Algis", "Marius", "Gintaras", "Tomas", "Lukas", "Simas", "Gabrielius", "Olegas" };
vector<string> pavardes = { "Kelmutis", "Kelmutaite", "Dangavicius", "Pieliauskas", "Lukavicius", "Simonavicius", "Skaudavicius", "Juzenas", "Darbavicius", "Stankevicius" };

bool isNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

double useMediana(const vector<int>& grades) {
    if (grades.empty()) {
        return 0.0; // Return 0 if the list of grades is empty
    }

    vector<int> sortedGrades = grades;
    sort(sortedGrades.begin(), sortedGrades.end());
    int count = sortedGrades.size();
    if (count >= 2) {
        return (sortedGrades[count / 2 - 1] + sortedGrades[count / 2]) / 2.0;
    }
    else {
        return sortedGrades[0]; // Return the single grade if there's only one element in the list of grades
    }
}

void Ivedimas(vector<Studentas>& stud, bool randomNames, bool randomGrades, bool studentCount) {
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
        cout << left << setw(15) << student.pavarde << left << setw(15) << student.vardas << left << setw(15) << fixed << setprecision(2) << student.galutinis << endl;
    }
}

void sortStudents(vector<Studentas>& students, const string& sortBy) {
    if (sortBy == "V" || sortBy == "v") {
        sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
            return a.vardas < b.vardas;
            });
    }
    else if (sortBy == "P" || sortBy == "p") {
        sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
            return a.pavarde < b.pavarde;
            });
    }
    else if (sortBy == "G" || sortBy == "g") {
        sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinis > b.galutinis;
            });
    }
    else {
        cout << "Neteisingas rikiavimo pasirinkimas. Vykdomas rikiavimas pagal varda." << endl;
        sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
            return a.vardas < b.vardas;
            });
    }
}

void Pasirinkimai(vector<Studentas>& students)
{
    char calcChoice;
    cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
    cin >> calcChoice;
    string sortBy;
    cout << "Pasirinkite, kaip norite surusiuoti studentus (V, P, G, EGZ): ";
    cin >> sortBy;
    bool Mediana = (toupper(calcChoice) == 'M');
    for (auto& student : students) {
        if (!Mediana) {
            double nd_sum = accumulate(student.nd.begin(), student.nd.end(), 0);
            double vidurkis = nd_sum / student.nd.size();
            student.galutinis = 0.4 * vidurkis + 0.6 * student.egzaminas;
        }
        else {
            student.galutinis = useMediana(student.nd);
        }
    }
    sortStudents(students, sortBy);
    Spausdinimas(students, Mediana);
}