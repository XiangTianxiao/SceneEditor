#include "stdafx.h"

#include "Sphere.h"

CSphere::CSphere()
{
	m_slices = 30;
	m_stacks = 30;
	m_r = 1;
}


CSphere::~CSphere()
{
}

void CSphere::draw()
{
	SetMaterial();

	glPushMatrix();
	Transform();
	glutSolidSphere(m_r, m_slices, m_stacks);
	glPopMatrix();
}

void CSphere::mark()
{
	glPushMatrix();
	Transform();
	glScalef(2, 2, 2);
	glScalef(1.1, 1.1, 1.1);

	glDisable(GL_LIGHTING);
	glColor3f(0, 1, 1);

	glBegin(GL_LINES);

	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);

	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);

	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);

	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glEnd();

	glEnable(GL_LIGHTING);
	glPopMatrix();
}

ostream& operator<<(ostream& out, CSphere sphere)
{
	out << "## sphere" << endl;
	out << (CObj)sphere;

	out << "r " << sphere.m_r << endl;
	out << "slices " << sphere.m_slices << endl;
	out << "stacks " << sphere.m_stacks << endl;

	out << endl;
	return out;
}