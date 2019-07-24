CXX = g++
CXXFLAGS = -std=c++17 -O3
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
LDFLAGS += -lboost_program_options

fucn: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) fucn
