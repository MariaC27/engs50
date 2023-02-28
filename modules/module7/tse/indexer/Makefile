CFLAGS=-Wall -pedantic -std=c11 -I../utils/src -L../lib -g
LIBS=-lutils -lcurl

indexer: indexer.c
	gcc $(CFLAGS) indexer.c $(LIBS) -o $@

tindexer: tindexer.c
	gcc $(CFLAGS) tindexer.c $(LIBS) -o $@


