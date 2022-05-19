#pragma once

#include "Bonus.h"
class Brick;

class Ammo : public Bonus
{
	olc::Sprite* sprAmmo;

public:
	Ammo(dragonfly* theGame);
	~Ammo();

	bool moveBonus(float fElapsedTime);
	void drawBonus();
	bool checkCollision(float fVerticalPosition, float birdWidth, float birdHeight);
};

