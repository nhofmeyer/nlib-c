TARGET = test_runner
INC_DIR = ./inc
SRC_DIR = ./src
TEST_DIR = ./test
CXX = gcc
CXXFLAGS = -I$(INC_DIR) -Wall -Wextra -pedantic -Werror
OBJECTS = $(TEST_DIR)/test_main.c $(SRC_DIR)/stack.c $(TEST_DIR)/test_ringbuffer.c $(TEST_DIR)/test_stack.c

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm test_runner

.PHONY: all clean