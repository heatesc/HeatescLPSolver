CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LIBS = 
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
HEAD_DIR = headers

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/solver

.PHONY: all clean test run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -I./$(HEAD_DIR) $(OBJS) -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(HEAD_DIR) -c $< -o $@

test: 
	./testing/run_tests.sh

run:
	./bin/solver

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

