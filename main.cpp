#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(448, 512), "Space Invaders");
	GameBoard board;
	SFMLboard sfmlboard(board, window,board.getEnemiesVector(),board.getMissilesVector());
	Game game(board, sfmlboard, window);
	while (window.isOpen())
	{
		game.Play();		
	}

	return 0;
}