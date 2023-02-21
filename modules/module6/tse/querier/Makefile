CFLAGS=-Wall -pedantic -std=c11 -I../utils/src -L../lib -g
LIBS=-lutils -lcurl


step3_querier: step3_query.c
	gcc $(CFLAGS) step3_query.c $(LIBS) -o $@

step2_querier: step2_query.c
	gcc $(CFLAGS) step2_query.c $(LIBS) -o $@

step1_querier: step1_query.c
	gcc $(CFLAGS) step1_query.c $(LIBS) -o $@



