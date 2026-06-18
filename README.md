# Lista obecności 4

Program konsolowy w C++ do zarządzania listami obecności studentów i pracowników.

# Opis

Program umożliwia:
- dodawanie osób do bazy,
- wybór typu osoby: student albo pracownik,
- tworzenie kilku list obecności,
- przypisywanie osób do list,
- ustawianie obecności,
- usuwanie osoby z listy,
- edycję danych osoby,
- wyświetlanie list w formie tabeli.

W tej wersji dodano dziedziczenie i polimorfizm.

- `Osoba` — klasa bazowa abstrakcyjna,
- `Student` — klasa pochodna z numerem indeksu,
- `Pracownik` — klasa pochodna z ID pracownika,
- `ListaObecnosci` — obsługuje jedną listę obecności,
- `InterfejsUzytkownika` — odpowiada za menu programu.

# 286260-Paradygmaty-Programowania-Obiektowego
ISA, Nazar Horodynskyi, 286260
