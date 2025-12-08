CXX = g++
CLANG = clang
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.cpp)
BIN = $(patsubst src/%.cpp,bin/%,$(SRC))
AS = $(patsubst src/%.cpp, as/%.s, $(SRC))
LLVM = $(patsubst src/%.cpp, ll/%.ll, $(SRC))

.PHONY: clean check

all: $(BIN)

assembly: $(AS)

as/%.s: src/%.cpp
	mkdir -p as
	$(CLANG) -S $(CXXFLAGS) $< -o $@ 

llvm: $(LLVM)

ll/%.ll : src/%.cpp
	mkdir -p ll
	$(CLANG) -emit-llvm -S $(CXXFLAGS) $< -o $@

bin/%: src/%.cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf bin

check:
	cppcheck --enable=all --inconclusive --std=c++20 -Iinclude --suppress=missingIncludeSystem $(SRC) 