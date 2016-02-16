#include <iostream>
#include "BatManager.h"
#include <cmath>
#include "RicianDist.h"
#include "VonMisesDist.h"
#define PI 3.14159265

double myRandom(double min, double max)
//Return random double within range [0,1]
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

double Distance(double dX0, double dY0, double dX1, double dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

BatManager::BatManager(int b_delay, int b_flight, int b_hearingThreshold, Echo b_echo) : velocityDist(4.81, 2.18) {
	delay = b_delay;
	flight = 0;
	hearingThreshold = b_hearingThreshold;
	echo = b_echo;
};

double BatManager::getAmplitude(BatManager* bat) {

	double distance = Distance(currentState.x, bat->currentState.x, currentState.y, bat->currentState.y);

	double distanceSlope = (currentState.y - bat->currentState.y)/(currentState.x - bat->currentState.x);
	double tanAngle = (tan(currentState.heading) - distanceSlope) / (1 - tan(currentState.heading)*distanceSlope);

	double azimuth = (echo.A + 2)*(cos(atan(tanAngle)) - 1);
	double soundLosses = 20 * (log(0.1 / distance)) + distance*echo.c;
	return echo.sourceLevel + bat->echo.targetStrength + azimuth + soundLosses;
}

bool BatManager::echolocateBat(BatManager* bat) {
	bool isSeen = false;
	if (getAmplitude(bat) > hearingThreshold) {
		if (identifiedBats.size()==100)
			identifiedBats.erase(identifiedBats.begin());
		identifiedBats.insert(std::pair<int, BatManager*>(time + 1, bat));
		isSeen = true;
	}
	std::map<int, BatManager*>::iterator potentialLeader = identifiedBats.find(time+1-delay);
	if (potentialLeader != identifiedBats.end()) {
		flight = 1;
		leader = potentialLeader->second;
	}
	else {
		flight = 0;
		leader = NULL;
	}
	return isSeen;
}


BatState BatManager::updateBat() {

	if (time==0) {
		currentState.heading = myRandom(-PI, PI);
		currentState.x = myRandom(1, 10);
		currentState.y = myRandom(1, 10);
		time++;
		return currentState;		
	}

	BatState newState;
	newState.speed = velocityDist.getRand(4.81, 2.18);

	double desiredHeading;
	if (myRandom(0,1) < 0.05)
		flight = 0;
	
	if (!flight || (flight && leader->time<delay) ) {
		desiredHeading = (*(gcnew VonMisesDist(currentState.heading, 557))).getRand();
		//std::cout << desiredHeading << std::endl;
	}
	else
	{
		std::map<int, BatState>::iterator leaderPos = leader->prevStates.find(time - delay);
		if (leaderPos != leader->prevStates.end()) {
			desiredHeading = (*(gcnew VonMisesDist((currentState.heading + leaderPos->second.heading)/2, 2473))).getRand();
		}
	}

	double headingChange = desiredHeading - currentState.heading;
	double maxAngularChange = 9.81 / 50 / newState.speed;
	if (abs(headingChange) <= maxAngularChange)
		newState.heading = desiredHeading;
	else if (headingChange < maxAngularChange)
		newState.heading = currentState.heading - maxAngularChange;
	else
		newState.heading = currentState.heading + maxAngularChange;
	double a = cos(newState.heading);
	double b = sin(newState.heading);
	newState.x = currentState.x + newState.speed * 1 / 50 * cos(newState.heading);
	newState.y = currentState.y + newState.speed * 1 / 50 * sin(newState.heading);
	if (prevStates.size() == 1000)
		prevStates.erase(prevStates.begin());
	prevStates.insert(std::pair<int, BatState>(time, currentState));
	time = time + 1;
	currentState = newState;
	return newState;
}	
		

