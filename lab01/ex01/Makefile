CC = gcc -Wall

static:
	make clean
	$(CC) -c count.c
	ar rcs count.a count.o

shared:
	make clean
	$(CC) -shared -o libcount.so -fPIC count.c

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so