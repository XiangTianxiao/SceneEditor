#include "stdafx.h"

#include "Sphere.h"

CSphere::CSphere()
{
	m_slices = 30;
	m_stacks = 30;
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