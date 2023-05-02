# System plików, operacje na plikach

W __zadaniu 1__ proszę skorzystać z obu wariantów implementacji:

- `lib` - przy użyciu funkcji biblioteki C: `fread()` i `fwrite()`
- `sys` - przy użyciu funkcji systemowych: `read()` i `write()`

Dla obu wariantów implementacji należy przeprowadzić pomiar czasu wykonywania. Wyniki należy przedstawić w formie pliku `pomiar_zad_1.txt`.


## Zadanie 1 (25%)
Napisz program, który przyjmuje 4 argumenty wiersza poleceń 

1. znak `ASCII`, który należy znaleźć w pliku wejściowym;
2. znak `ASCII`, na który należy zamienić wszystkie wystąpienia pierwszego argumentu;
3. nazwa pliku wejściowego, w którym należy znaleźć pierwszy argument;
4. nazwa pliku wyjściowego, do którego należy zapisać zawartość pliku wejściowego z zamienionym znakami `argv[1]` na `argv[2]`.

Porównaj wyjście programu z wynikiem polecenia `tr`:

```bash
./zamien [znak1] [znak2] plik_wejściowy plik_wyjściowy ; tr [znak1] [znak2] < plik_wejściowy > tmp ; diff -s tmp plik_wyjściowy
```