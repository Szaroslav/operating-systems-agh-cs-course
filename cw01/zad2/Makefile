CC = gcc -Wall

static:
	make clean
	$(CC) -c count.c
	ar rcs count.a count.o
	$(CC) -c main.c
	$(CC) main.o count.o -o main

shared:
	make clean
	$(CC) -fPIC -c count.c -o count_shared.o
	$(CC) -shared count_shared.o -o libcount_shared.so
	$(CC) -c main.c -o main_shared.o
	$(CC) main_shared.o -L. -Wl,-rpath=. -lcount_shared -o main_shared

dynamic:
	make clean
	$(CC) -fPIC -c count.c -o count_dynamic.o
	$(CC) -shared count_dynamic.o -o libcount_dynamic.so
	$(CC) -c -DDYNAMIC main.c -o main_dynamic.o
	$(CC) main_dynamic.o -L. -Wl,-rpath=. -lcount_dynamic -o main_dynamic

clean:
	rm -f *.o
	rm -f *.so*
	rm -f *.a