#ifndef GAME
#define GAME "GAME.hpp"

#include "SFML/Graphics.hpp"
#include "map.hpp"

const std::string GAME_TITLE = "Bomber-man";

class Game {
private:
    sf::RenderWindow *window;
    sf::Event event{};
    bool finished = false;

    void handleEvents();

public:
    Game();

    ~Game();

    void start();

    bool isClosed();

    void run();

    bool isFinished();

    static int getRandomNumber(int startRange, int endRange);
};


#endif
