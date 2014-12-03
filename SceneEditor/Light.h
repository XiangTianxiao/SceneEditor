#pragma once
class CLight
{
public:
	CLight();
	~CLight();

public:
	CString m_name;
	bool m_on;
	GLfloat m_light_pos[4];
	GLfloat m_color[4];
	void draw_light(int num);
	void draw_property(CMFCPropertyGridCtrl* PropList);
	void change_value(CMFCPropertyGridProperty* pProp);
};
