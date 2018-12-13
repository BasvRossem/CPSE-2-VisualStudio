#include "Turn.hpp"



//Turn::Turn()
//{
//}


Turn::~Turn()
{
}

void Turn::update(char newPlayer, int position) {
	player = newPlayer;
	layout[position] = newPlayer;
}

std::array<std::string, 9> Turn::getLayout() {
	return layout;
}

char Turn::getPlayer() {
	return player;
}

std::string Turn::getPlayerOnPos(int position) {
	return layout[position];
}