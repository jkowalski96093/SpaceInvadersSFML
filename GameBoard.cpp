#include "GameBoard.h"

GameBoard::GameBoard()
{
	tick = 0;
	enemiesHorizontal = 0;
	enemiesVertical = 0;
	playerPosition = 104;
	playerLives = 3;
	score = 0;
	enemiesSpeed = 0;
	enemiesDirection = 1;
	maxVertical = 15;
	playerMissilleCount = 0;
	isPlayerHit = 0;
	isPaused = 0;
	isUnlimitedAmmo = 0;
	isInvincibility = 0;
	stage = 1;
	cooldown = 0;
	cooldownValue = 100;
	enemies.resize(5);
	for (int i = 0; i < 5; ++i)
	{
		enemies[i].resize(11);
		for (int j = 0; j < 11; j++)
		{
			if (i == 0)
			{
				enemies.at(i).at(j).isAlive = 1;
				enemies.at(i).at(j).type = 3;
			}
			else if (i == 1 || i == 2)
			{
				enemies.at(i).at(j).isAlive = 1;
				enemies.at(i).at(j).type = 2;
			}
			else if (i == 3 || i == 4)
			{
				enemies.at(i).at(j).isAlive = 1;
				enemies.at(i).at(j).type = 1;
			}
		}
	}
}

GameBoard::GameBoard(const GameBoard * board2)
{
	this->enemies = board2->enemies;
	this->missiles = board2->missiles;
	this->enemiesHorizontal = board2->enemiesHorizontal;
	this->enemiesVertical = board2->enemiesVertical;
	this->playerPosition = board2->playerPosition;
	this->tick = board2->tick;
}

void GameBoard::playerMoveRight()
{
	if (playerPosition > 1)
	{
		playerPosition--;
		playerPosition--;
	}
	return;
}

void GameBoard::playerMoveLeft()
{
	if (playerPosition < 207)
	{
		playerPosition++;
		playerPosition++;
	}
	return;
}

void GameBoard::killEnemy(int x, int y)
{
	enemies[x][y].isAlive = 0;
	return;
}

void GameBoard::setPlayerPosition(int x)
{
	playerPosition = x;
	return;
}

int GameBoard::getPlayerPosition()
{
	return playerPosition;
}

void GameBoard::setEnemiesHorizontal(int x)
{
	enemiesHorizontal = x;
}



int GameBoard::getEnemiesHorizontal()
{
	return enemiesHorizontal;
}

void GameBoard::setEnemiesVertical(int x)
{
	enemiesVertical = x;
}



int GameBoard::getEnemiesVertical()
{
	return enemiesVertical;
}

void GameBoard::setPlayerLives(int x)
{
	playerLives = x;
	return;
}

int GameBoard::getPlayerLives()
{
	return playerLives;
}

unsigned long GameBoard::getTick()
{
	return tick;
}

void GameBoard::addTick()
{
	tick++;
}

std::vector<std::vector<Enemy>>& GameBoard::getEnemiesVector()
{
	return enemies;
}

std::vector<Missile>& GameBoard::getMissilesVector()
{
	return missiles;
}

void GameBoard::shoot(bool who, int xPosition, int yPosition)
{
	if (who == 0)
	{
		Missile m;
		m.heading = 0;
		m.positionHorizontal = playerPosition;
		m.positionVertical = 30;
		missiles.push_back(m);
	}
	if (who == 1)
	{
		Missile m;
		m.heading = 1;
		m.positionHorizontal = xPosition;
		m.positionVertical = yPosition;
		missiles.push_back(m);
	}
}

void GameBoard::playerShoot()
{
	if (isPaused == 0) 
	{
		if (playerMissilleCount < 3 || isUnlimitedAmmo==1)
		{
			if (cooldown < tick)
			{
				shoot(0, playerPosition, 0);
				playerMissilleCount++;
				cooldown = tick + cooldownValue;
			}
		}
	}
}

void GameBoard::updateMissiles()
{
	if (tick % 40 == 0 && isPaused==0)
	{
		
		for (int i = 0; i < missiles.size(); ++i)
		{
			bool to_erase = 0;
			if (missiles.at(i).heading == 0)
			{
				if (missiles.at(i).positionVertical < 0 || missiles.at(i).positionVertical>250)
					to_erase = 1;
				missiles.at(i).positionVertical += 5;
			}
			else if (missiles.at(i).heading == 1)
			{
				if (missiles.at(i).positionVertical < 0 || missiles.at(i).positionVertical>400)
					to_erase = 1;
				missiles.at(i).positionVertical += 5;
			}
 			if (to_erase == 1)
			{
				deleteMissile(i);
				--i;
			}
		}
	}
}

void GameBoard::deleteMissile(int x)
{
	if (missiles.at(x).heading == 0)
		playerMissilleCount--;
	missiles.erase(missiles.begin() + x);
}

void GameBoard::update()
{
	updateEnemies();
	updateMissiles();
}

void GameBoard::updateEnemies()
{
	if (isPaused == 0)
	{
		updateMaxVertical();
		updateEnemiesSpeed();
		if (tick % (100 - enemiesSpeed) == 0)
		{
			if (enemiesDirection == 1)
			{
				if (enemiesHorizontal < 15)
					enemiesHorizontal++;
				else {
					enemiesDirection = 0;
					if (enemiesVertical < maxVertical)
						enemiesVertical++;
				}
			}
			else {
				if (enemiesHorizontal > 0)
					enemiesHorizontal--;
				else {
					enemiesDirection = 1;
					if (enemiesVertical < maxVertical)
						enemiesVertical++;
				}
			}
		}
	}
}

void GameBoard::updateEnemiesSpeed()
{
	enemiesSpeed = enemiesVertical * 3;
}

void GameBoard::updateMaxVertical()
{
	if (maxVertical == 15 && isRowAlive(4) == 0)
		maxVertical = 18;
	if (maxVertical == 18 && isRowAlive(3) == 0)
		maxVertical = 21;
	if (maxVertical == 21 && isRowAlive(2) == 0)
		maxVertical = 24;
	if (maxVertical == 24 && isRowAlive(1) == 0)
		maxVertical = 27;
}

bool GameBoard::isRowAlive(int x)
{
	for (int i = 0; i < 11; ++i)
	{
		if (enemies.at(x).at(i).isAlive == 1)
			return 1;
	}
	return 0;
}

bool GameBoard::isAnyRowAlive()
{
	if (isRowAlive(4) == 0 && isRowAlive(3) == 0 && isRowAlive(2) == 0 && isRowAlive(1) == 0 && isRowAlive(0) == 0)
		return 0;
	else return 1;
}

void GameBoard::resetScore()
{
	score = 0;
}

void GameBoard::addScore(int x)
{
	score += x;
}

int GameBoard::getScore()
{
	return score;
}

bool GameBoard::getIsPlayerHit()
{
	return isPlayerHit;
}

void GameBoard::setIsPlayerHit(bool x)
{
	if (x == 0)
	{
		isPlayerHit = 0;
		isPaused = 0;
	}
	else if (x == 1)
	{
		isPlayerHit = 1;
		isPaused = 1;
	}
}


void GameBoard::resetAll()
{
	tick = 0;
	enemiesHorizontal = 0;
	enemiesVertical = 0;
	playerPosition = 104;
	playerLives = 3;
	score = 0;
	enemiesSpeed = 0;
	enemiesDirection = 1;
	maxVertical = 15;
	playerMissilleCount = 0;
	isPlayerHit = 0;
	isPaused = 0;
	stage = 1;
	enemies.resize(5);
	for (int i = 0; i < 5; ++i)
	{
		enemies[i].resize(11);
		for (int j = 0; j < 11; j++)
		{
			if (i == 0)
			{
				enemies.at(i).at(j).isAlive = 1;
				enemies.at(i).at(j).type = 3;
			}
			else if (i == 1 || i == 2)
			{
				enemies.at(i).at(j).isAlive = 1;
				enemies.at(i).at(j).type = 2;
			}
			else if (i == 3 || i == 4)
			{
				enemies.at(i).at(j).isAlive = 1;
				enemies.at(i).at(j).type = 1;
			}
		}
	}
}

void GameBoard::nextStage()
{
	if (tick % 100 == 50)
	{
		if (isAnyRowAlive() == 0)
		{
			enemiesHorizontal = 0;
			enemiesVertical = 0;
			enemiesSpeed = 0;
			enemiesDirection = 1;
			maxVertical = 15;
			playerMissilleCount = 0;
			isPlayerHit = 0;
			if(stage!=15)
				stage++;
			playerLives++;
			missiles.clear();
			enemies.resize(5);
			for (int i = 0; i < 5; ++i)
			{
				enemies[i].resize(11);
				for (int j = 0; j < 11; j++)
				{
					if (i == 0)
					{
						enemies.at(i).at(j).isAlive = 1;
						enemies.at(i).at(j).type = 3;
					}
					else if (i == 1 || i == 2)
					{
						enemies.at(i).at(j).isAlive = 1;
						enemies.at(i).at(j).type = 2;
					}
					else if (i == 3 || i == 4)
					{
						enemies.at(i).at(j).isAlive = 1;
						enemies.at(i).at(j).type = 1;
					}
				}
			}
		}
	}
}

int GameBoard::getStage()
{
	return stage;
}

void GameBoard::toggleIsPaused()
{
	if (isPaused == 0)
		isPaused = 1;
	else isPaused = 0;
}

void GameBoard::setIsPaused(bool x)
{
	isPaused = x;
}

bool GameBoard::getIsPaused()
{
	return isPaused;
}

void GameBoard::setIsUnlimitedAmmo(bool x)
{
	isUnlimitedAmmo = x;
}

void GameBoard::setIsInvincibility(bool x)
{
	isInvincibility = x;
}

bool GameBoard::getIsInvincibility()
{
	if (isInvincibility == 1)
		return 1;
	else return 0;
}

void GameBoard::noCooldown()
{
	cooldownValue = 0;
}
