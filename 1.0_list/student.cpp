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

void Generacija(int Pas) {
    for (int fileIndex = 1000; fileIndex <= 10000000; fileIndex *= 10) {
        // Constructing file name with different index
        string fileName = ".studentaiGENERATED_" + to_string(fileIndex) + ".txt";
        if (Pas == 0)
        {
            ofstream fd(fileName);
            if (!fd) {
                cerr << "Failo kurimo error." << endl;
                return;
            }

            auto startCreate = high_resolution_clock::now();

            fd << "Vardas    Pavarde  ND1  ND2  ND3  ND4  ND5  ND6  ND7  ND8  ND9  ND10  Egzaminas" << endl;

            for (int i = 0; i < fileIndex; i++) {
                fd << fixed << left << "Vardas" << i + 1 << " Pavarde" << i + 1;
                cout << setw(15);
                for (int j = 0; j < 10; j++) {
                    fd << " " << fixed << setw(4) << left << rand() % 11;
                }
                fd << " " << rand() % 11 << endl;
            }

            auto stopCreate = high_resolution_clock::now();
            auto durationCreate = duration_cast<milliseconds>(stopCreate - startCreate);


            fd.flush();
            cout << "File " << fileName << " created." << "\n Execution time: " << durationCreate.count() / 1000.0 << " seconds." << endl;
            fd.close();
        }
        // Split students into two files based on their final grade
        if (Pas == 0 || Pas == 1)
        {
            // Split students into two files based on their final grade
        ifstream inputFile(fileName);
        if (!inputFile) {
            cerr << "Error opening file: " << fileName << endl;
            return;
        }

        ofstream highGradesFile(".galvociai_" + to_string(fileIndex) + ".txt");
        ofstream lowGradesFile(".nuskriaustukai_" + to_string(fileIndex) + ".txt");

        if (!highGradesFile || !lowGradesFile) {
            cerr << "Error creating output files." << endl;
            return;
        }

        auto startSort = high_resolution_clock::now();

        list<Studentas> highGrades;
        list<Studentas> lowGrades;

        string line;
        getline(inputFile, line); // Skip the header line
        while (getline(inputFile, line)) {
            istringstream iss(line);
            Studentas student;
            iss >> student.vardas >> student.pavarde;
            int grade;
            while (iss >> grade) {
                student.nd.push_back(grade);
            }
            if (student.nd.size() > 0) {
                student.egzaminas = student.nd.back();
                student.nd.pop_back();
                }
            double nd_sum = accumulate(student.nd.begin(), student.nd.end(), 0);
            double vidurkis = nd_sum / student.nd.size();
            student.galutinis = 0.4 * vidurkis + 0.6 * student.egzaminas;

            // Add student to appropriate vector based on final grade
            if (student.galutinis >= 5)
                highGrades.push_back(student);
            else
                lowGrades.push_back(student);
            }


        auto startOutput = high_resolution_clock::now();
        // Write high and low grade students to separate files
        highGradesFile << "Vardas    Pavarde  Galutinis (Vid.)" << endl;
        for (const auto& student : highGrades) {
            highGradesFile << left << setw(15) << student.vardas << left << setw(15) << student.pavarde << left << setw(15) << fixed << setprecision(2) << student.galutinis << endl;
        }

        lowGradesFile << "Vardas    Pavarde  Galutinis (Vid.)" << endl;
        for (const auto& student : lowGrades) {
            lowGradesFile << left << setw(15) << student.vardas << left << setw(15) << student.pavarde << left << setw(15) << fixed << setprecision(2) << student.galutinis << endl;
        }
        auto stopOutput = high_resolution_clock::now();
        auto durationOutput = duration_cast<milliseconds>(stopOutput - startOutput);
        cout << " File " << fileIndex << "  output execution time : " << durationOutput.count() / 1000.0 << " seconds." << endl;
        // Close input and output files
        inputFile.close();
        highGradesFile.close();
        lowGradesFile.close();

        auto stopSort = high_resolution_clock::now();
        auto durationSort = duration_cast<milliseconds>(stopSort - startSort);

        cout << " File " << fileIndex << "  sorting execution time : " << durationSort.count() / 1000.0 << " seconds." << endl;
        cout << endl;

        }
        if (Pas == 2)
        {
            ifstream inputFile(fileName);
            if (!inputFile) {
                cerr << "Error opening file: " << fileName << endl;
                return;
            }

            ofstream lowGradesFile(".nuskriaustukai_" + to_string(fileIndex) + ".txt");

            if (!lowGradesFile) {
                cerr << "Error creating output files." << endl;
                return;
            }

            auto startSort = high_resolution_clock::now();

            list<Studentas> lowGrades;

            string line;
            getline(inputFile, line); // Skip the header line
            while (getline(inputFile, line)) {
                istringstream iss(line);
                Studentas student;
                iss >> student.vardas >> student.pavarde;
                int grade;
                while (iss >> grade) {
                    student.nd.push_back(grade);
                }
                if (student.nd.size() > 0) {
                    student.egzaminas = student.nd.back();
                    student.nd.pop_back();
                }
                double nd_sum = accumulate(student.nd.begin(), student.nd.end(), 0);
                double vidurkis = nd_sum / student.nd.size();
                student.galutinis = 0.4 * vidurkis + 0.6 * student.egzaminas;

                // Add student to appropriate vector based on final grade
                if (student.galutinis < 5)
                    lowGrades.push_back(student);
            }
            auto stopSort = high_resolution_clock::now();
            auto durationSort = duration_cast<milliseconds>(stopSort - startSort);

            auto startOutput = high_resolution_clock::now();
            lowGradesFile << "Vardas    Pavarde  Galutinis (Vid.)" << endl;
            for (const auto& student : lowGrades) {
                lowGradesFile << left << setw(15) << student.vardas << left << setw(15) << student.pavarde << left << setw(15) << fixed << setprecision(2) << student.galutinis << endl;
            }
            auto stopOutput = high_resolution_clock::now();
            auto durationOutput = duration_cast<milliseconds>(stopOutput - startOutput);
            cout << " File " << fileIndex << "  output execution time : " << durationOutput.count() / 1000.0 << " seconds." << endl;
            // Close input and output files
            inputFile.close();
            lowGradesFile.close();

            cout << " File " << fileIndex << "  sorting execution time : " << durationSort.count() / 1000.0 << " seconds." << endl;
            cout << endl;
        }
        if (Pas == 3)
        {
            auto startread = high_resolution_clock::now();
            ifstream inputFile(fileName);
            if (!inputFile) {
                cerr << "Error opening file: " << fileName << endl;
                return;
            }
            string line;
            getline(inputFile, line); // Skip the header line
            list<Studentas> students; // Declare the students list
            while (getline(inputFile, line)) {
                istringstream iss(line);
                Studentas student;
                iss >> student.vardas >> student.pavarde;
                int grade;
                while (iss >> grade) {
                    student.nd.push_back(grade);
                }
                if (student.nd.size() > 0) {
                    student.egzaminas = student.nd.back();
                    student.nd.pop_back();
                }
                double nd_sum = accumulate(student.nd.begin(), student.nd.end(), 0);
                double vidurkis = nd_sum / student.nd.size();
                student.galutinis = 0.4 * vidurkis + 0.6 * student.egzaminas;
                students.push_back(student);
            }       

            auto stopread = high_resolution_clock::now();
            auto durationread = duration_cast<milliseconds>(stopread - startread);
            cout << " File " << fileIndex << "  read execution time : " << durationread.count() / 1000.0 << " seconds." << endl;

            auto startSort = high_resolution_clock::now();
            list<Studentas> highGradeStudents;
            list<Studentas> lowGradeStudents;
        
            for (auto& student : students) {
                if (student.galutinis >= 5.0) {
                    highGradeStudents.push_back(student);
                } else {
                    lowGradeStudents.push_back(student);
                }
            }

            auto stopSort = high_resolution_clock::now();
            auto durationSort = duration_cast<milliseconds>(stopSort - startSort);
            cout << " File " << fileIndex << "  sorting execution time : " << durationSort.count() / 1000.0 << " seconds." << endl;

            auto startOutput = high_resolution_clock::now();
            ofstream highGradesFile(".galvociai_" + to_string(fileIndex) + ".txt");
            ofstream lowGradesFile(".vargsiukai_" + to_string(fileIndex) + ".txt");
        
            // Write high grade students to highGradesFile
            for (auto& student : highGradeStudents) {
                highGradesFile << student.vardas.c_str() << " " << student.pavarde.c_str() << " " << student.galutinis << "\n";
            }
            
            // Write low grade students to lowGradesFile
            for (auto& student : lowGradeStudents) {
                lowGradesFile << student.vardas.c_str() << " " << student.pavarde.c_str() << " " << student.galutinis << "\n";
            }
            highGradesFile.close();
            lowGradesFile.close();

            auto stopOutput = high_resolution_clock::now();
            auto durationOutput = duration_cast<milliseconds>(stopOutput - startOutput);
            cout << " File " << fileIndex << "  output execution time : " << durationOutput.count() / 1000.0 << " seconds." << endl;
        }
    }
}
