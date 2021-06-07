#pragma once
#include <SFML\Graphics.hpp>

class player {
protected:

public:
	player() {}
	~player() {}
	virtual sf::Vector2i move() = 0;
};