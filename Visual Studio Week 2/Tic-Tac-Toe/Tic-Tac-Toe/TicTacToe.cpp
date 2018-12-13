#include "TicTacToe.hpp"

TicTacToe::TicTacToe(){
	if (!font.loadFromFile("PIXEARG_.ttf")) {
		std::cout << "Could not load font" << std::endl;
	}
	lastUndo = std::chrono::system_clock::now();
}

TicTacToe::~TicTacToe()
{
}

int TicTacToe::checkKeypress() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { return 1; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { return 2; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { return 3; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) { return 4; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) { return 5; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) { return 6; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) { return 7; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) { return 8; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) { return 9; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) { return 0; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) { return 1; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) { return 2; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) { return 3; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) { return 4; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) { return 5; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) { return 6; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) { return 7; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) { return 8; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) { return 9; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) { return 0; }
		else { return 20; }
}

void TicTacToe::update() {
	int command = checkKeypress();
	if (command == 0) {
		undo();
	}
	else if (command != 0 && command < 10 && !gameFinished){
		selectPosition(command);
	}


}

void TicTacToe::selectPosition(int command) {
	Turn lastTurn = turns.back();
	int position = command - 1;
	if (lastTurn.getPlayerOnPos(position) == "#") {
		if (turns.size() > 0) {
			lastTurn.update(currentPlayer, position);
			turns.push_back(lastTurn);
			checkForWin();
			if (currentPlayer == 'X') {
				currentPlayer = 'O';
			}
			else if (currentPlayer == 'O') {
				currentPlayer = 'X';
			}
		}
		if (!gameFinished) {
			std::cout << "It's " << currentPlayer << "'s turn." << std::endl;
			printTurn();
		}
	}
}

void TicTacToe::checkForWin() {
	Turn lastTurn = turns.back();
	std::array<std::string , 9> layout = lastTurn.getLayout();
	//Row
	if ((layout[0] != "#" && layout[1] != "#" && layout[1] != "#") && (layout[0] == layout[1] && layout[1] == layout[2])) { gameFinished = true; winner = currentPlayer;}
	if ((layout[3] != "#" && layout[4] != "#" && layout[5] != "#") && (layout[3] == layout[4] && layout[4] == layout[5])) { gameFinished = true; winner = currentPlayer;}
	if ((layout[6] != "#" && layout[7] != "#" && layout[8] != "#") && (layout[6] == layout[7] && layout[7] == layout[8])) { gameFinished = true; winner = currentPlayer;}

	//Column
	if ((layout[0] != "#" && layout[3] != "#" && layout[6] != "#") && (layout[0] == layout[3] && layout[3] == layout[6])) { gameFinished = true; winner = currentPlayer;}
	if ((layout[1] != "#" && layout[4] != "#" && layout[7] != "#") && (layout[1] == layout[4] && layout[4] == layout[7])) { gameFinished = true; winner = currentPlayer;}
	if ((layout[2] != "#" && layout[5] != "#" && layout[8] != "#") && (layout[2] == layout[5] && layout[5] == layout[8])) { gameFinished = true; winner = currentPlayer;}

	//Diagonal
	if ((layout[0] != "#" && layout[4] != "#" && layout[8] != "#") && (layout[0] == layout[4] && layout[4] == layout[8])) { gameFinished = true; winner = currentPlayer;}
	if ((layout[2] != "#" && layout[4] != "#" && layout[6] != "#") && (layout[2] == layout[4] && layout[4] == layout[6])) { gameFinished = true; winner = currentPlayer;}
	
	if (layout[0] != "#" && layout[1] != "#" && layout[2] != "#" && 
		layout[3] != "#" && layout[4] != "#" && layout[5] != "#" && 
		layout[6] != "#" && layout[7] != "#" && layout[8] != "#") 
	{ 
		gameFinished = true; 
		winner = "#";
	}
}

void TicTacToe::start() {
	std::array<std::string, 9> emptyField = {"#", "#", "#", "#", "#", "#", "#", "#", "#", };
	Turn firstTurn = Turn(0, 'A', emptyField);
	turns.push_back(firstTurn);
	std::cout << "It's " << currentPlayer << "'s turn." << std::endl;
	printTurn();
}

void TicTacToe::undo() {
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<double> period = now - lastUndo;
	if (period.count() > 0.250) {
		if (!turns.empty() && turns.size() > 1) {
			
			Turn lastTurn = turns.back();
			turns.pop_back();
			currentPlayer = lastTurn.getPlayer();
			if (gameFinished) { gameFinished = !gameFinished; }
			lastUndo = std::chrono::system_clock::now();
			std::cout << "It's " << currentPlayer << "'s turn." << std::endl;
			printTurn();
		}
	}
}

void TicTacToe::printTurn() {
	Turn lastTurn = turns.back();
	std::array<std::string, 9> layout = lastTurn.getLayout();

	std::string firstRow = layout[6] + " " + layout[7] + " " + layout[8];
	std::string secondRow = layout[3] + " " + layout[4] + " " + layout[5];
	std::string thirdRow = layout[0] + " " + layout[1] + " " + layout[2];
	
	std::cout << firstRow << std::endl;
	std::cout << secondRow << std::endl;
	std::cout << thirdRow << std::endl;
}

void TicTacToe::showScreen(sf::RenderWindow & window) {
	Turn lastTurn = turns.back();
	std::array<std::string, 9> layout = lastTurn.getLayout();

	std::string firstRow = layout[6] + " " + layout[7] + " " + layout[8];
	std::string secondRow = layout[3] + " " + layout[4] + " " + layout[5];
	std::string thirdRow = layout[0] + " " + layout[1] + " " + layout[2];

	sf::Text first(firstRow, font, 24);
	sf::Text second(secondRow, font, 24);
	sf::Text third(thirdRow, font, 24);
	first.setPosition(sf::Vector2f(0, 0));
	second.setPosition(sf::Vector2f(0, 32));
	third.setPosition(sf::Vector2f(0, 64));
	first.setFillColor(sf::Color::White);
	second.setFillColor(sf::Color::White);
	third.setFillColor(sf::Color::White);

	window.draw(first);
	window.draw(second);
	window.draw(third);
}

void TicTacToe::printWinner() {
	if (winner == "#") {
		std::cout << "It's a tie!" << std::endl;
	}
	else {
		std::cout << winner << " has won!" << std::endl;
	}
	printTurn();
}

void TicTacToe::showWinner(std::string & info) {
	if (!winnerDeclared) {
		printWinner();
		winnerDeclared = true;
	}
	if (winner == "#") {
		info += "It's a tie!";
	}
	else {
		info += winner;
		info += " has won!";
	}
}

void TicTacToe::showGame(sf::RenderWindow & window) {
	Turn lastTurn = turns.back();
	std::array<std::string, 9> layout = lastTurn.getLayout();
	std::array<int, 9> layoutI;
	for (int i = 0; i < layout.size(); i++) {
		if (layout[i] == "#") { layoutI[i] = 1; }
		if (layout[i] == "O") { layoutI[i] = 2; }
		if (layout[i] == "X") { layoutI[i] = 3; }
	}
	
	level[6] = layoutI[6];
	level[7] = layoutI[7];
	level[8] = layoutI[8];
	level[11] = layoutI[3];
	level[12] = layoutI[4];
	level[13] = layoutI[5];
	level[16] = layoutI[0];
	level[17] = layoutI[1];
	level[18] = layoutI[2];

	if (!map.load("TicTacToe.png", sf::Vector2u(64,64), level, 5, 6)) {
		std::cout << "Could not load map." << std::endl;
	}

	std::string info = "";

	
	if (!gameFinished) {
		info += "It's ";
		info += currentPlayer;
		info += "'s turn.";
	}
	else {
		showWinner(info);
	}
	

	sf::Text turn(info, font, 24);
	turn.setPosition(sf::Vector2f(4, 4));
	turn.setFillColor(sf::Color::White);

	sf::Text undo("Undo", font, 32);
	undo.setPosition(sf::Vector2f(80, 336));
	undo.setFillColor(sf::Color::White);

	
	window.draw(map);
	window.draw(turn);
	window.draw(undo);
}

void TicTacToe::interact(sf::RenderWindow & window) {
	if (sf::Mouse::isButtonPressed(leftMouseButton)) {
		sf::Vector2i position = sf::Mouse::getPosition(window);
		
		int tileY = (position.y / 64) * 5;
		int tileX = (position.x / 64);
		int tilePosition = tileY + tileX;

		if (tilePosition < 30) {
			if (!gameFinished) {
				if (tilePosition == 6) { selectPosition(7); }
				if (tilePosition == 7) { selectPosition(8); }
				if (tilePosition == 8) { selectPosition(9); }

				if (tilePosition == 11) { selectPosition(4); }
				if (tilePosition == 12) { selectPosition(5); }
				if (tilePosition == 13) { selectPosition(6); }

				if (tilePosition == 16) { selectPosition(1); }
				if (tilePosition == 17) { selectPosition(2); }
				if (tilePosition == 18) { selectPosition(3); }
			}


			if (tilePosition == 26 || tilePosition == 27) {
				undo();
			}
		}

	}
}