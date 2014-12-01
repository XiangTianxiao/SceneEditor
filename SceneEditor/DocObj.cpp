
#include "stdafx.h"
#include "DocObj.h"
CDocObj::CDocObj(CString name, OBJ_TYPE type)
{
	m_name = name;
	m_type = type;
	switch (type)
	{
	case CUBE:
		m_obj = new CCube();
		break;
	case CYLINDER:
		m_obj = new CCylinder();
		break;
	case PRISM:
		m_obj = new CPrism();
		break;
	case SPHERE:
		m_obj = new CSphere();
		break;
	default:
		throw CString("CDocObj(OBJ_TYPE type)");
		break;
	}

	m_whether_texture = false;
	m_bitmapData = NULL;
}

CDocObj::CDocObj(CString name, CString file_name)
{

}


CDocObj::~CDocObj()
{
	delete m_obj;
}

void CDocObj::draw_property(CMFCPropertyGridCtrl* PropList)
{
	PropList->RemoveAll();
	draw_property_obj(PropList);
	switch (m_type)
	{
	case CUBE:
		draw_property_cube(PropList);
		break;
	case CYLINDER:
		draw_property_cylinder(PropList);
		break;
	case PRISM:
		draw_property_prism(PropList);
		break;
	case SPHERE:
		draw_property_sphere(PropList);
		break;
	default:
		throw CString("draw_property");
		break;
	}
}

void CDocObj::draw()
{
	if (m_whether_texture == true)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glEnable(GL_TEXTURE_2D);
	}
	m_obj->draw();
	glDisable(GL_TEXTURE_2D);
}

void CDocObj::draw_property_obj(CMFCPropertyGridCtrl* PropList)
{
	PropList->EnableHeaderCtrl(FALSE);
	PropList->EnableDescriptionArea();
	PropList->SetVSDotNetLook();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("通用"));

	CMFCPropertyGridProperty* pLocation = new CMFCPropertyGridProperty(_T("对象位置"), 0, TRUE);
	CMFCPropertyGridProperty* p = new CMFCPropertyGridProperty(_T("X"), (_variant_t)m_obj->m_x, _T("世界坐标中X的位置"));
	pLocation->AddSubItem(p);
	p = new CMFCPropertyGridProperty(_T("Y"), (_variant_t)m_obj->m_y, _T("世界坐标中Y的位置"));
	pLocation->AddSubItem(p);
	p = new CMFCPropertyGridProperty(_T("Z"), (_variant_t)m_obj->m_z, _T("世界坐标中Z的位置"));
	pLocation->AddSubItem(p);
	pLocation->AllowEdit(FALSE);
	pGroup1->AddSubItem(pLocation);



	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("对象大小"), 0, TRUE);
	p = new CMFCPropertyGridProperty(_T("长"), (_variant_t)m_obj->m_l, _T("物体的长度"));
	pSize->AddSubItem(p);
	p = new CMFCPropertyGridProperty(_T("宽"), (_variant_t)m_obj->m_w, _T("物体的宽度"));
	pSize->AddSubItem(p);
	p = new CMFCPropertyGridProperty(_T("高"), (_variant_t)m_obj->m_h, _T("物体的高度"));
	pSize->AddSubItem(p);
	pSize->AllowEdit(FALSE);
	pGroup1->AddSubItem(pSize);


	CMFCPropertyGridProperty* pAngle = new CMFCPropertyGridProperty(_T("对象旋转角度"), 0, TRUE);
	p = new CMFCPropertyGridProperty(_T("X轴角度"), (_variant_t)m_obj->m_angle_x, _T("物体的X轴方向旋转角度"));
	pAngle->AddSubItem(p);
	p = new CMFCPropertyGridProperty(_T("Y轴角度"), (_variant_t)m_obj->m_angle_y, _T("物体的Y轴方向旋转角度"));
	pAngle->AddSubItem(p);
	p = new CMFCPropertyGridProperty(_T("Z轴角度"), (_variant_t)m_obj->m_angle_z, _T("物体的Z轴方向旋转角度"));
	pAngle->AddSubItem(p);
	pAngle->AllowEdit(FALSE);
	pGroup1->AddSubItem(pAngle);

	PropList->AddProperty(pGroup1);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("纹理"));
	CMFCPropertyGridProperty* whether_texture = new CMFCPropertyGridProperty(_T("是否纹理"), (_variant_t)m_whether_texture, _T("指是否选择纹理"));
	pGroup2->AddSubItem(whether_texture);

	if (m_whether_texture == true)
	{
		pGroup2->AddSubItem(new CMFCPropertyGridFileProperty(_T("选择纹理文件"), TRUE, m_texture_file_name, _T("bmp"), NULL, _T("bmp Files(*.bmp)|*.bmp|"), _T("选择bmp文件")));//选择文件按钮  
	}

	PropList->AddProperty(pGroup2);

}
void CDocObj::draw_property_cube(CMFCPropertyGridCtrl* PropList)
{

}
void CDocObj::draw_property_cylinder(CMFCPropertyGridCtrl* PropList)
{

}
void CDocObj::draw_property_prism(CMFCPropertyGridCtrl* PropList)
{

}
void CDocObj::draw_property_sphere(CMFCPropertyGridCtrl* PropList)
{

}

void CDocObj::change_value(CMFCPropertyGridProperty* pProp)
{
	CString name = pProp->GetName();  //被改变的参数名
	COleVariant t = pProp->GetValue(); //改变之后的值
	//m_obj->m_x += 1;
	if (name == "X")
	{
		m_obj->m_x = GLfloat(t.fltVal);
		return;
	}
	if (name == "Y")
	{
		m_obj->m_y = GLfloat(t.fltVal);
		return;
	}
	if (name == "Z")
	{
		m_obj->m_z = GLfloat(t.fltVal);
		return;
	}

	if (name == "长")
	{
		m_obj->m_l = GLfloat(t.fltVal);
		return;
	}
	if (name == "宽")
	{
		m_obj->m_w = GLfloat(t.fltVal);
		return;
	}
	if (name == "高")
	{
		m_obj->m_h = GLfloat(t.fltVal);
		return;
	}

	if (name == "X轴角度")
	{
		m_obj->m_angle_x = GLfloat(t.fltVal);
		return;
	}
	if (name == "Y轴角度")
	{
		m_obj->m_angle_y = GLfloat(t.fltVal);
		return;
	}
	if (name == "X轴角度")
	{
		m_obj->m_angle_z = GLfloat(t.fltVal);
		return;
	}
	if (name == "是否纹理")
	{
		m_whether_texture = (t.boolVal != 0);
		return;
	}
	if (name == "选择纹理文件")
	{
		m_texture_file_name = t;
		if (m_bitmapData != NULL)
		{
			delete[] m_bitmapData;
			m_bitmapData = NULL;
		}

		//M$我操你大爷，搞得这么麻烦
		//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
		int n = m_texture_file_name.GetLength();    // n = 14, len = 18
		//获取宽字节字符的大小，大小是按字节计算的
		int len = WideCharToMultiByte(CP_ACP, 0, m_texture_file_name, m_texture_file_name.GetLength(), NULL, 0, NULL, NULL);
		//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
		char * pFileName = new char[len + 1];  //以字节为单位
		//宽字节编码转换成多字节编码
		WideCharToMultiByte(CP_ACP, 0, m_texture_file_name, m_texture_file_name.GetLength(), pFileName, len, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, m_texture_file_name, m_texture_file_name.GetLength() + 1, pFileName, len + 1, NULL, NULL);
		pFileName[len + 1] = 0;  //多字节字符以'/0'结束

		texload(pFileName);

		return;
	}
}

void CDocObj::texload(const char *filename)
{
	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头

	m_bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, m_texture);
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

unsigned char* CDocObj::LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
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
		throw CString("Error in LoadBitmapFile: the file is not a bitmap file\n");
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
		throw CString("Error in LoadBitmapFile: memory error\n");
	}

	// 读入bitmap图像数据
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功
	if (bitmapImage == NULL) {
		throw CString("Error in LoadBitmapFile: memory error\n");
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