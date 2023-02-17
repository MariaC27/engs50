CFLAGS = -Wall -pedantic -std=c17 -I. -g
OFILES = queue.o hash.o webpage.o pageio.o

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

clean:
	rm -f *.o

