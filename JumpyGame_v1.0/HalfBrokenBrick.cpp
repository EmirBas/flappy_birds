#include "olcSimpleEngine.h"

#include "HalfBrokenBrick.h"
#include "dragonfly.h"


HalfBrokenBrick::HalfBrokenBrick(dragonfly* theGame, float yLoc, Wall*theWall) :Section(theGame, yLoc,theWall)
{
	sprHalfBroken = new olc::Sprite("HalfBrokenBrick.jpg");
	sprBroken = new olc::Sprite("BrokenBrick.png");
	durability = 1;
}


HalfBrokenBrick::~HalfBrokenBrick()
{
	delete sprHalfBroken;
	delete sprBroken;
}

void HalfBrokenBrick::drawSection(float xLoc)
{	
	if (durability)
		game->DrawSprite(xLoc, yLocation, sprHalfBroken, 1);
	else
		game->DrawSprite(xLoc, yLocation, sprBroken, 1);
}

bool HalfBrokenBrick::checkBulletCollision(float xLoc, float bulletYPos, float bulletXPos, float bulletWidth, float bulletHeight) {
	if (xLoc < bulletXPos + bulletWidth)
		if (xLoc + sprHalfBroken->width > bulletXPos)
			if (yLocation < bulletYPos + bulletHeight)
				if (yLocation + sprHalfBroken->height > bulletYPos) {
					if(!durability)
						wall->deleteSection(this);
					durability--;
					return true;
				}
	return false;
}