# Wątki

W archiwum załączonym do tego zadania znajdziesz implementację gry w życie Conway-a. Na podstawie tego kodu wykonaj poniższe zadania:

1. (70%) Napisz współbieżną wersję gry w życie. Utwórz jeden wątek dla każdej komórki planszy. Każdy z utworzonych wątków powinien obliczać stan swojej przypisanej komórki w następnym kroku czasowym. Wątek główny powinien zajmować się tylko zlecaniem prac i wyświetlaniem wyników. Wątki powinny być tworzone tylko raz na początku programu i powinny wykonywać swoją pracę raz na iterację. (_sugestia rozwiązania:_ `pause()` _i_ `pthread_kill()`).
2. (30%) Przygotuj zmodyfikowaną wersję programu z punktu __1.__, gdzie ilość wątków jest ograniczona i podana z góry jako parametr wywołania programu. Rozdziel prace pomiędzy wątkami maksymalnie równomiernie.

Do skompilowania gry potrzebna jest biblioteka ncurses. W niektórych dystrybucjach Linuxa trzeba zainstalować nagłówki tej biblioteki. Na przykład:
```bash
apt install ncurses-devel
```

Gra wykorzystuje dwie tablice dla obecnego i następnego kroku czasowego. Każdy wątek zapisuje dane tylko do jednej komórki tablicy następnego kroku, a zatem dostęp do tych tablic nie musi być synchronizowany. 

Pomiędzy wyświetleniami planszy program czeka 0,5 sekundy na wykonanie obliczeń. W tym zadaniu ignorujemy możliwość nieskończenia obliczeń w wyznaczonym czasie, tj. żadna dodatkowa synchronizacja wątków nie jest wymagana.

_Szablon zadania znajduje się w tym katalogu:_
- _life.tar.gz_
- _life.zip_
