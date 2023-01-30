#%.o: %.c %.h
#		gcc $(CFLAGS) -c $<
CFLAGS = -Wall -pedantic -std=c17 -I. -g

all: queue hash test_hash1 test_hash2

queue:	queue.c
				gcc ${CFLAGS} queue.c -c
hash:		hash.c queue.c
				gcc ${CFLAGS} hash.c -c

test_hash1:	test_hash1.c
						gcc ${CFLAGS} test_hash1.c -c
						gcc hash.o test_hash1.o -o test_hash1
test_hash2: test_hash2.c
						gcc ${CFLAGS} test_hash2.c -c
						gcc hash.o test_hash2.o -o test_hash2


clean:
	rm -f *.o test_hash1 test_hash2

