#pragma once
#include <iostream>
#using <Accord.dll>
#using <Accord.Statistics.dll>
using namespace Accord::Statistics;
using namespace Accord::Statistics::Distributions::Univariate;
ref class VonMisesDist {
private:
	VonMisesDistribution^ distribution;
public:
	VonMisesDist(double mean, double k) {
		distribution = gcnew VonMisesDistribution(mean, k);
	};
	double getRand() {
		return (*distribution).Generate();
	}
};