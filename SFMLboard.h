#pragma once
#include "GameBoard.h"
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
struct RowPosition
{
	int left;
	int right;
	int y;
};
class SFMLboard :
	public GameBoard
{
	GameBoard &board;
	sf::RenderWindow &window;
	std::vector<std::vector<Enemy>>& enemies;
	std::vector<Missile>& missiles;
	int screenWidth = 448;
	int screenHeight = 512;
	unsigned long timeout;
	bool showTick;
	bool start;
	bool isIntro;
	bool isGameOver;
	bool isNewHighScore;
	bool resetEnabled;
	unsigned int highScore;
	RowPosition rows[5];

	sf::Texture playerTexture;
	sf::Texture enemy1Texture;
	sf::Texture enemy2Texture;
	sf::Texture enemy3Texture;
	sf::Texture playerMissileTexture; // 6x15px
	sf::Texture enemyMissileTexture;
	sf::Texture playerExplosionTexture;

	sf::Sprite player;
	sf::Sprite enemy1;
	sf::Sprite enemy2;
	sf::Sprite enemy3;
	sf::Sprite playerMissile;
	sf::Sprite enemyMissile;
	sf::Sprite playerExplosion;

	sf::Font font;
	sf::Text txt;

	void drawPlayer();
	void drawEnemies();
	void drawMissile();
	void drawInterface();
	void drawIntro();
	void drawStart();
	void drawTxt(std::string s, int x, int y);
	bool checkCollisionsWithEnemy(int missileNo); //0 - no hit ,1 - hit
	bool checkCollisionsWithPlayer(int missileNo);//0 - no hit, 1 - hit
	int getXPosition(int row, int position); //left edge
	int getYPosition(int row, int position); //down edge
	int onWhichEnemyTheCollisionOccured(int x);
	int whichRowHaveYouTouched(int y);
	bool killTheEnemy(int row, int k, int missileNo); //1-success 0-fail
	void playerHit();
	void gameOver();
	void Victory();
	bool isTimeout();
	void setTimeout(int x);
	void drawAll();
	void checkCollisions();
	void randomEnemyShoot();
	
public:
	SFMLboard();
	SFMLboard(GameBoard & board, sf::RenderWindow & window, std::vector<std::vector<Enemy>>& enemies, std::vector<Missile>& missiles);
	void update();
	void drawGameOver();
	void toggleShowTick();
	void setResetEnabled(bool x);
	bool isFinished();
	void giveHighScore(unsigned int mHighScore);
};

