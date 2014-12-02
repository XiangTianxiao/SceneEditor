#pragma once
#include "Obj.h"

#include "float2.h"
#include "float3.h"
#include <vector>
#include <string>

#include <fstream>

using namespace std;
struct TriangleFace
{
	int v[3]; // vertex indices
	int vt[3];
};

class CObjFile :
	public CObj
{
public:
	CObjFile();
	~CObjFile();

	void draw();
	void loadObj(string filename);
public:
	vector<float3> verts;
	vector<float2> vt;
	vector<TriangleFace> faces;
	//模型的包围盒
	float3 bounding_box[2];
	//模型的包围球参数
	float3 bounding_sphere_c;
	float bounding_sphere_r;
};

