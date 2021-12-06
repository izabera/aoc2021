ifeq ($(origin CXX), default)
	CXX := g++
endif
#CXXFLAGS := -Ofast -march=native -fsanitize=address -Wall -Wextra -ggdb3 -std=c++20 -pthread $(CXXFLAGS)
CXXFLAGS := -fsanitize=address -Wall -Wextra -ggdb3 -std=c++20 -pthread $(CXXFLAGS)
LDFLAGS = -lcrypto -march=native -pthread -ltbb

days = $(basename $(wildcard [0-9]*.cpp))
dayobjs = $(addsuffix .o, $(days))
objs = $(dayobjs) main.o library.o

aoc: $(objs) Makefile
	$(CXX) $(CXXFLAGS) $(objs) -o $@ $(LDFLAGS)

$(objs): base.hpp Makefile

$(dayobjs): CPPFLAGS += -Dcurrentday=$*
$(dayobjs): day.hpp library.hpp

$(addsuffix .cpp, $(shell seq 25)):
	cp template $@

clean:
	rm -rf *.o aoc

.PHONY: clean
