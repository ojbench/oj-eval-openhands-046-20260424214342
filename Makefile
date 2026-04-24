CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -static -s
LDFLAGS :=

all: code

code: main.cpp Role.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o code $(LDFLAGS)

clean:
	rm -f code
