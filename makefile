# Makefile for building SFML app

CXX = clang++
CXXFLAGS = -std=c++17 -I./SFML-3.0.2/include
LDFLAGS = -L./SFML-3.0.2/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = app
SRC := $(wildcard src/**/*.cpp src/*.cpp) 

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	DYLD_LIBRARY_PATH=./SFML-3.0.2/lib ./$(TARGET)

clean:
	rm -f $(TARGET)
