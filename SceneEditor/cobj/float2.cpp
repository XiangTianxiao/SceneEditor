#include "stdafx.h"
#include "float2.h"

float2 float2::operator +(float2 m)
{
	float2 result;
	result.x = x + m.x;
	result.y = y + m.y;
	return result;
}

float2 float2::operator - (float2 m)
{
	float2 result;
	result.x = x - m.x;
	result.y = y - m.y;
	return result;
}

float2 float2::operator /(float m)
{
	if (m == 0){
		throw "error";
		return float2(x, y);
	}
	else
		return float2(x / m, y / m);
}

float2 float2::operator =(float2 f2)
{
	x = f2.x;
	y = f2.y;
	return float2(x, y);
}
