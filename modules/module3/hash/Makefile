CFLAGS = -Wall -pedantic -std=c17 -I. -g

all: hash queue test1_hash test2_hash test3_hash

hash: hash.c queue.c
	gcc ${CFLAGS} hash.c -c
queue: queue.c 
	gcc ${CFLAGS} queue.c -c
test1_hash: test1_hash.c
	gcc ${CFLAGS} test1_hash.c -c 
	gcc queue.o hash.o test1_hash.o -o test1_hash
test2_hash: test2_hash.c
	gcc ${CFLAGS} test2_hash.c -c 
	gcc queue.o hash.o test2_hash.o -o test2_hash
test3_hash: test3_hash.c
	gcc ${CFLAGS} test3_hash.c -c 
	gcc queue.o hash.o test3_hash.o -o test3_hash

clean:
	#rm -f *.o
	#rm -f test1_hash test2_hash test3_hash
	#rm -f valgrind_test1_hash.txt valgrind_test2_hash.txt valgrind_test3_hash.txt
	rm -f test1_hash.exe test2_hash.exe test3_hash.exe
	rm -f hash.o queue.o test1_hash.o test2_hash.o test3_hash.o 
