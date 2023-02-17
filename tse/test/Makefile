CFLAGS=-Wall -pedantic -std=c11 -I../utils/src -L../lib -g
LIBS=-lutils -lcurl

pageio_test: pageio_test.c
	gcc $(CFLAGS) pageio_test.c $(LIBS) -o $@

indexio_test: indexio_test.c
	gcc $(CFLAGS) indexio_test.c $(LIBS) -o $@
