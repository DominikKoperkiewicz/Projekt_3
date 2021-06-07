#include "bot.h"

int bot::minimax(bool isMax, int depth)
{
    if (depth <= 0) { return map->score(this->sign)-map->score('x'); }
    switch (map->checkWinner())
    {
    case winner::_circle:
        if (this->sign == 'o') 
        { 
            return 1000+depth;
        }
        else 
        {
            return -1000 - depth;
        }
        break;
    case winner::_cross:
        if (this->sign == 'x')
        {
            return 1000 + depth;
        }
        else
        {
            return -1000 - depth;
        }
        break;
    case winner::_tie:
        return 0;
        break;
    }

    if (isMax)
    {
        int best = INT_MIN;

        for (int i = 0; i < map->getSize(); i++)
            for (int j = 0; j < map->getSize(); j++)
            {
                if (map->getGrid()[i][j] == 'e')
                {
                    map->getGrid()[i][j] = this->sign;
                    int score = this->minimax(false,depth-1);
                    map->getGrid()[i][j] = 'e';
                    if (score > best)
                    {
                        best = score;
                    }
                }
            }
        return best;
    }
    else
    {
        int best = INT_MAX;

        for (int i = 0; i < map->getSize(); i++)
            for (int j = 0; j < map->getSize(); j++)
            {
                if (map->getGrid()[i][j] == 'e')
                {
                    if (this->sign == 'o')
                    {
                        map->getGrid()[i][j] = 'x';
                    }
                    else
                    {
                        map->getGrid()[i][j] = 'o';
                    }

                    int score = this->minimax(true, depth - 1);
                    map->getGrid()[i][j] = 'e';
                    if (score < best)
                    {
                        best = score;
                    }
                }
            }
        return best;
    }

}

sf::Vector2i bot::move()
{
    int width = map->getWindowSize() / map->getSize();
    int best = INT_MIN;
    sf::Vector2i ret;

    for (int i = 0; i < map->getSize(); i++)
        for (int j = 0; j < map->getSize(); j++)
        {
            if ( map->getGrid()[i][j] == 'e')
            {
                map->getGrid()[i][j] = this->sign;
                int score = this->minimax(false,12 - 2*map->getSize());
                map->getGrid()[i][j] = 'e';
                if (score > best)
                {
                    best = score;
                    ret = sf::Vector2i((i + 0.5f) * width, (j + 0.5f) * width);
                }
            }
        }

    return ret;
}

/* TO DO LIST
* score(); - wyliczanie wartoœci 'pozycji' na podstawie iloœci lini i ich d³ugpoœci
*            wtedy powinno dzia³aæ przy mniejszym depth
*/