#include "stdafx.h"
#include "float3.h"

float3 float3::operator +(float3 m)
{
	float3 result;
	result.x = x + m.x;
	result.y = y + m.y;
	result.z = z + m.z;
	return result;
}

float3 float3::operator - (float3 m)
{
	float3 result;
	result.x = x - m.x;
	result.y = y - m.y;
	result.z = z - m.z;
	return result;
}

float3 float3::operator /(float m)
{
	if (m == 0){
		printf("error /");
		return float3(x, y, z);
	}
	else
		return float3(x / m, y / m, z / m);
}

float3 float3::operator =(float3 f3)
{
	x = f3.x;
	y = f3.y;
	z = f3.z;
	return float3(x, y, z);
}
