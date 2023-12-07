#ifndef GAME
#define GAME "GAME.hpp"

#include "SFML/Graphics.hpp"
#include "player.hpp"
#include "enemy.hpp"
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
    std::vector<Enemy*> enemies;

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
    bool isClosed();

    void run();
    void render();

    void initEnemies(const std::vector<std::vector<MapObject>> &objects);
    void initTimer();
    bool isFinished();
    void updateEnemies();

    static int getRandomNumber(int startRange, int endRange);
    void renderEnemies();
};


#endif
