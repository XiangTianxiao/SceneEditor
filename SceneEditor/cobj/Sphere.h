//球状物体

#pragma once
#include "Obj.h"
class CSphere :
	public CObj//这是注释
{
public:
	CSphere();
	CSphere(istream& file);
	~CSphere();
	//半径
	GLfloat m_r;
	GLint m_slices;
	GLint m_stacks;
	void draw();
	void mark();
	bool is_collision(float x, float y, float z);
	friend ostream& operator<<(ostream& out, CSphere sphere);

	GLUquadricObj *quadObj;
};

