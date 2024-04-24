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
        cout << "5 - Sugeneruoti irasus" << endl;
        cout << "6 - Testavimas su 3 strategijomis" << endl;
        cout << "7 - Baigti programa" << endl; // "7 - Baigti programa
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
                int skin;
                int st;
                cout << "Ar tikrai norite sugeneruoti naujus irasus? (1 - Taip, any - Ne): ";
                cin >> skin;
                if (skin != 1) {
					break;
				}
                Generacija(0);
                break;
            }
            case 6: {
                cout << "Pasirinkite testavimo strategija: 1-a, 2-a: " << endl;
                cout << "Jusu pasirinkimas : ";
                int Pas;
                cin >> Pas;
                if (Pas == 1) {
					Generacija(1);
				}
                else if (Pas == 2) {
					Generacija(2);
				}
                else {
					cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
				}
                break;
            }
            case 7: {
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
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("pause");
        system("cls");
    } while (true);
}