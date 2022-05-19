#include "olcSimpleEngine.h"

#include "MoonOrSun.h"
#include "dragonfly.h"



MoonOrSun::MoonOrSun()
{
	ylocation = -30;
	sprMoon = new olc::Sprite("moon.png");
	sprSun = new olc::Sprite("sun.png");
}

MoonOrSun::~MoonOrSun()
{
	delete sprMoon;
	delete sprSun;
}


void MoonOrSun::moveMoonorSun(float fLocalTime, float fElapsedTime) {
	if ((fLocalTime > 12 && fLocalTime <= 18)||(fLocalTime > 0 && fLocalTime <= 6)) {
		ylocation += 8 * fElapsedTime;
	}

	else
	{
		ylocation -= 8 * fElapsedTime;
	}
}



void MoonOrSun::drawMoonorSun(dragonfly* game, float fLocalTime)
{
	game->SetPixelMode(olc::Pixel::ALPHA);
	if (fLocalTime > 12 && fLocalTime <= 18) {
		game->DrawSprite(game->ScreenWidth() - 2 * sprSun->width, ylocation, sprSun, 1);
	}
	else if (fLocalTime > 18 && fLocalTime <= 24)
	{
		game->DrawSprite(game->ScreenWidth() - 2 * sprMoon->width, ylocation, sprMoon, 1);
	}
	else if (fLocalTime > 0 && fLocalTime <= 6)
	{
		game->DrawSprite(game->ScreenWidth() - 2 * sprMoon->width, ylocation, sprMoon, 1);
	}
	else
	{
		game->DrawSprite(game->ScreenWidth() - 2 * sprSun->width, ylocation, sprSun, 1);
	}

}

void MoonOrSun::resetLocation()
{
	ylocation = 0;
}
