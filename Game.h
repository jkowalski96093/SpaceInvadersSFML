#pragma once
#include "SFMLboard.h"
#include <fstream>
class Game :
	public SFMLboard
{
	GameBoard &board;
	SFMLboard &sfmlboard;
	sf::RenderWindow &window;
	bool allowCheats;
	bool allowPause;
	unsigned int highScore;
public:
	Game(GameBoard &board, SFMLboard &sfmlboard, sf::RenderWindow &window);
	void Play();
	void saveScore();
	void readScore();
};

