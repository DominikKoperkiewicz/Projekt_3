#include "human.h"

sf::Vector2i human::move()
{
    while (true)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            return sf::Mouse::getPosition(this->window);
        }
    }
}
