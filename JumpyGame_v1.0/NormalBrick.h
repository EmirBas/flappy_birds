#pragma once
#include "Section.h"
class Section;
class dragonfly;
class Wall;
class NormalBrick :public Section
{
	olc::Sprite* sprNormal;

public:
	NormalBrick(dragonfly* theGame, float yLoc, Wall*theWall);
	~NormalBrick();

	void drawSection(float xLoc);
	bool checkBulletCollision(float xLoc, float bulletYPos, float bulletXPos, float bulletWidth, float bulletHeight);
};

