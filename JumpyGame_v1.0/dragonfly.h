#pragma once
#include <iostream>
#include <string>
#include <sstream> //for to_string_with_precision


#include "olcSimpleEngine.h"
#include "background.h"
#include "bird.h"
#include "Heart.h"
#include "MoonOrSun.h"
#include "Bonus.h"
#include "Wall.h"
#include "Bullet.h"
#include "Ammo.h"





class dragonfly : public olc::PixelGameEngine
{
	float fLocalTime;
	float fTotalTime;
	int Lives;
	int Ammunition;

	int PauseMode;
	int StartCheck;

	float endTimer;
	int endArrow;

	Bonus** Bonuses; //first inidice heart, second ammo
	Wall** Walls;   // two section columns


	bird* mybird;
	background* mysky;
	MoonOrSun* mymoonorsun;
	Bullet* headBullet;

	olc::Sprite* sprEnd;
	olc::Sprite* sprStart;
	olc::Sprite* sprLives;
	olc::Sprite* sprAmmunition;

public:
	template <typename T> std::string to_string_with_precision(const T a_value, const int n = 6){
		std::ostringstream out;
		out.precision(n);
		out << std::fixed << a_value;
		return out.str();
	}

	dragonfly();
	~dragonfly();

private:
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);

	bool StartScreen();
	bool GameOverScreen(float fElapsedTime);
	void createBullet();
	void createBonus();
	void deleteObjects();
	void writeStats();
};

