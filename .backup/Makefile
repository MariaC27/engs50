CFLAGS = -Wall -pedantic -std=c17 -I. -g

all: list puttest gettest removetest

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
	rm -f *.o puttest.exe

