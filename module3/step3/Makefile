CFLAGS=-Wall -pedantic -std=c17 -I. -g

all:			puttest gettest removetest applytest

list.o:		list.c list.h
					gcc ${CFLAGS} list.c -c

puttest:	list.o puttest.c
					gcc ${CFLAGS} puttest.c -c 
					gcc ${CFLAGS} list.o puttest.o -o puttest

gettest:	list.o gettest.c
					gcc ${CFLAGS} gettest.c -c 
					gcc ${CFLAGS} list.o gettest.o -o gettest

applytest:	list.o applytest.c
						gcc ${CFLAGS} applytest.c -c 
						gcc ${CFLAGS} list.o applytest.o -o applytest

removetest: list.o removetest.c
						gcc ${CFLAGS} removetest.c -c 
						gcc ${CFLAGS} list.o removetest.o -o removetest

run:
						./puttest
						./gettest
						./removetest
						./applytest

clean:
						rm -f *.o puttest gettest applytest removetest

