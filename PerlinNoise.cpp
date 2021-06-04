#include "PerlinNoise.h"
#include <random>
#include<cmath>
#include<iostream>




float PerlinNoise::Lerp(float a, float b,float t) 
{
	return a + t * (b - a);
}


float PerlinNoise::SmoothStep(float a) 
{
	return a * a * a * (a * (a * 6 - 15) + 10);
}

float PerlinNoise::ValueNoise1D(int x)
{
	float normX = ((float)x / sizeX) * freqency;
	
	int i0 = (int)(normX);
	float t = SmoothStep(normX - i0);

	
	i0 %= hashMask;
	int i1 = i0 + 1;

	//Interpolate
	int val1 = hash[i0];
	int val2 = hash[i1];
	return (Lerp(val1,val2,t)/hashMask) * 255;
}

float PerlinNoise::ValueNoise2D(float x, float y) 
{
	float normX = (x / sizeX) * freqency + xOffset;
	float normY = (y / sizeY) * freqency + yOffset;


	int x0 = floor(normX);
	int y0 = floor(normY);

	float tx = SmoothStep(normX - x0);
	float ty = SmoothStep(normY - y0);

	x0 = x0 % hashMask;
	y0 = y0 % hashMask;
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	int h0 = hash[x0];
	int h1 = hash[x1];

	int h00 = hash[h0 + y0];
	int h10 = hash[h1 + y0];
	int h01 = hash[h0 + y1];
	int h11 = hash[h1 + y1];
	
	float r1 = Lerp(h00, h10, tx);
	float r2 = Lerp(h01, h11, tx);

	return Lerp(r1, r2, ty);
}

PerlinNoise::PerlinNoise(float _freqency, int _sizeX, int _sizeY, int _xOffset, int _yOffset)
{
	freqency = _freqency;
	sizeX = _sizeX;
	sizeY = _sizeY;
	xOffset = _xOffset;
	yOffset = _yOffset;

}