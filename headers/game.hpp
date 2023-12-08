#ifndef GAME
#define GAME "GAME.hpp"

#include "SFML/Graphics.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "map.hpp"

const std::string GAME_TITLE = "Bomber-man";
const std::string MAP_INIT_FILE = "map.txt";
const std::string DEFAULT_FONT_FILE = "fonts/arial.ttf";
const std::string SECONDARY_FONT_FILE = "fonts/calibri.ttf";

const int GAME_FPS = 100;
const int INVINCIBLE_DURATION = 2;

class Game {
private:
    bool finished = false;
    long lastHitTime;

    sf::RenderWindow *window;
    sf::Event event{};
    sf::Clock clock{};
    sf::Text timer{};
    sf::Text stats{};
    sf::Font font{};
    sf::Font secondaryFont{};
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
    void updateStats();
    void updateMap();
    bool isClosed();

    void run();
    void render();

    void initEnemies(const std::vector<std::vector<MapObject>> &objects);
    void initTimer();
    void initFonts();
    void initStats();
    bool isFinished() const;
    void updateEnemies();

    void renderEnemies();
    void playerEnemyCollision();
    bool isPlayerDead();
    bool isPlayerInvincible() const;
};


#endif
