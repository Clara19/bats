#pragma once
#include <map>
#include "RicianDist.h"

#include "Prey.h"


class BatManager {
public:
	std::map<int, BatManager*> identifiedBats;
	std::map<double, Prey*> identifiedPreys;
	std::map<int, State> prevStates;
	State currentState;
	int delay, flight, time = 0;

	BatManager* leader = NULL;
	double hearingThreshold;
	RicianDist velocityDist;
	Echo echo;

public:
	BatManager(int b_delay, int b_flight, int b_hearingThreshold, Echo b_echo);
	double getAmplitude(double targetX, double targetY, double targetStrength);
	bool echolocateBat(BatManager* bat);
	void locatePrey(std::vector<Prey*> preys);
	State updateBat();
};