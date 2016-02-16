#pragma once
#include <iostream>
#include <random>

class RicianDist {	
private:
	std::default_random_engine* generator1;
	std::normal_distribution<double>* distribution1;
	std::default_random_engine* generator2;
	std::normal_distribution<double>* distribution2;
public:
	RicianDist(double s, double sigma);
	double getRand(double s, double sigma);
};