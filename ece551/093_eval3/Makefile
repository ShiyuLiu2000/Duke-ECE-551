FLAGS = -std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS = cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS = $(patsubst %, %.o, $(PROGS)) cyoa.o

all: $(PROGS)
cyoa-step%: cyoa.o cyoa-step%.o
	g++ -o $@ $^

%.o: %.cpp
	g++ $(FLAGS) -c $<

cyoa.o: cyoa.cpp cyoa.hpp
	g++ $(FLAGS) -c cyoa.cpp

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)
