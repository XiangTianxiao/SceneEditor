#pragma once

#include "Obj.h"

#include "Cylinder.h"
#include "Cube.h"
#include "Prism.h"
#include "Sphere.h"

class CDocObj
{
public:
	CDocObj(CString name, OBJ_TYPE type);
	~CDocObj();

	CString m_name;
	CObj* m_obj;
	OBJ_TYPE m_type;
	void draw_property(CMFCPropertyGridCtrl* PropList);
	void change_value(CMFCPropertyGridProperty* pProp);
	void draw();

	void draw_property_obj(CMFCPropertyGridCtrl* PropList);
	void draw_property_cube(CMFCPropertyGridCtrl* PropList);
	void draw_property_cylinder(CMFCPropertyGridCtrl* PropList);
	void draw_property_prism(CMFCPropertyGridCtrl* PropList);
	void draw_property_sphere(CMFCPropertyGridCtrl* PropList);
};

