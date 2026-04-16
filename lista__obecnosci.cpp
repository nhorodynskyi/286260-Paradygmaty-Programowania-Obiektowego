#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

class Osoba {
private:
    string nazwisko;
    string imie;
    string indeks;
    string dataUrodzenia;
    int wzrost;

public:
    Osoba() {
        nazwisko = "";
        imie = "";
        indeks = "";
        dataUrodzenia = "";
        wzrost = 0;
    }

    bool tylkoLitery(const string& txt) {
        if (txt.empty()) return false;
        for (int i = 0; i < (int)txt.size(); i++) {
            if (!isalpha((unsigned char)txt[i]) && !isspace((unsigned char)txt[i])) {
                return false;
            }
        }
        return true;
    }

    bool prawidlowyIndeks(const string& txt) {
        if (txt.size() != 6) return false;
        for (int i = 0; i < 6; i++) {
            if (!isdigit((unsigned char)txt[i])) return false;
        }
        return true;
    }

    bool prawidlowaData(const string& data) {
        if (data.size() != 10) return false;
        if (data[2] != '.' || data[5] != '.') return false;

        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) continue;
            if (!isdigit((unsigned char)data[i])) return false;
        }

        int dzien = stoi(data.substr(0, 2));
        int miesiac = stoi(data.substr(3, 2));
        int rok = stoi(data.substr(6, 4));

        if (dzien < 1 || dzien > 31) return false;
        if (miesiac < 1 || miesiac > 12) return false;
        if (rok < 1900 || rok > 2100) return false;

        return true;
    }

    bool setNazwisko(const string& noweNazwisko) {
        if (!tylkoLitery(noweNazwisko)) return false;
        nazwisko = noweNazwisko;
        return true;
    }

    bool setImie(const string& noweImie) {
        if (!tylkoLitery(noweImie)) return false;
        imie = noweImie;
        return true;
    }

    bool setIndeks(const string& nowyIndeks) {
        if (!prawidlowyIndeks(nowyIndeks)) return false;
        indeks = nowyIndeks;
        return true;
    }

    bool setDataUrodzenia(const string& nowaData) {
        if (!prawidlowaData(nowaData)) return false;
        dataUrodzenia = nowaData;
        return true;
    }

    bool setWzrost(int nowyWzrost) {
        if (nowyWzrost < 50 || nowyWzrost > 250) return false;
        wzrost = nowyWzrost;
        return true;
    }

    string getNazwisko() const { return nazwisko; }
    string getImie() const { return imie; }
    string getIndeks() const { return indeks; }
    string getDataUrodzenia() const { return dataUrodzenia; }
    int getWzrost() const { return wzrost; }
    
};
class listaObecnosci {
private:
    static const int MAX = 10;

    Osoba osoby[MAX];
    int ileOsob;

    Osoba* obecni[MAX];
    int ileObecnych;

    Osoba* nieobecni[MAX];
    int ileNieobecnych;

    int szukajOsobe(const string& nazwisko) {
        for (int i = 0; i < ileOsob; i++) {
            if (osoby[i].getNazwisko() == nazwisko) return i;
        }
        return -1;
    }

    int znajdzWskaznik(Osoba* tablica[], int ile, Osoba* wskOsoby) {
        for (int i = 0; i < ile; i++) {
            if (tablica[i] == wskOsoby) return i;
        }
        return -1;
    }

    void usunZListy(Osoba* tablica[], int& ile, int index) {
        if (index < 0 || index >= ile) return;

        for (int i = index; i < ile - 1; i++) {
            tablica[i] = tablica[i + 1];
        }

        tablica[ile - 1] = nullptr;
        ile--;
    }

    void statusObecnych(bool statusObecnosci[]) {
        ileObecnych = 0;
        ileNieobecnych = 0;

        for (int i = 0; i < MAX; i++) {
            obecni[i] = nullptr;
            nieobecni[i] = nullptr;
        }

        for (int i = 0; i < ileOsob; i++) {
            if (statusObecnosci[i]) {
                obecni[ileObecnych] = &osoby[i];
                ileObecnych++;
            } else {
                nieobecni[ileNieobecnych] = &osoby[i];
                ileNieobecnych++;
            }
        }
    }
    void drukujListe(Osoba* tablica[], int ile, const string& lista, const string& obecnosc) const {
        const char* PURPLE = "\033[1;35m";
        const char* CYAN = "\033[1;36m";
        const char* GREEN = "\033[1;32m";
        const char* RESET = "\033[0m";

        cout << "\n--- " << lista << " ---\n";
        if (ile == 0) {
            cout << "Brak " << lista << "!" << endl;
            return;
        }

        cout << PURPLE << "+--------+------------+--------------+----------------+--------+----------+\n" << RESET;
        cout << CYAN << "| Indeks | Imie       | Nazwisko     | Data urodzenia | Wzrost | Obecnosc |\n" << RESET;
        cout << PURPLE << "+--------+------------+--------------+----------------+--------+----------+\n" << RESET;

        for (int i = 0; i < ile; i++) {
            if (tablica[i] == nullptr) continue;
            cout << GREEN
                 << "| " << setw(6) << left << tablica[i]->getIndeks()
                 << " | " << setw(10) << left << tablica[i]->getImie()
                 << " | " << setw(12) << left << tablica[i]->getNazwisko()
                 << " | " << setw(14) << left << tablica[i]->getDataUrodzenia()
                 << " | " << setw(6) << right << tablica[i]->getWzrost()
                 << " | " << setw(8) << left << obecnosc << " |\n"
                 << RESET;
        }

        cout << PURPLE << "+--------+------------+--------------+----------------+--------+----------+\n" << RESET;
    }
public:
    listaObecnosci() {
        ileOsob = 0;
        ileObecnych = 0;
        ileNieobecnych = 0;

        for (int i = 0; i < MAX; i++) {
            obecni[i] = nullptr;
            nieobecni[i] = nullptr;
        }
    }
   
    

    void dodajOsobe() {
        if (ileOsob >= MAX) {
            cout << "Brak miejsca" << endl;
            return;
        }

        string nazwisko, imie, indeks, dataUrodzenia;
        int wzrost;

        cout << "Nazwisko: ";
        getline(cin, nazwisko);
        cout << "Imie: ";
        getline(cin, imie);
        cout << "Nr indeksu : ";
        getline(cin, indeks);
        cout << "Data urodzenia (dd.mm.rrrr): ";
        getline(cin, dataUrodzenia);
        cout << "Wzrost : ";
        cin >> wzrost;
        cin.ignore();

        Osoba nowaOsoba;
        if (!nowaOsoba.setNazwisko(nazwisko)) {
            cout << "Nieprawidlowe nazwisko!" << endl;
            return;
        }
        if (!nowaOsoba.setImie(imie)) {
            cout << "Nieprawidlowe imie!" << endl;
            return;
        }
        if (!nowaOsoba.setIndeks(indeks)) {
            cout << "Nieprawidlowy indeks!" << endl;
            return;
        }
        if (!nowaOsoba.setDataUrodzenia(dataUrodzenia)) {
            cout << "Nieprawidlowa data urodzenia!" << endl;
            return;
        }
        if (!nowaOsoba.setWzrost(wzrost)) {
            cout << "Nieprawidlowy wzrost!" << endl;
            return;
        }

        osoby[ileOsob] = nowaOsoba;
        nieobecni[ileNieobecnych] = &osoby[ileOsob];
        ileNieobecnych++;
        ileOsob++;

    }

    void ustawObecnosc() {
        string nazwisko;
        int obecnosc;

        cout << "Nazwisko: ";
        getline(cin, nazwisko);
        cout << "Obecnosc (1/0): ";
        cin >> obecnosc;
        cin.ignore();

        if (obecnosc != 0 && obecnosc != 1) {
            cout << "Nieprawidlowy wybor obecnosc!" << endl;
            return;
        }

        int index = szukajOsobe(nazwisko);
        if (index == -1) {
            cout << "Nie znaleziono!" << endl;
            return;
        }

        Osoba* wskOsoby = &osoby[index];

        int idxObecny = znajdzWskaznik(obecni, ileObecnych, wskOsoby);
        int idxNieobecny = znajdzWskaznik(nieobecni, ileNieobecnych, wskOsoby);

        if (obecnosc == 1) {
            if (idxNieobecny != -1) {
                usunZListy(nieobecni, ileNieobecnych, idxNieobecny);
            }
            if (idxObecny == -1 && ileObecnych < MAX) {
                obecni[ileObecnych] = wskOsoby;
                ileObecnych++;
            }
        } else {
            if (idxObecny != -1) {
                usunZListy(obecni, ileObecnych, idxObecny);
            }
            if (idxNieobecny == -1 && ileNieobecnych < MAX) {
                nieobecni[ileNieobecnych] = wskOsoby;
                ileNieobecnych++;
            }
        }

    }

    void pokazObecnych() {
       drukujListe(obecni, ileObecnych, "OBECNI", "1");  
    }

    void pokazNieobecnych() {
        drukujListe(nieobecni, ileNieobecnych, "NIEOBECNI", "0");
    }

    void edytuj() {
        string nazwisko;
        cout << "Nazwisko osoby do edycji: ";
        getline(cin, nazwisko);

        int index = szukajOsobe(nazwisko);
        if (index == -1) {
            cout << "Nie znaleziono!" << endl;
            return;
        }

        int wybor;
        cout << "\t1.Nazwisko\n  2.Imie\n  3.Indeks\n  4.Data urodzenia\n  5.Wzrost\nWybierz: ";
        cin >> wybor;
        cin.ignore();

        if (wybor == 1) {
            string noweNazwisko;
            cout << "Nowe nazwisko: ";
            getline(cin, noweNazwisko);
            if (!osoby[index].setNazwisko(noweNazwisko)) cout << "Nieprawidlowe nazwisko!" << endl;

        } else if (wybor == 2) {
            string noweImie;
            cout << "Nowe imie: ";
            getline(cin, noweImie);
            if (!osoby[index].setImie(noweImie)) cout << "Nieprawidlowe imie!" << endl;

        } else if (wybor == 3) {
            string nowyIndeks;
            cout << "Nowy indeks: ";
            getline(cin, nowyIndeks);
            if (!osoby[index].setIndeks(nowyIndeks)) cout << "Nieprawidlowy indeks!" << endl;

        } else if (wybor == 4) {
            string nowaData;
            cout << "Nowa data urodzenia (dd.mm.rrrr): ";
            getline(cin, nowaData);
            if (!osoby[index].setDataUrodzenia(nowaData)) cout << "Nieprawidlowa data!" << endl;

        } else if (wybor == 5) {
            int nowyWzrost;
            cout << "Nowy wzrost: ";
            cin >> nowyWzrost;
            cin.ignore();
            if (!osoby[index].setWzrost(nowyWzrost)) cout << "Nieprawidlowy wzrost!" << endl;

        } else {
            cout << "Nieprawidlowy wybor!" << endl;
        }
    }

    void usun() {
        string nazwisko;
        cout << "Podaj nazwisko osoby do usuniecia: ";
        getline(cin, nazwisko);

        int index = szukajOsobe(nazwisko);
        if (index == -1) {
            cout << "Nie znaleziono." << endl;
            return;
        }

        bool statusObecnosci[MAX];
        for (int i = 0; i < ileOsob; i++) {
            statusObecnosci[i] = (znajdzWskaznik(obecni, ileObecnych, &osoby[i]) != -1);
        }

        for (int i = index; i < ileOsob - 1; i++) {
            osoby[i] = osoby[i + 1];
            statusObecnosci[i] = statusObecnosci[i + 1];
        }

        ileOsob--;
        statusObecnych(statusObecnosci);

        cout << "Usunieto osobe." << endl;
    }
   
};

int main() {
    listaObecnosci lista;
    int wybor;

    do {
        cout << "\n1. Dodaj\n"
                "2. Obecnosc\n"
                "3. Obecni\n"
                "4. Nieobecni\n"
                "5. Edytuj\n"
                "6. Usun\n"
                "0. Wyjdz\n"
                "Wybierz: ";
        cin >> wybor;
        cin.ignore();

        if (wybor == 1) lista.dodajOsobe();
        else if (wybor == 2) lista.ustawObecnosc();
        else if (wybor == 3) lista.pokazObecnych();
        else if (wybor == 4) lista.pokazNieobecnych();
        else if (wybor == 5) lista.edytuj();
        else if (wybor == 6) lista.usun();

    } while (wybor != 0);

    return 0;
}
