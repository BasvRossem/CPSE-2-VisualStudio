#pragma once

#include <SFML/Graphics.hpp>

class objectSuper{
public:
	sf::Rect<float> hitbox;
	virtual void draw(sf::RenderWindow &) = 0;
	virtual void collision(objectSuper&) = 0;
};