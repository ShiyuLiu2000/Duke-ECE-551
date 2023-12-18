CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic

#note that $^ is "all pre-requisites"
sumfactors-test: sumfactors-test.o sumfactors.o 
	gcc $(CFLAGS) -o sumfactors-test $^ 

%.o: %.c sumfactors.h prime.h
	gcc -c $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f *.o *~ sumfactors-test

