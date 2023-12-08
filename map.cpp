#include "headers/map.hpp"
#include "headers/wall.hpp"
#include "headers/grass.hpp"
#include "headers/breakable_wall.hpp"
#include "headers/non_breakable_wall.hpp"
#include "headers/door.hpp"
#include "headers/key.hpp"
#include "headers/random_generator.hpp"
#include "headers/bomb.hpp"
#include "headers/powerUp.hpp"

Map::Map(sf::RenderWindow *renderWindow, sf::Event _event) : window(renderWindow), event(_event) {
    this->grass = this->createGrass();
    this->wall1 = this->createWall(1);
    this->wall2 = this->createWall(2);
    this->door = this->createDoor();
    this->key1 = this->createKey(1);
    this->key2 = this->createKey(2);
    this->key3 = this->createKey(3);
    this->keyTextures = {key1, key2, key3};
    this->rows = 0;
    this->columns = 0;
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
    switch (type) {
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
        keyTexture.setSmooth(true);
    }

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

Bomb* Map::plantBomb(const sf::Vector2f &position) {
    Bomb* newBomb = new Bomb(position, BASE_SPRITES_DIR + "/" + BOMB_FILE);
    this->bombs.push_back(newBomb);
    return newBomb;
}

void Map::updateBombs(const std::vector<Enemy*>& enemies) {
    for (auto bomb : this->bombs) {
        if (!bomb->isExploded() && bomb->isTimeToExplode()) {
            bomb->explode();
            for (size_t j = 0; j < this->walls.size(); j++) {
                if (this->walls[j]->canBreak() && bomb->shouldDestroy(this->walls[j]->getPosition())) {
                    std::cout << "going to destroy:" << j <<
                    ">> " << this->walls[j]->getPosition().x << ":" << this->walls[j]->getPosition().y << std::endl;
                    this->walls[j]->destroy();
                }
            }
            for (auto enemy: enemies) {
                if (bomb->shouldDestroy(enemy->getPosition())) {
                    enemy->destroy();
                }
            }
        }
    }
}

void Map::placeKeysUnderWalls() {
    RandomNumberGenerator generator(0, static_cast<int>(this->mapElements.size()) - 1);
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

MapElement *Map::createElement(MapObject element, float xPos, float yPos) {
    sf::Sprite sprite;
    sf::Sprite grasSprite;
    sf::Sprite wallSprite;
    grasSprite.setTexture(this->grass);
    wallSprite.setTexture(this->wall1);

    this->grasses.push_back(new Grass(sf::Vector2f(xPos, yPos), grasSprite));
    switch (element) {
        case GrassTexture: {
            sprite.setTexture(this->grass);
            return new Grass(sf::Vector2f(xPos, yPos), sprite);
        }
        case Wall1: {
            sprite.setTexture(this->wall1);
            return new BreakableWall(sf::Vector2f(xPos, yPos), sprite);
        }
        case Wall2: {
            sprite.setTexture(this->wall2);
            return new NonBreakableWall(sf::Vector2f(xPos, yPos), sprite);
        }
        case DoorTexture: {
            this->mapElements.push_back(new BreakableWall(sf::Vector2f(xPos, yPos), wallSprite));
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
    for (const auto &elements: mapObjects) {
        x = 0;
        for (const auto &element: elements) {
            this->mapElements.push_back(this->createElement(element, static_cast<float>(x), static_cast<float>(y)));
            x += ELEMENT_SIZE_X;
        }
        y += ELEMENT_SIZE_Y;
    }

    this->placeKeysUnderWalls();
    this->placePowerUpsUnderWalls();
}

sf::Vector2f Map::getMapSize() const {
    return {static_cast<float>(this->rows), static_cast<float>(this->columns)};
}

void Map::update(const std::vector<Enemy *> &enemies) {
    this->walls.clear();
    this->doors.clear();
    this->keys.clear();
    this->powerUps.clear();

    for (int i = 0; i < this->mapElements.size(); i++) {
        MapElement *element = this->mapElements[i];
        if (dynamic_cast<Wall*>(element)) {
            this->walls.push_back(dynamic_cast<Wall*>(element));
        } else if (dynamic_cast<Door *>(element)) {
            this->doors.push_back(dynamic_cast<Door*>(element));
        } else if (dynamic_cast<Key *>(element)) {
            this->keys.push_back(dynamic_cast<Key*>(element));
        } else if (dynamic_cast<PowerUp *>(element)) {
            this->powerUps.push_back(dynamic_cast<PowerUp*>(element));
        }
    }

    this->updateBombs(enemies);
    this->draw();
}

void Map::draw() {
    for (auto &_grass: this->grasses) {
        _grass->draw(this->window);
    }
    for (auto &_key: this->keys) {
        _key->draw(this->window);
    }
    for (auto &_door: this->doors) {
        _door->draw(this->window);
    }
    for (auto &_wall: this->walls) {
        _wall->draw(this->window);
    }
    for (auto &_bomb: this->bombs) {
        _bomb->draw(this->window);
    }
    for (auto &_power: this->powerUps) {
        _power->draw(this->window);
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

std::vector<Key*> Map::getKeys() const {
    return this->keys;
}

void Map::placePowerUpsUnderWalls() {
    std::cout << "placing power ups...\n";
    RandomNumberGenerator generator(0, static_cast<int>(this->mapElements.size()) - 1);
    int count = 0;

    while (count < NUMBER_OF_POWER_UPS) {
        int rand = generator.generateRandomNumber();
        if (dynamic_cast<BreakableWall *>(this->mapElements[rand])) {
            sf::Vector2f position = this->mapElements[rand]->getPosition();
            this->mapElements.push_back(new PowerUp((count) ? PowerUpsTypes::SPEED_BOOSTER : PowerUpsTypes::SYRINGE, position));
            std::cout << "placed a power up under sprite of column " << position.x / ELEMENT_SIZE_X << " : row "<< position.y / ELEMENT_SIZE_Y << std::endl;
            count++;
        }
    }
}

std::vector<Door *> Map::getDoors() const {
    return this->doors;
}
