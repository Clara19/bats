#pragma once
#include <map>

#include "BatManager.h"

class Prey {
public:
	std::map<int, State> prevStates;
	State currentState;
	double targetStrength;
};