#ifndef GAME
#define GAME "GAME.hpp"
#ifndef PLAYER
#define PLAYER "player.hpp"
#include "SFML/Graphics.hpp"
#include "map.hpp"
#define MAX_HP 3;

class Player {
private:
    sf::RectangleShape shape;

    float movementSpeed;
    int hp;

    void initVariables();

    void initShape();

public:
    Player(float x = 0.f, float y = 0.f);

    void updatePosition();

    void updateWindowBoundsCollision(const sf::RenderTarget *target);

    void update(const sf::RenderTarget *target);

    void render(sf::RenderTarget *target);
};

#endif




const std::string GAME_TITLE = "Bomber-man";
const std::string MAP_INIT_FILE = "map.txt";

class Game {
private:
    bool finished = false;

    sf::RenderWindow *window;
    sf::Event event{};
    sf::Clock clock{};
    sf::Text timer{};
    sf::Font font{};

    Player player;
    Map *map;

    void handleEvents();

    void update();

    void updateTimer();

    std::vector<std::vector<MapObject>> readMap();

public:
    Game();

    ~Game();

    void start();
    void updatePlayer();
    bool isClosed();

    void run();
    void render();

    void initTimer();

    bool isFinished();

    static int getRandomNumber(int startRange, int endRange);
};


#endif
