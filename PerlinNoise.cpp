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
}

float PerlinNoise::ValueNoise1D(int x)
{
	float normX = ((float)x / sizeX) * freqency;
	
	int i0 = (int)(normX);
	float c = SmoothStep(normX - i0);

	
	i0 = i0 % hashMask;
	int i1 = i0 + 1;

	//Interpolate
	int val1 = hash[i0];
	int val2 = hash[i1];
	return (Lerp(val1,val2,c)/hashMask) * 255;
}

float PerlinNoise::ValueNoise2D(int x, int y) 
{
	float normX = ((float)x / sizeX) * freqency;
	float normY = ((float)y / sizY) * freqency;

	
	int iX = (int)(normX);
	int iY = (int)(normY);

	float cx = SmoothStep(normX - iX);
	float cy = SmoothStep(normY - iY);

	//std::cout << cx << ";" << cy << std::endl;

	iX = iX % hashMask;
	iY = iY % hashMask;

	int iX1 = iX + 1;
	int iY1 = iY + 1;

	int h0 = hash[iX];
	int h1 = hash[iX1];
	int h00 = hash[h0 + iY];
	int h10 = hash[h1 + iY];
	int h01 = hash[h0 + iY1];
	int h11 = hash[h1 + iY1];

	return (Lerp(Lerp(h00, h10, cx), Lerp(h01, h11, cx), cy) / hashMask) * 255;
}

PerlinNoise::PerlinNoise(float _freqency, int _sizeX, int _sizeY) 
{
	freqency = _freqency;
	sizeX = _sizeX;
	sizY = _sizeY;

}