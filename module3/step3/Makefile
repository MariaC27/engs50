CFLAGS = -Wall -pedantic -std=c17 -I. -g

all: list puttest gettest applytest removetest 

list: list.c
	gcc ${CFLAGS} list.c -c
puttest: puttest.c
	gcc ${CFLAGS} puttest.c -c 
	gcc list.o puttest.o -o puttest
gettest: gettest.c
	gcc ${CFLAGS} gettest.c -c 
	gcc list.o gettest.o -o gettest
applytest: applytest.c
	gcc ${CFLAGS} applytest.c -c 
	gcc list.o applytest.o -o applytest
removetest: removetest.c
	gcc ${CFLAGS} removetest.c -c 
	gcc list.o removetest.o -o removetest


clean:
<<<<<<< HEAD
	rm -f list.o puttest.o gettest.o applytest.o removetest.o
	rm -f puttest.exe gettest.exe applytest.exe removetest.exe  
	#rm -f *.o
	#rm -f valgrind_puttest.txt valgrind_gettest.txt valgrind_applytest.txt valgrind_removetest.txt
=======
	rm -f *.o puttest gettest applytest removetest  
	rm -f valgrind_puttest.txt valgrind_gettest.txt valgrind_applytest.txt valgrind_removetest.txt
>>>>>>> 44bfab35154bf15b61c53169b49e9f164dcb0813
