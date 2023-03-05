lib.a:
	gcc -c lib.c
	ar rcs lib.a lib.o

lib.so:
	gcc -c -fPIC lib.c
	gcc -shared -Wl,-soname,liblib.so.1 -o lib.so lib.o -lc

clean:
	rm -f *.o