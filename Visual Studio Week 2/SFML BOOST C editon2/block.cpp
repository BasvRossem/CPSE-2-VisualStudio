#include "block.hpp"
#include "action.hpp"

block::block(sf::Vector2f mysize, sf::Vector2f myposition)
{
	position = myposition;
	size = mysize;
	wallShape.setSize(size);
	wallShape.setPosition(position);
	wallShape.setFillColor(sf::Color(50, 50, 50));
}

void block::move(sf::Vector2f delta) {
	position += delta;
}

void block::jump(sf::Vector2f target) {
	position = target;
}

void block::jump(sf::Vector2i target) {
	jump(sf::Vector2f(
		static_cast<float>(target.x),
		static_cast<float>(target.y)
	));
}

void block::collision(objectSuper& object) {
	if (this != &object) {
		if (hitbox.intersects(object.hitbox)) {
			//SideRacts
			sf::Rect<float> topBox(hitbox.left + 5, hitbox.top, hitbox.width - 10, 5);
			sf::Rect<float> botBox(hitbox.left + 5, hitbox.top + hitbox.height - 5, hitbox.width - 10, 5);
			sf::Rect<float> lefBox(hitbox.left, hitbox.top + 5, 5, hitbox.height - 10);
			sf::Rect<float> rigBox(hitbox.left + hitbox.width - 5, hitbox.top + 5, 5, hitbox.height - 10);

			action actions[] = {
				action([&] { return object.hitbox.intersects(topBox); },	[&]() { move(sf::Vector2f(0.0,  +3.0)); }),
				action([&] { return object.hitbox.intersects(botBox); },	[&]() { move(sf::Vector2f(0.0,  -3.0)); }),
				action([&] { return object.hitbox.intersects(lefBox); },	[&]() { move(sf::Vector2f(+3.0,  0.0)); }),
				action([&] { return object.hitbox.intersects(rigBox); },	[&]() { move(sf::Vector2f(-3.0,  0.0)); })
			};

			for (auto & action : actions) {
				action();
			}
		}
	}
}