CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.cpp)
BIN = $(patsubst src/%.cpp,bin/%,$(SRC))

.PHONY: clean check

all: $(BIN)

bin/%: src/%.cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf bin

check:
	cppcheck --enable=all --inconclusive --std=c++20 -Iinclude --suppress=missingIncludeSystem $(SRC) 