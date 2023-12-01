#include <iostream>
#include <random>
#include "headers/game.hpp"

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), GAME_TITLE);
    this->font.loadFromFile("fonts/arial.ttf");
    this->map = new Map(this->window, this->event);
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
    this->initTimer();

    MapObject obj = Grass;
    std::vector<std::vector<MapObject>> vec = {{obj, obj}, {obj, obj}};

    std::cout << "Loading map...\n";
    this->map->init(vec);
    std::cout << "Loading of map finished\n";

    this->window->display();
    std::cout << "Game is starting...\n";
}

void Game::run() {
    this->handleEvents();
    this->update();
    this->window->display();
}

void Game::initTimer() {
    std::cout << "Loading timer...\n";
    this->clock.restart();
    this->timer.setFillColor(sf::Color::Black);
    this->timer.setCharacterSize(24);
    this->timer.setOutlineColor(sf::Color::Red);
    this->timer.setPosition(static_cast<float>(this->window->getSize().x - 150), 0.f);
    this->timer.setFont(this->font);
    std::cout << "Finished loading timer";
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

void Game::update() {
    this->updateTimer();
    this->map->update();

}

void Game::updateTimer() {
    sf::Time elapsedTime = this->clock.getElapsedTime();
    int seconds = static_cast<int>(elapsedTime.asSeconds());

    this->timer.setString("Timer: " + std::to_string(seconds));
    this->window->clear(sf::Color::White);
    this->window->draw(this->timer);
}
