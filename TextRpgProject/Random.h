#pragma once
#include <random>

inline int GetIntToRandom(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);

	return dis(gen);
}

inline double GetDoubleToRandom(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(min, max);

	return dis(gen);
}