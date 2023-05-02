# Zarządzanie pamięcią, biblioteki, pomiar czasu 

## Zadanie 1. Alokacja tablicy ze wskaźnikami na bloki pamięci zawierające znaki (25%)

Zaprojektuj i przygotuj zestaw funkcji (bibliotekę) do zarządzania tablicą bloków, w których zapisywane są rezultaty operacji zliczania lini, słów i znaków (poleceniem `wc`) w plikach przekazywanych jako odpowiedni parametr.

Poniżej, jeżeli mowa o zliczaniu ilośći słów, chodzi o wykonanie programu `wc` w trybie domyślnym.

Interfejs biblioteki powinien obejmować 5 funkcji realizujących następujące zadania:

1. Utworzenie i zwrócenie struktury zawierającej: 
    - Zainicializowaną zerami (`calloc()`) tablicę wskaźników w której będą przechowywane wskaźniki na bloki pamięci.
    - Rozmiar tablicy, tj. maksymalna ilość bloków jakie można zapisać.
    - Aktualny rozmiar, tj. ilość zapisanych bloków.
2. Przeprowadzenie procedury zliczania ilości linii i słów dla podanego pliku:
    - Procedura przyjmuje strukturę z pkt.1 oraz nazwę pliku.
    - Uruchomienie (`system()`) programu wc do zliczenia lini, słów i znaków dla zadanego pliku i przesłanie wyniku do pliku tymczasowego w katalogu `/tmp`. 
    - Zarezerwowanie bloku pamięci (`calloc()`) o rozmiarze odpowiadającym rzeczywistemu rozmiarowi danych znajdujących się w buforze tymczasowym i przeniesienie tych danych do nowo zaalokowanego bloku pamięci.
    - Inkrementację licznika ilości zapisanych bloków.
    - Usunięcie pliku tymczasowego.
3. Zwrócenie zawartości bloku o zadanym indeksie. Procedura przyjmuje strukturę z pkt.1
4. Usunięcie z pamięci bloku o zadanym indeksie. Procedura przyjmuje strukturę z pkt.1
5. Zwolnienie pamięci tablicy wskaźników.


Przygotuj plik `Makefile`, zawierający polecenia kompilujące pliki źródłowe biblioteki oraz tworzące biblioteki w dwóch wersjach: statyczną i współdzieloną.