#pragma once
class dragonfly;
class Wall;
class Bullet
{
	dragonfly* game;
	olc::Sprite* sprBullet;

	Bullet* nextBullet;
	float fHorizontalPosition;
	float fVerticalPosition;
	float fGravity;
	float fVerticalSpeed;
	float fHorizontalSpeed;


public:
	Bullet(dragonfly* theGame,float xPosition, float yPosition,Bullet* previousHead);
	~Bullet();

	Bullet* moveBullet(float fElapsedTime);
	void drawBullet();
	Bullet* checkCollision(Wall ** wallcheck);
	//void deleteList();

};

