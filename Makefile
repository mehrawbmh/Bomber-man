PROJECT_NAME := bomberman.out
CC := g++ --std=c++20

HEADERS_DIR := headers
BUILD_DIR := build
BIN_DIR := .

TARGET := $(BIN_DIR)/$(PROJECT_NAME)

SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR);

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR);

$(BUILD_DIR)/main.o: main.cpp
	$(CC) -c main.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/main.o;

$(BUILD_DIR)/game.o: $(HEADERS_DIR)/game.hpp $(HEADERS_DIR)/map.hpp $(HEADERS_DIR)/player.hpp ./game.cpp
	$(CC) -c game.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/game.o;

$(BUILD_DIR)/map.o: $(HEADERS_DIR)/map.hpp ./map.cpp
	$(CC) -c map.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/map.o;

$(BUILD_DIR)/player.o: $(HEADERS_DIR)/player.hpp ./player.cpp
	$(CC) -c player.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/player.o;

$(TARGET): $(BUILD_DIR) $(BIN_DIR) $(BUILD_DIR)/main.o $(BUILD_DIR)/game.o $(BUILD_DIR)/map.o $(BUILD_DIR)/player.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/game.o $(BUILD_DIR)/map.o $(BUILD_DIR)/player.o -o $(TARGET) $(SFML_FLAGS);

clean:
	rm -f *.o;
	rm -f *.out;
	rm -f $(TARGET);
	rm -rf $(BUILD_DIR);

