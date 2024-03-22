all: mainLC mainH mainCP

biblioLC.o: biblioLC.c biblioLC.h
	gcc -c -o biblioLC.o biblioLC.c

entreeSortieLC.o: entreeSortieLC.c entreeSortieLC.h
	gcc -c -o entreeSortieLC.o entreeSortieLC.c

biblioH.o: biblioH.c biblioH.h
	gcc -c -o biblioH.o biblioH.c

entreeSortieH.o: entreeSortieH.c entreeSortieH.h
	gcc -c -o entreeSortieH.o entreeSortieH.c

mainLC.o: mainLC.c
	gcc -c -o mainLC.o mainLC.c

mainH.o: mainH.c
	gcc -c -o mainH.o mainH.c

mainCP.o: mainCP.c
	gcc -c -o mainCP.o mainCP.c

mainLC: mainLC.o biblioLC.o entreeSortieLC.o
	gcc -o mainLC mainLC.o biblioLC.o entreeSortieLC.o

mainH: mainH.o biblioH.o entreeSortieH.o
	gcc -o mainH mainH.o biblioH.o entreeSortieH.o

mainCP: mainCP.o biblioLC.o biblioH.o entreeSortieH.o entreeSortieLC.o
	gcc -o mainCP mainCP.o biblioLC.o biblioH.o entreeSortieH.o entreeSortieLC.o

clean:
	rm -f mainLC mainH mainCP *.o
