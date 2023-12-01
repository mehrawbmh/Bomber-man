PROJECT_NAME := Bomber-man
CC := g++ --std=c++20

HEADERDIR := headers
BUILDDIR  := build
BINDIR    := bin

TARGET    := $(BINDIR)/$(PROJECT_NAME)

SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR);

main.o: main.cpp
	$(CC) -c main.cpp $(SFML_FLAGS);

game.o: headers/game.hpp headers/map.hpp ./game.cpp
	$(CC) -c game.cpp $(SFML_FLAGS);

map.o: headers/map.hpp ./map.cpp
	$(CC) -c map.cpp $(SFML_FLAGS);

player.o: headers/player.hpp ./player.cpp
	$(CC) -c player.cpp $(SFML_FLAGS);

$(TARGET): $(BINDIR) main.o game.o map.o player.o
	$(CC) main.o game.o map.o player.o -o $(TARGET) $(SFML_FLAGS);

clean:
	rm -f *.o;
	rm -f $(TARGET);
