CXX = clang++
CXXFLAGS = -fsanitize=address -Wall -Wextra -ggdb3 -std=c++17 -Dcurrentday=$*
LDFLAGS = -flto

src = $(wildcard *.cpp)
headers = $(wildcard *.hpp)

days = $(basename $(src))
objs = $(addsuffix .o, $(days))
inputs = $(addsuffix .input, $(days))

aoc: $(objs) Makefile
	$(CXX) $(CXXFLAGS) $(objs) -o $@ $(LDFLAGS)

#%.cpp:
#	cp template $@

%.o: %.cpp $(headers) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf *.o aoc

.PHONY: clean
