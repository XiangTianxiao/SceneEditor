#pragma once
class float2
{
public:
	float x;
	float y;
public:
	float2(){ x = 0; y = 0; }
	float2(float mx, float my){ x = mx; y = my; }
	~float2(){}

	float2 operator+(float2);
	float2 operator-(float2);
	float2 operator/(float);

	friend float2 operator*(float m, float2 f2)
	{
		return float2(f2.x*m, f2.y*m);
	}
	friend float2 operator*(float2 f2, float m)
	{
		return float2(f2.x*m, f2.y*m);
	}

	float2 operator=(float2);

	float2& operator += (float2);

};