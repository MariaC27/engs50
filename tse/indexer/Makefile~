CFLAGS=-Wall -pedantic -std=c11 -I../utils/src -L../lib -g
LIBS=-lutils -lcurl

indexer: indexer.c
	gcc $(CFLAGS) indexer.c $(LIBS) -o $@

indexer5: indexer_step5.c
	gcc $(CFLAGS) indexer_step5.c $(LIBS) -o $@

indexer4: indexer_step4.c
	gcc $(CFLAGS) indexer_step4.c $(LIBS) -o $@

indexer3: indexer_step3.c
	gcc $(CFLAGS) indexer_step3.c $(LIBS) -o $@


