#include "olcSimpleEngine.h"
#include "Bullet.h"
#include "dragonfly.h"
#include "Wall.h"



Bullet::Bullet(dragonfly* theGame,float xPosition,float yPosition, Bullet* previousHead):fHorizontalPosition(xPosition),fVerticalPosition(yPosition)
{
	game = theGame;
	nextBullet = previousHead;
	sprBullet = new olc::Sprite("FireBall.png");
	fVerticalSpeed = 0;
	fHorizontalSpeed = 100;
	fGravity = 40;
}


Bullet::~Bullet()
{
	delete sprBullet;
	//deleteList();
}

Bullet* Bullet::moveBullet(float fElapsedTime) {
	fHorizontalPosition += fHorizontalSpeed * fElapsedTime;
	fVerticalPosition += fVerticalSpeed * fElapsedTime;
	fVerticalSpeed += fGravity* fElapsedTime;

	if (fHorizontalPosition > game->ScreenWidth() + sprBullet->width || fVerticalPosition > game->ScreenHeight())
		return nextBullet;

	if (!nextBullet)
		return this;

	if (fHorizontalPosition > game->ScreenWidth() + sprBullet->width+50 || fVerticalPosition > game->ScreenHeight()+50) {
		fHorizontalPosition = 0;
		fVerticalPosition = 0;
	}

	Bullet* temp = nextBullet->moveBullet(fElapsedTime);
	if (temp != nextBullet) {
		delete nextBullet;
		nextBullet = temp;
	}
	return this;
}

void Bullet::drawBullet()
{
	game->DrawSprite(fHorizontalPosition, fVerticalPosition, sprBullet, 1);
	
	if (!nextBullet)
		return;

	nextBullet->drawBullet();
}

Bullet* Bullet::checkCollision(Wall** wallcheck) {
	for (int i = 0; i < 2; i++) {
		if(wallcheck[i])
			if (wallcheck[i]->checkBulletCollision(fVerticalPosition, fHorizontalPosition, sprBullet->width, sprBullet->height))
				return nextBullet;
	}

	if (!nextBullet)
		return this;

	Bullet* temp = nextBullet->checkCollision(wallcheck);
	if(temp!=nextBullet)
	delete nextBullet;
	nextBullet = temp;
	return this;
}

/*void Bullet::deleteList() {
	while (nextBullet)
		 nextBullet->deleteList();	
		delete nextBullet;
		nextBullet = nullptr;
}*/