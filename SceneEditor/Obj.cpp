#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;

	m_angle_x = 0;
	m_angle_y = 0;
	m_angle_z = 0;

	m_l = 1.0;
	m_w = 1.0;
	m_h = 1.0;

	m_ambient[0] = 0.2;
	m_ambient[1] = 0.2;
	m_ambient[2] = 0.2;
	m_ambient[3] = 1.0;

	m_diffuse[0] = 0.8;
	m_diffuse[1] = 0.8;
	m_diffuse[2] = 0.8;
	m_diffuse[3] = 1.0;
	
	m_specular[0] = 0.0;
	m_specular[1] = 0.0;
	m_specular[2] = 0.0;
	m_specular[3] = 0.0;

	m_shininess = 0.0;
}


CObj::~CObj()
{
}

void CObj::SetMaterial()
{
	glColor3f(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
}

void CObj::Transform()
{
	glTranslatef(m_x, m_y, m_z);
	glScalef(m_l, m_w, m_h);
	glRotatef(m_angle_x, 1, 0, 0);
	glRotatef(m_angle_y, 0, 1, 0);
	glRotatef(m_angle_z, 0, 0, 1);
}