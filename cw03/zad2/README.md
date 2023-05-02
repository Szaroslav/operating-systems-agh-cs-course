# Tworzenie procesów. Środowisko procesu, sterowanie procesami.

## Zadanie 2 (20%)

Napisz program, który przyjmuje jeden argument: `argv[1]` — ścieżkę katalogu. Program ma wypisać na standardowym wyjściu swoją nazwę (bez znaku nowego wiersza), korzystając z funkcji `printf`, a następnie wykonać program `/bin/ls` z argumentem `argv[1]`, korzystając z funkcji `execl`.

Ważne: funkcje biblioteki standardowej języka C buforują dane zapisywane na wyjściu. Zawartość bufora jest wypisywana na wyjściu po każdym wierszu lub po każdych `BUFSIZ` bajtach. Ostatni bufor jest wypisywany automatycznie podczas kończenia procesu. W tym programie proces nie kończy się przed wywołaniem funkcji `execl`, a bufor, który należy do segmentu danych użytkowych procesu, jest zamazywany, zanim jego zawartość mogła zostać wypisana. Aby wymusić brak buforowania danych wyjściowych, można użyć funkcji `setbuf(stdout, NULL)`. Można też wypisać zawartość bufora tuż przed wywołaniem funkcji `execl`, używając funkcji `fflush(stdout)`.

Proszę przetestować program, podając jako `argv[1]` katalogi zawierające 0 plików, kilka plików i wiele plików.