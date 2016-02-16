#include <iostream>
#include <random>
#include "RicianDist.h"
#include <time.h>

RicianDist::RicianDist(double s, double sigma) {

	generator1 = new std::mt19937;
	(*generator1).seed(time(NULL));
	distribution1 = new std::normal_distribution<double>();

	generator2 = new std::mt19937;
	(*generator2).seed(time(NULL));
	distribution2 = new std::normal_distribution<double>();
}


double RicianDist::getRand(double s, double sigma) {
	
	double x = sigma*(*distribution1)(*generator1) + s;
	double y = sigma*(*distribution2)(*generator2);
	return sqrt(x*x + y*y);
}

