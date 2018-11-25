#include <iostream>
#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "action.hpp"
#include "wall.hpp"
#include "block.hpp"

int main(){
	std::cout << "Starting application 01-05 array of actions\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 640 }, "SUPER COOLE GAME WOW" };
	ball my_ball{ sf::Vector2f{ 320.0,	240.0 }};
	wall top	{ sf::Vector2f{ 640.0,	32.0  }, sf::Vector2f{ 0.0,   0.0 }  };
	wall down	{ sf::Vector2f{ 640.0,	32.0  }, sf::Vector2f{ 0.0,   608.0} };
	wall left	{ sf::Vector2f{ 32.0,	640.0 }, sf::Vector2f{ 0.0,   0.0}   };
	wall right	{ sf::Vector2f{ 32.0,	640.0 }, sf::Vector2f{ 608.0, 0.0}   };
	block my_blokje { sf::Vector2f{ 128.0,	32.0  }, sf::Vector2f{ 50.0,  50.0}  };
	
	objectSuper * objects[] = {
		&my_blokje,
		&my_ball,
		&top,
		&down,
		&left,
		&right
	};

	action actions[] = {
		action(sf::Keyboard::Up,	[&]() { my_blokje.move	(sf::Vector2f(0.0,  -2.0)); }),
		action(sf::Keyboard::Down,	[&]() { my_blokje.move	(sf::Vector2f(0.0,  +2.0)); }),
		action(sf::Keyboard::Left,	[&]() { my_blokje.move	(sf::Vector2f(-2.0,  0.0)); }),
		action(sf::Keyboard::Right,	[&]() { my_blokje.move	(sf::Vector2f(+2.0,  0.0)); }),
		action(sf::Mouse::Left,		[&]() { my_blokje.jump	(sf::Mouse::getPosition(window)); }),
		action(sf::Mouse::Right,	[&]() { my_ball.jump	(sf::Mouse::getPosition(window)); }),
		action(						[&]() { my_ball.move	(); })
	};

	while (window.isOpen()) {
		window.clear();

		for( auto & action : actions ){
			action();
		}

		for (auto & p : objects) {
			p->draw(window);
			for (auto & other : objects) {
				p->collision(*other);
			}
		}

        sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}	

		window.display();
		sf::sleep(sf::milliseconds(1000 / 60));
	}

	std::cout << "Terminating application\n";
	return 0;
}

