#include "stdafx.h"
#include "DocObj.h"


CDocObj::CDocObj(OBJ_TYPE type)
{
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
void CDocObj::change_value(CMFCPropertyGridProperty* pProp)
{

}
void CDocObj::draw_property_obj(CMFCPropertyGridCtrl* PropList)
{

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