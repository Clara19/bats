#pragma once
#include <map>

#include "Base.h"

class Prey {
public:
	std::map<int, State> prevStates;
	State currentState;
	double targetStrength;
public:
	Prey(double initLocX, double initLocY, double p_targetStrength) {
		currentState.x = initLocX;
		currentState.y = initLocY;
		targetStrength = p_targetStrength;
	};
};