# Compiler
CXX = g++

# Compiler flags
# -std=c++11: Use C++11 standard
# -Wall: Enable all warnings
# -g: Generate debugging info
CXXFLAGS = -std=c++11 -Wall -g

# Libraries
# -lncurses: Link against the ncurses library
LDFLAGS = -lncurses

# Source files
SRCS = ./main.cpp

# Executable name
TARGET = editor

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(TARGET)

.PHONY: all clean
