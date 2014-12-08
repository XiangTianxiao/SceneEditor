#include "stdafx.h"
#include "Cylinder.h"

CCylinder::CCylinder()
{
	m_quadricObj = gluNewQuadric();

	m_baseRadius = 1.0;
	m_topRadius = 1.0;
	m_height = 1.0;
	m_slices = 30;
	m_stacks = 30;
}

CCylinder::CCylinder(istream& file) :CCylinder()
{
	string temp;
	file >> temp;

	while (temp != "</cylinder>")
	{
		if (temp == "<obj>")
		{
			CObj::load(file);
		}
		//ÏÂµ×°ë¾¶
		if (temp == "baseRadius")
			file >> m_baseRadius;
		//ÉÏµ×°ë¾¶
		if (temp == "topRadius")
			file >> m_topRadius;
		//¸ß¶È
		if (temp == "height")
			file >> m_height;
		//Äã¶®µÃ
		if (temp == "slices")
			file >> m_slices;
		//Äã¶®µÃ
		if (temp == "stacks")
			file >> m_stacks;
		file >> temp;
	}
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
	glNormal3f(0, 0, 1);
	DrawCircleArea(0.0, 0.0, m_height, m_topRadius, m_slices);
	//base  
	glNormal3f(0, 0, -1);
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

void CCylinder::mark()
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

ostream& operator<<(ostream& out, CCylinder cylinder)
{
	out << "<cylinder>" << endl;
	out << (CObj)cylinder;

	//ÏÂµ×°ë¾¶
	out << "baseRadius " << cylinder.m_baseRadius << endl;
	//ÉÏµ×°ë¾¶
	out << "topRadius " << cylinder.m_topRadius << endl;
	//¸ß¶È
	out << "height " << cylinder.m_height << endl;
	//Äã¶®µÃ
	out << "slices " << cylinder.m_slices << endl;
	//Äã¶®µÃ
	out << "stacks " << cylinder.m_stacks << endl;
	out << "</cylinder>" << endl;
	out << endl;
	return out;
}

bool CCylinder::is_collision(float x, float y, float z)
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
	if (r > (m_baseRadius-result.z*(m_baseRadius-m_topRadius)/m_height))
		return false;
	return true;
}