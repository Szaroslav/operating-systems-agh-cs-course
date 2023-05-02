# System plików, operacje na plikach

W __zadaniu 2__ można wybrać do zaimplementowania tylko jeden wariant:

- albo `fopen()`, `fseek()`, `fread()`, `fwrite()`, `fclose()`;
- albo `open()`, `lseek()`, `read()`, `write()`, `close()`.

Wybrany wariant należy opracować na dwa sposoby:

1. Czytanie po 1 znaku.
2. Czytanie bloków po 1024 znaki (plik wynikowy powinien być identyczny jak w wariancie 1.)

Dla obu sposobów implementacji należy przeprowadzić pomiar czasu wykonywania. Wyniki należy przedstawić w formie pliku `pomiar_zad_2.txt`.


## Zadanie 2 (25%)
Napisz program, który kopiuje zawartość jednego pliku do drugiego, odwróconą bajt po bajcie .

__Wskazówki__: Wywołania w rodzaju `fseek(infile, +1024, SEEK_END)` lub `lseek(in, +1024, SEEK_END)` są zupełnie legalne i nie powodują żadnych skutków ubocznych. Aby po przeczytaniu bloku znaków cofnąć się na początek poprzedniego bloku, należy jako drugi argument funkcji `fseek(..., ..., SEEK_CUR)` lub `lseek(..., ..., SEEK_CUR)` podać podwojoną długość bloku ze znakiem minus.

Działanie programu należy zweryfikować następująco:
1. Odwrócić krótki plik tekstowy, podejrzeć wynik, sprawdzić szczególnie początkowe i końcowe znaki.
2. 
    ```bash
    ./reverse plik_binarny tmp1 ; ./reverse tmp1 tmp2 ; diff -s tmp2 plik_binarny
    ```
3. Można też porównać (`diff -s`) wynik działania programu i wynik polecenia:
    ```bash
    tac < plik_wejściowy | rev > plik_wyjściowy
    ```