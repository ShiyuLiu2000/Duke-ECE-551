CFLAGS = -std=gnu99 -pedantic -Wall

maxSeq: maxSeq.o test-subseq.o
	gcc -o maxSeq maxSeq.o test-subseq.o
maxSeq.o: maxSeq.c
	gcc $(CFLAGS) -c  maxSeq.c
test-subseq.o: test-subseq.c
	gcc $(CFLAGS) -c test-subseq.c

.PHONY: clean
clean:
	rm -f maxSeq *.o *.c~
