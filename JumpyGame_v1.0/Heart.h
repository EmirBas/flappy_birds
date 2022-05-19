#pragma once
#include "Bonus.h"

class Heart :public Bonus
{
	olc::Sprite* sprHeartFly;
public:
	Heart(dragonfly* theGame);
	~Heart();

	bool moveBonus(float fElapsedTime);
	void drawBonus();
	bool checkCollision(float fVerticalPosition, float birdWidth, float birdHeight);
};

