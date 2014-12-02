
//I copied these functions and classes from this blog
//http://blog.csdn.net/wangjiannuaa/article/details/6758173
#include "stdafx.h"
#include "ObjFile.h"

#undef max
#undef min

#include <algorithm>
#include <math.h>

using namespace std;

#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z*(v).z)  
#define norm2(v)   dot(v,v)        // norm2 = squared length of vector  
#define norm(v)    sqrt(norm2(v))  // norm = length of vector  
#define d(u,v)     norm(u-v)       // distance = norm of difference  

CObjFile::CObjFile()
{
}


CObjFile::~CObjFile()
{
}

void CObjFile::draw()
{
	SetMaterial();

	glPushMatrix();
	Transform();

	glBegin(GL_TRIANGLES);
	auto v = faces;
	for (auto i = v.begin(); i != v.end(); i++)
	{
		glTexCoord2f(vt[i->vt[0] - 1].x, vt[i->vt[0] - 1].y);
		glVertex3f(verts[i->v[0] - 1].x, verts[i->v[0] - 1].y, verts[i->v[0] - 1].z);

		glTexCoord2f(vt[i->vt[1] - 1].x, vt[i->vt[1] - 1].y);
		glVertex3f(verts[i->v[1] - 1].x, verts[i->v[1] - 1].y, verts[i->v[1] - 1].z);

		glTexCoord2f(vt[i->vt[2] - 1].x, vt[i->vt[2] - 1].y);
		glVertex3f(verts[i->v[2] - 1].x, verts[i->v[2] - 1].y, verts[i->v[2] - 1].z);
	}
	glEnd();
	glPopMatrix();
}


void CObjFile::loadObj(string filename)
{
	std::ifstream in(filename.c_str());

	if (!in.good())
		throw "ERROR: loading obj:(" + filename + ") file is not good";

	char buffer[256], str[255];
	float f1, f2, f3;

	while (!in.getline(buffer, 255).eof())
	{
		buffer[255] = '\0';
		sscanf_s(buffer, "%s", str, 255);
		// reading a vertex
		if (buffer[0] == 'v' && buffer[1] == ' ')
		{
			if (sscanf_s(buffer, "v %f %f %f", &f1, &f2, &f3, 255) == 3)
				verts.push_back(float3(f1, f2, f3));
			else
				throw "ERROR: vertex not in wanted format in OBJLoader";
		}
		//read vt
		if (buffer[0] == 'v'&& buffer[1] == 't'&&buffer[2] == ' ')
		{
			if (sscanf_s(buffer, "vt %f %f", &f1, &f2, 255) == 2)
				vt.push_back(float2(f1, f2));
			else
				throw "ERROR: vertex not in wanted format in OBJLoader";
		}
		// reading FaceMtls 
		else if (buffer[0] == 'f' && buffer[1] == ' ')
		{
			TriangleFace f;
			int nt = sscanf_s(buffer, "f %d/%d %d/%d %d/%d", &f.v[0], &f.vt[0], &f.v[1], &f.vt[1], &f.v[2], &f.vt[2], 255);
			if (nt != 6)
				throw "ERROR: I don't know the format of that FaceMtl";
			faces.push_back(f);
		}
	}

	float xmin, ymin, zmin, xmax, ymax, zmax;
	int Pxmin, Pxmax, Pymin, Pymax, Pzmin, Pzmax;

	//calculate the bounding sphere
	xmin = xmax = verts[0].x;
	ymin = ymax = verts[0].y;
	zmin = zmax = verts[0].z;
	Pxmin = Pxmax = Pymin = Pymax = Pzmin = Pzmax = 0;

	//calculate the bounding box
	bounding_box[0] = float3(verts[0].x, verts[0].y, verts[0].z);
	bounding_box[1] = float3(verts[0].x, verts[0].y, verts[0].z);

	for (unsigned int i = 1; i < verts.size(); i++)
	{
		//update min value
		bounding_box[0].x = min(verts[i].x, bounding_box[0].x);
		bounding_box[0].y = min(verts[i].y, bounding_box[0].y);
		bounding_box[0].z = min(verts[i].z, bounding_box[0].z);

		//update max value
		bounding_box[1].x = max(verts[i].x, bounding_box[1].x);
		bounding_box[1].y = max(verts[i].y, bounding_box[1].y);
		bounding_box[1].z = max(verts[i].z, bounding_box[1].z);

		//update the  x min and max
		if (verts[i].x < xmin){
			xmin = verts[i].x;
			Pxmin = i;
		}
		else if (verts[i].x > xmax){
			xmax = verts[i].x;
			Pxmax = i;
		}
		//update the y min and max
		if (verts[i].y < ymin){
			ymin = verts[i].y;
			Pymin = i;
		}
		else if (verts[i].y > ymax){
			ymax = verts[i].y;
			Pymax = i;
		}
		//update the z min and max
		if (verts[i].z < zmin){
			zmin = verts[i].z;
			Pzmin = i;
		}
		else if (verts[i].z > zmax){
			zmax = verts[i].z;
			Pzmax = i;
		}
	}

	//calculate the bounding sphere
	float3 dVx = verts[Pxmax] - verts[Pxmin];
	float3 dVy = verts[Pymax] - verts[Pymin];
	float3 dVz = verts[Pzmax] - verts[Pzmin];
	float dx2 = norm2(dVx);
	float dy2 = norm2(dVy);
	float dz2 = norm2(dVz);

	float3 center;
	float  radius2;
	float  radius;

	if (dx2 >= dy2 && dx2 >= dz2) {					// x direction is largest extent  
		center = verts[Pxmin] + (dVx / 2.0);	// Center = midpoint of extremes  
		radius2 = norm2(verts[Pxmax] - center);// radius squared  
	}
	else if (dy2 >= dx2  && dy2 >= dz2){				// y direction is largest extent  
		center = verts[Pymin] + (dVy / 2.0);	// Center = midpoint of extremes  
		radius2 = norm2(verts[Pymax] - center);// radius squared  
	}
	else{
		center = verts[Pzmin] + (dVz / 2.0);	// Center = midpoint of extremes  
		radius2 = norm2(verts[Pzmax] - center);// radius squared  	
	}

	radius = sqrt(radius2);

	// now check that all points V[i] are in the ball  
	// and if not, expand the ball just enough to include them  
	float3 dV;
	float dist2, dist;
	for (unsigned int i = 0; i<verts.size(); i++)
	{
		dV = verts[i] - center;
		dist2 = norm2(dV);
		if (dist2 <= radius2) // V[i] is inside the ball already  
			continue;

		// V[i] not in ball, so expand ball to include it  
		dist = sqrt(dist2);
		radius = (radius + dist) / 2.0;         // enlarge radius just enough  
		radius2 = radius * radius;
		center = center + ((dist - radius) / dist) * dV;   // shift Center toward V[i]  

	}

	bounding_sphere_c = center;
	bounding_sphere_r = radius;
/*
	cout << "----------obj file loaded-------------" << endl;
	cout << "number of faces: " << mesh.faces.size() << endl;
	cout << "number of vt: " << mesh.vt.size() << endl;
	cout << "number of vertices: " << verts.size() << endl << endl;
	cout << "obj bounding box: min:("
		<< mesh.bounding_box[0].x << "," << mesh.bounding_box[0].y << "," << mesh.bounding_box[0].z << ") max:("
		<< mesh.bounding_box[1].x << "," << mesh.bounding_box[1].y << "," << mesh.bounding_box[1].z << ")" << endl
		<< "obj bounding sphere center:" << mesh.bounding_sphere_c.x << "," << mesh.bounding_sphere_c.y << "," << mesh.bounding_sphere_c.z << endl
		<< "obj bounding sphere radius:" << mesh.bounding_sphere_r << endl;
*/		
}