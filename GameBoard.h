#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
struct Enemy
{
	int type; //1-10 points, 2-20 points, 3-30 points
	bool isAlive;
};

struct Missile
{
	bool heading;//from: 0-player 1-enemies
	int positionVertical;//0-max up
	int positionHorizontal;
};

class GameBoard
{
	std::vector < std::vector<Enemy>> enemies;
	std::vector<Missile> missiles;
	unsigned long tick;
	int enemiesHorizontal; 
	int enemiesVertical; 
	int enemiesSpeed;
	int maxVertical;
	bool enemiesDirection; //0-left, 1-right;
	int playerPosition; //0-max right, 208-max left (+1 -> +2 pixels)
	int playerLives;
	int playerMissilleCount; //max 3 playerMissiles at once
	unsigned int score;
	bool isPlayerHit;
	bool isPaused;
	bool isUnlimitedAmmo;
	bool isInvincibility;
	int stage;
	unsigned long cooldown;
	int cooldownValue;

	void updateEnemies();
	void updateEnemiesSpeed();
	void updateMaxVertical();
	void updateMissiles();
public:	
	GameBoard();
	GameBoard(const GameBoard *board2);
	void playerMoveRight();
	void playerMoveLeft();
	void killEnemy(int x, int y);
	void setPlayerPosition(int x);
	int getPlayerPosition();
	void setEnemiesHorizontal(int x);
	int getEnemiesHorizontal();
	void setEnemiesVertical(int x);
	int getEnemiesVertical();
	void setPlayerLives(int x);
	int getPlayerLives();
	unsigned long getTick();
	void addTick();
	std::vector<std::vector<Enemy>>& getEnemiesVector();
	std::vector<Missile>& getMissilesVector();
	void shoot(bool who, int xPosition, int yPosition);  //who:0-from player, 1-enemy
	void playerShoot();
	void deleteMissile(int x);
	void update();
	bool isRowAlive(int x);
	bool isAnyRowAlive();
	void resetScore();
	void addScore(int x);
	int getScore();
	bool getIsPlayerHit();
	void setIsPlayerHit(bool x);
	void resetAll();
	void nextStage();
	int getStage();
	void toggleIsPaused();
	void setIsPaused(bool x);
	bool getIsPaused();
	void setIsUnlimitedAmmo(bool x);
	void setIsInvincibility(bool x);
	bool getIsInvincibility();
	void noCooldown();
};

