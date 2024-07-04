#pragma once
#include <random>
int randomInt(int min, int max) {
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

float randomFloat(float min, float max) {
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());

	std::uniform_real_distribution<> dis(min, max);

	return static_cast<float>(dis(gen));
}

double randomDouble(double min, double max) {
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd());

	std::uniform_real_distribution<> dis(min, max);

	return dis(gen);
}