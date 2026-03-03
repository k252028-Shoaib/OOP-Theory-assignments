# Name of your final program
TARGET = program

# The compiler you are using
CXX = g++

# Compiler flags (Warnings and C++11/17 standard)
CXXFLAGS = -std=c++23 -Wall

# This line automatically finds all .cpp files in your current folder
SRCS = $(wildcard *.cpp)

# This converts the list of .cpp files into .o (object) files
OBJS = $(SRCS:.cpp=.o)

# The default rule: Build the final target
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to "clean" the folder (removes the .o and executable files)
clean:
	rm -f $(OBJS) $(TARGET)