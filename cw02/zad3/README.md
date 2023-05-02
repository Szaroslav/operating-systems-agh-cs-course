# System plików, operacje na plikach

## Zadanie 3 (25%)
Napisz program, który będzie przeglądał bieżący katalog, korzystając z funkcji `opendir()`, `readdir()` i `stat()`. Dla każdego znalezionego pliku, który nie jest katalogiem, czyli `!S_ISDIR(bufor_stat.st_mode)`, należy wypisać rozmiar i nazwę pliku. Ponadto na koniec należy wypisać sumaryczny rozmiar wszystkich plików. Nie należy przeglądać podkatalogów! Sumaryczny rozmiar plików należy przechowywać w zmiennej typu `long long` i wypisywać ją przez format `%lld`.

Działanie programu porównaj z działaniem polecenia:
```bash
wc --bytes *
```