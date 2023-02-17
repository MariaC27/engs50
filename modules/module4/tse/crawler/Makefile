CFLAGS=-Wall -pedantic -std=c11 -I../utils/src -L../lib -g
LIBS=-lutils -lcurl

crawler: crawler.c
	gcc $(CFLAGS) crawler.c $(LIBS) -o $@
