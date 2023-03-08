CC = gcc -Wall

static: clean
	$(CC) -c count.c
	ar rcs count.a count.o
	$(CC) -c main.c
	$(CC) main.o count.o -o main

shared: clean
	$(CC) -fPIC -c count.c -o count_shared.o
	$(CC) -shared count_shared.o -o libcount_shared.so
	$(CC) -c main.c -o main_shared.o
	$(CC) main_shared.o -L. -Wl,-rpath=. -lcount_shared -o main_shared

dynamic: clean
	$(CC) -fPIC -c count.c -o count_dynamic.o
	$(CC) -shared count_dynamic.o -o libcount_dynamic.so
	$(CC) main.c -o main_dynamic -ldl -DDYNAMIC

clean:
	rm -f *.o
	rm -f *.so*
	rm -f *.a
