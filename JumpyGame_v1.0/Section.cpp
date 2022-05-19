#include "Section.h"
#include "dragonfly.h"
#include "Wall.h"



Section::Section(dragonfly* theGame,float yLoc,Wall* theWall):game(theGame),wall(theWall)
{
	yLocation = yLoc;
}


Section::~Section()
{
}

bool Section::checkBirdCollision(float xLoc,float birdYpos, float birdWidth, float birdHeight)
{
	if (xLoc < (game->ScreenWidth() / 2 + (birdWidth / 2)))
		if (xLoc + birdWidth > (game->ScreenWidth() / 2 - (birdWidth / 2)))
			if (yLocation < birdYpos + birdHeight)
				if (yLocation + 50 > birdYpos)
					return true;
	return false;
}


