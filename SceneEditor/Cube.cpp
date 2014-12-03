#include "stdafx.h"
#include "Cube.h"


CCube::CCube()
{
}


CCube::~CCube()
{
}


void CCube::draw()
{
	SetMaterial();

	glPushMatrix();
	Transform();
	/*
	glBegin(GL_QUADS);
	// 前面
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);	// 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);	// 纹理和四边形的左上

	// 后面
	glNormal3f(0, 0, -1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);	// 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);	// 纹理和四边形的左下

	// 顶面
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);	// 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);	// 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);	// 纹理和四边形的右上

	// 底面
	glNormal3f(0, -1, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);	// 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);	// 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);	// 纹理和四边形的右下

	// 右面
	glNormal3f(1, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);	// 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);	// 纹理和四边形的左下

	// 左面
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);	// 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);	// 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);	// 纹理和四边形的左上
	glEnd();
	*/
	glPopMatrix();
}
