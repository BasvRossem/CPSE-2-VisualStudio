#pragma once
#include <array>
#include <string>
class Turn{
private:
	int number;
	std::string player;
	std::array<std::string, 9> layout;
public:
	Turn(int number, std::string player, std::array<std::string, 9> layout):
		number(number),
		player(player),
		layout(layout)
	{};

	void update(std::string player, int position);
	std::array<std::string, 9> getLayout();
	std::string getPlayer();
	std::string getPlayerOnPos(int position);
	~Turn();
};