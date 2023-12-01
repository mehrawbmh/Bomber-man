#include "headers/map.hpp"

Map::Map(sf::RenderWindow *renderWindow, sf::Event _event) {
    this->window = renderWindow;
    this->event = _event;

    this->grass = this->createGrass();
    this->wall1 = this->createWall(1);
    this->wall2 = this->createWall(2);
}

Map::~Map() {
    //todo: delete sprites.
    return;
}

 sf::Texture Map::createGrass() {
    sf::Texture grassTexture;
    if (grassTexture.loadFromFile(BASE_SPRITES_DIR + "/" + GRASS_FILE)) {
        grassTexture.setSmooth(true); //TODO?
        std::cout << "Grass:" << grassTexture.getSize().x << grassTexture.getSize().y << std::endl;
        std::cout << "grass loaded\n";
    }

    return grassTexture;
}

sf::Texture Map::createWall(int type) {
    sf::Texture wallTexture;
    std::string file = (type == 1) ? WALL1_FILE : WALL2_FILE;
    if (wallTexture.loadFromFile(BASE_SPRITES_DIR + "/" + file)) {
        wallTexture.setSmooth(true);
        std::cout << "Grass:" << wallTexture.getSize().x << wallTexture.getSize().y << std::endl;
        std::cout << "grass loaded\n";
    }

    return wallTexture;
}

sf::Sprite Map::createElement(MapObject element, int xPos, int yPos) {
    sf::Sprite sprite;
    switch (element) {
        case Grass:
        {
            sprite.setTexture(this->grass);
            std::cout << "sprite grass created... at " << sprite.getPosition().x << ":" << sprite.getPosition().y << "\n";
            std::cout << sprite.getScale().x << sprite.getScale().y << std::endl;
            break;
        }
        case Wall1:
        {
            sprite.setTexture(this->wall1);
            std::cout << "sprite wall1 created... at " << sprite.getPosition().x << ":" << sprite.getPosition().y << "\n";
            break;
        }
        case Wall2:
        {
            sprite.setTexture(this->wall2);
            std::cout << "sprite wall2 created... at " << sprite.getPosition().x << ":" << sprite.getPosition().y << "\n";
            break;
        }
        default:
            std::cout << "NOT handling others yet!\n";
    }

    sprite.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));

    return sprite;
}

void Map::init(std::vector<std::vector<MapObject>> mapObjects) {
    int x = 0, y = 0;
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
