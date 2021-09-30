#include "SFMLboard.h"



SFMLboard::SFMLboard() :board(board), window(window),enemies(enemies), missiles(missiles)
{
}



SFMLboard::SFMLboard(GameBoard & board, sf::RenderWindow & window, std::vector<std::vector<Enemy>>& enemies, std::vector<Missile>& missiles) :
	board(board), window(window),enemies(enemies),missiles(missiles)
{
	if (!font.loadFromFile("smallee.ttf"))
		std::cout << "Failed to load font\n";
	if (!playerTexture.loadFromFile("player.png"))
		std::cout << "Failed to load player texture\n";
	if (!enemy1Texture.loadFromFile("enemy1.png"))
		std::cout << "Failed to load enemy1 texture\n";
	if (!enemy2Texture.loadFromFile("enemy2.png"))
		std::cout << "Failed to load enemy2 texture\n";
	if (!enemy3Texture.loadFromFile("enemy3.png"))
		std::cout << "Failed to load enemy3 texture\n";
	if (!playerMissileTexture.loadFromFile("playerMissile.png"))
		std::cout << "Failed to load playerMissile texture\n";
	if (!enemyMissileTexture.loadFromFile("enemyMissile.png"))
		std::cout << "Failed to load enemyMissile texture\n";
	if (!playerExplosionTexture.loadFromFile("playerExplosion.png"))
		std::cout << "Failed to load playerExplosion texture\n";
	player.setTexture(playerTexture);
	enemy1.setTexture(enemy1Texture);
	enemy2.setTexture(enemy2Texture);
	enemy3.setTexture(enemy3Texture);
	playerMissile.setTexture(playerMissileTexture);
	enemyMissile.setTexture(enemyMissileTexture);
	playerExplosion.setTexture(playerExplosionTexture);
	txt.setFont(font);

	timeout = 1800; //timeout for drawIntro
	showTick = 0;
	start = 1;
	isIntro = 1;
	isGameOver = 0;
	resetEnabled = 0;
	highScore = 0;
	isNewHighScore = 0;
}

void SFMLboard::drawIntro()
{
	if (isTimeout() == 1)
	{
		drawInterface();
		drawTxt("PLAY", 200, 110);
		drawTxt("SPACE      INVADERS", 140, 155);
		drawTxt("*SCORE  ADVANCE  TABLE*", 110, 220);
		enemy3.setPosition(160, 280);
		window.draw(enemy3);
		drawTxt("= 30 POINTS", 190, 276);
		enemy2.setPosition(160, 320);
		window.draw(enemy2);
		drawTxt("= 20 POINTS", 190, 316);
		enemy1.setPosition(160, 360);
		window.draw(enemy1);
		drawTxt("= 10 POINTS", 190, 356);
	}
	else
	{
		isIntro = 0;
		setTimeout(1000);//timeout for drawStart
	}
}

void SFMLboard::drawStart()
{
	if (isTimeout() == 1)
	{
		drawInterface();
		drawTxt("STAGE " + std::to_string(board.getStage()), 190, 240);
	}
	else start = 0;
}

void SFMLboard::drawAll()
{
	if (isIntro == 1)
	{
		drawIntro();
	}
	else if (isGameOver == 1)
	{
		drawGameOver();
	}
	else
	{
		if (start == 1)
		{
			drawStart();
			return;
		}
		else
		{
			drawPlayer();
			drawInterface();
			drawEnemies();
			drawMissile();
		}
	}
}

void SFMLboard::drawPlayer()
{
	if (board.getIsPlayerHit() == 0)
	{
		player.setPosition((screenWidth - 31) - board.getPlayerPosition() * 2, screenHeight - 80);
		window.draw(player);
	}
	else
	{
		playerExplosion.setPosition((screenWidth - 31) - board.getPlayerPosition() * 2, screenHeight - 80);
		window.draw(playerExplosion);
		playerHit();
	}
}

void SFMLboard::drawEnemies()
{
	int posX = 0;
	int	posY = 0 ;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			posX = board.getEnemiesHorizontal() * 8 + 30 * j;
			posY = board.getEnemiesVertical() * 10 + 30 * i + 80;
			if (j == 0)
				rows[i].left = posX;
			if (j == 10)
				rows[i].right = posX + 30;
			if (enemies.at(i).at(j).isAlive == 1)
			{
				switch (enemies.at(i).at(j).type)
				{
				case(1): enemy1.setPosition(posX, posY);
					window.draw(enemy1);
					break;
				case(2): enemy2.setPosition(posX, posY);
					window.draw(enemy2);
					break;
				case(3): enemy3.setPosition(posX, posY);
					window.draw(enemy3);
					break;
				default:break;
				}
			}
		}
		if (posY != 0)
			rows[i].y = posY + 30;
	}
}

void SFMLboard::drawMissile()
{
	for (int i = 0; i < missiles.size(); i++)
	{
		if (missiles.at(i).heading == 0)
		{
			int posX = (screenWidth - 31) - (missiles.at(i).positionHorizontal-6) * 2;
			int posY = screenHeight - 63 - (missiles.at(i).positionVertical-15) * 2;
			playerMissile.setPosition(posX,posY);
			window.draw(playerMissile);
		}
		if (missiles.at(i).heading == 1)
		{
			enemyMissile.setPosition(missiles.at(i).positionHorizontal + 13, missiles.at(i).positionVertical+30);
			window.draw(enemyMissile);
		}
	}
}

void SFMLboard::drawInterface()
{
	sf::RectangleShape line;
	line.setFillColor(sf::Color::Green);
	line.setSize(sf::Vector2f(448, 2));
	line.setPosition(0, 478);
	window.draw(line);
	if (isIntro == 0)
	{
		player.setPosition(50, 482);
		window.draw(player);
		drawTxt("Score: " + std::to_string(board.getScore()), 200, 0);
		if (board.getIsInvincibility() == 1)
		{
			txt.setRotation(90);
			drawTxt("8", 45, 490);
			txt.setRotation(0);
		}
		else
			drawTxt(std::to_string(board.getPlayerLives()), 20, 475);
	}
	if (showTick == 1)
	{
		drawTxt("Tick" + std::to_string(board.getTick()), 0, 0);
	}

}

void SFMLboard::drawTxt(std::string s, int x, int y)
{
	txt.setString(s);
	txt.setPosition(x, y);
	window.draw(txt);
}

void SFMLboard::checkCollisions()
{
	if (board.getIsPlayerHit() == 0)
	{
		for (int i = 0; i < missiles.size(); ++i)
		{
			if (board.getIsPlayerHit() == 0) {
				if (missiles.at(i).heading == 0)
				{
					if (checkCollisionsWithEnemy(i) == 1)
						i--;
				}
				else if (missiles.at(i).heading == 1 && board.getIsInvincibility()==0)
				{
					if (checkCollisionsWithPlayer(i) == 1)
					{
						board.deleteMissile(i);
						i--;
						board.setIsPlayerHit(1);
					}
				}
			}
		}
	}

}

bool SFMLboard::checkCollisionsWithEnemy(int missileNo)
{
	int missileY = screenHeight - 48 - (missiles.at(missileNo).positionVertical - 15) * 2;
	int missileX = (screenWidth - 28) - (missiles.at(missileNo).positionHorizontal - 6) * 2;
	if (missileY < rows[0].y - 46)
	{
		board.deleteMissile(missileNo);
		return 1;
	}
	else
	{
		int j = whichRowHaveYouTouched(missileY);
		if (j != -1)
		{
			int k = onWhichEnemyTheCollisionOccured(missileX);
			if (killTheEnemy(j, k, missileNo) == 1)
			{
				return 1;
			}
		}

	}
	return 0;
}

bool SFMLboard::checkCollisionsWithPlayer(int missileNo)
{
	if ((screenWidth-16) - board.getPlayerPosition() * 2 >= missiles.at(missileNo).positionHorizontal &&
		missiles.at(missileNo).positionHorizontal >= (screenWidth - 44) - board.getPlayerPosition() * 2) //if(right X)
	{
		if (screenHeight - 109 <= missiles.at(missileNo).positionVertical)//if(right Y)
			return 1;
		else return 0;
	}
	else return 0;
}

void SFMLboard::randomEnemyShoot()
{
	if (board.isAnyRowAlive() == 0)
		Victory();
	else if (board.getTick()%(800-board.getStage()*50)==0 && board.getIsPaused()==0 && isTimeout()==0)
	{
		std::srand(time(0));
		int row = -1;
		int position = -1;
		for (int p = 1; p > 0; p++)
		{
			int j = std::rand() % 11;
			for (int i = 4; i >= 0; i--)
			{
				if (enemies.at(i).at(j).isAlive == 1)
				{
					row = i;
					position = j;
					break;
				}
			}
			if (row != -1 && position != -1)
				break;
		}
		int x = getXPosition(row, position);
		int y = getYPosition(row, position);
		board.shoot(1, x, y);
	}
}

void SFMLboard::update()
{
	randomEnemyShoot();
	drawAll();
	checkCollisions();
}

void SFMLboard::drawGameOver()
{
	if (isTimeout() == 1)
	{
		drawTxt("GAME  OVER", 155, 170);
		if (isNewHighScore == 1)
			drawTxt("NEW HIGHSCORE!: " + std::to_string(board.getScore()), 120, 250);
		else
		{
			drawTxt("HIGHSCORE:" + std::to_string(highScore), 135, 250);
			drawTxt("YOUR SCORE:" + std::to_string(board.getScore()), 145, 290);
		}
	}
	else
	{
		if (resetEnabled == 1)
		{
			isGameOver = 0;
			board.resetAll();
			start = 1;
			isIntro = 1;
			timeout = 1800;
		}
		else
			window.close();
	}

}

int SFMLboard::getXPosition(int row, int position)
{
	return board.getEnemiesHorizontal() * 8 + 30 * position;
}

int SFMLboard::getYPosition(int row, int position)
{
	return board.getEnemiesVertical() * 10 + 30 * row + 80;
}


int SFMLboard::onWhichEnemyTheCollisionOccured(int x)
{
	for (int k = 0; k <11; k++)
	{
		int l = x;
		l -= (k + 1) * 30;
		if (l < rows[0].left)
		{
			return k;
		}
	}
}

int SFMLboard::whichRowHaveYouTouched(int y)
{
	for (int i = 0; i < 5; i++)
	{
		if (y < rows[i].y)
			return i;
	}
	return -1;
}

bool SFMLboard::killTheEnemy(int row, int k,int missileNo)
{

	if (k<11 && enemies.at(row).at(k).isAlive == 1)
	{
		enemies.at(row).at(k).isAlive = 0;
		board.addScore(enemies.at(row).at(k).type * 10);
		board.deleteMissile(missileNo);
		return 1;
	}
	return 0;
}

void SFMLboard::playerHit()
{
	if (timeout == 0)
	{
		if (board.getPlayerLives() > 0)
			board.setPlayerLives(board.getPlayerLives() - 1);
		else gameOver();
		board.setIsPlayerHit(1);
		setTimeout(800);

	}
	else if(board.getTick()>timeout)
	{
		timeout = 0;
		board.setIsPlayerHit(0);
	}
}

void SFMLboard::gameOver()
{
	if (board.getScore() > highScore)
		isNewHighScore = 1;
	isGameOver = 1;
	setTimeout(3000);
}

void SFMLboard::toggleShowTick()
{
	if (showTick == 0)
		showTick = 1;
	else showTick = 0;
}

void SFMLboard::setResetEnabled(bool x)
{
	resetEnabled = x;
}

bool SFMLboard::isFinished()
{
	if (isGameOver == 1)
		return 1;
	else return 0;
}

void SFMLboard::giveHighScore(unsigned int mHighScore)
{
	highScore = mHighScore;
}


void SFMLboard::Victory()
{
	board.nextStage();
	setTimeout(1000);
	window.clear();
	start = 1;
	drawStart();
}

bool SFMLboard::isTimeout()
{
	if (timeout == 0)
		return 0;
	else if (board.getTick() > timeout)
	{
		timeout = 0;
		return 0;
	}
	return 1;

}

void SFMLboard::setTimeout(int x)
{
	timeout = board.getTick() + x;
}
