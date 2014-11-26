#pragma once

//VC的 math.h 里有 M_PI 等数学常量，要求在 #include <math.h> 前面定义 _USE_MATH_DEFINES 宏
#define _USE_MATH_DEFINES
#include <cmath>

#include <windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
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
	~CObj();

	virtual void draw() = 0;
protected:
	void SetMaterial();
	void Transform();
};
