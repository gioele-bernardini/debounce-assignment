# Variable for the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Name of the executable
TARGET = main

# Default rule to build the program
all: $(TARGET)

# Rule to link the object file and create the executable
$(TARGET): main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o

# Rule to compile the source file into an object file
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Rule to clean up the build files
clean:
	rm -f $(TARGET) main.o

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Rule to display help
help:
	@echo "Usage:"
	@echo "  make        - Compile the program"
	@echo "  make run    - Compile and run the program"
	@echo "  make clean  - Remove the build files"
	@echo "  make help   - Show this help message"

