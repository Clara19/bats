#pragma once
#include <iostream>

#include <cmath>

struct State {
	double speed, heading, x, y;
};
struct Echo {
	double sourceLevel, targetStrength, A, c;
};

static double myRandom(double min, double max)
//Return random double within range [0,1]
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
};


static double Distance(double dX0, double dY0, double dX1, double dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
};
