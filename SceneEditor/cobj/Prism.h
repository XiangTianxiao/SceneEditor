#pragma once
#include "Obj.h"
class CPrism :
	public CObj
{
public:
	CPrism();
	CPrism(istream& file);
	~CPrism();

	GLint m_edge;
	//下底半径
	GLfloat m_baseRadius;
	//上底半径
	GLfloat m_topRadius;
	//高度
	GLfloat m_height;

	void draw();
	void mark();
	bool is_collision(float x, float y, float z);
	friend ostream& operator<<(ostream& out, CPrism prism);

private:
	void DrawBottom(GLfloat h, GLfloat r);
	void DrawSide();
};