#include "stdafx.h"
#include "Cube.h"


CCube::CCube()
{
}


CCube::~CCube()
{
}


void CCube::draw()
{
	SetMaterial();

	glPushMatrix();
	Transform();
	glutSolidCube(1);
	glPopMatrix();
}
