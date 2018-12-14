#include <iostream>
#include "movableScreenObject.hpp"
#include <string>
#include <fstream>
#include "errorsAndExceptions.hpp"
#include <SFML/Graphics.hpp>
#include "movableScreenObject.hpp"
#include <vector>
#include "iostreamOverloaders.hpp"


movableScreenObject * screenObjectRead(std::ifstream & input) {
	sf::Vector2f position;
	std::string name;
	input >> position >> name;
	//std::cout << name << std::endl;
	if (name == "CIRCLE") {
		sf::Color color;
		float size;
		input >> color >> size;
		return new circleObject(position, size, color);
	}
	else if (name == "RECTANGLE") {
		sf::Vector2f size;
		sf::Color color;
		input >> color >> size;
		return new rectangleObject(position, size, color);
	}
	else if (name == "PICTURE") {
		std::string pictureName;
		input >> pictureName;
		return new pictureObject(position, pictureName);
	}
	else if (name == "LINE") {
		sf::Vector2f endPoint;
		sf::Color color;
		input >> color >> endPoint;
		return new lineObject(position, endPoint, color);
	}
	else if (name == "") {
		throw endOfFile();
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	throw unknownShape(name);
}

int main() {
	std::cout << "Starting application 01-05 array of actions\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 640 }, "Beweeg die shit" };

	std::ifstream input("objects.txt");
	std::ofstream output("save.txt", std::ofstream::out);
	std::ofstream errors("errors.txt", std::ofstream::out);
	std::vector<movableScreenObject *> objects = {};
	
	for (;;) {
		try {
			objects.push_back(screenObjectRead(input)); objects.push_back(screenObjectRead(input));
		}
		catch (endOfFile) {
			break;

		}
		catch (std::exception & problem) {
			
			std::cout << problem.what() << std::endl;
			errors << problem.what() << '\n';
		}
	}



	//rectangleObject blokje( sf::Vector2f(0.0, 0.0), sf::Vector2f(50.0, 100.0), sf::Color::Red );
	//circleObject	ball(sf::Vector2f(250.0, 250.0), 30.0, sf::Color::Blue);
	//lineObject		line(sf::Vector2f(150.0, 150.0), sf::Vector2f(300.0, 300.0), sf::Color::Green);
	//pictureObject	wow(sf::Vector2f(500.0, 500.0), "Wow1.png");

	bool lastMouseState = 0;
	auto leftMouseButton = sf::Mouse::Left;
	

	sf::Vector2f upDirection =		sf::Vector2f(0.0, -2.0);
	sf::Vector2f downDirection =	sf::Vector2f(0.0, +2.0);
	sf::Vector2f leftDirection =	sf::Vector2f(-2.0, 0.0);
	sf::Vector2f rightDirection =	sf::Vector2f(+2.0, 0.0);

	//action actions[] = {
	//	action(sf::Keyboard::Up,	[&]() { object->move(upDirection); }),
	//	action(sf::Keyboard::Down,	[&](movableScreenObject * object) { object->move(downDirection); }),
	//	action(sf::Keyboard::Left,	[&](movableScreenObject * object) { object->move(leftDirection); }),
	//	action(sf::Keyboard::Right,	[&](movableScreenObject * object) { object->move(rightDirection); })
	//};



	while (window.isOpen()) {
		window.clear();

		//for (auto & action : actions) {
		//	action();
		//}
		
		if (sf::Mouse::isButtonPressed(leftMouseButton) && sf::Mouse::isButtonPressed(leftMouseButton) != lastMouseState) {
			for (auto & p : objects) {
				p->select(sf::Vector2f(sf::Mouse::getPosition(window)));
				if (p->getSelect()) {
					std::cout << p->getName() << std::endl;
				}				
			}
			lastMouseState = !lastMouseState;
			
		}
		else if (!sf::Mouse::isButtonPressed(leftMouseButton)) {
			lastMouseState = 0;
		}

		for (auto & p : objects) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { p->move(upDirection); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { p->move(downDirection); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { p->move(leftDirection); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { p->move(rightDirection); }
			p->draw(window);
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				for (auto & p : objects) {
					p->writeSave(output);
				}
				input.close();
				output.close();
				errors.close();
				window.close();
			}
		}

		window.display();
		sf::sleep(sf::milliseconds(1000 / 60));
	}

	std::cout << "Terminating application\n";
	return 0;
}