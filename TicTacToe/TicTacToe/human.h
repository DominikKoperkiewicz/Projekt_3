#pragma once
#include "player.h"

class human : public player {
	sf::RenderWindow& window;
public:
	human(sf::RenderWindow& win) : window(win) {}
	sf::Vector2i move() override;
};