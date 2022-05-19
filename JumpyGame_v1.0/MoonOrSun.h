#pragma once
class dragonfly;

class MoonOrSun
{
	olc::Sprite* sprMoon;
	olc::Sprite* sprSun;
	float ylocation;
public:
	MoonOrSun();
	~MoonOrSun();
	void moveMoonorSun(float fLocalTime, float fElapsedTime);
	void drawMoonorSun(dragonfly* game, float fLocalTime);
	void resetLocation();

};

