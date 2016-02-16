#pragma once
#include <map>
#include "RicianDist.h"


struct BatState {
	double speed, heading, x, y;
};
struct Echo {
	double sourceLevel, targetStrength, A, c;
};
class BatManager {
public:
	std::map<int, BatState> prevStates;
	std::map<int, BatManager*> identifiedBats;
	BatState currentState;
	int delay, flight, time = 0;
	BatManager* leader = NULL;
	double hearingThreshold;
	RicianDist velocityDist;
	Echo echo;

public:
	BatManager(int b_delay, int b_flight, int b_hearingThreshold, Echo b_echo);
	double getAmplitude(BatManager* bat);
	bool echolocateBat(BatManager* bat);
	BatState updateBat();
};