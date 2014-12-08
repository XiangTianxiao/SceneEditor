//长方形
//具有长宽高(l, w, h)三个属性

#pragma once
#include "Obj.h"
class CCube :
	public CObj
{
public:
	CCube();
	CCube(istream& file);
	~CCube();
	void draw();
	void mark();
	bool is_collision(float x, float y, float z);
	friend ostream& operator<<(ostream& out, CCube cube);
};
