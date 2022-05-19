#include "olcSimpleEngine.h"

#include "BrokenBrick.h"
#include "dragonfly.h"



BrokenBrick::BrokenBrick(dragonfly* theGame, float yLoc, Wall*theWall) :Section(theGame, yLoc,theWall)
{
	sprBroken = new olc::Sprite("BrokenBrick.png");

}


BrokenBrick::~BrokenBrick()
{
	delete sprBroken;
}

void BrokenBrick::drawSection(float xLoc)
{
	game->DrawSprite(xLoc, yLocation, sprBroken, 1);
}

bool BrokenBrick::checkBulletCollision(float xLoc, float bulletYPos, float bulletXPos, float bulletWidth, float bulletHeight) {
	if (xLoc < bulletXPos + bulletWidth)
		if (xLoc + sprBroken->width > bulletXPos)
			if (yLocation < bulletYPos + bulletHeight)
				if (yLocation + sprBroken->height > bulletYPos) {
					wall->deleteSection(this);
					return true;
				}
	return false;
}