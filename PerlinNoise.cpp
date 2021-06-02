#include "PerlinNoise.h"
#include <random>
#include<cmath>



float PerlinNoise::ValueNoise1D(int x)
{
	float normX = ((float)x / sizeX) * freqency;
	
	int i = round(normX);
	i = i % hashMask;
	return ((float)hash[i] / hashMask) * 255;
}

float PerlinNoise::ValueNoise2D(int x, int y) 
{
	float normX = ((float)x / sizeX) * freqency;
	float normY = ((float)y / sizY) * freqency;


	int iX = round(normX);
	int iY = round(normY);

	iX = iX % hashMask;
	iY = iY % hashMask;

	return ((float)hash[(hash[iX] + iY)] / hashMask) * 255;
}

PerlinNoise::PerlinNoise(float _freqency, int _sizeX, int _sizeY) 
{
	freqency = _freqency;
	sizeX = _sizeX;
	sizY = _sizeY;

}