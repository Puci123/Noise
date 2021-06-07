#include "ValueNoise.h"
#include <random>
#include<cmath>
#include<iostream>




double ValueNoise::Lerp(double a, double b,double t) 
{
	return  t * (b - a) + a;
}


double ValueNoise::SmoothStep(double a) 
{
	if (a > 1) a = 1;
	else if (a < 0) a = 0;

	return a * a * a * (a * (a * 6 - 15) + 10);
}

double ValueNoise::ValueNoise1D(float x)
{
	
	
	double value = 0;
	float freqency = lacurity;
	float amplitude = peristance;

	for (size_t i = 0; i < octaves; i++)
	{
		double normX = (x / sizeX) * freqency;
		int i0 = (int)(normX);
		double t = SmoothStep(normX - (double)i0);


		i0 %= hashMask;
		int i1 = i0 + 1;

		//Interpolate
		int val1 = hash[i0];
		int val2 = hash[i1];

		value += (Lerp(val1, val2, t) / hashMask) * amplitude;
	}
	


	return value ;
}

double ValueNoise::ValueNoise2D(float x, float y) 
{
	double freqency = lacurity;
	double amplitudte = peristance;	
	double value = 0;


	for (int i = 0; i < octaves; i++)
	{

		double normX = (x / sizeX) * freqency + xOffset;
		double normY = (y / sizeY) * freqency + yOffset;


		int x0 = floor(normX);
		int y0 = floor(normY);

		double tx = SmoothStep(normX - x0);
		double ty = SmoothStep(normY - y0);

		x0 = x0 % (int)(hashMask/2 - 1);
		y0 = y0 % (int)(hashMask/2 - 1);
		int x1 = x0 + 1;
		int y1 = y0 + 1;

		int h0 = hash[x0];
		int h1 = hash[x1];

		
		int h00 = hash[h0 + y0];
		int h10 = hash[h1 + y0];
		int h01 = hash[h0 + y1];
		int h11 = hash[h1 + y1];


		double r1 = Lerp(h00, h10, tx);
		double r2 = Lerp(h01, h11, tx);
		
		value += (Lerp(r1, r2, ty) / hashMask) * amplitudte;

		freqency *= lacurity;
		amplitudte *= peristance;

	}
	return value;
}

ValueNoise::ValueNoise(float _lacunarity,float _persitacne, int _sizeX, int _sizeY, int _xOffset, int _yOffset,int _octaves)
{
	lacurity = _lacunarity;
	peristance = _persitacne;
	sizeX = _sizeX;
	sizeY = _sizeY;
	xOffset = _xOffset;
	yOffset = _yOffset;
	octaves = _octaves;

}