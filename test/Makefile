all: lib1.so lib2.so a.out
	./a.out

lib1.so:  lib1.c
	gcc -fPIC -shared -o lib1.so lib1.c

lib2.so:	lib1.so
	gcc -fPIC -shared -fvisibility=default -o lib2.so lib2.c lib1.so

a.out:	lib1.so lib2.so
	cc main.c

clean:
	rm -rf lib1.so lib2.so a.out

re: clean all
