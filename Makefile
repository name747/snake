CXX = g++
CXXFLAGS = -std=c++11 -Wall
LIBS = -lncurses
SOURCES = $(wildcard *.cpp)
TARGET = GreedySnake

build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean build