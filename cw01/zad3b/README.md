# Zarządzanie pamięcią, biblioteki, pomiar czasu 

## Zadanie 3. Testy i pomiary (50%)

__A)__ (25%) W pliku `Makefile` stwórz wpisy przeprowadzające test programu. Test powinien uruchomić program, podać na standardowe wejście poniższe komendy, a wyniki zapisać do pliku tekstowego `results_[suffix].txt`:

1. Tworząca tablicę.
2. Zliczające słowa w każdym z plików źródłowych niniejszego zadania.
3. Wypisujące rezultaty zliczania.
4. Usuwające wszystkie wpisy po kolei.
5. Usuwający tablicę z pamięci.

Utwórz wpisy w `Makefile` uruchamiający testy z pkt. __A__ w trzech wariantach programu

1. Z wykorzystaniem biblioteki statycznej
2. Z wykorzystaniem bilbioteki dzielonej (dynamiczne ładowanie podczas uruchamiania programu)
3. Z wykorzystaniem biblioteki ładowanej dynamicznie (`dlopen()`)

Wyniki pomiarów zbierz w plikach `results_[suffix].txt` (gdzie `suffix` to: `static`, `shared`, `dynamic`).
Otrzymane wyniki krótko skomentuj. Wygenerowane pliki z raportami załącz jako element rozwiązania w pliku `report.txt`.

__B)__ (25%) Rozszerz plik `Makefile` z punktu __3A__ dodając możliwość skompilowania programu na trzech różnych poziomach optymalizacji — `-O0`…`-Os`. Przeprowadź ponownie pomiary, kompilując i uruchamiając program dla różnych poziomów optymalizacji. Wyniki pomiarów dodaj do pliku `results_[suffix1]_[suffix2].txt`.
Otrzymane wyniki krótko skomentuj. Wygenerowane pliki z raportami załącz jako element rozwiązania w pliku `report.txt`.