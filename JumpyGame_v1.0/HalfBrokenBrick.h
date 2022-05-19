#pragma once
#include "Section.h"
class Section;
class dragonfly;
class HalfBrokenBrick :
	public Section
{
	olc::Sprite* sprHalfBroken;
	olc::Sprite* sprBroken;

	int durability;

public:
	HalfBrokenBrick(dragonfly* theGame, float yLoc, Wall*theWall);
	~HalfBrokenBrick();
	void drawSection(float xLoc);

	bool checkBulletCollision(float xLoc, float bulletYPos, float bulletXPos, float bulletWidth, float bulletHeight);

};

