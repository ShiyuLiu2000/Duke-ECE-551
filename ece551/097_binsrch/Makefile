FLAGS = -std=gnu++98 -pedantic -Wall -Werror -ggdb3

test: test-bsearch.o search.o
	g++ $(FLAGS) -o test test-bsearch.o search.o
test-bsearch.o: test-bsearch.cpp function.h
	g++ $(FLAGS) -c test-bsearch.cpp
search.o: search.cpp function.h
	g++ $(FLAGS) -c search.cpp

.PHONY: clean
clean:
	rm -f *~ *.o test
