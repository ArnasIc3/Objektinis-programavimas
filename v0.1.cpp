#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

const int NUM_NAMES = 10; // Skaicius kiek random vardu ir pavardziu sugeneruoti imanoma

string vardai[NUM_NAMES] = { "Jonas", "Petras", "Algis", "Marius", "Gintaras", "Tomas", "Lukas", "Simas", "Gabrielius", "Olegas" };
string pavardes[NUM_NAMES] = { "Kelmutis", "Kelmutaite", "Dangavicius", "Pieliauskas", "Lukavicius", "Simonavicius", "Skaudavicius", "Juzenas", "Darbavicius", "Stankevicius" };

struct Studentas {
    string vardas,
        pavarde;
    int* nd,
        egzaminas,
        ndCount,
        vidurkis = 0;
    double galutinis;
};

bool isNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

double useMediana(int grades[], int count) {
    sort(grades, grades + count);
    if (count % 2 == 0) {
        return (grades[count / 2 - 1] + grades[count / 2]) / 2.0;
    }
    else {
        return grades[count / 2];
    }
}

void Ivedimas(Studentas* stud, int n, bool randomNames = false, bool randomGrades = false) {
    for (int i = 0; i < n; i++) {
        if (!randomNames) {
            cout << "Iveskite " << i + 1 << " studento varda ir pavarde: ";
            cin >> stud[i].vardas >> stud[i].pavarde;
        }
        else {
            // Random vardu generavimas
            int randIndex = rand() % NUM_NAMES;
            stud[i].vardas = vardai[randIndex];
            stud[i].pavarde = pavardes[randIndex];
        }

        string input;
        do {
        cout << "Kiek pazymiu rezultatu turi " << stud[i].vardas << " " << stud[i].pavarde << " :";
        cin >> input;
        } while (!isNumber(input));
        stud[i].ndCount = stoi(input);

        // Paskirti tiek atminties kiek yra rezultatu
        stud[i].nd = new int[stud[i].ndCount];

        if (randomGrades) {
            // Sugeneruoti pazymius nuo 0 iki 10
            for (int j = 0; j < stud[i].ndCount; j++) {
                stud[i].nd[j] = rand() % 11; // Generates a random number between 0 and 10
                stud[i].vidurkis += stud[i].nd[j];
            }
            stud[i].egzaminas = rand() % 11;
        }
        else {
            // Rankiniu budu
            for (int j = 0; j < stud[i].ndCount; j++) {
                do {
                    cout << j + 1 << " balas: ";
                    cin >> input;
                } while (!(isNumber(input) && stoi(input) >= 0 && stoi(input) <= 10));
                stud[i].nd[j] = stoi(input);
                stud[i].vidurkis += stud[i].nd[j];
            }

            do {
                cout << "Iveskite " << stud[i].vardas << " " << stud[i].pavarde << " egzamino rezultata: ";
                cin >> input;
            } while (!(isNumber(input) && stoi(input) >= 0 && stoi(input) <= 10));
            stud[i].egzaminas = stoi(input);
        }
    }
}

void Spausdinimas(Studentas* stud, int n, bool Mediana) {
    cout << left << setw(15) << "Pavarde" << left << setw(15) << "vardas" << left << setw(15) << "Galutinis " << left << setw(2);
    if (Mediana) {
        cout << "Med.";
    }
    else {
        cout << "Vid.";
    }
    cout << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        double galutinis;
        if (Mediana) {
            int grades[100];
            for (int j = 0; j < stud[i].ndCount; j++) {
                grades[j] = stud[i].nd[j];
            }
            galutinis = useMediana(grades, stud[i].ndCount);
        }
        else {
            galutinis = 0.4 * stud[i].vidurkis / stud[i].ndCount + 0.6 * stud[i].egzaminas;
        }
        cout << left << setw(15) << stud[i].pavarde << left << setw(15) << stud[i].vardas << left << setw(15) << fixed << setprecision(2) << galutinis << endl;
    }
}

int main() {
    srand(time(0)); // Seed for randomization

    int n;
    string input;
    string choice; // Change the type of choice to string

    do {
        do {
            cout << "Pasirinkite veiksma: " << endl;
            cout << "1 - Uzpildyti ranka" << endl;
            cout << "2 - Sugeneruoti tik pazymius" << endl;
            cout << "3 - Sugeneruoti pazymius ir vardus" << endl;
            cout << "4 - Baigti programa" << endl;
            cout << " :"; cin >> choice;

            if (choice != "1" && choice != "2" && choice != "3" && choice != "4") { // Check if the input is valid
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
            }
        } while (choice != "1" && choice != "2" && choice != "3" && choice != "4"); // Repeat until a valid option is entered

        if (choice == "4") // Exit if the user chose to end the program
            break;

        switch (stoi(choice)) { // Convert string choice to integer for switch statement
        case 1: {
            do {
                cout << "Iveskite studentu skaiciu: ";
                cin >> input;
            } while (!isNumber(input));
            n = stoi(input);

            Studentas* stud = new Studentas[n];
            Ivedimas(stud, n);

            char calcChoice;
            cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
            cin >> calcChoice;
            bool Mediana = (toupper(calcChoice) == 'M');

            Spausdinimas(stud, n, Mediana);

            system("Pause");
            system("CLS");

            delete[] stud;
            break;
        }
        case 2: {
            do {
                cout << "Iveskite studentu skaiciu: ";
                cin >> input;
            } while (!isNumber(input));
            n = stoi(input);

            Studentas* stud = new Studentas[n];
            Ivedimas(stud, n, false, true);

            char calcChoice;
            cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
            cin >> calcChoice;
            bool Mediana = (toupper(calcChoice) == 'M');

            Spausdinimas(stud, n, Mediana);

            system("Pause");
            system("CLS");

            delete[] stud;
            break;
        }
        case 3: {
            do {
                cout << "Iveskite studentu skaiciu: ";
                cin >> input;
            } while (!isNumber(input));
            n = stoi(input);

            Studentas* stud = new Studentas[n];
            Ivedimas(stud, n, true, true);

            char calcChoice;
            cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
            cin >> calcChoice;
            bool Mediana = (toupper(calcChoice) == 'M');

            Spausdinimas(stud, n, Mediana);

            system("Pause");
            system("CLS");

            delete[] stud;
            break;
        }
        }
    } while (true);

    return 0;
}