#pragma once
class dragonfly;

class background
{
	dragonfly* game;
	olc::Sprite* sprCloud;

	float cloud[2];
	float cloudSpeed;

public:
	background(dragonfly* theGame);
	~background();

	void Clear(float fLocalTime);
	void updateSky(float fElapsedTime);
	void drawCloud();
private:
	void createCloud();
	void moveCloud(float fElapsedTime);
};

