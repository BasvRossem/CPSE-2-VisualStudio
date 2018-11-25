#include "ball.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
ball::ball(sf::Vector2f position, float size, sf::Vector2f direction) :
	position{ position },
	size{ size },
	direction{ direction }
{
	ballShape.setRadius(size);
	ballShape.setPosition(position);
}

void ball::draw(sf::RenderWindow & window) {
	ballShape.setPosition(position);
	window.draw(ballShape);
}

void ball::collision(objectSuper& object) {
	if (this != &object) {
		hitbox = ballShape.getGlobalBounds();
		if (hitbox.intersects(object.hitbox)) {
			//SideRacts
			sf::Rect<float> topBox (hitbox.left + 5,				hitbox.top,						hitbox.width - 10, 5);
			sf::Rect<float> botBox (hitbox.left + 5,				hitbox.top + hitbox.height - 5,	hitbox.width - 10, 5);
			sf::Rect<float> lefBox (hitbox.left,					hitbox.top + 5,					5, hitbox.height - 10);
			sf::Rect<float> rigBox (hitbox.left + hitbox.width - 5, hitbox.top + 5,					5, hitbox.height - 10);

			action actions[] = {

				action([&] { return object.hitbox.intersects(topBox); },	[&]() { direction.y *= -1; move(sf::Vector2f(0.0,  +1.0)); }),
				action([&] { return object.hitbox.intersects(botBox); },	[&]() { direction.y *= -1; move(sf::Vector2f(0.0, -1.0)); }),
				action([&] { return object.hitbox.intersects(lefBox); },	[&]() { direction.x *= -1; move(sf::Vector2f(+1.0, 0.0)); }),
				action([&] { return object.hitbox.intersects(rigBox); },	[&]() { direction.x *= -1; move(sf::Vector2f(-1.0, 0.0)); })
			};

			for (auto & action : actions) {
				action();
			}
		}
	}
}

void ball::move(sf::Vector2f delta) {
	position += delta;
}

void ball::move() {
	position += direction;
}

void ball::jump(sf::Vector2f target) {
	position = target;
}

void ball::jump(sf::Vector2i target) {
	jump(sf::Vector2f(
		static_cast<float>(target.x),
		static_cast<float>(target.y)
	));
}

