#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

struct Studentas {
    string  vardas,
            pavarde;
    int     nd[10],
            egzaminas,
            vidurkis = 0;
    double  galutinis;
};

bool isNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

void Ivedimas(Studentas* stud, int n)
{
    for (int i = 0; i < n; i++) {
        cout << "Iveskite " << i + 1 << " studento varda ir pavarde: ";
        cin >> stud[i].vardas >> stud[i].pavarde;

        string input;
        int l;
        do {
            cout << "Iveskite kiek namu darbu rezultatu turejo " << stud[i].vardas << " " << stud[i].pavarde << " studentas:";
            cin >> input;
        } while (!isNumber(input));
        l = stoi(input);

        for (int j = 0; j < l; j++) {
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
        stud[i].galutinis = 0.4 * stud[i].vidurkis / l + 0.6 * stud[i].egzaminas;
        cout << " -- -- -- -- -- -- " << endl;
    }
}

int main() {
    int n;
    string input;
    do {
        cout << "Iveskite studentu skaiciu: ";
        cin >> input;
    } while (!isNumber(input));
    n = stoi(input);
    Studentas* stud = new Studentas[n];
    Ivedimas(stud, n);
    cout << left << setw(15) << "Pavarde" <<left << setw(15) << "vardas" << left << setw(15) << "Galutinis vidurkis(Vid.)" << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << left << setw(15) << stud[i].pavarde << " " << left << setw(15)  << stud[i].vardas << " " << left << setw(15) << fixed << setprecision(2) << stud[i].galutinis << endl;
    }
    delete[] stud;
    return 0;
}