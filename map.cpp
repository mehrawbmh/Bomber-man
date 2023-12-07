#include "headers/map.hpp"
#include "headers/wall.hpp"
#include "headers/grass.hpp"
#include "headers/breakable_wall.hpp"
#include "headers/non_breakable_wall.hpp"
#include "headers/door.hpp"
#include "headers/key.hpp"
#include "headers/random_generator.hpp"

Map::Map(sf::RenderWindow *renderWindow, sf::Event _event) : window(renderWindow), event(_event) {
    this->grass = this->createGrass();
    this->wall1 = this->createWall(1);
    this->wall2 = this->createWall(2);
    this->door = this->createDoor();
    this->key1 = this->createKey(1);
    this->key2 = this->createKey(2);
    this->key3 = this->createKey(3);
    this->keyTextures = {key1, key2, key3};
}

Map::~Map() = default;

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

sf::Texture Map::createKey(int type) {
    std::string file;
    switch (type)
    {
    case 1:
        file = this->KEY1_FILE;
        break;
    case 2:
        file = this->KEY2_FILE;
        break;
    case 3:
        file = this->KEY3_FILE;
        break;
    default:
        break;
    }

    sf::Texture keyTexture;
    if (keyTexture.loadFromFile(BASE_SPRITES_DIR + "/" + file)) {
        keyTexture.getSize();
        keyTexture.setSmooth(true);
    };

    return keyTexture;
}

sf::Texture Map::createDoor() {
    sf::Texture doorTexture;
    std::string file = DOOR_FILE;
    if (doorTexture.loadFromFile(BASE_SPRITES_DIR + "/" + file)) {
        doorTexture.setSmooth(true);
    }

    doorTexture.setSrgb(true);
    return doorTexture;
}

void Map::placeKeysUnderWalls() {
    RandomNumberGenerator generator(0, this->mapElements.size() - 1);
    int count = 0;

    while (count < AVAILABLE_KEYS) {
        int rand = generator.generateRandomNumber();
        if (dynamic_cast<BreakableWall*>(this->mapElements[rand])) {
            sf::Sprite sprite;
            sf::Vector2f position = this->mapElements[rand]->getPosition();

            sprite.setPosition(position);
            sprite.setTexture(this->keyTextures[count]);
            sprite.setColor(sf::Color::White);
            sprite.setScale(0.85f, 0.95f);

            this->mapElements.push_back(new Key(position, sprite));
            std::cout << "placed a key under sprite of column " << position.x / ELEMENT_SIZE_X << " : row " << position.y / ELEMENT_SIZE_Y << std::endl;
            count++;
        }
    }
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
        case DoorTexture: {
            sprite.setTexture(this->door);
            return new Door(sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)), sprite);
        }
        default:
            sprite.setTexture(this->grass);
            return new Grass(sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)), sprite);
    }
}

void Map::init(const std::vector<std::vector<MapObject>> &mapObjects) {
    this->rows = static_cast<int>(mapObjects.size());
    this->columns = static_cast<int>(mapObjects[0].size());
    int x, y = 0;
    std::vector<Enemy*> enemies;
    for (const auto &elements: mapObjects) {
        x = 0;
        for (const auto &element: elements) {
            this->mapElements.push_back(this->createElement(element, x, y));
            x += ELEMENT_SIZE_X;
        }
        y += ELEMENT_SIZE_Y;
    }

    this->placeKeysUnderWalls();
}

sf::Vector2f Map::getMapSize() const {
    return {static_cast<float>(this->rows), static_cast<float>(this->columns)};
}

void Map::update() {
    this->walls.clear();
    this->doors.clear();
    this->grasses.clear();
    this->keys.clear();
    for(int i = 0; i < this->mapElements.size(); i++) {
        MapElement* element = this->mapElements[i];
        if (dynamic_cast<Wall*>(element)) {
            this->walls.push_back(dynamic_cast<Wall*>(element));
        } else if (dynamic_cast<Door*>(element)) {
            this->doors.push_back(dynamic_cast<Door*>(element));
        } else if (dynamic_cast<Key*>(element)) {
            this->keys.push_back(dynamic_cast<Key*>(element));
        } else if (dynamic_cast<Grass*>(element)) {
            this->grasses.push_back(dynamic_cast<Grass*>(element));
        }
    }
    this->draw();
}

void Map::draw() {
    // for (auto &mapElement: this->mapElements) {
    //     mapElement->draw(this->window);
    // }

    for (auto &grass: this->grasses) {
        grass->draw(this->window);
    }
    for (auto &key: this->keys) {
        key->draw(this->window);
    }
    for (auto &door: this->doors) {
        door->draw(this->window);
    }
    for (auto &wall: this->walls) {
        wall->draw(this->window);
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
        return MapObject::DoorTexture;
    } else {
        throw std::logic_error("Invalid Map operator in txt file detected!\n");
    }
}

const std::vector<MapElement*> Map::giveMapElements() const
{
    return mapElements;
}

