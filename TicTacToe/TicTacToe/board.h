#pragma once
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "human.h"
#include "bot.h"
#include "winner.h"

class board {
	std::vector<std::vector<char>> grid;
	int requirement;
	int size;
	sf::RenderWindow& window;
	bool turn;
	player* p1;
	player* p2;
public:
	board(sf::RenderWindow& win, int size, int requi, int mode);
	~board() { delete p1, p2; }
	void draw();
	void play();
	bool check(char c);
	bool full();
	winner checkWinner();
	int getSize() { return this->size; }
	std::vector<std::vector<char>>& getGrid() { return this->grid; }
	int getWindowSize() { return this->window.getSize().x; }
	int score(char c);
};