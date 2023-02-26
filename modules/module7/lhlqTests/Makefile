CFLAGS = -Wall -pedantic -std=c17 -I. -g

all: lqueue lqputgettest lqclosetest lqapplytest lqsearchtest lqthread1 lqthread2 lhash queue test1_hash test2_hash test3_hash lhthread1 lhthread2

lqueue: lqueue.c
	gcc ${CFLAGS} lqueue.c -c
lqputgettest: lqputgettest.c
	gcc ${CFLAGS} lqputgettest.c -c 
	gcc lqueue.o lqputgettest.o -o lqputgettest
lqclosetest: lqclosetest.c
	gcc ${CFLAGS} lqclosetest.c -c 
	gcc lqueue.o lqclosetest.o -o lqclosetest
lqapplytest: lqapplytest.c
	gcc ${CFLAGS} lqapplytest.c -c 
	gcc lqueue.o lqapplytest.o -o lqapplytest
lqsearchtest: lqsearchtest.c
	gcc ${CFLAGS} lqsearchtest.c -c 
	gcc lqueue.o lqsearchtest.o -o lqsearchtest
lqthread1: lqthread1.c
	gcc ${CFLAGS} lqthread1.c -c 
	gcc lqueue.o lqthread1.o -o lqthread1
lqthread2: lqthread2.c
	gcc ${CFLAGS} lqthread2.c -c
	gcc lqueue.o lqthread2.o -o lqthread2
lhash: lhash.c queue.c
	gcc ${CFLAGS} lhash.c -c
queue: queue.c
	gcc ${CFLAGS} queue.c -c
test1_hash: test1_hash.c
	gcc ${CFLAGS} test1_hash.c -c
	gcc queue.o lhash.o test1_hash.o -o test1_hash
test2_hash: test2_hash.c
	gcc ${CFLAGS} test2_hash.c -c
	gcc queue.o lhash.o test2_hash.o -o test2_hash
test3_hash: test3_hash.c
	gcc ${CFLAGS} test3_hash.c -c
	gcc queue.o lhash.o test3_hash.o -o test3_hash
lhthread1: lhthread1.c
	gcc ${CFLAGS} lhthread1.c -c 
	gcc queue.o lhash.o lhthread1.o -o lhthread1
lhthread2: lhthread2.c
	gcc ${CFLAGS} lhthread2.c -c
	gcc queue.o lhash.o lhthread2.o -o lhthread2


clean:
	rm -f *.o
	rm -f lqputgettest lqclosetest lqapplytest lqsearchtest lqthread1 lqthread2 test1_hash test2_hash test3_hash lhthread1 lhthread2
	rm -f *.txt
