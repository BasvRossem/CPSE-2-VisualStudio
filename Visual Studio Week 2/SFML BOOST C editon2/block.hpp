#pragma once
#include "wall.hpp"

class block : public wall{
public:
	block(sf::Vector2f mysize, sf::Vector2f myposition);
	
	void move(sf::Vector2f delta);
	void jump(sf::Vector2f target);
	void jump(sf::Vector2i target);
	void collision(objectSuper& object);
};

