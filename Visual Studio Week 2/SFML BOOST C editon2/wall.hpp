#pragma once
#include "objectSuper.hpp"
#include <SFML/Graphics.hpp>

class wall : public objectSuper{
protected:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape wallShape;
public:
	wall();
	wall(sf::Vector2f size, sf::Vector2f position);
	void draw(sf::RenderWindow & window) override;
	void collision(objectSuper& object) override;
};