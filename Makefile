CXX = clang++
CXXFLAGS = -fsanitize=address -Wall -Wextra -ggdb3 -std=c++17

days = $(basename $(wildcard [0-9]*.cpp))
dayobjs = $(addsuffix .o, $(days))
objs = $(dayobjs) main.o

aoc: $(objs) Makefile
	$(CXX) $(CXXFLAGS) $(objs) -o $@ $(LDFLAGS)

$(objs): base.hpp Makefile

$(dayobjs): CPPFLAGS += -Dcurrentday=$*
$(dayobjs): day.hpp

$(addsuffix .cpp, $(shell seq 25)): %.cpp:
	cp template $@

clean:
	rm -rf *.o aoc

.PHONY: clean
