#pragma once
#include <random>
namespace RNG {
	inline std::default_random_engine engine{ std::random_device{}() };
	//random int [0, max)
	int NextInt(int max);
	//random int [min, max)
	int NextInt(int min, int max);
	//random double [0, 1]
	double NextDouble();
}