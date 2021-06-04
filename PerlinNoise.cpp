#include "PerlinNoise.h"
#include <random>
#include<cmath>
#include<iostream>




float PerlinNoise::Lerp(float a, float b,float t) 
{
	return a + t * (b - a);
	//return a;
}


float PerlinNoise::SmoothStep(float a) 
{
	return a * a * a * (a * (a * 6 - 15) + 10);
	//return a;
}

float PerlinNoise::ValueNoise1D(int x)
{
	float normX = ((float)x / sizeX) * freqency;
	
	int i0 = (int)(normX);
	float c = SmoothStep(normX - i0);

	
	i0 %= hashMask;
	int i1 = i0 + 1;

	//Interpolate
	int val1 = hash[i0];
	int val2 = hash[i1];
	return (Lerp(val1,val2,c)/hashMask) * 255;
}

float PerlinNoise::ValueNoise2D(float x, float y) 
{
	float normX = (x / sizeX) * freqency;
	float normY = (y / sizeY) * freqency;


	int iX = floor(normX);
	int iY = floor(normY);

	iX = iX % hashMask;
	iY = iY % hashMask;

	return ((float)hash[(hash[iX] + iY)]);
	

}

PerlinNoise::PerlinNoise(float _freqency, int _sizeX, int _sizeY, int _xOffset, int _yOffset)
{
	freqency = _freqency;
	sizeX = _sizeX;
	sizeY = _sizeY;
	xOffset = _xOffset;
	yOffset = _yOffset;

}