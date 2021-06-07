#pragma once
#include "player.h"
#include "board.h"

class board;

class bot : public player {
	board* map;
	char sign;
	int minimax(bool isMax, int depth);
public:
	bot(board* b, char c) : map(b), sign(c) {}

	sf::Vector2i move() override;
};