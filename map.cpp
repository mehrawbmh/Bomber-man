#include "headers/map.hpp"
#include "headers/wall.hpp"
#include "headers/grass.hpp"
#include "headers/breakable_wall.hpp"
#include "headers/non_breakable_wall.hpp"

Map::Map(sf::RenderWindow *renderWindow, sf::Event _event) {
    this->window = renderWindow;
    this->event = _event;

    this->grass = this->createGrass();
    this->wall1 = this->createWall(1);
    this->wall2 = this->createWall(2);
}

Map::~Map() {

}

sf::Texture Map::createGrass() {
    sf::Texture grassTexture;
    if (grassTexture.loadFromFile(BASE_SPRITES_DIR + "/" + GRASS_FILE)) {
        grassTexture.setSmooth(true); //TODO?
    }

    return grassTexture;
}

sf::Texture Map::createWall(int type) {
    sf::Texture wallTexture;
    std::string file = (type == 1) ? WALL1_FILE : WALL2_FILE;
    if (wallTexture.loadFromFile(BASE_SPRITES_DIR + "/" + file)) {
        wallTexture.setSmooth(true);
    }

    return wallTexture;
}

MapElement *Map::createElement(MapObject element, int xPos, int yPos) {
    sf::Sprite sprite;

    switch (element) {
        case GrassTexture: {
            sprite.setTexture(this->grass);
            return new Grass(sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)), sprite);
        }
        case Wall1: {
            sprite.setTexture(this->wall1);
            return new BreakableWall(sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)), sprite);
        }
        case Wall2: {
            sprite.setTexture(this->wall2);
            return new NonBreakableWall(sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)), sprite);
        }
        default:
            throw std::runtime_error("Unknown element given to be created\n");
    }
}

void Map::init(const std::vector<std::vector<MapObject>> &mapObjects) {
    int x, y = 0;
    for (const auto &elements: mapObjects) {
        x = 0;
        for (const auto &element: elements) {
            this->mapElements.push_back(this->createElement(element, x, y));
            x += ELEMENT_SIZE_X;
        }
        y += ELEMENT_SIZE_Y;
    }
}

void Map::update() {
    this->draw();
}

void Map::draw() {
    for (int i = 0; i < this->mapElements.size(); i++) {
        this->mapElements[i]->draw(this->window);
    }
}

MapObject Map::mapObjectFactory(char item) {
    if (item == ' ') {
        return MapObject::GrassTexture;
    } else if (item == 'H') {
        return MapObject::EnemyH;
    } else if (item == 'V') {
        return MapObject::EnemyV;
    } else if (item == 'B') {
        return MapObject::Wall1;
    } else if (item == 'P') {
        return MapObject::Wall2;
    } else if (item == 'D') {
        return MapObject::Door;
    } else {
        throw std::logic_error("Invalid Map operator in txt file detected!\n");
    }
}

