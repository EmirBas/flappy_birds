#include "olcSimpleEngine.h"

#include "Ammo.h"
#include "dragonfly.h"


Ammo::Ammo(dragonfly* theGame):Bonus(theGame){
	sprAmmo = new olc::Sprite("ammo.png");
	bonus[0] = game->ScreenWidth();
	bonus[1] = rand() % (game->ScreenHeight() - sprAmmo->height);
}

Ammo::~Ammo(){
	delete sprAmmo;
}

bool Ammo::moveBonus(float fElapsedTime){
	if (bonus[0] > -sprAmmo->width)
		bonus[0] -= horizontalSpeed * fElapsedTime;
	if (bonus[0] < -sprAmmo->width)
		return true;
}

void Ammo::drawBonus() {
		game->DrawSprite(bonus[0], bonus[1], sprAmmo, 1);
}

bool Ammo::checkCollision(float fVerticalPosition, float birdWidth, float birdHeight) {
	if (bonus[0] < (game->ScreenWidth() / 2 + (birdWidth / 2)))
		if (bonus[0] + sprAmmo->width > (game->ScreenWidth() / 2 - (birdWidth / 2)))
			if ((fVerticalPosition >= bonus[1] && fVerticalPosition + birdHeight <= bonus[1] + sprAmmo->height)) {				
				return true; 
				//delete this;
			}
	return false;
}
