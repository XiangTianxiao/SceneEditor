#include "stdafx.h"

#include "Sphere.h"

CSphere::CSphere()
{
	m_slices = 30;
	m_stacks = 30;
	m_r = 1;
	quadObj = NULL;
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
	gluDeleteQuadric(quadObj);
}

void CSphere::draw()
{
	if (quadObj == NULL)
	{
		quadObj = gluNewQuadric();//创建一个二次曲面物体
		gluQuadricTexture(quadObj, GL_TRUE);        //启用该二次曲面的纹理
	}

	SetMaterial();

	glPushMatrix();
	Transform();
	//glutSolidSphere(m_r, m_slices, m_stacks);
	gluSphere(quadObj, m_r, m_slices, m_stacks);
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


bool CSphere::is_collision(float x, float y, float z)
{
	float dx = x - m_x;
	float dy = y - m_y;
	float dz = z - m_z;

	MATRIX4X4 m;
	VECTOR4D v(dx, dy, dz, 1);
	{
		glPushMatrix();
		glLoadIdentity();
		glScalef(m_l, m_w, m_h);
		glRotatef(m_angle_x, 1, 0, 0);
		glRotatef(m_angle_y, 0, 1, 0);
		glRotatef(m_angle_z, 0, 0, 1);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		glPopMatrix();
	}
	VECTOR4D result = m.GetInverse()*v;
	float r = sqrt(result.x*result.x + result.y*result.y + result.z*result.z);
	if (r > m_r)
		return false;
	return true;
}

