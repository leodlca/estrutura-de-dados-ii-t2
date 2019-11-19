cv: main.o cv.o avl.o hashmap.o listaord.o
	gcc -o cv main.o cv.o avl.o hashmap.o listaord.o -lm

cv.o: cv.c cv.h
	gcc -c cv.c
	
avl.o: avl.c avl.h
	gcc -c avl.c

hashmap.o: hashmap.c hashmap.h
	gcc -c hashmap.c

listaord.o: listaord.c listaord.h
	gcc -c listaord.c
	
main.o: main.c cv.h
	gcc -c main.c
