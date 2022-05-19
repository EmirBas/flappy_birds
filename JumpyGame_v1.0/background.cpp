#include "olcSimpleEngine.h"

#include "background.h"
#include "dragonfly.h"


background::background(dragonfly* theGame)
{
	game = theGame;
	sprCloud = new olc::Sprite("cloud.png");

	cloud[0] = 130;
	cloud[1] = 20;
	cloudSpeed = 30;
}


background::~background()
{
	delete sprCloud;
}

void background::Clear(float fLocalTime)
{
		if (fLocalTime > 12 && fLocalTime <= 18) 
			game->Clear(olc::Pixel(50 - ((fLocalTime - 12) * 5), 50 - ((fLocalTime - 12) * 5), 255 - ((fLocalTime - 12) * 30)));
		
		else if (fLocalTime > 18 && fLocalTime <= 24)		
			game->Clear(olc::Pixel(125 - (fLocalTime - 18) * 15, 0, 155 - (fLocalTime - 18) * 30));
		
		else if (fLocalTime > 0 && fLocalTime <= 6)		
			game->Clear(olc::Pixel(0, 25 + fLocalTime * 30, 25 + fLocalTime * 30));
		
		else
			game->Clear(olc::Pixel(0, 25 + (fLocalTime - 6) * 15, 50 + (fLocalTime - 6) * 30));
		
}
void background::updateSky(float fElapsedTime) {
	createCloud();
	moveCloud(fElapsedTime);
}

void background::createCloud() {
	if (cloud[0] <= -sprCloud->width)
		if (0.001 > (float)rand() / RAND_MAX)
		{
			cloud[0] = game->ScreenWidth();
			cloud[1] = rand() % (game->ScreenHeight()/3 - sprCloud->height);
		}
}
void background::moveCloud(float fElapsedTime) {
	if (!(cloud[0] <= -sprCloud->width))
		cloud[0] -= cloudSpeed * fElapsedTime;
	if (cloud[0] < -sprCloud->width)
		cloud[0] = -sprCloud->width;
}

void background::drawCloud() {
	if (!(cloud[0] <= -sprCloud->width))
		game->DrawSprite(cloud[0], cloud[1], sprCloud, 1);
}

