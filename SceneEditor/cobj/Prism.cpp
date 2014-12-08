#include "stdafx.h"
#include "Prism.h"
#include <algorithm>
#include "float3.h"
using namespace std;
CPrism::CPrism()
{
	m_edge = 3;
	m_height = 1.0;
	m_baseRadius = 1.0;
	m_topRadius = 1.0;
}

CPrism::CPrism(istream& file) :CPrism()
{
	CPrism();
	string temp;
	file >> temp;

	while (temp != "</prism>")
	{
		if (temp == "<obj>")
			CObj::load(file);
		if (temp == "edge")
			file >> m_edge;
		if (temp == "baseRadius")
			file >> m_baseRadius;
		if (temp == "topRadius")
			file >> m_topRadius;
		if (temp == "height")
			file >> m_height;
		file >> temp;
	}
}


CPrism::~CPrism()
{
}

void CPrism::draw()
{
	SetMaterial();

	glPushMatrix();
	Transform();
	glNormal3f(0, 0, -1);
	DrawBottom(0, m_baseRadius);
	glNormal3f(0, 0, 1);
	DrawBottom(m_height, m_topRadius);
	DrawSide();
	glPopMatrix();
}

void CPrism::DrawBottom(GLfloat h, GLfloat r)
{
	GLfloat vertex[4];
	const GLfloat delta_angle = 2.0*M_PI / m_edge;

	glBegin(GL_TRIANGLE_FAN);
	vertex[0] = 0;
	vertex[1] = 0;
	vertex[2] = h;
	vertex[3] = 1.0;
	glTexCoord2f(0.5f, 0.5f);
	glVertex4fv(vertex);
	for (int i = 0; i <= m_edge; i++)
	{
		glTexCoord2f(sin(delta_angle*i), cos(delta_angle*i));
		vertex[0] = std::sin(delta_angle*i)*r;
		vertex[1] = std::cos(delta_angle*i)*r;
		glVertex4fv(vertex);
	}
	glEnd();
}

void CPrism::DrawSide()
{
	const GLfloat delta_angle = 2.0*M_PI / m_edge;
	///////////////////////////////////////////////////
	glBegin(GL_QUADS);
	for (int i = 0; i < m_edge; i++)
	{
		float3 v1(sin(delta_angle*i)*m_baseRadius, cos(delta_angle*i)*m_baseRadius, 0);
		float3 v2(sin(delta_angle*i)*m_topRadius, cos(delta_angle*i)*m_topRadius, m_height);
		float3 v3(sin(delta_angle*(i + 1))*m_topRadius, cos(delta_angle*(i + 1))*m_topRadius, m_height);
		float3 v4(sin(delta_angle*(i + 1))*m_baseRadius, cos(delta_angle*(i + 1))*m_baseRadius, 0);
		float3 vt = (v2 - v1)*(v3 - v2);
		glNormal3f(vt.x, vt.y, vt.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(v1.x, v1.y, v1.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(v2.x, v2.y, v2.z);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(v3.x, v3.y, v3.z);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(v4.x, v4.y, v4.z);
	}
	glEnd();
	///////////////////////////////////////////////////
	/*
	GLfloat vertex[4];

	glBegin(GL_QUAD_STRIP);
	vertex[3] = 1.0;

	for (int i = 0; i <= m_edge; i++)
	{


		vertex[2] = 0.0;
		vertex[0] = std::sin(delta_angle*i)*m_baseRadius;
		vertex[1] = std::cos(delta_angle*i)*m_baseRadius;
		glVertex4fv(vertex);

		vertex[2] = m_height;
		vertex[0] = std::sin(delta_angle*i)*m_topRadius;
		vertex[1] = std::cos(delta_angle*i)*m_topRadius;
		glVertex4fv(vertex);
	}
	glEnd();
	*/
}

void CPrism::mark()
{
	glPushMatrix();
	glTranslatef(0, 0, m_height / 2);
	Transform();
	GLfloat max_r = max(m_baseRadius, m_topRadius);
	glScalef(max_r, max_r, 1);
	glScalef(2, 2, m_height);
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

ostream& operator<<(ostream& out, CPrism prism)
{
	out << "<prism>" << endl;
	out << (CObj)prism;

	//边数
	out << "edge " << prism.m_edge << endl;
	//下底半径
	out << "baseRadius " << prism.m_baseRadius << endl;
	//上底半径
	out << "topRadius " << prism.m_topRadius << endl;
	//高度
	out << "height " << prism.m_height << endl;
	out << "</prism>" << endl;

	out << endl;
	return out;
}

bool CPrism::is_collision(float x, float y, float z)
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
	if (result.z > m_height || result.z < 0)
		return false;
	float r = sqrt(result.x*result.x + result.y*result.y);
	if (r >(m_baseRadius - result.z*(m_baseRadius - m_topRadius) / m_height))
		return false;
	return true;
}

