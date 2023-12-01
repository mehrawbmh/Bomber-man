
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>
class Player{
    private:
        sf::RectangleShape shape;

        float movementSpeed;
        int hp;
        int MaxHp;

        void initVariables();
        void initShape();
    public:
    Player(float x = 0.f, float y = 0.f);

    void updatePosition();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};