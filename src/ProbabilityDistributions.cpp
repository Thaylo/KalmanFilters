#include "ProbabilityDistributions.h"

std::random_device rd;
std::mt19937 gen(rd());

double
centeredNormal(double stdDev)
{
	std::normal_distribution<> d(0.0,stdDev);
	return d(gen);
}
