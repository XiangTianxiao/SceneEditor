//圆柱体

#pragma once
#include "Obj.h"
class CCylinder :
	public CObj
{
public:
	CCylinder();
	~CCylinder();
private:
	GLUquadricObj* m_quadricObj;
public:
	//下底半径
	GLfloat m_baseRadius;
	//上底半径
	GLfloat m_topRadius;
	//高度
	GLfloat m_height;
	//你懂得
	GLint m_slices;
	//你懂得
	GLint m_stacks;

	void draw();
private:
	void DrawCircleArea(float cx, float cy, float cz, float r, int num_segments);
};

