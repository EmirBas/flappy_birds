#pragma once
class dragonfly;
class Wall;
class Section
{
protected:
	float yLocation;
	dragonfly* game;
	Wall* wall;
public:
	Section(dragonfly* theGame,float yLoc,Wall* theWall);
	virtual ~Section();

	virtual void drawSection(float xLoc) = 0;
	virtual bool checkBulletCollision(float xLoc, float verticalPos, float horizontalPos, float bulletWidth, float bulletHeight) = 0;
	bool checkBirdCollision(float xLoc, float birdYpos, float birdWidth, float birdHeight);

};

