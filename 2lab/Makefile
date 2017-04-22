all: bstree1 bstree2 hashtab1 hashtab2

bstree1: bstree1.o bstree.o
	gcc -o bin/bstree1 build/bstree1.o build/bstree.o

bstree2: bstree2.o bstree.o
	gcc -o bin/bstree2 build/bstree2.o build/bstree.o

bstree1.o: src/bstree1.c
	gcc -o build/bstree1.o -c src/bstree1.c

bstree2.o: src/bstree2.c
	gcc -o build/bstree2.o -c src/bstree2.c

hashtab1: hashtab1.o hashtab.o
	gcc -o bin/hashtab1 build/hashtab1.o build/hashtab.o

hashtab2: hashtab2.o hashtab.o
	gcc -o bin/hashtab2 build/hashtab2.o build/hashtab.o

hashtab1.o: src/hashtab1.c
	gcc -o build/hashtab1.o -c src/hashtab1.c

hashtab2.o: src/hashtab2.c
	gcc -o build/hashtab2.o -c src/hashtab2.c

bstree.o: src/bstree.c
	gcc -o build/bstree.o -c src/bstree.c

hashtab.o: src/hashtab.c
	gcc -o build/hashtab.o -c src/hashtab.c

clean:
	rm -rf build/* bin/*
