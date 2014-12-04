//球状物体

#pragma once
#include "Obj.h"
class CSphere :
	public CObj//这是注释
{
public:
	CSphere();
	~CSphere();
	//半径
	GLfloat m_r;
	GLint m_slices;
	GLint m_stacks;
	void draw();
	void mark();
	friend ostream& operator<<(ostream& out, CSphere sphere);

};

