CFLAGS = -Wall -pedantic -std=c17 -I. -g
OFILES = queue.o hash.o webpage.o pageio.o indexio.o

all: $(OFILES)
	ar cr ../../lib/libutils.a $(OFILES)

hash: ../src/hash.c ../src/queue.c
	gcc ${CFLAGS} ../src/hash.c -c
queue: ../src/queue.c 
	gcc ${CFLAGS} ../src/queue.c -c
webpage: ../src/webpage.c
	gcc ${CFLAGS} ../src/webpage.c -c
pageio: ../src/pageio.c
	gcc ${CLFAGS} ../src/pageio.c -c
indexio: ../src/indexio.c
	gcc ${CFLAGS} ../src/indexio.c -c
lqueue: ../src/lqueue.c
	gcc ${CFLAGS} ../src/lqueue.c -c
lhash: ../src/lhash.c ../src/queue.c
	gcc ${CFLAGS} ../src/lhash.c -c

clean:
	rm -f *.o

