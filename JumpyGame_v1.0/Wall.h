#pragma once
class dragonfly;
class Section;
class Wall
{
	dragonfly* game;
	float xLocation;
	float holeLocation;
	float horizontalSpeed;
	Section** Sections;
	int SectionType[6];

public:
	Wall(dragonfly* theGame);
	Wall(dragonfly * theGame, int x);
	~Wall();

	void createWall();
	void drawWall();

	bool moveWall(float fElapsedTime);

	bool checkBirdCollision(float fVerticalPosition, float birdWidth, float birdHeight);

	bool checkBulletCollision(float verticalPos, float horizontalPos, float bulletWidth, float bulletHeight);

	void deleteSection(Section * section);

	bool checkBonusOverlap();
};

