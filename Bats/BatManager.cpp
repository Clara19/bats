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

double BatManager::getAmplitude(double targetX, double targetY, double oTargetStrength) {
	double distance = Distance(currentState.x, currentState.y, targetX, targetY);

	double dotProduct = (cos(currentState.heading)*(targetX - currentState.x) + sin(currentState.heading)*(targetX - currentState.y));
	//(currentState.x - bat->currentState.x);
	//double tanAngle = (tan(currentState.heading) - distanceSlope) / (1 - tan(currentState.heading)*distanceSlope);
	double cosAngle = dotProduct / distance;
	double azimuth = (echo.A + 2)*(cosAngle - 1);
	double soundLosses = 20 * (log(0.1 / distance)) + distance*echo.c;
	return echo.sourceLevel + oTargetStrength + azimuth + soundLosses;
}

bool BatManager::echolocateBat(BatManager* bat) {
	bool isSeen = false;
	double amplitude = getAmplitude(bat->currentState.x, bat->currentState.y, bat->echo.targetStrength);
	if (amplitude >= hearingThreshold) {
		if (identifiedBats.size()==1000)
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

void BatManager::locatePrey(Prey *preys[]) {
	identifiedPreys.clear();
	for (int i = 0; i < sizeof(preys); i++) {
		if (getAmplitude(preys[i]->currentState.x, preys[i]->currentState.y, preys[i]->targetStrength)) {
			double dist = Distance(currentState.x, currentState.y, preys[i]->currentState.x, preys[i]->currentState.y);
			identifiedPreys.insert(std::pair<double, Prey*>(dist, preys[i]);
		}
	}
}

State BatManager::updateBat() {

	if (time==0) {
		currentState.heading = myRandom( -3*PI/4, -PI/4);
		currentState.x = myRandom(-3, 3);
		currentState.y = myRandom(28, 30);
		time++;
		return currentState;		
	}

	State newState;
	newState.speed = velocityDist.getRand(4.81, 2.18);

	double desiredHeading;
	if (flight == 1 && myRandom(0, 1) < 0.05) {
		flight = 0; leader = NULL;  std::cout << "changed ";
	}
	std::cout << flight << std::endl;
	if (!flight || (flight && leader->time<delay) ) {
		desiredHeading = (*(gcnew VonMisesDist(currentState.heading, 557))).getRand();
		//std::cout << desiredHeading << std::endl;
	}
	else
	{
		std::map<int, State>::iterator leaderPos = leader->prevStates.find(time - delay);
		if (leaderPos != leader->prevStates.end()) {
			//std::cout << leaderPos->second.heading;
			desiredHeading = (*(gcnew VonMisesDist((currentState.heading + leaderPos->second.heading)/2, 2473))).getRand();
		}
	}

	double headingChange = desiredHeading - currentState.heading;
	double maxAngularChange = 4 * 9.81 / 50 / newState.speed;
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
	prevStates.insert(std::pair<int, State>(time, currentState));
	time = time + 1;
	currentState = newState;

	return newState;
}	
		

