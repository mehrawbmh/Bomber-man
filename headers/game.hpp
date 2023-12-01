#ifndef GAME
#define GAME "GAME.hpp"

#include "SFML/Graphics.hpp"
#include "map.hpp"

const std::string GAME_TITLE = "Bomber-man";

class Game {
private:
    bool finished = false;

    sf::RenderWindow *window;
    sf::Event event{};
    sf::Clock clock{};
    sf::Text timer{};
    sf::Font font{};

    Map* map;

    void handleEvents();

    void update();

    void updateTimer();

    std::vector<std::vector<MapObject>> readMap();

public:
    Game();

    ~Game();

    void start();

    bool isClosed();

    void run();

    void initTimer();

    bool isFinished();

    static int getRandomNumber(int startRange, int endRange);
};


#endif
