#include <SFML/Graphics.hpp>
#include <iostream>
#include "board.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Tic-Tac-Toe");

	sf::Event event;

	restart:

	
	int s, r, m;
	std::cout << "Rozmiar: \n";
	std::cin >> s;

	std::cout << "Wymagania: \n";
	std::cin >> r;

	std::cout << "Tryb: \n";
	std::cout << " 0 - Gracz vs Gracz \n";
	std::cout << " 1 - Gracz vs SI\n";
	std::cout << " 2 - SI vs Gracz\n";
	std::cout << " 3 - SI vs SI \n";
	std::cin >> m;

	board game(window, s, r, m);
	
	//board game(window, 3, 3);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
				return 0;
			}
		}

		window.clear();
		game.draw();
		window.display();
		switch ( game.checkWinner() )
		{
		case winner::_circle :
			std::cout << "***** O wygral *****\n";
			goto restart;
			break;
		case winner::_cross:
			std::cout << "***** X wygral *****\n";
			goto restart;
			break;
		case winner::_tie:
			std::cout << "***** Remis *****\n";
			goto restart;
			break;
		}
		game.play();
	}
	
	return 0;
}