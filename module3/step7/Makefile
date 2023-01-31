#%.o: %.c %.h
#		gcc $(CFLAGS) -c $<
CFLAGS = -Wall -pedantic -std=c17 -I. -g

all:		hash test1_hash test2_hash test3_hash

hash:		hash.c
				gcc ${CFLAGS} hash.c -c

test1_hash:				test1_hash.c
									gcc ${CFLAGS} test1_hash.c -c
									gcc hash.o test1_hash.o -o test1_hash

test2_hash: 			test2_hash.c
									gcc ${CFLAGS} test2_hash.c -c
									gcc hash.o test2_hash.o -o test2_hash

test3_hash: 			test3_hash.c
									gcc ${CFLAGS} test3_hash.c -c
									gcc hash.o test3_hash.o -o test3_hash

clean:						rm -f *.o test1_hash.c test2_hash.c test3_hash.c

