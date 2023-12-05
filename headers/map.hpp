#ifndef MAP
#define MAP "MAP.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "map_element.hpp"

enum MapObject {
    Wall1, Wall2, Door, GrassTexture, EnemyH, EnemyV
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
    const std::string KEY_FILE = "key.png";
    const std::string KEY2_FILE = "key2.png";
    const std::string KEY3_FILE = "key3.jpg";

    std::vector<MapElement*> mapElements;

    int rows = 10;
    int columns = 10;

    sf::RenderWindow *window;
    sf::Event event;
    sf::Texture grass;
    sf::Texture wall1;
    sf::Texture wall2;

    MapElement *createElement(MapObject element, int x, int y);

    sf::Texture createGrass();

    sf::Texture createWall(int type);

    void draw();

public:
    Map(sf::RenderWindow *_window, sf::Event _event);

    ~Map();

    const std::vector<MapElement*> giveMapElements()  const;
    void init(const std::vector<std::vector<MapObject>> &objects);

    static MapObject mapObjectFactory(char item);

    void update();
};

#endif
