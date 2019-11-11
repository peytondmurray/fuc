CXX = clang++
CXXFLAGS = -std=c++17 -Ofast
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
LDFLAGS += -lboost_system -lboost_filesystem

fuc: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) fuc
