#ifndef MAP
#define MAP "MAP.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "map_element.hpp"
#include "door.hpp"
#include "key.hpp"
#include "wall.hpp"
#include "grass.hpp"
#include "bomb.hpp"

enum MapObject {
    Wall1, Wall2, DoorTexture, GrassTexture, EnemyH, EnemyV
};

const int ELEMENT_SIZE_Y = 100;
const int ELEMENT_SIZE_X = 100;
const std::string BASE_SPRITES_DIR = "sprites";


class Map {
private:
    const std::string GRASS_FILE = "grass.png";
    const std::string BOMB_FILE = "bomb.png";
    const std::string WALL1_FILE = "wall-1.png";
    const std::string WALL2_FILE = "wall-2.png";
    const std::string KEY1_FILE = "key.png";
    const std::string KEY2_FILE = "key2.png";
    const std::string KEY3_FILE = "key3.jpg";
    const std::string DOOR_FILE = "door.png";
    const int AVAILABLE_KEYS = 3;

    std::vector<MapElement*> mapElements;
    std::vector<Wall*> walls;
    std::vector<Door*> doors;
    std::vector<Key*> keys;
    std::vector<Grass*> grasses;
    std::vector<Bomb*> bombs;

    int rows;
    int columns;

    sf::RenderWindow *window;
    sf::Event event;
    sf::Texture grass;
    sf::Texture wall1;
    sf::Texture wall2;
    sf::Texture door;
    sf::Texture key1;
    sf::Texture key2;
    sf::Texture key3;
    std::vector<sf::Texture> keyTextures;

    MapElement *createElement(MapObject element, float x, float y);

    sf::Texture createGrass();

    sf::Texture createWall(int type);

    sf::Texture createKey(int type);

    sf::Texture createDoor();

    void updateBombs();

    void placeKeysUnderWalls();

    void draw();

public:
    Map(sf::RenderWindow *_window, sf::Event _event);

    ~Map();

    const std::vector<MapElement*> giveMapElements()  const;
    void init(const std::vector<std::vector<MapObject>> &objects);

    static MapObject mapObjectFactory(char item);

    Bomb* plantBomb(const sf::Vector2f &position);

    sf::Vector2f getMapSize() const;

    void update();
};

#endif
