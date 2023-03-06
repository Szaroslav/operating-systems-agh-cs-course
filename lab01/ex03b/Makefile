CC = gcc -Wall

all: static shared dynamic static_o shared_o dynamic_o static_os shared_os dynamic_os

static:
	$(CC) -c count.c
	ar rcs count.a count.o
	$(CC) -c main.c
	$(CC) main.o count.o -o main
	./main < test_cmds.txt > results_static_O0.txt

shared:
	$(CC) -fPIC -c count.c -o count_shared.o
	$(CC) -shared count_shared.o -o libcount_shared.so
	$(CC) -c main.c -o main_shared.o
	$(CC) main_shared.o -L. -Wl,-rpath=. -lcount_shared -o main_shared
	./main_shared < test_cmds.txt > results_shared_O0.txt

dynamic:
	$(CC) -fPIC -c count.c -o count_dynamic.o
	$(CC) -shared count_dynamic.o -o libcount_dynamic.so
	$(CC) -c main.c -o main_dynamic.o 
	$(CC) main_dynamic.o -L. -Wl,-rpath=. -lcount_dynamic -o main_dynamic
	./main_dynamic < test_cmds.txt > results_dynamic_O0.txt

static_o:
	$(CC) -c count.c
	ar rcs count.a count.o
	$(CC) -c main.c
	$(CC) main.o count.o -o main
	./main < test_cmds.txt > results_static_O.txt

shared_o:
	$(CC) -fPIC -c count.c -o count_shared.o
	$(CC) -shared count_shared.o -o libcount_shared.so
	$(CC) -c main.c -o main_shared.o
	$(CC) main_shared.o -L. -Wl,-rpath=. -lcount_shared -o main_shared
	./main_shared < test_cmds.txt > results_shared_O.txt

dynamic_o:
	$(CC) -fPIC -c count.c -o count_dynamic.o
	$(CC) -shared count_dynamic.o -o libcount_dynamic.so
	$(CC) -c main.c -o main_dynamic.o 
	$(CC) main_dynamic.o -L. -Wl,-rpath=. -lcount_dynamic -o main_dynamic
	./main_dynamic < test_cmds.txt > results_dynamic_O.txt

static_os:
	$(CC) -c count.c
	ar rcs count.a count.o
	$(CC) -c main.c
	$(CC) main.o count.o -o main
	./main < test_cmds.txt > results_static_Os.txt

shared_os:
	$(CC) -fPIC -c count.c -o count_shared.o
	$(CC) -shared count_shared.o -o libcount_shared.so
	$(CC) -c main.c -o main_shared.o
	$(CC) main_shared.o -L. -Wl,-rpath=. -lcount_shared -o main_shared
	./main_shared < test_cmds.txt > results_shared_Os.txt

dynamic_os:
	$(CC) -fPIC -c count.c -o count_dynamic.o
	$(CC) -shared count_dynamic.o -o libcount_dynamic.so
	$(CC) -c main.c -o main_dynamic.o 
	$(CC) main_dynamic.o -L. -Wl,-rpath=. -lcount_dynamic -o main_dynamic
	./main_dynamic < test_cmds.txt > results_dynamic_Os.txt

clean:
	rm -f *.o
	rm -f *.so*
	rm -f *.a
	rm -f results*.txt