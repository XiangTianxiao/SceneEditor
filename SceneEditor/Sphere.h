//球状物体

#pragma once
#include "Obj.h"
class CSphere :
	public CObj//这是注释
{
public:
	CSphere();
	~CSphere();

	GLint m_slices;
	GLint m_stacks;
	void draw();
};

