#include "headers/game.hpp"

int main() {
    Game game;
    game.start();
    
    do {
        game.run();
    } while (!game.isClosed());

    return 0;
}
