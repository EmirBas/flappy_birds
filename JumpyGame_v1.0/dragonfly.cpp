#include "dragonfly.h"

dragonfly::dragonfly()
{
	StartCheck = 0;	
}


dragonfly::~dragonfly()
{
}



bool dragonfly::OnUserCreate()
{
	delete sprLives;
	delete sprEnd;

	Bonuses = new (Bonus*[2]);
	for (int i = 0; i <= 1; i++) {
		Bonuses[i] = nullptr;
	}

	Walls = new (Wall*[2]);
	for (int i = 0; i <= 1; i++) {
		Walls[i] = nullptr;
	}
	Walls[1] = new Wall(this, 133);

	fTotalTime = 0;
	fLocalTime = 0;
	Lives = 3;
	Ammunition = 10;
	PauseMode = 0;
	endTimer = 0;
	endArrow = 0;

	mybird = new bird(this);	
	mysky = new background(this);
	mymoonorsun = new MoonOrSun();	
	headBullet = nullptr;

	sprStart = new olc::Sprite("dragon.png");
	sprEnd = new olc::Sprite("dragon2.png");
	sprLives = new olc::Sprite("heartIcon.png");
	sprAmmunition = new olc::Sprite("bulletIcon.png");
	return true;
}

bool dragonfly::OnUserUpdate(float fElapsedTime)
{	
	if (!StartCheck)
		return StartScreen();
	if (Lives == 0) 
		return GameOverScreen(fElapsedTime);

	if (!PauseMode) {
		fTotalTime += fElapsedTime;
		fLocalTime = (12 + ((int)(fTotalTime / 6))) % 24 + ((fTotalTime / 6) - ((int)fTotalTime / 6));

		for (int i = 0; i < 2; i++)
			if(Bonuses[i]) 
				if (Bonuses[i]->moveBonus(fElapsedTime)) {
					delete Bonuses[i];
					Bonuses[i] = nullptr;
				}
		

		for (int i = 0; i < 2; i++) {
			if (!Walls[i]) {
				Walls[i] = new Wall(this);
			}
			if (Walls[i]->moveWall(fElapsedTime)) {
				delete Walls[i];
				Walls[i] = nullptr;
			}
		}

		createBonus();

		mysky->updateSky(fElapsedTime);
		mymoonorsun->moveMoonorSun(fLocalTime, fElapsedTime);

		mybird->UpdateBird(fElapsedTime);
		mybird->checkWallCollision(Walls,  Lives);
		mybird->checkBonusCollision(Bonuses, Lives, Ammunition);

		createBullet();

		if (headBullet) {
			headBullet->moveBullet(fElapsedTime);
			headBullet=headBullet->checkCollision(Walls);
		}			
	}
	mysky->Clear(fLocalTime);
	mymoonorsun->drawMoonorSun(this, fLocalTime);
	mysky->drawCloud(); 

	for (int i = 0; i <= 1; i++)
		if (Walls[i])
			Walls[i]->drawWall();

	for (int i = 0; i <= 1; i++)
		if (Bonuses[i])  
			Bonuses[i]->drawBonus();

	mybird->DrawBird();
	
	if (headBullet)
		headBullet->drawBullet();

	writeStats();

	if (GetKey(olc::Key::Q).bPressed) {
		Lives = 0;
	}
	if (GetKey(olc::Key::P).bPressed) {
		PauseMode = 1;
	}
	if (GetKey(olc::Key::R).bPressed) {
		PauseMode = 0;
	}
	if (Lives == 0)
		deleteObjects();

	return true;
}




bool dragonfly::StartScreen() {
		Clear(olc::WHITE);
		DrawSprite(40, 20, sprStart, 1);
		DrawString(20, 20, "Press S to Start", olc::RED);
		DrawString(30, 170, "In-Game Controls: ", olc::RED);
		DrawString(20, 180, "P: Pause", olc::RED);
		DrawString(20, 190, "R: Resume", olc::RED);
		DrawString(20, 200, "Q: Quit", olc::RED);

		if (GetKey(olc::Key::S).bPressed) 
			StartCheck = 1;		

		return true;
}

bool dragonfly::GameOverScreen(float fElapsedTime) { 
		endTimer += fElapsedTime;

		Clear(olc::BLACK);
		DrawSprite(0, 40, sprEnd, 1);
		DrawString(ScreenWidth() / 2 - 38, ScreenHeight() / 2 - 20, "GAME OVER", olc::WHITE);
		DrawString(ScreenWidth() / 2 - 35, ScreenHeight() / 2 - 10, "SCORE: " + (to_string_with_precision(fTotalTime, 0)), olc::WHITE);
		DrawString(ScreenWidth() / 2 - 40, ScreenHeight() / 2, "TRY AGAIN?", olc::WHITE);	
		DrawString(ScreenWidth() / 2 - 40, ScreenHeight() / 2 + 10, "(yes / no)", olc::WHITE);

		if ((int)(2 * endTimer) % 2) {
			DrawSprite(ScreenWidth() / 2 - 20 + (endArrow % 2) * 40, ScreenHeight() / 2 + 20, sprLives, 1);
			DrawString(3, 3, "Press ENTER to select", olc::WHITE);
			DrawString(3, 13, "Press LEFT/RIGHT to swap", olc::WHITE);
		}

		if (GetKey(olc::Key::LEFT).bPressed || GetKey(olc::Key::RIGHT).bPressed)
			endArrow++;

		if (GetKey(olc::Key::ENTER).bPressed) {
			if (!(endArrow % 2))
				OnUserCreate();
			if (endArrow % 2){
				delete sprLives;
				delete sprEnd;
				return false;
			}	
		}
		return true;
}

void dragonfly::createBullet() {
	if (GetKey(olc::Key::W).bPressed && Ammunition > 0) {
		headBullet = mybird->createBullet(headBullet);
		Ammunition--;}
}

void dragonfly::createBonus() {
	for (int i = 0; i < 2; i++)
		if (!Bonuses[i]) {
			if (0.001 - (1-i)*0.0007 > (float)rand() / RAND_MAX)// kalpse 0.0003 mermiyse 0.001 ihtimal
			{
				if (i == 0)
					Bonuses[i] = new Heart(this);
				else if (i == 1)
					Bonuses[i] = new Ammo(this);

				for (int j = 0; j < 2; j++)
					if (Walls[j]->checkBonusOverlap()) {
						delete Bonuses[i];
						Bonuses[i] = nullptr;
					}
			}
		}
}

void dragonfly::deleteObjects() {
	delete mybird;
	mybird = nullptr;

	delete mymoonorsun;
	mymoonorsun = nullptr;

	delete mysky;
	mysky = nullptr;

	for (int i = 0; i <= 1; i++) {
		delete Walls[i];
		delete Bonuses[i];
		Bonuses[i] = nullptr;
		Walls[i] = nullptr;
	}
	delete headBullet;
	headBullet = nullptr;

	delete sprStart;
	delete sprAmmunition;

}

void dragonfly::writeStats() {
	mybird->writeSpeed();
	DrawString(ScreenWidth() - 95, 3, "Time :", olc::GREEN);
	DrawString(ScreenWidth() - 45, 3, (to_string_with_precision(fLocalTime, 2)), olc::RED);
	DrawString(3, 3, "Lives :", olc::GREEN);
	for (int i = 0; i < Lives; i++) {
		DrawSprite(58 + i * 10, 2, sprLives, 1);
	}
	DrawString(3, 13, "Ammo  :", olc::GREEN);
	for (int i = 0; i < fmin(6,Ammunition); i++) {
		DrawSprite(58 + i * 10, 12, sprAmmunition, 1);
	}
	if(Ammunition>6)
		DrawString(118, 13, "+" + (to_string_with_precision(Ammunition-6, 2)), olc::YELLOW);

	if (PauseMode) {
		DrawString(ScreenWidth() / 2 - 20, ScreenHeight() / 2, "PAUSED", olc::WHITE);
	}
}

