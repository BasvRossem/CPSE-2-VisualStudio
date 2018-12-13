#pragma once
#include <array>
#include <string>
class Turn{
private:
	int number;
	char player;
	std::array<std::string, 9> layout;
public:
	Turn(int number, char player, std::array<std::string, 9> layout):
		number(number),
		player(player),
		layout(layout)
	{};

	void update(char player, int position);
	std::array<std::string, 9> getLayout();
	char getPlayer();
	std::string getPlayerOnPos(int position);
	~Turn();
};