# Makefile for compiling and running the project

# Compiler
CXX = g++

# Target executable
TARGET = p5

# Source file
SRC = program.cpp

# Input file
INPUT = ./test_input/input1.txt

# Default target
all: $(TARGET)

# Compile the source file into the target executable
$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET)

# Run the program with redirected input
run: $(TARGET)
	./$(TARGET) < $(INPUT)

# Clean up the generated files
clean:
	rm -f $(TARGET)