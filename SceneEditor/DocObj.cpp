
#include "stdafx.h"
#include "DocObj.h"

CDocObj::CDocObj()
{
	m_whether_texture = false;
	m_texture_loaded = false;
	m_bitmapData = NULL;
}

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
	case HELICOPTER:
		m_obj = new helicopter();
		break;
	default:
		throw CString("CDocObj(OBJ_TYPE type)");
		break;
	}

	m_whether_texture = false;
	m_texture_loaded = false;
	m_bitmapData = NULL;
}

CDocObj::CDocObj(CString name, CString file_name)
{
	m_name = name;
	m_type = OBJ_FILE;
	CObjFile* m_objfile = new CObjFile();
	string filename;
	filename = cstring_to_string(file_name);

	m_objfile->loadObj(filename);

	m_obj = (CObj*)m_objfile;

	m_whether_texture = false;
	m_bitmapData = NULL;
}


CDocObj::~CDocObj()
{
	switch (m_type)
	{
	case CUBE:
		((CCube*)m_obj)->~CCube();
		break;
	case CYLINDER:
		((CCylinder*)m_obj)->~CCylinder();
		break;
	case PRISM:
		((CPrism*)m_obj)->~CPrism();
		break;
	case SPHERE:
		((CSphere*)m_obj)->~CSphere();
		break;
	case OBJ_FILE:
		((CObjFile*)m_obj)->~CObjFile();
		break;
	default:
		break;
	}
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
	case OBJ_FILE:
		draw_property_objfile(PropList);
		break;
	default:
		throw CString("draw_property");
		break;
	}
}

void CDocObj::draw()
{
	if (m_whether_texture == true && m_texture_loaded == true)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glEnable(GL_TEXTURE_2D);
	}
	if (m_whether_texture == false)
		glDisable(GL_TEXTURE_2D);
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


	////////////////////////////////////

	int am_rgb[] = { m_obj->m_ambient[0] * 255.0, m_obj->m_ambient[1] * 255.0, m_obj->m_ambient[2] * 255.0 };
	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("环境反射光"), RGB(am_rgb[0], am_rgb[1], am_rgb[2]), NULL, _T("材质的环境反射光"));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pGroup1->AddSubItem(pColorProp);

	int di_rgb[] = { m_obj->m_diffuse[0] * 255.0, m_obj->m_diffuse[1] * 255.0, m_obj->m_diffuse[2] * 255.0 };
	pColorProp = new CMFCPropertyGridColorProperty(_T("漫反射光"), RGB(di_rgb[0], di_rgb[1], di_rgb[2]), NULL, _T("材质的漫反射光"));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pGroup1->AddSubItem(pColorProp);

	int sp_rgb[] = { m_obj->m_specular[0] * 255.0, m_obj->m_specular[1] * 255.0, m_obj->m_specular[2] * 255.0 };
	pColorProp = new CMFCPropertyGridColorProperty(_T("镜面反射光"), RGB(sp_rgb[0], sp_rgb[1], sp_rgb[2]), NULL, _T("材质的镜面反射光"));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pGroup1->AddSubItem(pColorProp);

	CMFCPropertyGridProperty* pLightness = new CMFCPropertyGridProperty(_T("物体亮度"), m_obj->m_shininess, _T("指物体的亮度"));

	pGroup1->AddSubItem(pLightness);

	/////////////////////////////////////
	

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
	PropList->EnableHeaderCtrl(FALSE);
	PropList->EnableDescriptionArea();
	PropList->SetVSDotNetLook();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("圆柱体"));

	CMFCPropertyGridProperty* pBaseRadius = new CMFCPropertyGridProperty(_T("圆柱下底半径"), ((CCylinder*)m_obj)->m_baseRadius, _T("指圆柱的下底半径"));

	pGroup1->AddSubItem(pBaseRadius);

	CMFCPropertyGridProperty* pTopRadius = new CMFCPropertyGridProperty(_T("圆柱上底半径"), ((CCylinder*)m_obj)->m_topRadius, _T("指圆柱的上底半径"));

	pGroup1->AddSubItem(pTopRadius);

	CMFCPropertyGridProperty* pHeight = new CMFCPropertyGridProperty(_T("圆柱高度"), ((CCylinder*)m_obj)->m_height, _T("指圆柱的高度"));

	pGroup1->AddSubItem(pHeight);

	CMFCPropertyGridProperty* pSlices = new CMFCPropertyGridProperty(_T("圆柱经度"), (float)((CCylinder*)m_obj)->m_slices, _T("越高越平滑"));

	pGroup1->AddSubItem(pSlices);

	CMFCPropertyGridProperty* pStacks = new CMFCPropertyGridProperty(_T("圆柱纬度"), (float)((CCylinder*)m_obj)->m_stacks, _T("越高越平滑"));

	pGroup1->AddSubItem(pStacks);

	PropList->AddProperty(pGroup1);
}
void CDocObj::draw_property_prism(CMFCPropertyGridCtrl* PropList)
{
	PropList->EnableHeaderCtrl(FALSE);
	PropList->EnableDescriptionArea();
	PropList->SetVSDotNetLook();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("棱体"));

	CMFCPropertyGridProperty* pEdge = new CMFCPropertyGridProperty(_T("棱体边数"), (float)((CPrism*)m_obj)->m_edge, _T("指棱体的边数"));

	pGroup1->AddSubItem(pEdge);

	CMFCPropertyGridProperty* pBaseRadius = new CMFCPropertyGridProperty(_T("棱体下底半径"), ((CPrism*)m_obj)->m_baseRadius, _T("指棱体的下底半径"));

	pGroup1->AddSubItem(pBaseRadius);

	CMFCPropertyGridProperty* pTopRadius = new CMFCPropertyGridProperty(_T("棱体上底半径"), ((CPrism*)m_obj)->m_topRadius, _T("指棱体的上底半径"));

	pGroup1->AddSubItem(pTopRadius);

	CMFCPropertyGridProperty* pHeight = new CMFCPropertyGridProperty(_T("棱体高度"), ((CPrism*)m_obj)->m_height, _T("指棱体的高度"));

	pGroup1->AddSubItem(pHeight);

	PropList->AddProperty(pGroup1);
}
void CDocObj::draw_property_sphere(CMFCPropertyGridCtrl* PropList)
{
	PropList->EnableHeaderCtrl(FALSE);
	PropList->EnableDescriptionArea();
	PropList->SetVSDotNetLook();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("球体"));



	CMFCPropertyGridProperty* pSlices = new CMFCPropertyGridProperty(_T("球体经度"), (float)((CSphere*)m_obj)->m_slices, _T("越高越平滑"));

	pGroup1->AddSubItem(pSlices);

	CMFCPropertyGridProperty* pStacks = new CMFCPropertyGridProperty(_T("球体纬度"), (float)((CSphere*)m_obj)->m_stacks, _T("越高越平滑"));

	pGroup1->AddSubItem(pStacks);

	PropList->AddProperty(pGroup1);
}
void CDocObj::draw_property_objfile(CMFCPropertyGridCtrl* PropList)
{

}
void CDocObj::change_value(CMFCPropertyGridProperty* pProp)
{
	CString name = pProp->GetName();  //被改变的参数名
	COleVariant t = pProp->GetValue(); //改变之后的值
	//m_obj->m_x += 1;
	///////////////////////////////////////////////////////////

	if (name == "环境反射光")
	{
		COLORREF c = t.lVal;
		m_obj->m_ambient[0] = (c & 0xff) / 255.0;
		m_obj->m_ambient[1] = (c >> 8 & 0xff) / 255.0;
		m_obj->m_ambient[2] = (c >> 16 & 0xff) / 255.0;
		return;
	}

	if (name == "漫反射光")
	{
		COLORREF c = t.lVal;
		m_obj->m_diffuse[0] = (c & 0xff) / 255.0;
		m_obj->m_diffuse[1] = (c >> 8 & 0xff) / 255.0;
		m_obj->m_diffuse[2] = (c >> 16 & 0xff) / 255.0;
		return;
	}

	if (name == "镜面反射光")
	{
		COLORREF c = t.lVal;
		m_obj->m_specular[0] = (c & 0xff) / 255.0;
		m_obj->m_specular[1] = (c >> 8 & 0xff) / 255.0;
		m_obj->m_specular[2] = (c >> 16 & 0xff) / 255.0;
		return;
	}

	if (name == "物体亮度")
	{
		m_obj->m_shininess = GLfloat(t.fltVal);
		return;
	}

	if (name == "圆柱下底半径")
	{
		((CCylinder*)m_obj)->m_baseRadius = GLfloat(t.fltVal);
		return;
	}
	if (name == "圆柱上底半径")
	{
		((CCylinder*)m_obj)->m_topRadius = GLfloat(t.fltVal);
		return;
	}
	if (name == "圆柱高度")
	{
		((CCylinder*)m_obj)->m_height = GLfloat(t.fltVal);
		return;
	}
	if (name == "圆柱经度")
	{
		((CCylinder*)m_obj)->m_slices = GLfloat(t.fltVal);
		return;
	}
	if (name == "圆柱纬度")
	{
		((CCylinder*)m_obj)->m_stacks = GLfloat(t.fltVal);
		return;
	}
	if (name == "棱体下底半径")
	{
		((CPrism*)m_obj)->m_baseRadius = GLfloat(t.fltVal);
		return;
	}
	if (name == "棱体上底半径")
	{
		((CPrism*)m_obj)->m_topRadius = GLfloat(t.fltVal);
		return;
	}
	if (name == "棱体高度")
	{
		((CPrism*)m_obj)->m_height = GLfloat(t.fltVal);
		return;
	}
	if (name == "棱体边数")
	{
		((CPrism*)m_obj)->m_edge = GLfloat(t.fltVal);
		return;
	}
	if (name == "球体经度")
	{
		((CSphere*)m_obj)->m_slices = GLfloat(t.fltVal);
		return;
	}
	if (name == "球体纬度")
	{
		((CSphere*)m_obj)->m_stacks = GLfloat(t.fltVal);
		return;
	}
	///////////////////////////////////////////////////////////




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
	if (name == "Z轴角度")
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

		string filename;
		filename = cstring_to_string(m_texture_file_name);

		glGenTextures(1, &m_texture);
		texload(filename.c_str());

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
	m_texture_loaded = true;
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

void CDocObj::exportobj(CString file_name)
{
	if (m_type != OBJ_FILE)
		throw CString("void CDocObj::exportobj(CString filename) not obj file");
	string filename;
	filename = cstring_to_string(file_name);
	((CObjFile*)m_obj)->exportobj(filename);

}