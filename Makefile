# Makefile for Dungeon of Shadows
# Requires: g++ with C++11 support
# Usage: make         -> build the game
#        make clean   -> remove compiled files

CXX      = g++
CXXFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -Iinclude
TARGET   = dungeon_game
SRCDIR   = src
OBJDIR   = obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

.PHONY: all clean

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET) save.dat
