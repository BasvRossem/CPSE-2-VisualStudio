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
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	throw unknownColor(s);
}

std::ifstream & operator>>(std::ifstream & input, sf::Vector2f & rhs) {
	std::string s;
	input >> s;
	bool x_fetched = false;
	for (unsigned int index = 0; index < s.length(); index++) {
		if (s[index] == '(') {
			x_fetched = false;
		}
		else if (s[index] == ',') {
			x_fetched = true;
		}
		else if ((s[index] >= '0' && s[index] <= '9') && x_fetched == false) {
			rhs.x *= 10;
			rhs.x += (int)s[index] - '0';
		}
		else if (s[index] >= '0' && s[index] <= '9' && x_fetched == true) {
			rhs.y *= 10;
			rhs.y += (int)s[index] - '0';
		}
		else if (s[index] == ')') {
			return input;
		}
		else {
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw wrongCoordinate(s);
		}
	}
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