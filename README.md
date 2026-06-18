# Lista obecności

Program konsolowy w C++ do zarządzania listami obecności studentów i pracowników.

## Opis projektu

Program został napisany w języku C++ i wykorzystuje podstawowe elementy programowania obiektowego.

Program umożliwia:
- dodawanie studentów i pracowników do bazy,
- tworzenie kilku list obecności,
- przypisywanie osób do wybranej listy,
- ustawianie obecności,
- usuwanie osoby z listy,
- edycję danych osoby,
- wyświetlanie list w konsoli,
- eksport listy do pliku .txt,
- eksport listy do pliku .csv.

## Struktura klas

- `Osoba` — klasa bazowa dla wszystkich osób w programie.
- `Student` — przechowuje dane studenta, np. imię, nazwisko i numer indeksu.
- `Pracownik` — przechowuje dane pracownika, np. imię, nazwisko i ID pracownika.
- `ListaObecnosci` — przechowuje osoby dodane do listy oraz informację, czy są obecne.
- `InterfejsUzytkownika` — obsługuje menu programu i wybory użytkownika.
- `EksporterTXT` — zapisuje listę obecności do pliku tekstowego.
- `EksporterCSV` — zapisuje listę obecności do pliku CSV.
- `Serializable` — pozwala zamienić obiekt na tekst.
- `Eksportowalny` — pozwala przygotować dane do eksportu.
- `Eksporter` — klasa bazowa dla różnych sposobów eksportu danych.

## Struktura repozytorium
- main — końcowa wersja projektu.
- lab1 — pierwsza wersja programu z podstawową listą obecności.
- lab2 — wersja z klasami i walidacją danych.
- lab3 — wersja z bazą osób i wieloma listami obecności.
- lab4 — wersja z polimorfizmem.
- lab5 — wersja z interfejsem Serializable.
- lab6 — wersja z zapisem listy do pliku.

# 286260-Paradygmaty-Programowania-Obiektowego
ISA, Nazar Horodynskyi, 286260
