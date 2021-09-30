#include "Game.h"


Game::Game(GameBoard & board, SFMLboard & sfmlboard, sf::RenderWindow & window) :board(board), sfmlboard(sfmlboard), window(window)
{
	allowCheats = 0;
	allowPause = 1;
	highScore = 0;
	if (allowCheats == 1)
	{
		board.setIsUnlimitedAmmo(1);
		board.setIsInvincibility(1);
		board.noCooldown();
		sfmlboard.setResetEnabled(1);
	}
}

void Game::Play()
{
	readScore();
	sfmlboard.giveHighScore(highScore);
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
				board.playerMoveRight();
			if (event.key.code == sf::Keyboard::Left)
				board.playerMoveLeft();
			if (event.key.code == sf::Keyboard::Space)
				board.playerShoot();
			if (event.key.code == sf::Keyboard::T)
				sfmlboard.toggleShowTick();
			if (allowPause == 1)
			{
				if (event.key.code == sf::Keyboard::P)
					board.toggleIsPaused();
			}
		}
	}

	window.clear();
	board.update();
	sfmlboard.update();
	window.display();
	std::this_thread::sleep_for(std::chrono::microseconds(10));
	board.addTick();
	if (sfmlboard.isFinished() == 1)
	{
		saveScore();
		sfmlboard.giveHighScore(highScore);
	}
}

void Game::saveScore()
{
	if (board.getScore() > highScore)
	{
		std::ofstream write;
		write.open("Highscore.txt");
		std::string s = std::to_string(board.getScore());
		write << s;
		write.close();
		highScore = board.getScore();
	}
}

void Game::readScore()
{
	std::string s;
	std::ifstream file("Highscore.txt");
	file >> s;
	unsigned int score = std::stoi(s);
	if (score > highScore)
		highScore = score;
}

