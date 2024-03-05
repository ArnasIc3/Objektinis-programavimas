#include "menu.h"
#include "student.h"


using namespace std;

void Menu_execute() {
    char calcChoice = ' ';
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
        try {
            switch (stoi(choice)) {
            case 1: {
                vector<Studentas> students;
                Ivedimas(students, false, false);
                Pasirinkimai(students);
                break;
            }
            case 2: {
                vector<Studentas> students;
                Ivedimas(students, false, true);
                Pasirinkimai(students);
                break;
            }
            case 3: {
                vector<Studentas> students;
                Ivedimas(students, true, true, true);
                Pasirinkimai(students);
                break;
            }
            case 4: {
                ifstream fd("studentai10000.txt");
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

                Pasirinkimai(students);
                break;
            }
            case 5: {
                return;
            }
            default: {
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
                break;
            }
            }
        }
        catch (const invalid_argument& e) {
            cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
        }
        system("pause");
        system("cls");
    } while (true);
}