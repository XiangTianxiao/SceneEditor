#include "stdafx.h"

#include "Sphere.h"

CSphere::CSphere()
{
	m_slices = 30;
	m_stacks = 30;
	m_r = 1;
}

CSphere::CSphere(istream& file) :CSphere()
{
	CSphere();
	string temp;
	file >> temp;

	while (temp != "</sphere>")
	{
		if (temp == "<obj>")
			CObj::load(file);
		if (temp == "r")
			file >> m_r;
		if (temp == "slices")
			file >> m_slices;
		if (temp == "stacks")
			file >> m_stacks;
		file >> temp;
	}

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
	out << "<sphere>" << endl;
	out << (CObj)sphere;

	out << "r " << sphere.m_r << endl;
	out << "slices " << sphere.m_slices << endl;
	out << "stacks " << sphere.m_stacks << endl;
	out << "</sphere>" << endl;

	out << endl;
	return out;
}