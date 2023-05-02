# Tworzenie procesów. Środowisko procesu, sterowanie procesami.

## Zadanie 3 (60%)

Napisz program, którzy przyjmuje dwa argumenty:

- `argv[1]` — ścieżkę katalogu;
- `argv[2]` — łańcuch znaków nie dłuższy niż 255 bajtów.

Program ma rekurencyjnie przeglądać katalog `argv[1]` i drzewo jego podkatalogów, tworząc drzewo procesów tego samego kształtu, co drzewo katalogów, po jednym procesie dla każdego katalogu. Każdy proces powinien przeglądać wszystkie pliki w katalogu.
- Jeśli przeglądany plik jest katalogiem, to proces powinien utworzyć proces potomny dla tego katalogu poprzez rekurencyjne wywołanie funkcji przeglądającej katalog.
- Jeśli przeglądany plik nie jest katalogiem, można go otworzyć do odczytu i jego treść pliku zaczyna się od łańcucha znaków `argv[2]`, to proces ma na standardowym wyjściu wypisać w jednym wierszu: ścieżkę pliku (nie nazwę pliku) i swój identyfikator.

__Wskazówki__:
- Żeby sprawdzić, czy plik jest katalogiem, proszę użyć funkcji systemowej `fstat` lub `stat`.
- Proszę napisać program tak, żeby sprawdzał przy wywołaniu każdej funkcji systemowej, czy zwróciła ona błąd. Jeśli błąd uniemożliwia dalsze działanie programu, powinien on wypisać rodzaj błędu, korzystając z funkcji `perror`, i zakończyć działanie.
- Przy wywołaniach rekurencyjnych proszę pomijać katalogi `.` i `..`, ale nie pomijać pozostałych katalogów ani plików zwykłych, których nazwa zaczyna się od kropki.
- Procesy nie muszą czekać na zakończenie swoich procesów potomnych.
- Długość ścieżki do dowolnego pliku, wraz z końcowym znakiem `\0`, nie przekracza stałej `PATH_MAX`, zdefiniowanej w pliku nagłówkowym `limits.h`.
- Proszę przetestować program, podając jako `argv[1]` między innymi ścieżki `.` `..` `../..` `~` `/root`, a jako `argv[2]` między innymi łańcuchy znaków `\#include asdf zadanie`.