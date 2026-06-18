#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <map>
#include <fstream>
using namespace std;

class Eksportowalny {
public:
    virtual ~Eksportowalny() = default;
    virtual map<string, string> eksportuj() const = 0;
};

class Serializable {
public:
    virtual ~Serializable() = default;
    virtual string serialize() const = 0;
};

void drukuj(const Serializable* obj) {
    if (obj != nullptr) cout << obj->serialize() << endl;
}

class Osoba : public Serializable {
protected:
    string nazwisko, imie, dataUrodzenia;
    int wzrost;

public:
    Osoba() : nazwisko(""), imie(""), dataUrodzenia(""), wzrost(0) {}
    virtual ~Osoba() = default;

    bool tylkoLitery(const string& txt) {
        if (txt.empty()) return false;
        for (char c : txt)
            if (!isalpha((unsigned char)c) && !isspace((unsigned char)c))
                return false;
        return true;
    }

    bool prawidlowaData(const string& data) {
        if (data.size() != 10 || data[2] != '.' || data[5] != '.') return false;
        for (int i = 0; i < 10; i++)
            if (i != 2 && i != 5 && !isdigit((unsigned char)data[i]))
                return false;
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
    string getDataUrodzenia() const { return dataUrodzenia; }
    int getWzrost() const { return wzrost; }

    virtual string getTyp() const = 0;
    virtual string getIdentyfikator() const = 0;

    virtual void drukuj() const {
        cout << imie << " " << nazwisko
             << " (" << dataUrodzenia << ", " << wzrost << "cm)";
    }
};

class Student : public Osoba, public Eksportowalny {
private:
    string indeks;

public:
    Student() : Osoba(), indeks("") {}

    bool prawidlowyIndeks(const string& txt) {
        if (txt.size() != 6) return false;
        for (char c : txt)
            if (!isdigit((unsigned char)c)) return false;
        return true;
    }

    bool setIndeks(string wartosc) {
        if (prawidlowyIndeks(wartosc)) {
            indeks = wartosc;
            return true;
        }
        return false;
    }

    string getIndeks() const { return indeks; }
    string getTyp() const override { return "Student"; }
    string getIdentyfikator() const override { return indeks; }

    string serialize() const override {
        return getTyp() + ";" + indeks + ";" + imie + ";" +
               nazwisko + ";" + dataUrodzenia + ";" + to_string(wzrost);
    }

    void drukuj() const override {
        Osoba::drukuj();
        cout << " | Indeks: " << indeks;
    }
    map<string, string> eksportuj() const override {
        map<string, string> dane;
        dane["Typ"] = "Student";
        dane["Indeks"] = indeks;
        dane["Imie"] = imie;
        dane["Nazwisko"] = nazwisko;
        dane["DataUrodzenia"] = dataUrodzenia;
        dane["Wzrost"] = to_string(wzrost);
        return dane;
    }

};

class Pracownik : public Osoba, public Eksportowalny {
private:
    int id_pracownika;

public:
    Pracownik() : Osoba(), id_pracownika(0) {}

    bool setIdPracownika(int id) {
        if (id >= 1) {
            id_pracownika = id;
            return true;
        }
        cout << "Blad: ID musi byc wieksze od 0!" << endl;
        return false;
    }

    int getIdPracownika() const { return id_pracownika; }
    string getTyp() const override { return "Pracownik"; }
    string getIdentyfikator() const override { return to_string(id_pracownika); }

    string serialize() const override {
        return getTyp() + ";" + to_string(id_pracownika) + ";" + imie + ";" +
               nazwisko + ";" + dataUrodzenia + ";" + to_string(wzrost);
    }

    void drukuj() const override {
        Osoba::drukuj();
        cout << " | ID: " << id_pracownika;
    }
    map<string, string> eksportuj() const override {
        map<string, string> dane;
        dane["Typ"] = "Pracownik";
        dane["ID"] = to_string(id_pracownika);
        dane["Imie"] = imie;
        dane["Nazwisko"] = nazwisko;
        dane["DataUrodzenia"] = dataUrodzenia;
        dane["Wzrost"] = to_string(wzrost);
        return dane;
    }
};

class ListaObecnosci : public Serializable, public Eksportowalny {
private:
    string nazwaListy;
    Osoba* tabOsob[10];
    bool tabObecnosc[10];
    int iloscNaLiscie;

public:
    ListaObecnosci() : nazwaListy("Nieznana"), iloscNaLiscie(0) {
        for (int i = 0; i < 10; i++) {
            tabOsob[i] = nullptr;
            tabObecnosc[i] = false;
        }
    }

    void setNazwa(string nazwa) { nazwaListy = nazwa; }
    string getNazwa() const { return nazwaListy; }

    bool dodajOsobeDoListy(Osoba* osoba) {
        if (iloscNaLiscie >= 10) return false;

        for (int i = 0; i < iloscNaLiscie; i++)
            if (tabOsob[i] == osoba) return false;

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

    string serialize() const override {
        return "ListaObecnosci;" + nazwaListy + ";" + to_string(iloscNaLiscie);
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

        cout << PURPLE << "+-----------+-----------+------------+--------------+----------------+--------+----------+\n" << RESET;
        cout << CYAN   << "| Typ       | ID/Indeks | Imie       | Nazwisko     | Data urodzenia | Wzrost | Obecnosc |\n" << RESET;
        cout << PURPLE << "+-----------+-----------+------------+--------------+----------------+--------+----------+\n" << RESET;

        for (int i = 0; i < iloscNaLiscie; i++) {
            if (tabOsob[i] == nullptr) continue;

            cout << GREEN
                 << "| " << setw(9) << left << tabOsob[i]->getTyp()
                 << " | " << setw(9) << left << tabOsob[i]->getIdentyfikator()
                 << " | " << setw(10) << left << tabOsob[i]->getImie()
                 << " | " << setw(12) << left << tabOsob[i]->getNazwisko()
                 << " | " << setw(14) << left << tabOsob[i]->getDataUrodzenia()
                 << " | " << setw(6) << right << tabOsob[i]->getWzrost()
                 << " | " << setw(8) << left << (tabObecnosc[i] ? "1" : "0") << " |\n"
                 << RESET;
        }

        cout << PURPLE << "+-----------+-----------+------------+--------------+----------------+--------+----------+\n" << RESET;
    }

    void drukuj(const string& nazwaPliku) const {
        ofstream plik(nazwaPliku);

        if (!plik.is_open()) {
            cout << "Blad otwarcia pliku!" << endl;
            return;
        }

        plik << "\n--- LISTA: " << nazwaListy << " ---\n";

        if (iloscNaLiscie == 0) {
            plik << "Brak osob na tej liscie!" << endl;
            cout << "Lista zapisana do pliku: " << nazwaPliku << endl;
            return;
        }

        plik << "+-----------+-----------+------------+--------------+----------------+--------+----------+\n";
        plik << "| Typ       | ID/Indeks | Imie       | Nazwisko     | Data urodzenia | Wzrost | Obecnosc |\n";
        plik << "+-----------+-----------+------------+--------------+----------------+--------+----------+\n";

        for (int i = 0; i < iloscNaLiscie; i++) {
            if (tabOsob[i] == nullptr) continue;

            plik << "| " << setw(9) << left << tabOsob[i]->getTyp()
                 << " | " << setw(9) << left << tabOsob[i]->getIdentyfikator()
                 << " | " << setw(10) << left << tabOsob[i]->getImie()
                 << " | " << setw(12) << left << tabOsob[i]->getNazwisko()
                 << " | " << setw(14) << left << tabOsob[i]->getDataUrodzenia()
                 << " | " << setw(6) << right << tabOsob[i]->getWzrost()
                 << " | " << setw(8) << left << (tabObecnosc[i] ? "1" : "0") << " |\n";
        }

        plik << "+-----------+-----------+------------+--------------+----------------+--------+----------+\n";
        cout << "Lista zapisana do pliku: " << nazwaPliku << endl;
    }

    map<string, string> eksportuj() const override {
        map<string, string> dane;
        dane["typ"] = "ListaObecnosci";
        dane["nazwa"] = nazwaListy;
        dane["ilosc"] = to_string(iloscNaLiscie);
        return dane;
    }
    int getIloscNaLiscie() const { 
        return iloscNaLiscie;
    }
    Osoba* getOsoba(int index) const {
        if (index >= 0 && index < iloscNaLiscie) {
            return tabOsob[index];
        }
        return nullptr;
    }
    bool getObecnosc(int index) const {
        if (index >= 0 && index < iloscNaLiscie) {
            return tabObecnosc[index];
        }
        return false;
    }
};

class Eksporter {
    public:
       virtual ~Eksporter() = default;

       virtual void wykonajEksport(const ListaObecnosci& lista, string nazwaPliku) const = 0;
};

class EksporterTXT : public Eksporter {
    public:
        void wykonajEksport(const ListaObecnosci& lista, string nazwaPliku) const override {
            lista.drukuj(nazwaPliku);
        }
};

class EksporterCSV : public Eksporter {
    public:
        void wykonajEksport(const ListaObecnosci& lista, string nazwaPliku) const override {
            ofstream plik(nazwaPliku);

            if (!plik.is_open()) {
                cout << "Blad otwarcia pliku!" << endl;
                return;
            }

            plik << "Typ;ID/Indeks;Imie;Nazwisko;Data urodzenia;Wzrost;Obecnosc\n";

            for (int i = 0; i < lista.getIloscNaLiscie(); i++) {
                Osoba* osoba = lista.getOsoba(i);
                if (osoba != nullptr) {
                    plik << osoba->getTyp() << ";"
                         << osoba->getIdentyfikator() << ";"
                         << osoba->getImie() << ";"
                         << osoba->getNazwisko() << ";"
                         << osoba->getDataUrodzenia() << ";"
                         << osoba->getWzrost() << ";"
                         << (lista.getObecnosc(i) ? "1" : "0") << "\n";
                }
            }

            cout << "Lista zapisana do pliku: " << nazwaPliku << endl;
        }
};
        

class InterfejsUzytkownika {
private:
    Osoba** tabOsob;
    ListaObecnosci* tablicaList;
    int maxOsob, maxList, iloscOsob, iloscList;

    int znajdzOsobeWbazie(string nazwisko) {
        for (int i = 0; i < iloscOsob; i++)
            if (tabOsob[i]->getNazwisko() == nazwisko) return i;
        return -1;
    }

    int znajdzListe(string nazwa) {
        for (int i = 0; i < iloscList; i++)
            if (tablicaList[i].getNazwa() == nazwa) return i;
        return -1;
    }

    void dodajOsobe() {
        if (iloscOsob >= maxOsob) {
            cout << "Brak miejsca w bazie!\n";
            return;
        }

        int typ;
        cout << "Kogo chcesz dodac?\n1. Student\n2. Pracownik\nWybierz: ";
        cin >> typ;
        cin.ignore();

        if (typ != 1 && typ != 2) {
            cout << "Niepoprawny wybor!\n";
            return;
        }

        string nazw, im, data;
        int wzr;

        cout << "Nazwisko: "; getline(cin, nazw);
        cout << "Imie: "; getline(cin, im);
        cout << "Data ur (dd.mm.rrrr): "; getline(cin, data);
        cout << "Wzrost: "; cin >> wzr;
        cin.ignore();

        Osoba* nowaOsoba = nullptr;

        if (typ == 1) {
            string ind;
            cout << "Indeks (6 cyfr): ";
            getline(cin, ind);

            Student* s = new Student();

            if (s->setNazwisko(nazw) && s->setImie(im) &&
                s->setDataUrodzenia(data) && s->setWzrost(wzr) &&
                s->setIndeks(ind)) {
                nowaOsoba = s;
            } else delete s;
        }

        if (typ == 2) {
            int id;
            cout << "ID pracownika (wieksze od 0): ";
            cin >> id;
            cin.ignore();

            Pracownik* p = new Pracownik();

            if (p->setNazwisko(nazw) && p->setImie(im) &&
                p->setDataUrodzenia(data) && p->setWzrost(wzr) &&
                p->setIdPracownika(id)) {
                nowaOsoba = p;
            } else delete p;
        }

        if (nowaOsoba != nullptr) {
            tabOsob[iloscOsob++] = nowaOsoba;
            cout << "Osoba dodana do bazy.\n";
        } else {
            cout << "Blad walidacji wprowadzonych danych!\n";
        }
    }

    void przypiszOsobeDoListy() {
        string nazw, nListy;

        cout << "Nazwisko osoby: ";
        getline(cin, nazw);

        int idxOs = znajdzOsobeWbazie(nazw);

        if (idxOs == -1) {
            cout << "Nie ma takiej osoby!\n";
            return;
        }

        cout << "Nazwa listy: ";
        getline(cin, nListy);

        int idxList = znajdzListe(nListy);

        if (idxList == -1) {
            cout << "Nie ma takiej listy!\n";
            return;
        }

        if (tablicaList[idxList].dodajOsobeDoListy(tabOsob[idxOs]))
            cout << "Osoba przypisana.\n";
        else
            cout << "Blad (limit lub duplikat).\n";
    }

    void dodajListe() {
        if (iloscList >= maxList) {
            cout << "Brak miejsca na listy!\n";
            return;
        }

        string nazwa;
        cout << "Podaj nazwe listy: ";
        getline(cin, nazwa);

        tablicaList[iloscList++].setNazwa(nazwa);
        cout << "Lista dodana.\n";
    }

    void ustawObecnosc() {
        string nazw, nListy;
        bool ob;

        cout << "Nazwa listy: ";
        getline(cin, nListy);

        int idxList = znajdzListe(nListy);

        if (idxList == -1) {
            cout << "Brak listy!\n";
            return;
        }

        cout << "Nazwisko: ";
        getline(cin, nazw);

        cout << "Obecny (1/0): ";
        cin >> ob;
        cin.ignore();

        if (!tablicaList[idxList].ustawObecnosc(nazw, ob))
            cout << "Nie znaleziono osoby na liscie.\n";
    }

    void usunOsobeZListy() {
        string nazw, nListy;

        cout << "Nazwa listy: ";
        getline(cin, nListy);

        int idxList = znajdzListe(nListy);
        if (idxList == -1) return;

        cout << "Nazwisko: ";
        getline(cin, nazw);

        tablicaList[idxList].usunOsobeZListy(nazw);
    }

    void zmienDaneOsoby() {
        string nazw;

        cout << "Nazwisko osoby do edycji: ";
        getline(cin, nazw);

        int idxOs = znajdzOsobeWbazie(nazw);

        if (idxOs == -1) {
            cout << "Osoba nie znaleziona.\n";
            return;
        }

        string nN;
        int nW;

        cout << "Nowe nazwisko: ";
        getline(cin, nN);
        tabOsob[idxOs]->setNazwisko(nN);

        cout << "Nowy wzrost: ";
        cin >> nW;
        cin.ignore();
        tabOsob[idxOs]->setWzrost(nW);

        cout << "Dane zaktualizowane.\n";
    }

    void wyswietlWszystko() {
        for (int i = 0; i < iloscList; i++)
            tablicaList[i].wyswietlTabelarycznie();
    }

    void zapiszListeDoPliku() {
        string nListy, nazwaPliku;

        cout << "Nazwa listy: ";
        getline(cin, nListy);

        int idxList = znajdzListe(nListy);

        if (idxList == -1) {
            cout << "Nie ma takiej listy!\n";
            return;
        }

        cout << "Wybierz format pliku:\n";
        cout << "1. TXT\n";
        cout << "2. CSV\n";
        cout << "Wybierz: ";
        int format;
        cin >> format;
        cin.ignore();

        cout << "Nazwa pliku" << (format == 2 ? ".csv" : ".txt") << ": ";
        getline(cin, nazwaPliku);

        if (format == 1) {
            if (nazwaPliku.find('.') == string::npos) nazwaPliku += ".txt";
            EksporterTXT eksportTxt;
            eksportTxt.wykonajEksport(tablicaList[idxList], nazwaPliku);
        } else if (format == 2) {
            if (nazwaPliku.find('.') == string::npos) nazwaPliku += ".csv";
            EksporterCSV eksportCsv;
            eksportCsv.wykonajEksport(tablicaList[idxList], nazwaPliku);
        } else {
            cout << "Niepoprawny format!\n";
        }
    }

public:
    InterfejsUzytkownika(Osoba** tO, int mO, ListaObecnosci* tL, int mL)
        : tabOsob(tO), tablicaList(tL),
          maxOsob(mO), maxList(mL), iloscOsob(0), iloscList(0) {}

    ~InterfejsUzytkownika() {
        for (int i = 0; i < iloscOsob; i++)
            delete tabOsob[i];
    }

    void petla() {
        int wybor;

        do {
            cout << "\n========== MENU ==========\n";
            cout << "0. Dodaj osobe do bazy\n";
            cout << "1. Przypisz osobe do listy\n";
            cout << "2. Dodaj liste\n";
            cout << "3. Ustaw obecnosc\n";
            cout << "4. Usun osobe z listy\n";
            cout << "5. Zmien dane osoby\n";
            cout << "6. Wyswietl wszystkie listy\n";
            cout << "7. Zapisz liste do pliku\n";
            cout << "8. Zakoncz\n";
            cout << "Wybierz: ";

            cin >> wybor;
            cin.ignore();

            switch (wybor) {
                case 0: dodajOsobe(); break;
                case 1: przypiszOsobeDoListy(); break;
                case 2: dodajListe(); break;
                case 3: ustawObecnosc(); break;
                case 4: usunOsobeZListy(); break;
                case 5: zmienDaneOsoby(); break;
                case 6: wyswietlWszystko(); break;
                case 7: zapiszListeDoPliku(); break;
                case 8: cout << "Koniec programu.\n"; break;
                default: cout << "Niepoprawny wybor!\n"; break;
            }

        } while (wybor != 8);
    }
};

int main() {
    Osoba* bOsob[50] = {nullptr};
    ListaObecnosci bList[5];

    InterfejsUzytkownika ui(bOsob, 50, bList, 5);
    ui.petla();

    return 0;
}