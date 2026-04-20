CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = dungeon_game
SOURCES = main.cpp game.cpp player.cpp enemy.cpp item.cpp map.cpp event.cpp battle.cpp save.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
