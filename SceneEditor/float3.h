#pragma once
class float3
{
public:
	float x;
	float y;
	float z;
public:
	float3(){ x = 0; y = 0; z = 0; }
	float3(float mx, float my, float mz){ x = mx; y = my; z = mz; }
	~float3(){}

	float3 operator+(float3);
	float3 operator-(float3);
	float3 operator/(float);

	friend float3 operator*(float m, float3 f3)
	{
		return float3(f3.x*m, f3.y*m, f3.z*m);
	}
	friend float3 operator*(float3 f3, float m)
	{
		return float3(f3.x*m, f3.y*m, f3.z*m);
	}

	float3 operator=(float3);

	float3& operator += (float3);

};
