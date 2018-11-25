#pragma once
#include <SFML/Graphics.hpp>
#include "objectSuper.hpp"
#include "action.hpp"
class ball : public objectSuper{
private:
	sf::CircleShape ballShape;
	sf::Vector2f position;
	sf::Vector2f direction;
	float size;

public:
	
	ball(sf::Vector2f position, float size = 30.0, sf::Vector2f direction = sf::Vector2f{ +1,  +1 });

	void draw(sf::RenderWindow & window) override;
	void collision(objectSuper& object) override;
	void move();
	void move(sf::Vector2f delta);

	void jump(sf::Vector2f target);
	void jump(sf::Vector2i target);
};

