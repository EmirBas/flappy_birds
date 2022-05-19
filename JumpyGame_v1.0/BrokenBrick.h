#pragma once
#include "Section.h"
class Section;
class dragonfly;
class BrokenBrick :public Section
{
	olc::Sprite* sprBroken;

public:
	BrokenBrick(dragonfly* theGame, float yLoc, Wall*theWall);
	~BrokenBrick();
	void drawSection(float xLoc);

	bool checkBulletCollision(float xLoc, float bulletYPos, float bulletXPos, float bulletWidth, float bulletHeight);

};

