#pragma once

//VC的 math.h 里有 M_PI 等数学常量，要求在 #include <math.h> 前面定义 _USE_MATH_DEFINES 宏
#define _USE_MATH_DEFINES
#include <cmath>

#include <windows.h>

#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>

#include <fstream>
#include <string>

#include "../Maths/Maths.h"
using namespace std;

class CObj
{
public:
	//位置
	GLfloat m_x, m_y, m_z;
	//长宽高
	GLfloat m_l, m_w, m_h;
	//角度
	GLfloat m_angle_x, m_angle_y, m_angle_z;
	GLfloat m_ambient[4];
	GLfloat m_diffuse[4];
	GLfloat m_specular[4];
	GLfloat m_shininess;

	CObj();
	CObj(istream& file);
	~CObj();

	virtual void draw(){};// = 0;
	virtual void mark(){};// = 0;
	virtual bool is_collision(float x, float y, float z){ return false; };
	friend ostream& operator<<(ostream& out, CObj obj);
	void load(istream& file);
	
protected:
	void SetMaterial();
	void Transform();
};

