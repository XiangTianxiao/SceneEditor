#include "stdafx.h"
#include "Cylinder.h"

CCylinder::CCylinder()
{
	m_quadricObj = gluNewQuadric();

	m_baseRadius = 1.0;
	m_topRadius = 1.0;
	m_height = 1.0;
	m_slices = 10;
	m_stacks = 10;
}


CCylinder::~CCylinder()
{
	gluDeleteQuadric(m_quadricObj);
}

void CCylinder::draw()
{
	SetMaterial();
	
	glPushMatrix();
	Transform();
	gluCylinder(m_quadricObj, m_baseRadius, m_topRadius, m_height, m_slices, m_stacks);
	//top  
	DrawCircleArea(0.0, 0.0, m_height, m_topRadius, m_slices);
	//base  
	DrawCircleArea(0.0, 0.0, 0.0, m_baseRadius, m_slices);
	glPopMatrix();

}

void CCylinder::DrawCircleArea(float cx, float cy, float cz, float r, int num_segments)
{
	GLfloat vertex[4];

	const GLfloat delta_angle = 2.0*M_PI / num_segments;

	glBegin(GL_TRIANGLE_FAN);

	vertex[0] = cx;
	vertex[1] = cy;
	vertex[2] = cz;
	vertex[3] = 1.0;
	glVertex4fv(vertex);

	//draw the vertex on the contour of the circle   
	for (int i = 0; i < num_segments; i++)
	{
		vertex[0] = std::cos(delta_angle*i) * r + cx;
		vertex[1] = std::sin(delta_angle*i) * r + cy;
		vertex[2] = cz;
		vertex[3] = 1.0;
		glVertex4fv(vertex);
	}

	vertex[0] = 1.0 * r + cx;
	vertex[1] = 0.0 * r + cy;
	vertex[2] = cz;
	vertex[3] = 1.0;
	glVertex4fv(vertex);
	glEnd();
}