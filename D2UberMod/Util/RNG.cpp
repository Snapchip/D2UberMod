#include "RNG.h"

int RNG::NextInt(int max) {	
	return RNG::NextInt(0, max);
}
int RNG::NextInt(int min, int max) {
	std::uniform_int_distribution<int> distr(min, max-1);
	return distr(RNG::engine);
}
double RNG::NextDouble() {
	std::uniform_real_distribution<double> distr(0.0, 1.0);
	return distr(RNG::engine);
}