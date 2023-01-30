CFLAGS = -Wall -pedantic -std=c17 -I. -g

all: queue test_queue1 test_queue2 concat_test

queue: queue.c
	gcc ${CFLAGS} queue.c -c
test_queue1: test_queue1.c
	gcc ${CFLAGS} test_queue1.c -c 
	gcc queue.o test_queue1.o -o test_queue1
test_queue2: test_queue2.c
	gcc ${CFLAGS} test_queue2.c -c 
	gcc queue.o test_queue2.o -o test_queue2
concat_test: concat_test.c
	gcc ${CFLAGS} concat_test.c -c 
	gcc queue.o concat_test.o -o concat_test

clean:
	rm -f *.o test_queue1 test_queue2

