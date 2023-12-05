#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <stdexcept>
#include "headers/game.hpp"

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), GAME_TITLE);
    this->font.loadFromFile("fonts/arial.ttf");
    this->map = new Map(this->window, this->event);
    this->player = new Player(200.f, 100.f);
}

Game::~Game() {
    delete this->map;
    delete this->window;
    delete this->player;
}

int Game::getRandomNumber(int startRange, int endRange) {
    /* Generates a random int number. start and end number also included in result. */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(startRange, endRange);

    return dis(gen);
}

void Game::start() {
    this->window->setFramerateLimit(100); //TODO: change it?
    this->window->clear(sf::Color::White);
    this->initTimer();

    std::cout << "Loading map...\n";
    this->readMap();
    std::cout << "Loading of map finished\n";

    this->window->display();
    std::cout << "Game is starting...\n";
}

void Game::run() {
    this->handleEvents();
    this->update();
    this->render();
}

void Game::initTimer() {
    std::cout << "Loading timer...\n";
    this->clock.restart();
    this->timer.setFillColor(sf::Color::Black);
    this->timer.setCharacterSize(24);
    this->timer.setOutlineColor(sf::Color::Red);
    this->timer.setPosition(static_cast<float>(this->window->getSize().x - 190), 0.f);
    this->timer.setFont(this->font);
    std::cout << "Loading of timer finished\n";
}

void Game::handleEvents() {
    while (this->window->pollEvent(this->event)) {
        switch (event.type) {
            case sf::Event::Closed:
                std::cout << "game is closing...\n";
                this->finished = true;
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Escape has pressed. exiting...\n";
                    this->finished = true;
                    this->window->close(); //todo: close with escape?
                }
                break;
            default:
                break;
        }
    }
}

bool Game::isClosed() {
    return !this->window->isOpen();
}

bool Game::isFinished() {
    return this->finished;
}

void Game::updatePlayer() {
    this->player->update(this->window);
}

void Game::update() {
    this->window->clear(sf::Color::White);
    if (!this->isFinished()) {
        this->updatePlayer();
    }
    this->updateCollision();
    this->updateTimer();
    this->map->update();
}

void Game::updateTimer() {
    this->timer.setString("Timer: " + std::to_string(this->clock.getElapsedTime().asSeconds()));
    this->window->draw(this->timer);
}

void Game::readMap() {
    std::ifstream file(MAP_INIT_FILE);
    if (!file.is_open()) {
        throw std::ifstream::failure("could not open map file!\n");
    }

    std::string line, timeString;
    getline(file, timeString);
    this->gameTime = readGameTime(timeString);

    std::vector<std::vector<MapObject>> rows;
    while (getline(file, line)) {
        std::vector<MapObject> row;
        for (const char &item: line) {
            row.push_back(Map::mapObjectFactory(item));
        }
        rows.push_back(row);
    }

    file.close();
    this->map->init(rows);
}

sf::Time Game::readGameTime(const std::string &timeString) {
    std::istringstream iss(timeString);
    int minute, second;
    char delimiter = ':';
    iss >> minute >> delimiter >> second;

    sf::Time time = sf::Time::Zero;
    time += sf::seconds(static_cast<float>(second));
    time += sf::seconds(static_cast<float>(minute * 60));

    return time;
}

void Game::render() {
    this->player->render(this->window);
    this->window->display();
}
void Game::updateCollision()
{
    std::vector<MapElement*> elements=this->map->giveMapElements();
    for(size_t i=0; i< elements.size();i++ ){
        if(this->player->getSprite().getGlobalBounds().intersects(elements[i]->getSprite().getGlobalBounds())){
            switch (elements[i]->type)
            {
            case MapElementTypes::UNBREAKABLE_WALL:
                this->player->undoMovement();
                break;
            case MapElementTypes::BREAKABLE_WALL:
                this->player->undoMovement();
                break;
            default:
                break;
            }
        }
    }
}