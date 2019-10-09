CXX = clang++
CXXFLAGS = -std=c++17 -O3
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
LDFLAGS += -lboost_system -lboost_filesystem

fucn: $(OBJ)
	$(CXX) -Ofast $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) fucn
