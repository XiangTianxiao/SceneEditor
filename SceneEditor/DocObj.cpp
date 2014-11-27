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
	m_obj->draw();
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
}