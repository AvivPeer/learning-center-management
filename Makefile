makefile# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LIBS = $(shell pkg-config --cflags --libs libmongocxx)

# Target executable
TARGET = learning_center

# Source files
SOURCES = main.cpp LearningCenterManager.cpp DatabaseManager.cpp Student.cpp Assignment.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

# Build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(shell pkg-config --cflags libmongocxx)

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install dependencies (Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install libmongocxx-dev libbsoncxx-dev mongodb-org

# Run the application
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean install-deps run