#include "stdafx.h"

#include "Sphere.h"

CSphere::CSphere()
{
	m_slices = 10;
	m_stacks = 10;
}


CSphere::~CSphere()
{
}

void CSphere::draw()
{
	SetMaterial();

	glPushMatrix();
	Transform();
	glutSolidSphere(1, m_slices, m_stacks);
	glPopMatrix();
}