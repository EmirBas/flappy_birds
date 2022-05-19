#include "olcSimpleEngine.h"
#include "Heart.h"
#include "dragonfly.h"

Heart::Heart(dragonfly* theGame) :Bonus(theGame){
	sprHeartFly = new olc::Sprite("heart_Fly.png");
	bonus[0] = game->ScreenWidth();
	bonus[1] = rand() % (game->ScreenHeight() - sprHeartFly->height);
}

Heart::~Heart(){
	delete sprHeartFly;
}


bool Heart::moveBonus(float fElapsedTime){
	if (!(bonus[0] <= -sprHeartFly->width))
		bonus[0] -= horizontalSpeed * fElapsedTime;
	if (bonus[0] < -sprHeartFly->width)
		return true;
}

void Heart::drawBonus() {
	game->DrawSprite(bonus[0], bonus[1], sprHeartFly, 1);
}

bool Heart::checkCollision(float fVerticalPosition, float birdWidth, float birdHeight){
	if (bonus[0] < (game->ScreenWidth() / 2 + (birdWidth / 2)))
		if (bonus[0] + sprHeartFly->width > (game->ScreenWidth() / 2 - (birdWidth / 2)))
			if ((fVerticalPosition >= bonus[1] && fVerticalPosition + birdHeight <= bonus[1] + sprHeartFly->height)) {
				return true;
			}
	return false;
}

