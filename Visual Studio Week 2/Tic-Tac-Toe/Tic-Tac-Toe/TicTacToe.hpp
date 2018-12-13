#pragma once
#include "Turn.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <string>
#include "Tilemap.hpp"
#include <vector>
#include <chrono>
#include <ctime>

class TicTacToe{
private:
	std::vector<Turn> turns = {};
	char currentPlayer = 'X';
	char lastPlayer = 'O';
	bool gameFinished = false;
	std::string winner = "#";
	bool winnerDeclared = false;
	sf::Font font;
	TileMap map;
	sf::Mouse::Button leftMouseButton = sf::Mouse::Left;
	sf::Mouse::Button rightMouseButton = sf::Mouse::Right;
	std::vector<int> level = {
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,4,5,0,0, };
	std::chrono::time_point<std::chrono::system_clock> lastUndo;

public:
	TicTacToe();
	~TicTacToe();

	int checkKeypress();
	void update();
	void start();
	void undo();
	void printTurn();
	void checkForWin();
	void showScreen(sf::RenderWindow & window);
	void printWinner();
	void showWinner(std::string & info);
	void showGame(sf::RenderWindow & window);
	void interact(sf::RenderWindow & window);
	void selectPosition(int command);
};

