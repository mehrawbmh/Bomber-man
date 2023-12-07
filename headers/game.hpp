#ifndef GAME
#define GAME "GAME.hpp"

#include "SFML/Graphics.hpp"
#include "player.hpp"
#include "map.hpp"

const std::string GAME_TITLE = "Bomber-man";
const std::string MAP_INIT_FILE = "map.txt";
const std::string DEFAULT_FONT_FILE = "fonts/arial.ttf";

class Game {
private:
    bool finished = false;

    sf::RenderWindow *window;
    sf::Event event{};
    sf::Clock clock{};
    sf::Text timer{};
    sf::Font font{};
    sf::Time gameTime;

    Player *player;
    Map *map;

    void handleEvents();

    void update();

    void updateTimer();

    void readMap();
    static sf::Time readGameTime(const std::string &timeString);

public:
    Game();

    ~Game();

    void start();
    void updatePlayer();
    void updateMap();
    bool isClosed();

    void run();
    void render();

    void initTimer();
    void updateCollision();
    bool isFinished() const;

    static int getRandomNumber(int startRange, int endRange);
};


#endif
