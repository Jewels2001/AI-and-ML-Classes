CXX=g++
CXXFLAGS= -std=c++14 -Wall

SRC_DIR = src
SRCS = $(SRC_DIR)/*.cpp
GAME_MAIN = $(SRC_DIR)/a1/main.cpp

PROGRAM = a1

SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o	$(PROGRAM)

$(PROGRAM): $(SRCS) $(GAME_MAIN)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) -I $(SRC_INCLUDE) $(SRCS) $(GAME_MAIN)
