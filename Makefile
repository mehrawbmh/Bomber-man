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

$(BUILD_DIR)/game.o: $(HEADERS_DIR)/game.hpp $(HEADERS_DIR)/map.hpp $(HEADERS_DIR)/player.hpp ./game.cpp $(HEADERS_DIR)/person.hpp  ./person.cpp $(HEADERS_DIR)/enemy.hpp  ./enemy.cpp
	$(CC) -c game.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/game.o;

$(BUILD_DIR)/map.o: $(HEADERS_DIR)/map.hpp ./map.cpp $(BUILD_DIR)/grass.o $(BUILD_DIR)/non_breakable_wall.o $(BUILD_DIR)/breakable_wall.o $(BUILD_DIR)/door.o $(BUILD_DIR)/key.o $(BUILD_DIR)/bomb.o $(BUILD_DIR)/powerUp.o
	$(CC) -c map.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/map.o;

$(BUILD_DIR)/player.o: $(HEADERS_DIR)/player.hpp $(HEADERS_DIR)/person.hpp ./player.cpp  ./person.cpp
	$(CC) -c player.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/player.o;

$(BUILD_DIR)/enemy.o: $(HEADERS_DIR)/enemy.hpp $(HEADERS_DIR)/person.hpp ./enemy.cpp  ./person.cpp
	$(CC) -c enemy.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/enemy.o;

$(BUILD_DIR)/person.o: $(HEADERS_DIR)/person.hpp  ./person.cpp
	$(CC) -c person.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/person.o;

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

$(BUILD_DIR)/door.o: $(HEADERS_DIR)/door.hpp ./door.cpp $(BUILD_DIR)/map_element.o
	$(CC) -c door.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/door.o

$(BUILD_DIR)/key.o: $(HEADERS_DIR)/key.hpp ./key.cpp $(BUILD_DIR)/map_element.o
	$(CC) -c key.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/key.o

$(BUILD_DIR)/bomb.o: $(HEADERS_DIR)/bomb.hpp ./bomb.cpp $(BUILD_DIR)/map_element.o
	$(CC) -c bomb.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/bomb.o

$(BUILD_DIR)/random_generator.o: $(HEADERS_DIR)/random_generator.hpp ./random_generator.cpp
	$(CC) -c random_generator.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/random_generator.o

$(BUILD_DIR)/powerUp.o: $(HEADERS_DIR)/powerUp.hpp ./powerUp.cpp $(BUILD_DIR)/map_element.o
	$(CC) -c powerUp.cpp $(SFML_FLAGS) -o $(BUILD_DIR)/powerUp.o

$(TARGET): $(BUILD_DIR) $(BIN_DIR) $(BUILD_DIR)/main.o $(BUILD_DIR)/game.o $(BUILD_DIR)/map.o $(BUILD_DIR)/player.o $(BUILD_DIR)/wall.o $(BUILD_DIR)/map_element.o $(BUILD_DIR)/breakable_wall.o $(BUILD_DIR)/non_breakable_wall.o $(BUILD_DIR)/grass.o $(BUILD_DIR)/door.o $(BUILD_DIR)/key.o $(BUILD_DIR)/random_generator.o $(BUILD_DIR)/person.o $(BUILD_DIR)/enemy.o $(BUILD_DIR)/bomb.o $(BUILD_DIR)/powerUp.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/game.o $(BUILD_DIR)/map.o $(BUILD_DIR)/player.o $(BUILD_DIR)/wall.o $(BUILD_DIR)/map_element.o $(BUILD_DIR)/breakable_wall.o $(BUILD_DIR)/non_breakable_wall.o $(BUILD_DIR)/grass.o -o $(TARGET) $(SFML_FLAGS) $(BUILD_DIR)/door.o $(BUILD_DIR)/key.o $(BUILD_DIR)/random_generator.o $(BUILD_DIR)/person.o $(BUILD_DIR)/enemy.o $(BUILD_DIR)/bomb.o $(BUILD_DIR)/powerUp.o;

clean:
	rm -f *.o;
	rm -f *.out;
	rm -f $(TARGET);
	rm -rf $(BUILD_DIR);

