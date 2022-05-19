#include "Wall.h"
#include "dragonfly.h"
#include "Section.h"
#include "NormalBrick.h"
#include "BrokenBrick.h"
#include "HalfBrokenBrick.h"



Wall::Wall(dragonfly* theGame):game(theGame),xLocation(game->ScreenWidth())
{
	holeLocation = rand() % (game->ScreenHeight() - 50);
	//xLocation = game->ScreenWidth();
	horizontalSpeed = 40;
	Sections = new(Section*[6]);
	for (int i = 0; i < 6; i++) {
		Sections[i] = nullptr;
	}

	for (int i = 0; i < 6; i++) {
		SectionType[i] = 1;
	}

	createWall();
}

Wall::Wall(dragonfly* theGame,int x) :game(theGame), xLocation(game->ScreenWidth()+x) // oyunun 2. duvarý
{
	holeLocation = rand() % (game->ScreenHeight() - 50);
	horizontalSpeed = 40;
	Sections = new(Section*[6]);
	for (int i = 0; i < 6; i++) 
		Sections[i] = nullptr;
	
	for (int i = 0; i < 6; i++) 
		SectionType[i] = 1;  // default olarak normalBrick atýyoruz
	
	createWall();
}

Wall::~Wall()
{
	for (int i = 0; i < 6; i++)
		delete Sections[i];
	delete[] Sections;
}

void Wall::createWall()
{
	int index = (int)(holeLocation / 50) + 1;
	SectionType[index] = 0;

	for (int i = 0; i < 6; i++) {
		if (!SectionType[i])
			i++;
		if (rand() % 7 == 5) //if 5 occurs section becomes halfBroken
			SectionType[i] = 2;
		if (rand() % 7 == 4) //if 6 occurs section becomes Broken
			SectionType[i] = 3;
		//otherwise it stays normal
	}

	for (int i = 0; i < 6; i++) {
		float yLoc = ((int)holeLocation % 50) + (i - 1) * 50;
		
		if (SectionType[i] == 1) {
			Sections[i] = new NormalBrick(game,yLoc,this);
		}
		else if (SectionType[i] == 2) {
			Sections[i] = new HalfBrokenBrick(game, yLoc,this);
		}
		else if (SectionType[i] == 3) {
			Sections[i] = new BrokenBrick(game, yLoc,this);
		}
	}
}

void Wall::drawWall()
{
	for (int i = 0; i < 6; i++) {
		if(SectionType[i])
			Sections[i]->drawSection(xLocation);
	}
}

bool Wall::moveWall(float fElapsedTime)
{
	xLocation -= fElapsedTime * horizontalSpeed;
	if (xLocation < -26)
		return true;
	return false;
}

bool Wall::checkBirdCollision(float fVerticalPosition, float birdWidth, float birdHeight) {
	int collision = 0;
	for (int i = 0; i < 6; i++) {
		if (SectionType[i])
			if (Sections[i]->checkBirdCollision(xLocation, fVerticalPosition,  birdWidth, birdHeight))
				collision++;
	}
	return collision;
}


bool Wall::checkBulletCollision(float bulletYPos, float bulletXPos, float bulletWidth, float bulletHeight) {
	int collision = 0;
	for (int i = 0; i < 6; i++) {
		if (SectionType[i])
			if (Sections[i]->checkBulletCollision(xLocation, bulletYPos, bulletXPos, bulletWidth, bulletHeight))
				collision++;
	}
	return collision;
}

void Wall::deleteSection(Section* section) {
	for (int i = 0; i < 6; i++)
		if (Sections[i] == section) {
			SectionType[i] = 0;
			delete Sections[i];
			Sections[i] = nullptr;
		}

}

bool Wall::checkBonusOverlap()
{
	if (xLocation < game->ScreenWidth() / 2 - 13 + 24) 
		if (xLocation > game->ScreenWidth() / 2 - 1.5*26)
			return true;
	return false;
}
