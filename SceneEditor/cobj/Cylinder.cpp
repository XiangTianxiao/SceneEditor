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

CCylinder::CCylinder(istream& file)
{
	//placement new
	//http://blog.chinaunix.net/uid-23741326-id-3385581.html
	//不这么使用的话，则是新建一个临时变亮，而非调用这个函数

	string temp;
	file >> temp;

	while (temp != "</cylinder>")
	{
		if (temp == "<obj>")
		{
			new(this) CObj(file);
			new(this) CCylinder();
		}
		//下底半径
		if (temp == "baseRadius")
			file >> m_baseRadius;
		//上底半径
		if (temp == "topRadius")
			file >> m_topRadius;
		//高度
		if (temp == "height")
			file >> m_height;
		//你懂得
		if (temp == "slices")
			file >> m_slices;
		//你懂得
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

	//下底半径
	out << "baseRadius " << cylinder.m_baseRadius << endl;
	//上底半径
	out << "topRadius " << cylinder.m_topRadius << endl;
	//高度
	out << "height " << cylinder.m_height << endl;
	//你懂得
	out << "slices " << cylinder.m_slices << endl;
	//你懂得
	out << "stacks " << cylinder.m_stacks << endl;
	out << "</cylinder>" << endl;
	out << endl;
	return out;
}