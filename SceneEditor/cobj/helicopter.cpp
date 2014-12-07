#include "stdafx.h"
#include "helicopter.h"

#define BITMAP_ID 0x4D42

helicopter::helicopter()
{
	//旋翼
	m_rotor1.m_l = 4;
	m_rotor1.m_w = 0.1;
	m_rotor1.m_h = 0.01;

	m_rotor2.m_l = 0.1;
	m_rotor2.m_w = 4;
	m_rotor2.m_h = 0.01;
	//旋翼的轴
	cylinder1.m_topRadius = 0.05;
	cylinder1.m_baseRadius= 0.05;
	cylinder1.m_height = 0.3;

	//舱
	body.m_angle_x = 90;
	body.m_angle_y = 90;
	body.m_edge = 6;
	body.m_baseRadius = 0.5;
	body.m_topRadius= 0.5;

	body2.m_x = 1;
	body2.m_angle_x = 90;
	body2.m_angle_y = 90;
	body2.m_edge = 6;
	body2.m_baseRadius = 0.5;
	body2.m_topRadius = 0.2;
	body2.m_height = 0.5;

	//sphere.m_r = 0.5;
	sphere.m_r = 0.45;
	sphere.m_l = 1.5;
	//尾巴
	tail.m_l = 2.5;
	tail.m_h = 0.05;
	tail.m_w = 0.1;
	
	prism.m_angle_x = 90;
	prism.m_angle_z = 180;
	prism.m_l = 0.1;
	prism.m_w = 0.1;
	prism.m_y = 0.5;
	prism.m_x = -0.3;

	tail2.m_angle_x = 90;
	tail2.m_height = 0.01;
	tail2.m_baseRadius = 0.3;
	tail2.m_topRadius= 0.3;
	tail2.m_z = 0.17;
	tail2.m_x = -0.4;

	glGenTextures(2, m_texture);
	texload("texture/glass.bmp", m_texture[0]);
	texload("texture/camouflage.bmp", m_texture[1]);

}


helicopter::~helicopter()
{
}

void helicopter::draw()
{
	SetMaterial();
	glPushMatrix();
	Transform();
	{
		glPushMatrix();
		glTranslatef(0, 0, 0.7);
		m_rotor1.draw();
		m_rotor2.draw();
		glTranslatef(0, 0, -0.3);
		cylinder1.draw();
		glPopMatrix();
	}
	{
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, m_texture[0]);
		glEnable(GL_TEXTURE_2D);
		sphere.draw();
		body.draw();
		body2.draw();
		glTranslatef(2.5, 0, 0);
		tail.draw();
		glTranslatef(1.25, 0, 0);
		prism.draw();
		tail2.draw();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}



	glPopMatrix();

	rotate(15);
}

void helicopter::mark()
{

}

void helicopter::rotate(int delta_angle)
{
	m_rotor1.m_angle_z = (int)(m_rotor1.m_angle_z + delta_angle) % 360;
	m_rotor2.m_angle_z = (int)(m_rotor2.m_angle_z + delta_angle) % 360;
}


void helicopter::texload(const char *filename, GLuint texture)
{
	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头

	m_bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,
		0, 	    //mipmap层次(通常为，表示最上层) 
		GL_RGB,	//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2 
		bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2 
		0, //边框(0=无边框, 1=有边框) 
		GL_RGB,	//bitmap数据的格式
		GL_UNSIGNED_BYTE, //每个颜色数据的类型
		m_bitmapData);	//bitmap数据指针  
}

unsigned char* helicopter::LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;	// 文件指针
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
	unsigned char	*bitmapImage;		// bitmap图像数据
	int	imageIdx = 0;		// 图像位置索引
	unsigned char	tempRGB;	// 交换变量

	// 以“二进制+读”模式打开文件filename 
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) return NULL;
	// 读入bitmap文件图
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		throw ("Error in LoadBitmapFile: the file is not a bitmap file\n");
	}

	// 读入bitmap信息头
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存
	//下列语句如果不+1会造成HEAP CORRUPTION DETECTED错误
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage + 1];
	// 验证内存是否创建成功
	if (!bitmapImage) {
		throw ("Error in LoadBitmapFile: memory error\n");
	}

	// 读入bitmap图像数据
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功
	if (bitmapImage == NULL) {
		throw ("Error in LoadBitmapFile: memory error\n");
	}

	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
	for (imageIdx = 0; imageIdx < (int)bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件
	fclose(filePtr);
	return bitmapImage;
}
