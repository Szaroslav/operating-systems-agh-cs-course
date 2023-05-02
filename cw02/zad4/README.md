# System plików, operacje na plikach

## Zadanie 4 (25%)
Napisz program, który będzie przeglądał katalog podany jako argument wywołania i jego podkatalogi, korzystając z funkcji `ftw()` (uproszczonej wersji funkcji `nftw()`). Dla każdego znalezionego pliku, który nie jest katalogiem, czyli `!S_ISDIR(bufor_stat.st_mode)`, należy wypisać rozmiar i nazwę pliku. Ponadto na koniec należy wypisać sumaryczny rozmiar wszystkich plików. Dobra wiadomość: funkcja `ftw()` przyjmuje ścieżki i bezwzględne, i względne.

Działanie programu porównaj z działaniem polecenia:
```bash
find nazwa_katalogu | xargs wc --bytes
```