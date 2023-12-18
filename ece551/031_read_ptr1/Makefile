CFLAGS = -std=gnu99 -pedantic -Wall

test: test.c
	gcc -o test $(CFLAGS) test.c
	rm -f *~

.PHONY: clean
clean:
	rm -f test *.o *.c~ *.h~
