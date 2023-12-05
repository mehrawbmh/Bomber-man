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

$(BUILD_DIR)/map.o: $(HEADERS_DIR)/map.hpp ./map.cpp $(BUILD_DIR)/grass.o $(BUILD_DIR)/non_breakable_wall.o $(BUILD_DIR)/breakable_wall.o
	$(CC) -c map.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/map.o;

$(BUILD_DIR)/player.o: $(HEADERS_DIR)/player.hpp ./player.cpp
	$(CC) -c player.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/player.o;

$(BUILD_DIR)/map_element.o: $(HEADERS_DIR)/map_element.hpp ./map_element.cpp
	$(CC) -c map_element.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/map_element.o

$(BUILD_DIR)/wall.o: $(HEADERS_DIR)/wall.hpp ./wall.cpp $(BUILD_DIR)/map_element.o
	$(CC) -c wall.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/wall.o

$(BUILD_DIR)/breakable_wall.o: $(HEADERS_DIR)/breakable_wall.hpp ./breakable_wall.cpp $(BUILD_DIR)/wall.o
	$(CC) -c breakable_wall.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/breakable_wall.o

$(BUILD_DIR)/non_breakable_wall.o: $(HEADERS_DIR)/non_breakable_wall.hpp ./non_breakable_wall.cpp $(BUILD_DIR)/wall.o
	$(CC) -c non_breakable_wall.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/non_breakable_wall.o

$(BUILD_DIR)/grass.o: $(HEADERS_DIR)/grass.hpp ./grass.cpp $(BUILD_DIR)/map_element.o
	$(CC) -c grass.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/grass.o

$(TARGET): $(BUILD_DIR) $(BIN_DIR) $(BUILD_DIR)/main.o $(BUILD_DIR)/game.o $(BUILD_DIR)/map.o $(BUILD_DIR)/player.o $(BUILD_DIR)/wall.o $(BUILD_DIR)/map_element.o $(BUILD_DIR)/breakable_wall.o $(BUILD_DIR)/non_breakable_wall.o $(BUILD_DIR)/grass.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/game.o $(BUILD_DIR)/map.o $(BUILD_DIR)/player.o $(BUILD_DIR)/wall.o $(BUILD_DIR)/map_element.o $(BUILD_DIR)/breakable_wall.o $(BUILD_DIR)/non_breakable_wall.o $(BUILD_DIR)/grass.o -o $(TARGET) $(SFML_FLAGS);

clean:
	rm -f *.o;
	rm -f *.out;
	rm -f $(TARGET);
	rm -rf $(BUILD_DIR);

