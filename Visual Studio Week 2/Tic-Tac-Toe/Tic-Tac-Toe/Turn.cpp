#include "Turn.hpp"



//Turn::Turn()
//{
//}


Turn::~Turn()
{
}

void Turn::update(std::string newPlayer, int position) {
	player = newPlayer;
	layout[position] = newPlayer;
}

std::array<std::string, 9> Turn::getLayout() {
	return layout;
}

std::string Turn::getPlayer() {
	return player;
}

std::string Turn::getPlayerOnPos(int position) {
	return layout[position];
}