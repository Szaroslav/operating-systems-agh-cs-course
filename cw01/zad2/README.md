# Zarządzanie pamięcią, biblioteki, pomiar czasu 

## Zadanie 2. Program korzystający z biblioteki (25%)

Napisz program testujący działanie funkcji z biblioteki z zadania 1.

Program powinien udostępniać interfejs typu __REPL__, tj. zczytywać komendy użytkownika ze standardowego wejścia linia po linii (`fgets()`).

Program powinien udostępniać następujące komendy:

1. `init size` — stworzenie tablicy o rozmiarze size (`int`)
2. `count file` — zliczenie słów i linii w pliku file zapis wyniku w tablicy
3. `show index` – wyświetlenie zawartości tablicy o indeksie index 
4. `delete index index` — usunięcie z tablicy bloków o indeksie index
5. `destroy` – usunięcie z pamięci tablicy z pkt. 1

Po wykonaniu każdej z operacji program powinien wypisać na standardowe wyjście czas wykonania tej operacji: rzeczywisty, użytkownika i systemowy.

Przygotuj wpis w pliku Makefile kompilujący program w trzech wariantach:

1. Z wykorzystaniem biblioteki statycznej
2. Z wykorzystaniem bilbioteki dzielonej (dynamiczne ładowanie podczas uruchamiania programu)
3. Z wykorzystaniem biblioteki ładowanej dynamicznie (`dlopen()`)