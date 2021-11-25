CXX = clang++
CXXFLAGS = -fsanitize=address -Wall -Wextra -ggdb3 -std=c++17
CPPFLAGS = -Dcurrentday=$*

days = $(basename $(wildcard [0-9]*.cpp))
headers = base.hpp day.hpp
objs = $(addsuffix .o, $(days)) main.o
inputs = $(addsuffix .input, $(days))

aoc: $(objs) Makefile
	$(CXX) $(CXXFLAGS) $(objs) -o $@ $(LDFLAGS)

main.o: main.cpp base.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp $(headers) Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

#%.cpp:
#	cp template $@

clean:
	rm -rf *.o aoc

.PHONY: clean
