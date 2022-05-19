#pragma once
class dragonfly;
class Bonus
{
protected:
	float horizontalSpeed;
	float bonus[2];  // x and y positions
	dragonfly* game;


public:

	virtual bool moveBonus(float fElapsedTime)=0;

	virtual void drawBonus()=0;

	virtual bool checkCollision(float fVerticalPosition, float birdWidth, float birdHeight) = 0;


	Bonus(dragonfly* theGame);
	virtual ~Bonus();
};

