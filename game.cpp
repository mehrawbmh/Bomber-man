#include <iostream>
#include <random>
#include "headers/game.hpp"

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), GAME_TITLE);
}

Game::~Game() {
    delete this->window;
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

    MapObject obj = Grass;
    std::vector<std::vector<MapObject>> vec = {{obj, obj}, {obj, obj}};

    std::cout << "Loading map...\n";
    Map map(this->window, this->event);
    map.init(vec);
    std::cout << "Loading of map finished\n";

    this->window->display();
    std::cout << "Game is starting...\n";
}

void Game::run() {
    this->handleEvents();
    this->window->display();
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
