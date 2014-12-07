#pragma once
#include "Obj.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Prism.h"

class helicopter :
	public CObj
{
public:
	CCube m_rotor1, m_rotor2;
	CCylinder cylinder1;
	CSphere sphere;
	CCube tail;
	CPrism tail2;
	CPrism prism;
	CPrism body;
	CPrism body2;

	helicopter();
	~helicopter();
	void draw();
	void mark();
	void rotate(int delta_angle);


	GLuint m_texture[2];
	BYTE* m_bitmapData;
	void texload(const char *filename, GLuint texture);
	unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
};

