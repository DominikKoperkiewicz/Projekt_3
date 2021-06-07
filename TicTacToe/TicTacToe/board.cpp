#include "board.h"

board::board(sf::RenderWindow& win, int size, int requi, int mode) : window(win), size(size), requirement(requi) , turn(true)
{

	if (size < requi)
	{
		this->size = 3;
		this->requirement = 3;
		std::cout << "Liczba znakow w rzedzie nie moze przekraczac rozmiaru planszy! (Plansza ustawiona na domyœlne 3x3)\n";
	}
	
	if (mode < 0 || mode > 3)
	{
		mode = 0;
		std::cout << "Nie ma takiego trybu (tryb ustawiony na PvP)\n";
	}


	for (int i = 0; i < this->size; i++)
		this->grid.push_back(std::vector<char>());

	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			this->grid[i].push_back('e');

	switch (mode)
	{
		case 0: // PvP
			this->p1 = new human(win);
			this->p2 = new human(win);
			break;
		case 1: // PvAI
			this->p1 = new human(win);
			this->p2 = new bot(this, 'x');
			break;
		case 2: // AIvP
			this->p1 = new bot(this, 'o');
			this->p2 = new human(win);
			break;
		case 3: // AIvAI
			this->p1 = new bot(this, 'o');
			this->p2 = new bot(this, 'x');
			break;
			
	}
}

void board::draw()
{
	sf::Color black(0, 0, 0);
	sf::Color white(255, 255, 255);
	float width = (float)(this->window.getSize().x / this->size);
	//FIELD
	sf::RectangleShape square(sf::Vector2f(width, width));
	square.setOutlineThickness(2);
	square.setOutlineColor(black);
	square.setFillColor(white);

	//CIRCLE
	sf::CircleShape circle(width * 0.42f);
	circle.setOutlineThickness(3);
	circle.setOutlineColor(black);
	circle.setFillColor(white);
	//CROSS
	sf::RectangleShape line_1(sf::Vector2f(width, 3));
	sf::RectangleShape line_2(sf::Vector2f(width, 3));
	line_1.rotate(45);
	line_2.rotate(-45);
	line_1.setFillColor(black);
	line_2.setFillColor(black);

	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
		{
			square.setPosition(width * i, width * j);
			this->window.draw(square);

			if (grid[i][j] == 'o')
			{
				circle.setPosition(width * i + width * 0.08f, width * j + width * 0.08f);
				this->window.draw(circle);
			}
			else if (grid[i][j] == 'x')
			{
				line_1.setPosition(width * i + width * 0.146447f, width * j + width * 0.146447f);
				line_2.setPosition(width * i + width * 0.146447f, width * j + width * 0.146447f + width * 0.7071068f);
				this->window.draw(line_1);
				this->window.draw(line_2);
			}
		}
}

void board::play()
{
	float width = (float)(this->window.getSize().x / this->size);

	if(this->turn)
	{
		sf::Vector2i vec = p1->move();
		int _x = (int)(vec.x / width);
		int _y = (int)(vec.y / width);
		//std::cout << "[ " << vec.x << " , " << vec.y << " ]\n";
		//std::cout << "- [ " << _x << " , " << _y << " ]\n";
		if ( _x >= 0 && _y >= 0 && _x < this->size && _y < this->size && this->grid[_x][_y] == 'e' )
		{
			this->grid[_x][_y] = 'o';
			this->turn = false;
			std::cout << "X turn\n";
		}
	}
	else
	{
		sf::Vector2i vec = p2->move();
		int _x = (int)(vec.x / width);
		int _y = (int)(vec.y / width);
		if ( _x >= 0 && _y >= 0 && _x < this->size && _y < this->size && this->grid[_x][_y] == 'e')
		{
			this->grid[_x][_y] = 'x';
			this->turn = true;
			std::cout << "O turn\n";
		}

	}
}

bool board::check(char c)
{
	int tmp = this->size - this->requirement + 1;
	int r;
	//ROW
	for(int i = 0; i < this->size; i++)
		for (int j = 0; j < tmp; j++)
		{
			if (this->grid[j][i] == c)
			{
				for (r = 0; j < this->size && this->grid[j][i] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { return true; }
				
			}
		}

	//COLUMNS
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < tmp; j++)
		{
			if (this->grid[i][j] == c)
			{
				for (r = 0; j < this->size && this->grid[i][j] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { return true; }

			}
		}
	//DIAGONAL \. 
	for (int i = 0; i < tmp; i++)
		for (int j = 0; j < tmp-i; j++)
		{
			if (this->grid[i + j][j] == c)
			{
				for (r = 0; j < this->size-i && this->grid[i + j][j] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { return true; }

			}
		}
	for (int i = 0; i < tmp; i++)
		for (int j = 0; j < tmp - i; j++)
		{
			if (this->grid[j][i + j] == c)
			{
				for (r = 0; j < this->size - i && this->grid[j][i + j] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { return true; }

			}
		}
	//DIAGONAL /

	for (int i = this->requirement - 1; i < this->size; i++)
		for (int j = 0; j < i; j++)
		{
			if (this->grid[j][i-j] == c)
			{
				for (r = 0; j < i+1  && this->grid[j][i-j] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { return true; }

			}
		}
	for (int i = 1; i < tmp; i++)
		for (int j = 0; j < this->size-i; j++)
		{
			if (this->grid[i + j][this->size - j - 1] == c)
			{
				for (r = 0; j < this->size-i && this->grid[i + j][this->size - j - 1] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { return true; }

			}
		}
	return false;
}

bool board::full()
{
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
		{
			if ( this->grid[i][j] == 'e' ) { return false; }
		}
	return true;
}

winner board::checkWinner()
{
	if ( this->check('o') )
	{
		return winner::_circle;
	}
	if ( this->check('x') )
	{
		return winner::_cross;
	}
	if ( this->full() )
	{
		return winner::_tie;
	}
	
	return winner::_none;
}

int board::score(char c)
{
	int tmp = this->size - this->requirement + 1;
	int r;
	int score = 0;
	//ROW
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < tmp; j++)
		{
			if (this->grid[j][i] == c)
			{
				for (r = 0; j < this->size && this->grid[j][i] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { score += r * 5; }

			}
		}

	//COLUMNS
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < tmp; j++)
		{
			if (this->grid[i][j] == c)
			{
				for (r = 0; j < this->size && this->grid[i][j] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { score += r * 5; }

			}
		}
	//DIAGONAL \. 
	for (int i = 0; i < tmp; i++)
		for (int j = 0; j < tmp - i; j++)
		{
			if (this->grid[i + j][j] == c)
			{
				for (r = 0; j < this->size - i && this->grid[i + j][j] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { score += r * 5; }

			}
		}
	for (int i = 0; i < tmp; i++)
		for (int j = 0; j < tmp - i; j++)
		{
			if (this->grid[j][i + j] == c)
			{
				for (r = 0; j < this->size - i && this->grid[j][i + j] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { score += r * 5; }

			}
		}
	//DIAGONAL /

	for (int i = this->requirement - 1; i < this->size; i++)
		for (int j = 0; j < i; j++)
		{
			if (this->grid[j][i - j] == c)
			{
				for (r = 0; j < i + 1 && this->grid[j][i - j] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { score += r * 5; }

			}
		}
	for (int i = 1; i < tmp; i++)
		for (int j = 0; j < this->size - i; j++)
		{
			if (this->grid[i + j][this->size - j - 1] == c)
			{
				for (r = 0; j < this->size - i && this->grid[i + j][this->size - j - 1] == c; j++, r++); //r < this->requirement && 
				if (r >= this->requirement) { score += r * 5; }

			}
		}
	return score;
}
