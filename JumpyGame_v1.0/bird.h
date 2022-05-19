
#pragma once

class dragonfly;
class Heart;
class Bullet;
class Bonus;
class Wall;

class bird
{
	dragonfly* game;
	olc::Sprite* sprBird;
	olc::Sprite* sprBirdFly;

	float fHorizontalPosition;
	float fVerticalPosition;
	float fGracePeriod;
	float fVerticalSpeed;
public:
	bird(dragonfly* theGame);
	~bird();

	void UpdateBird(float fElapsedTime);
	void DrawBird();
	Bullet* createBullet(Bullet* currentHead);
	void checkWallCollision(Wall** wallcheck,int &Lives);
	void checkBonusCollision(Bonus** &bonuscheck, int & Lives, int &Ammunition);
	void writeSpeed();

private:
	void updateGracePeriod(float fElapsedTime);

};

