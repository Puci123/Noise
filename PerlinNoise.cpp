#include "PerlinNoise.h"
#include <random>


float PerlinNoise::GetValue() 
{
	return rand() % 256;
}

PerlinNoise::PerlinNoise() 
{

}