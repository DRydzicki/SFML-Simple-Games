#pragma once
#include <random>
#include <ctime>


template<typename RndEngine = std::mt19937>
class Random
{
	RndEngine rndEngine;

	template<typename T>
	using UniformRealDist = std::uniform_real_distribution<T>;
	using UniformDist = std::uniform_int_distribution<int>;
	

public:
	static Random rnd;

	Random(int seed = time(nullptr)) 
	: rndEngine(seed)
	{}


	int getIntInRange(int min, int max) {
		return UniformDist(min, max)(rndEngine);
	}

	template<typename T>
	T getRealInRange(T min, T max)
	{
		return UniformRealDist<float>(min, max)(rndEngine);
	}

};
