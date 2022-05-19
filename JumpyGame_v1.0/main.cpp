//olcPixelGameEngine is being developed and shared for education purposes by javidx9 in OneLoneCoder Youtube Channel:
//https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA/about
//JumpyGame based on olcPixelGameEngine is developed by Bahadir Pamuk for IE201 course in Industrial Engineering Department of Bogazici University
//Last Edit Date: 03.04.2019

#define OLC_PGE_APPLICATION
#include "dragonfly.h"


int main()
{
	dragonfly demo;
	if (demo.Construct(240, 240, 4, 4))
		demo.Start();

	return 0;
}
