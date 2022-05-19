#include "olcSimpleEngine.h"
#include "bird.h"
#include "dragonfly.h"
#include "Bonus.h"
#include "Bullet.h"
#include "Wall.h"


bird::bird(dragonfly* theGame):game(theGame){
	fGracePeriod = 0;
	sprBirdFly = new olc::Sprite("bird-fly.png");
	sprBird = new olc::Sprite("bird.png");
	fHorizontalPosition = game->ScreenWidth() / 2 - (sprBird->width / 2);
	fVerticalPosition = game->ScreenHeight() / 2 - (sprBird->height / 2);
	fVerticalSpeed = 0.0f;
}

bird::~bird() {
	delete sprBird;
	delete sprBirdFly;
}

void bird::UpdateBird(float fElapsedTime)
{
	if (game->GetKey(olc::Key::SPACE).bPressed)
	{
		if (fVerticalSpeed > 0)
			fVerticalSpeed = -50;
		else
			fVerticalSpeed -= 40;
	}

	if (fVerticalSpeed > 200)
		fVerticalSpeed = 200;

	if (fVerticalSpeed < -200)
		fVerticalSpeed = -200;

	fVerticalSpeed += 70 * fElapsedTime;
	fVerticalPosition += fVerticalSpeed * fElapsedTime;
	if (fVerticalPosition + sprBird->height >= game->ScreenHeight() || fVerticalPosition <= 0) 
		fVerticalSpeed = -fVerticalSpeed;

	updateGracePeriod(fElapsedTime);
}

void bird::DrawBird() {
	if (int(fGracePeriod * 10) % 2 == 0)
		if (game->GetKey(olc::Key::SPACE).bHeld)
			game->DrawSprite(fHorizontalPosition, fVerticalPosition, sprBirdFly, 1);
		else
			game->DrawSprite(fHorizontalPosition, fVerticalPosition, sprBird, 1);
}

Bullet* bird::createBullet(Bullet* currentHead){
	Bullet* newBullet = new Bullet(game, fHorizontalPosition, fVerticalPosition,currentHead);
	return newBullet;
}

void bird::checkWallCollision(Wall** wallcheck,int &Lives)
{	for(int i=0;i<2;i++)
		if(wallcheck[i])
			if (wallcheck[i]->checkBirdCollision(fVerticalPosition, sprBird->width, sprBird->height)) {
				if (fGracePeriod == 0)
				{
					Lives--;
					fGracePeriod = 6.0f;
				}
			}
}

void bird::updateGracePeriod(float fElapsedTime) {
	if (fGracePeriod>0) {
		fGracePeriod -= fElapsedTime;
	}
	else
		fGracePeriod = 0;
}

void bird::checkBonusCollision(Bonus** &bonuscheck, int &Lives,int &Ammunition) {
	for (int i = 0; i < 2; i++) {
		if (bonuscheck[i]) {
			if (!i)
				if (bonuscheck[i]->checkCollision(fVerticalPosition, sprBird->width, sprBird->height) ) {
					Lives++;
					if (Lives > 7)
						Lives = 7;
					delete bonuscheck[i];
					bonuscheck[i] = nullptr;
				}

			if (i)
				if (bonuscheck[i]->checkCollision(fVerticalPosition, sprBird->width, sprBird->height) ){
					Ammunition+=2;
					delete bonuscheck[i];
					bonuscheck[i] = nullptr;
			}
		}
	}
}

void bird::writeSpeed(){
	game->DrawString(game->ScreenWidth() - 95, 13, "Speed:" , olc::GREEN);
	game->DrawString(game->ScreenWidth() - 45, 13, (game->to_string_with_precision(fVerticalSpeed, 2)), olc::RED);
}

