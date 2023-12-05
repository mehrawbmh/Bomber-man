#include "headers/map.hpp"

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

sf::Sprite Map::createElement(MapObject element, int xPos, int yPos) {
    sf::Sprite sprite;
    switch (element) {
        case Grass: {
            sprite.setTexture(this->grass);
            break;
        }
        case Wall1: {
            sprite.setTexture(this->wall1);
            break;
        }
        case Wall2: {
            sprite.setTexture(this->wall2);
            break;
        }
        default:
            std::cout << "NOT handling other map objects yet!\n";
    }

    sprite.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));
    return sprite;
}

void Map::init(const std::vector<std::vector<MapObject>> &mapObjects) {
    int x, y = 0;
    for (const auto &elements: mapObjects) {
        x = 0;
        for (const auto &element: elements) {
            this->sprites.push_back(this->createElement(element, x, y));
            x += ELEMENT_SIZE_X;
        }
        y += ELEMENT_SIZE_Y;
    }
}

void Map::update() {
    this->draw();
}

void Map::draw() {
    for (const sf::Sprite &sprite: this->sprites) {
        this->window->draw(sprite);
    }
}

MapObject Map::mapObjectFactory(char item) {
    if (item == ' ') {
        return MapObject::Grass;
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

