#include "olcSimpleEngine.h"
#include "NormalBrick.h"
#include "dragonfly.h"



NormalBrick::NormalBrick(dragonfly* theGame, float yLoc,Wall*theWall):Section(theGame,yLoc,theWall)
{
	sprNormal = new olc::Sprite("BrickSmall.png");
}


NormalBrick::~NormalBrick()
{
	delete sprNormal;
}

void NormalBrick::drawSection(float xLoc)
{
	game->DrawSprite(xLoc, yLocation , sprNormal, 1);
}


bool NormalBrick::checkBulletCollision(float xLoc, float bulletYPos, float bulletXPos, float bulletWidth, float bulletHeight) {
	if (xLoc < bulletXPos + bulletWidth)
		if (xLoc + sprNormal->width > bulletXPos)
			if (yLocation < bulletYPos + bulletHeight)
				if (yLocation + sprNormal->height > bulletYPos)
					return true;
	return false;
}