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
    sf::Text endGameNote{};
    sf::Font font{};
    sf::Font secondaryFont{};
    sf::Time gameTime;

    Player *player;
    Map *map;
    std::vector<Enemy*> enemies;

    void handleEvents();

    void showEndGameText();

    void update();

    void updateTimer();

    void readMap();

    static sf::Time readGameTime(const std::string &timeString);

    void initEnemies(const std::vector<std::vector<MapObject>> &objects);

    void initTimer();

    void initFonts();

    void initStats();

    bool isFinished() const;

    void updateEnemies();

    void renderEnemies();

    void handlePlayerEnemyCollision();

    void handlePlayerKeyCollision();

    void handlePlayerDoorCollision();

    void handlePlayerPowerUpCollision();

    bool isPlayerDead();

    bool isPlayerInvincible() const;

    void updatePlayer();

    void updateStats();

    void updateMap();

    void render();

public:
    Game();

    ~Game();

    void start();

    bool isClosed();

    void run();

    bool hasPlayerWon();
};

#endif
