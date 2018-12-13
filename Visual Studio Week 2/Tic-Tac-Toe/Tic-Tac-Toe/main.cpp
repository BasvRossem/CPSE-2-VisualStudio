#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "TicTacToe.hpp"

int main()
{
	//test SFML
	sf::RenderWindow window(sf::VideoMode(320, 384), "SFML works!");

	TicTacToe game = TicTacToe();
	game.start();
	while (window.isOpen())
	{
		sf::Event event;
		window.clear();
		
		game.interact(window);
		game.update();
		game.showGame(window);

		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	} //END test SFML

	//test BOOST
	//END test BOOST
	return 0;
}