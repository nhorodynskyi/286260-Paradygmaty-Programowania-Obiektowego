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
            if (!isalpha((unsigned char)txt[i]) && !isspace((unsigned char)txt[i])) return false;
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
        return true;
    }

    bool setNazwisko(string wartosc) {
        if (wartosc.length() > 1 && tylkoLitery(wartosc)) {
            nazwisko = wartosc;
            return true;
        }
        return false;
    }

    bool setImie(string wartosc) {
        if (wartosc.length() > 1 && tylkoLitery(wartosc)) {
            imie = wartosc;
            return true;
        }
        return false;
    }

    bool setIndeks(string wartosc) {
        if (prawidlowyIndeks(wartosc)) {
            indeks = wartosc;
            return true;
        }
        return false;
    }

    bool setDataUrodzenia(string wartosc) {
        if (prawidlowaData(wartosc)) {
            dataUrodzenia = wartosc;
            return true;
        }
        return false;
    }

    bool setWzrost(int wartosc) {
        if (wartosc >= 50 && wartosc <= 250) {
            wzrost = wartosc;
            return true;
        }
        return false;
    }

    string getNazwisko() const { return nazwisko; }
    string getImie() const { return imie; }
    string getIndeks() const { return indeks; }
    string getDataUrodzenia() const { return dataUrodzenia; }
    int getWzrost() const { return wzrost; }
};

class ListaObecnosci {
private:
    string nazwaListy;
    Osoba* tabOsob[10];
    bool tabObecnosc[10];
    int iloscNaLiscie;

public:
    ListaObecnosci() {
        nazwaListy = "Nieznana";
        iloscNaLiscie = 0;
        for (int i = 0; i < 10; i++) {
            tabOsob[i] = nullptr;
            tabObecnosc[i] = false;
        }
    }

    void setNazwa(string nazwa) { nazwaListy = nazwa; }
    string getNazwa() const { return nazwaListy; }

    bool dodajOsobeDoListy(Osoba* osoba) {
        if (iloscNaLiscie >= 10) return false;
        for(int i=0; i<iloscNaLiscie; i++){
            if(tabOsob[i] == osoba) return false; 
        }
        tabOsob[iloscNaLiscie] = osoba;
        tabObecnosc[iloscNaLiscie] = false;
        iloscNaLiscie++;
        return true;
    }

    bool ustawObecnosc(string nazwisko_szukane, bool status) {
        for (int i = 0; i < iloscNaLiscie; i++) {
            if (tabOsob[i]->getNazwisko() == nazwisko_szukane) {
                tabObecnosc[i] = status;
                return true;
            }
        }
        return false;
    }

    bool usunOsobeZListy(string nazwisko_szukane) {
        int index = -1;
        for (int i = 0; i < iloscNaLiscie; i++) {
            if (tabOsob[i]->getNazwisko() == nazwisko_szukane) {
                index = i;
                break;
            }
        }
        if (index == -1) return false;
        for (int i = index; i < iloscNaLiscie - 1; i++) {
            tabOsob[i] = tabOsob[i + 1];
            tabObecnosc[i] = tabObecnosc[i + 1];
        }
        tabOsob[iloscNaLiscie - 1] = nullptr;
        iloscNaLiscie--;
        return true;
    }

    void wyswietlTabelarycznie() const {
        const char* PURPLE = "\033[1;35m";
        const char* CYAN = "\033[1;36m";
        const char* GREEN = "\033[1;32m";
        const char* RESET = "\033[0m";

        cout << "\n--- LISTA: " << nazwaListy << " ---\n";
        if (iloscNaLiscie == 0) {
            cout << "Brak osob na tej liscie!" << endl;
            return;
        }

        cout << PURPLE << "+--------+------------+--------------+----------------+--------+----------+\n" << RESET;
        cout << CYAN << "| Indeks | Imie       | Nazwisko     | Data urodzenia | Wzrost | Obecnosc |\n" << RESET;
        cout << PURPLE << "+--------+------------+--------------+----------------+--------+----------+\n" << RESET;

        for (int i = 0; i < iloscNaLiscie; i++) {
            if (tabOsob[i] == nullptr) continue;
            
            cout << GREEN
                 << "| " << setw(6) << left << tabOsob[i]->getIndeks()
                 << " | " << setw(10) << left << tabOsob[i]->getImie()
                 << " | " << setw(12) << left << tabOsob[i]->getNazwisko()
                 << " | " << setw(14) << left << tabOsob[i]->getDataUrodzenia()
                 << " | " << setw(6) << right << tabOsob[i]->getWzrost()
                 << " | " << setw(8) << left << (tabObecnosc[i] ? "1" : "0") << " |\n"
                 << RESET;
        }
        cout << PURPLE << "+--------+------------+--------------+----------------+--------+----------+\n" << RESET;
    }
};

class InterfejsUzytkownika {
private:
    Osoba* tabOsob;
    ListaObecnosci* tablicaList;
    int maxOsob, maxList;
    int iloscOsob, iloscList;

    int znajdzOsobeWbazie(string nazwisko) {
        for (int i = 0; i < iloscOsob; i++) {
            if (tabOsob[i].getNazwisko() == nazwisko) return i;
        }
        return -1;
    }

    int znajdzListe(string nazwa) {
        for (int i = 0; i < iloscList; i++) {
            if (tablicaList[i].getNazwa() == nazwa) return i;
        }
        return -1;
    }

    void dodajOsobe() {
        if (iloscOsob >= maxOsob) { cout << "Brak miejsca!\n"; return; }
        string nazw, im, ind, data; int wzr;
        cout << "Nazwisko: "; getline(cin, nazw);
        cout << "Imie: "; getline(cin, im);
        cout << "Indeks (6 cyfr): "; getline(cin, ind);
        cout << "Data ur (dd.mm.rrrr): "; getline(cin, data);
        cout << "Wzrost: "; cin >> wzr; cin.ignore();

        Osoba temp;
        if (temp.setNazwisko(nazw) && temp.setImie(im) && temp.setIndeks(ind) && 
            temp.setDataUrodzenia(data) && temp.setWzrost(wzr)) {
            tabOsob[iloscOsob] = temp;
            iloscOsob++;
            cout << "Osoba dodana до bazy.\n";
        } else {
            cout << "Blad walidacji!\n";
        }
    }

    void przypiszOsobeDoListy() {
        string nazw, nListy;
        cout << "Nazwisko osoby: "; getline(cin, nazw);
        int idxOs = znajdzOsobeWbazie(nazw);
        if (idxOs == -1) { cout << "Nie ma takiej osoby!\n"; return; }

        cout << "Nazwa listy: "; getline(cin, nListy);
        int idxList = znajdzListe(nListy);
        if (idxList == -1) { cout << "Nie ma takiej listy!\n"; return; }

        if (tablicaList[idxList].dodajOsobeDoListy(&tabOsob[idxOs])) {
            cout << "Osoba przypisana.\n";
        } else {
            cout << "Blad (limit lub duplikat).\n";
        }
    }

    void dodajListe() {
        if (iloscList >= maxList) { cout << "Brak miejsca на listy!\n"; return; }
        string nazwa;
        cout << "Podaj nazwe listy: "; getline(cin, nazwa);
        tablicaList[iloscList].setNazwa(nazwa);
        iloscList++;
        cout << "Lista dodana.\n";
    }

    void ustawObecnosc() {
        string nazw, nListy; bool ob;
        cout << "Nazwa listy: "; getline(cin, nListy);
        int idxList = znajdzListe(nListy);
        if (idxList == -1) { cout << "Brak listy!\n"; return; }
        cout << "Nazwisko: "; getline(cin, nazw);
        cout << "Obecny (1/0): "; cin >> ob; cin.ignore();
        if (!tablicaList[idxList].ustawObecnosc(nazw, ob)) cout << "Nie znaleziono osoby на liscie.\n";
    }

    void usunOsobeZListy() {
        string nazw, nListy;
        cout << "Nazwa listy: "; getline(cin, nListy);
        int idxList = znajdzListe(nListy);
        if (idxList == -1) return;
        cout << "Nazwisko: "; getline(cin, nazw);
        tablicaList[idxList].usunOsobeZListy(nazw);
    }

    void zmienDaneOsoby() {
        string nazw;
        cout << "Nazwisko osoby до edycji: "; getline(cin, nazw);
        int idxOs = znajdzOsobeWbazie(nazw);
        if (idxOs == -1) return;
        string nN; int nW;
        cout << "Nowe nazwisko: "; getline(cin, nN); tabOsob[idxOs].setNazwisko(nN);
        cout << "Nowy wzrost: "; cin >> nW; cin.ignore(); tabOsob[idxOs].setWzrost(nW);
    }

    void wyswietlWszystko() {
        for(int i=0; i<iloscList; i++) {
            tablicaList[i].wyswietlTabelarycznie();
        }
    }

public:
    InterfejsUzytkownika(Osoba* tO, int mO, ListaObecnosci* tL, int mL) {
        tabOsob = tO; maxOsob = mO; tablicaList = tL; maxList = mL;
        iloscOsob = 0; iloscList = 0;
    }

    void petla() {
        int wybor;
        do {
            cout << "\n========== MENU ==========\n";
            cout << "0. Dodaj osobe do bazy\n1. Przypisz osobe do listy\n2. Dodaj liste\n";
            cout << "3. Ustaw obecnosc\n4. Usun osobe z listy\n5. Zmien dane osoby\n";
            cout << "6. Wyswietl wszystkie listy\n7. Zakoncz\nWybierz: ";
            cin >> wybor; cin.ignore();
            switch (wybor) {
                case 0: dodajOsobe(); break;
                case 1: przypiszOsobeDoListy(); break;
                case 2: dodajListe(); break;
                case 3: ustawObecnosc(); break;
                case 4: usunOsobeZListy(); break;
                case 5: zmienDaneOsoby(); break;
                case 6: wyswietlWszystko(); break;
            }
        } while (wybor != 7);
    }
};

int main() {
    Osoba bOsob[50];
    ListaObecnosci bList[5];
    InterfejsUzytkownika ui(bOsob, 50, bList, 5);
    ui.petla();
    return 0;
}