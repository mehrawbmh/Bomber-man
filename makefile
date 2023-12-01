PROJECT_NAME := Bomber-man
CC := g++ --std=c++20

HEADERS_DIR := headers
BUILD_DIR := build
BIN_DIR := bin

TARGET    := $(BIN_DIR)/$(PROJECT_NAME)

SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR);

main.o: main.cpp
	$(CC) -c main.cpp $(SFML_FLAGS);

game.o: $(HEADERS_DIR)/game.hpp $(HEADERS_DIR)/map.hpp ./game.cpp
	$(CC) -c game.cpp $(SFML_FLAGS);

map.o: $(HEADERS_DIR)/map.hpp ./map.cpp
	$(CC) -c map.cpp $(SFML_FLAGS);

player.o: $(HEADERS_DIR)/player.hpp ./player.cpp
	$(CC) -c player.cpp $(SFML_FLAGS);

$(TARGET): $(BIN_DIR) main.o game.o map.o player.o
	$(CC) main.o game.o map.o player.o -o $(TARGET) $(SFML_FLAGS);

clean:
	rm -f *.o;
	rm -f $(TARGET);
