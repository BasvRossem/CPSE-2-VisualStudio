#pragma once
#include <iostream>
#include "movableScreenObject.hpp"
#include <string>
#include <fstream>
#include "errorsAndExceptions.hpp"
#include "customExceptions.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "iostreamOverloaders.hpp"

std::ifstream & operator>>(std::ifstream & input, sf::Color & rhs) {
	std::string s;
	input >> s;
	const struct { const char * name; sf::Color color; } colors[]{
		{"black", sf::Color::Black},
		{"white", sf::Color::White},
		{"red", sf::Color::Red},
		{"green", sf::Color::Green},
		{"blue", sf::Color::Blue},
		{"yellow", sf::Color::Yellow},
		{"magenta", sf::Color::Magenta},
		{"cyan", sf::Color::Cyan},
		{"transparent", sf::Color::Transparent}
	};
	for (auto const & color : colors) {
		if (color.name == s) {
			rhs = color.color;
			return input;
		}
	}
	if (s == "") {
		throw endOfFile();
	}
	throw unknownColor(s);
}

std::ifstream & operator>>(std::ifstream & input, sf::Vector2f & rhs) {
	char c;
	if (!(input >> c)) { throw endOfFile(); }
	if (c != '(') { throw wrongCharacter(c); }

	if (!(input >> rhs.x)) { notAFloat('a'); }

	if (!(input >> c)) { throw endOfFile(); }

	if (!(input >> rhs.y)) { notAFloat('b'); }

	if (!(input >> c)) { throw endOfFile(); }
	if (c != ')') { throw wrongCharacter(c); }

	return input;
}

std::ofstream & operator << (std::ofstream & output, sf::Color & rhs) {
	std::string s;
	
	const struct { const char * name; sf::Color color; } colors[]{
		{"black", sf::Color::Black},
		{"white", sf::Color::White},
		{"red", sf::Color::Red},
		{"green", sf::Color::Green},
		{"blue", sf::Color::Blue},
		{"yellow", sf::Color::Yellow},
		{"magenta", sf::Color::Magenta},
		{"cyan", sf::Color::Cyan},
		{"transparent", sf::Color::Transparent}
	};

	for (auto const & color : colors) {
		if (color.color == rhs) {
			s = color.name;
			output << s;
			return output;
		}
	}
	if (s == "") {
		throw endOfFile();
	}
	throw unknownColor(s);
}