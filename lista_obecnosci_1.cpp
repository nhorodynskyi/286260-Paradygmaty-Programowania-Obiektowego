#include <iostream>
#include <string>
using namespace std;

int n = 0;
string *tabNazwisko = nullptr;
string *tabImie = nullptr;
string *tabIndeks = nullptr;
bool *tabObecnosc = nullptr;

int szukaj(string nazwisko) {
    for (int i = 0; i < n; i++)
        if (tabNazwisko[i] == nazwisko) return i;
    return -1;
}

void dodaj() {
    string *nowenazwisko = new string[n + 1];
    string *noweimie = new string[n + 1];
    string *nowyindeks = new string[n + 1];
    bool *nowaobecnosc = new bool[n + 1];

    for (int i = 0; i < n; i++) {
        nowenazwisko[i] = tabNazwisko[i];
        noweimie[i] = tabImie[i];
        nowyindeks[i] = tabIndeks[i];
        nowaobecnosc[i] = tabObecnosc[i];
    }

    string noweNazwisko, noweImie, nowyIndeks;
    int obecnosc;
    cout << "Nazwisko: "; getline(cin, noweNazwisko);
    cout << "Imie: "; getline(cin, noweImie);
    cout << "Nr indeksu: "; getline(cin, nowyIndeks);
    cout << "Obecnosc (1/0): "; cin >> obecnosc; cin.ignore();

    nowenazwisko[n] = noweNazwisko;
    noweimie[n] = noweImie;
    nowyindeks[n] = nowyIndeks;
    nowaobecnosc[n] = (obecnosc == 1);

    delete[] tabNazwisko;
    delete[] tabImie;
    delete[] tabIndeks;
    delete[] tabObecnosc;

    tabNazwisko = nowenazwisko;
    tabImie = noweimie;
    tabIndeks = nowyindeks;
    tabObecnosc = nowaobecnosc;

    n++;
}

void zmienObecnosc() {
    string nazwisko;
    int ob;

    cout << "Nazwisko: "; getline(cin, nazwisko);
    cout << "Obecnosc (1/0): "; cin >> ob; cin.ignore();

    int index = szukaj(nazwisko);
    if (index == -1) {
        cout << "Nie znaleziono!" << endl;
        return;
    }

    tabObecnosc[index] = (ob == 1);
}

void drukuj() {
    if (n == 0) {
        return;
    }

    cout << "\nNR INDEKSU\tIMIE\t\tNAZWISKO\tOBECNOSC" << endl;
    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < n; i++) {
        cout << tabIndeks[i] << "\t\t"
             << tabImie[i] << "\t\t"
             << tabNazwisko[i] << "\t\t"
             << (tabObecnosc[i] ? "1" : "0") << endl;
    }
}

void edytuj() {
    string nazwisko;
    cout << "Nazwisko: "; getline(cin, nazwisko);

    int index = szukaj(nazwisko);
    if (index == -1) {
        cout << "Nie znaleziono!" << endl;
        return;
    }

    int wybor;
    cout << "1.Nazwisko  2.Imie  3.Nr indeksu  4.Obecnosc\nWybierz: ";
    cin >> wybor; cin.ignore();

    if (wybor == 1) {
        cout << "Nowe nazwisko: ";
        getline(cin, tabNazwisko[index]);
    }
    else if (wybor == 2) {
        cout << "Nowe imie: ";
        getline(cin, tabImie[index]);
    }
    else if (wybor == 3) {
        cout << "Nowy nr indeksu: ";
        getline(cin, tabIndeks[index]);
    }
    else if (wybor == 4) {
        int ob;
        cout << "Obecnosc (1/0): ";
        cin >> ob; cin.ignore();
        tabObecnosc[index] = (ob == 1);
    }

}

void usun() {
    string nazwisko;
    cout << "Nazwisko: "; getline(cin, nazwisko);

    int idx = szukaj(nazwisko);
    if (idx == -1) {
        cout << "Nie znaleziono!" << endl;
        return;
    }

    string *nowenazwisko = nullptr;
    string *noweimie = nullptr;
    string *nowyindeks = nullptr;
    bool *nowaobecnosc = nullptr;

    if (n - 1 > 0) {
        nowenazwisko = new string[n - 1];
        noweimie = new string[n - 1];
        nowyindeks = new string[n - 1];
        nowaobecnosc = new bool  [n - 1];

        int j = 0;
        for (int i = 0; i < n; i++) {
            if (i == idx) continue;
            nowenazwisko[j] = tabNazwisko[i];
            noweimie[j] = tabImie[i];
            nowyindeks[j] = tabIndeks[i];
            nowaobecnosc[j] = tabObecnosc[i];
            j++;
        }
    }

    delete[] tabNazwisko;
    delete[] tabImie;
    delete[] tabIndeks;
    delete[] tabObecnosc;

    tabNazwisko = nowenazwisko;
    tabImie = noweimie;
    tabIndeks = nowyindeks;
    tabObecnosc = nowaobecnosc;

    n--;
}

int main() {
    int wybor;
    do {
        cout << "\n1.Dodaj  2.Obecnosc  3.Lista  4.Edytuj  5.Usun  0.Wyjdz\nWybierz: ";
        cin >> wybor; cin.ignore();

        if (wybor == 1) dodaj();
        else if (wybor == 2) zmienObecnosc();
        else if (wybor == 3) drukuj();
        else if (wybor == 4) edytuj();
        else if (wybor == 5) usun();

    } while (wybor != 0);

    delete[] tabNazwisko;
    delete[] tabImie;
    delete[] tabIndeks;
    delete[] tabObecnosc;

    return 0;
}