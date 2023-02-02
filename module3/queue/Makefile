CFLAGS = -Wall -pedantic -std=c17 -I. -g

all: queue qputgettest qclosetest qapplytest qsearchtest qconcattest

queue: queue.c
	gcc ${CFLAGS} queue.c -c
qputgettest: qputgettest.c
	gcc ${CFLAGS} qputgettest.c -c 
	gcc queue.o qputgettest.o -o qputgettest
qclosetest: qclosetest.c
	gcc ${CFLAGS} qclosetest.c -c 
	gcc queue.o qclosetest.o -o qclosetest
qapplytest: qapplytest.c
	gcc ${CFLAGS} qapplytest.c -c 
	gcc queue.o qapplytest.o -o qapplytest
qsearchtest: qsearchtest.c
	gcc ${CFLAGS} qsearchtest.c -c 
	gcc queue.o qsearchtest.o -o qsearchtest
qconcattest: qconcattest.c
	gcc ${CFLAGS} qconcattest.c -c 
	gcc queue.o qconcattest.o -o qconcattest


clean:
	#rm -f *.o
	#rm -f qputgettest qclosetest qapplytest qsearchtest qconcattest 
	#rm -f valgrind_qputgettest.txt valgrind_qclosetest.txt valgrind_qapplytest.txt valgrind_qsearchtest.txt valgrind_qconcattest.txt
	rm -f queue.o qputgettest.o qclosetest.o qapplytest.o qsearchtest.o qconcattest.o
	rm -f qputgettest.exe qclosetest.exe qapplytest.exe qsearchtest.exe qconcattest.exe
