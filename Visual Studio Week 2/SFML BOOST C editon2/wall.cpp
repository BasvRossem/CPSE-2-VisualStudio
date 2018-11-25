#include "wall.hpp"
#include <SFML/Graphics.hpp>

wall::wall():
	position{ sf::Vector2f{ 0.0, 0.0  } },
	size{ sf::Vector2f{ 640.0,	32.0  } }
{
	wallShape.setSize(size);
	wallShape.setPosition(position);
	wallShape.setFillColor(sf::Color(100, 250, 50));
	hitbox = wallShape.getGlobalBounds();
}

wall::wall(sf::Vector2f size, sf::Vector2f position):
	position{ position },
	size{ size }
{
	wallShape.setSize(size);
	wallShape.setPosition(position);
	wallShape.setFillColor(sf::Color(100, 250, 50));
	hitbox = wallShape.getGlobalBounds();
}

void wall ::draw(sf::RenderWindow & window) {
	wallShape.setPosition(position);
	hitbox = wallShape.getGlobalBounds();
	window.draw(wallShape);
}

void wall::collision(objectSuper& object) {
	wallShape.getGlobalBounds();
}