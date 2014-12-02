#include "stdafx.h"
#include "Prism.h"

CPrism::CPrism()
{
	m_edge = 3;
	m_height = 1.0;
	m_baseRadius = 1.0;
	m_topRadius = 1.0;
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
	glVertex4fv(vertex);
	for (int i = 0; i <= m_edge; i++)
	{
		vertex[0] = std::sin(delta_angle*i)*r;
		vertex[1] = std::cos(delta_angle*i)*r;
		glVertex4fv(vertex);
	}
	glEnd();
}

void CPrism::DrawSide()
{
	GLfloat vertex[4];
	const GLfloat delta_angle = 2.0*M_PI / m_edge;

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
}