// 3D Graphics Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "olcConsoleGameEngine.h"
using namespace std;


//Constructs 3 floating point intervals used to construct our triangles
struct vec3d
{
	float x, y, z;
};


//A triangle that containes 3 vertices.
struct triangle
{
	vec3d p[3];
};

//Represents the object, groups together triangles
struct mesh
{
	vector <triangle> tris;

};

struct mat4x4
{
	float m[4][4] = { 0 };

};


//Sub-class of the ConsoleGameEngine
class olcEngine3D : public olcConsoleGameEngine
{
public:
	olcEngine3D()
	{
		m_sAppName = L"3D Demo";
	}
	// Adding meshes to our main class
private: 
	mesh meshF;
	mesh meshU;
	mesh meshC;
	mesh meshK;
	mat4x4 matProj;

	float fTheta;

	void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m)
	{
		o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.x /= w; o.y /= w, o.z /= w;
		}
	}

public:
	bool OnUserCreate() override
	{	//POPULATING MESHES
		meshF.tris = {


			//Main Pillar Bottom
			{0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 2.0f,   2.0f, 0.0f, 2.0f},
			{0.0f, 0.0f, 0.0f,   2.0f, 0.0f, 2.0f,   2.0f, 0.0f, 0.0f},

			//MAIN PILLAR EAST
			{2.0f, 0.0f, 0.0f ,  2.0f, 10.0f, 0.0f,   2.0f, 10.0f, 2.0f},
			{2.0f, 0.0f, 0.0f,   2.0f, 10.0f, 2.0f ,  2.0f, 0.0f, 2.0f},

			//MAIN PILLAR NORTH
			{2.0f, 0.0f, 2.0f,   2.0f, 10.0f, 2.0f,   0.0f, 10.0f, 2.0f},
			{2.0f, 0.0f, 2.0f,   0.0f, 10.0f, 2.0f,   0.0f, 0.0f, 2.0f},

			//MAIN PILLAR WEST
			{0.0f, 0.0f, 2.0f,   0.0f, 10.0f, 2.0f,   0.0f, 10.0f, 0.0f},
			{0.0f, 0.0f, 2.0f,   0.0f, 10.0f, 0.0f,   0.0f, 0.0f, 0.0f},

			//MAIN PILLAR TOP
			{0.0f, 10.0f, 0.0f,   0.0f, 10.0f, 2.0f,   2.0f, 10.0f, 2.0f},
			{0.0f, 10.0f, 0.0f,   2.0f, 10.0f, 2.0f,   2.0f, 10.0f, 0.0f},

			//MAIN PILLAR SOUTH
			{2.0f, 0.0f, 2.0f,   0.0f, 0.0f, 2.0f,    0.0f, 0.0f, 0.0f},
			{2.0f, 0.0f, 2.0f,   0.0f, 0.0f, 0.0f,    2.0f, 0.0f, 0.0f},




			//TOP LINE BOTTOM
			{6.0f, 2.0f, 0.0f,   0.0f, 2.0f, 0.0f,    0.0f, 2.0f, 2.0f},
			{6.0f, 2.0f, 0.0f,   0.0f, 2.0f, 2.0f,    6.0f, 2.0f, 2.0f},

			//TOP LINE EAST
			{6.0f, 2.0f, 2.0f,   6.0f, 2.0f, 0.0f,   6.0f, 0.0f, 0.0f},
			{6.0f, 2.0f, 2.0f,   6.0f, 0.0f, 0.0f,   6.0f, 0.0f, 2.0f},

			//TOP LINE  NORTH
			{6.0f, 0.0f, 2.0f,  6.0f, 2.0f, 2.0f,    0.0f, 2.0f, 2.0f},
			{6.0f, 0.0f, 2.0f,  0.0f, 2.0f, 2.0f,    0.0f, 0.0f, 2.0f},

			//TOP LINE WEST
			{0.0f, 0.0f, 2.0f,  0.0f, 2.0f, 2.0f,    0.0f, 2.0f, 0.0f},
			{0.0f, 0.0f, 2.0f,  0.0f, 2.0f, 0.0f,    0.0f, 0.0f, 0.0f},

			//TOP LINE TOP
			{0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 2.0f,    6.0f, 0.0f, 2.0f},
			{0.0f, 0.0f, 0.0f,  6.0f, 0.0f, 2.0f,    6.0f, 0.0f, 0.0f},

			//TOP LINE SOUTH
			{6.0f, 0.0f, 0.0f,  6.0f, 2.0f, 0.0f,  0.0f, 2.0f, 0.0f},
			{6.0f, 0.0f, 0.0f,  0.0f, 2.0f, 0.0f,  0.0f, 0.0f, 0.0f},




			//BOTTOM LINE TOP
			{4.0f, 4.0f, 0.0f,   0.0f, 4.0f, 0.0f,  0.0f, 4.0f, 2.0f},
			{4.0f, 4.0f, 0.0f,   0.0f, 4.0f, 2.0f,  4.0f, 4.0f, 2.0f},

			//BOTTOM LINE EAST
			{4.0f, 4.0f, 2.0f,   4.0f, 4.0f, 0.0f,  4.0f, 6.0f, 0.0f},
			{4.0f, 4.0f, 2.0f,   4.0f, 6.0f, 0.0f,  4.0f, 6.0f, 2.0f},


			//BOTTOM LINE NORTH
			{4.0f, 6.0f, 2.0f,   4.0f, 4.0f, 2.0f,   0.0f, 4.0f, 2.0f},
			{4.0f, 6.0f, 2.0f,   0.0f, 4.0f, 2.0f,   0.0f, 6.0f, 2.0f},

			//BOTTOM LINE WEST
			{0.0f, 6.0f, 2.0f,   0.0f, 6.0f, 0.0f,   0.0f, 4.0f, 0.0f},
			{0.0f, 6.0f, 2.0f,   0.0f, 4.0f, 0.0f,   0.0f, 4.0f, 2.0f},

			//BOTTOM LINE BOTTOM
			{0.0f, 6.0f, 2.0f,   4.0f, 6.0f, 2.0f,   4.0f, 6.0f, 0.0f},
			{0.0f, 6.0f, 2.0f,   4.0f, 6.0f, 0.0f,   0.0f, 6.0f, 0.0f},

			//BOTTOM LINE SOUTH
			{0.0f, 6.0f, 0.0f,   0.0f, 4.0f, 0.0f,   4.0f, 4.0f, 0.0f},
			{0.0f, 6.0f, 0.0f,   4.0f, 4.0f, 0.0f,   4.0f, 6.0f, 0.0f},
		

		};

		meshU.tris = {
			// LEFT PILLAR TOP
			{0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 2.0f,   2.0f, 0.0f, 2.0f},
			{0.0f, 0.0f, 0.0f,   2.0f, 0.0f, 2.0f,   2.0f, 0.0f, 0.0f},

			//LEFT PILLAR EAST 
			{2.0f, 0.0f, 0.0f,   2.0f, 0.0f, 2.0f,   2.0f, 10.0f, 2.0f},
			{2.0f, 0.0f, 0.0f,   2.0f, 10.0f, 2.0f,  2.0f, 10.0f, 0.0f},

			//LEFT PILLAR SOUTH
			{2.0f, 10.0f, 0.0f,   0.0f, 10.0f, 0.0f,  0.0f, 0.0f, 0.0f},
			{2.0f, 10.0f, 0.0f,   0.0f, 0.0f, 0.0f,   2.0f, 0.0f, 0.0f},

			//LEFT PILLAR WEST
			{2.0f, 0.0f, 0.0f,   2.0f, 0.0f, 2.0f,    2.0f, 10.0f, 2.0f},
			{2.0f, 0.0f, 0.0f,   2.0f, 10.0f, 2.0f,   2.0f, 10.0f, 0.0f},


			//LEFT PILLAR BOTTOM
			{2.0f, 10.0f, 0.0f,  0.0f, 10.0f, 0.0f,   0.0f, 10.0f, 2.0f},
			{2.0f, 10.0f, 0.0f,  0.0f, 10.0f, 2.0f,   2.0f, 10.0f, 2.0f},


			//LEFT PILLAR NORTH
			{2.0f, 10.0f, 2.0f,  0.0f, 10.0f, 2.0f,  0.0f, 0.0f, 2.0f},
			{2.0f, 10.0f, 2.0f,  0.0f, 0.0f, 2.0f,   2.0f, 0.0f, 2.0f},







			//BOTTOM LINE TOP
			{2.0f, 8.0f, 0.0f,   2.0f, 8.0f, 2.0f,    8.0f, 8.0f, 2.0f},
			{2.0f, 8.0f, 0.0f,   8.0f, 8.0f, 2.0f,    8.0f, 8.0f, 0.0f},


			//BOTTOM LINE EAST
			{8.0f, 8.0f, 0.0f,   8.0f, 8.0f, 2.0f,    8.0f, 10.0f, 2.0f},
			{8.0f, 8.0f, 0.0f,   8.0f, 10.0f, 2.0f,   8.0f, 10.0f, 0.0f},


			//BOTTOM LINE SOUTH
			{8.0f, 10.0f, 0.0f,  2.0f, 10.0f, 0.0f,   2.0f, 8.0f, 0.0f},
			{8.0f, 10.0f, 0.0f,  2.0f, 8.0f, 0.0f,    8.0f, 8.0f, 0.0f},


			//BOTTOM LINE WEST
			{8.0f, 8.0f, 0.0f,   8.0f, 8.0f, 2.0f,    8.0f, 10.0f, 2.0f},
			{8.0f, 8.0f, 0.0f,   8.0f, 10.0f, 2.0f,   8.0f, 10.0f, 0.0f},


			//BOTTOM LINE BOTTOM
			{8.0f, 10.0f, 0.0f,  2.0f, 10.0f, 0.0f,   2.0f, 10.0f, 2.0f},
			{8.0f, 10.0f, 0.0f,  2.0f, 10.0f, 2.0f,   8.0f, 10.0f, 2.0f,},


			//BOTTOM LINE NORTH
			{8.0f, 10.0f, 2.0f,  2.0f, 10.0f, 2.0f,   2.0f, 8.0f, 2.0f},
			{8.0f, 10.0f, 2.0f,  2.0f, 8.0f, 2.0f,    8.0f, 8.0f, 2.0f},







			// RIGHT PILLAR TOP
			{8.0f, 0.0f, 0.0f,   8.0f, 0.0f, 2.0f,    10.0f, 0.0f, 2.0f},
			{8.0f, 0.0f, 0.0f,   10.0f, 0.0f, 2.0f,   10.0f, 0.0f, 0.0f},

			//RIGHT PILLAR EAST 
			{10.0f, 0.0f, 0.0f,   10.0f, 0.0f, 2.0f,   10.0f, 10.0f, 2.0f},
			{10.0f, 0.0f, 0.0f,   10.0f, 10.0f, 2.0f,  10.0f, 10.0f, 0.0f},

			//RIGHT PILLAR SOUTH
			{10.0f, 10.0f, 0.0f,   8.0f, 10.0f, 0.0f,  8.0f, 0.0f, 0.0f},
			{10.0f, 10.0f, 0.0f,   8.0f, 0.0f, 0.0f,   10.0f, 0.0f, 0.0f},

			//RIGHT PILLAR WEST
			{10.0f, 0.0f, 0.0f,   10.0f, 0.0f, 2.0f,    10.0f, 10.0f, 2.0f},
			{10.0f, 0.0f, 0.0f,   10.0f, 10.0f, 2.0f,   10.0f, 10.0f, 0.0f},


			//RIGHT PILLAR BOTTOM
			{10.0f, 10.0f, 0.0f,  8.0f, 10.0f, 0.0f,   8.0f, 10.0f, 2.0f},
			{10.0f, 10.0f, 0.0f,  8.0f, 10.0f, 2.0f,   10.0f, 10.0f, 2.0f},


			//RIGHT PILLAR NORTH
			{10.0f, 10.0f, 2.0f,  8.0f, 10.0f, 2.0f,  8.0f, 0.0f, 2.0f},
			{10.0f, 10.0f, 2.0f,  8.0f, 0.0f, 2.0f,   10.0f, 0.0f, 2.0f},



		};


		meshC.tris =
		{

			//MAIN PILLAR TOP
			{0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 2.0f,  2.0f, 0.0f, 2.0f},
			{0.0f, 0.0f, 0.0f,  2.0f, 0.0f, 2.0f,  2.0f, 0.0f, 0.0f},


			//MAIN PILLAR EAST
			{2.0f, 0.0f, 0.0f,  2.0f, 10.0f, 0.0f,  2.0f, 10.0f, 2.0f},
			{2.0f, 0.0f, 0.0f,  2.0f, 10.0f, 2.0f,  2.0f, 0.0f, 2.0f,},


			//MAIN PILLAR SOUTH
			{2.0f, 0.0f, 2.0f,  0.0f, 0.0f, 2.0f,  0.0f, 10.0f, 2.0f},
			{2.0f, 0.0f, 2.0f,  0.0f, 10.0f, 2.0f, 2.0f, 10.0f, 2.0f},


			//MAIN PILLAR WEST
			{2.0f, 10.0f, 2.0f,  2.0f, 0.0f, 2.0f,   0.0f, 0.0f, 2.0f},
			{2.0f, 10.0f, 2.0f,   0.0f, 0.0f, 2.0f,  0.0f, 10.0f, 2.0f},


			//MAIN PILLAR BOTTOM
			{0.0f, 10.0f, 2.0f,  2.0f, 10.0f, 2.0f,   2.0f, 10.0f, 0.0f},
			{0.0f, 10.0f, 2.0f,   2.0f, 10.0f, 0.0f,  0.0f, 10.0f, 0.0f},


			//MAIN PILLAR NORTH
			{0.0f, 10.0f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 2.0f},
			{0.0f, 10.0f, 0.0f,   0.0f, 0.0f, 2.0f,  0.0f, 10.0f, 2.0f,},






			//BOTTOM LINE TOP
			{2.0f, 2.0f, 0.0f,    2.0f, 2.0f, 2.0f,   6.0f, 2.0f, 2.0f},
			{2.0f, 2.0f, 0.0f,    6.0f, 2.0f, 2.0f,   6.0f, 2.0f, 0.0f},


			//BOTTOM LINE WEST
			{6.0f, 2.0f, 0.0f,  6.0f, 2.0f, 2.0f,   6.0f, 0.0f, 2.0f},
			{6.0f, 2.0f, 0.0f,  6.0f, 0.0f, 2.0f,   6.0f, 0.0f, 0.0f},


			//BOTTOM LINE SOUTH
			{6.0f, 0.0f, 0.0f,   2.0f, 0.0f, 0.0f,   2.0f, 2.0f, 0.0f},
			{6.0f, 0.0f, 0.0f,   2.0f, 2.0f, 0.0f,   6.0f, 2.0f, 0.0f,},


			//BOTTOM LINE EAST
			{2.0f, 2.0f, 0.0f,  2.0f, 2.0f, 2.0f,    2.0f, 0.0f, 2.0f},
			{2.0f, 2.0f, 0.0f,  2.0f, 0.0f, 2.0f,    2.0f, 0.0f, 0.0f},


			//BOTTOM LINE BOTTOM
			{2.0f, 0.0f, 0.0f,   2.0f, 0.0f, 2.0f,    6.0f, 0.0f, 2.0f},
			{3.0f, 0.0f, 0.0f,   6.0f, 0.0f, 2.0f,    6.0f, 0.0f, 0.0f},

			//BOTTOM LINE NORTH
			{6.0f, 0.0f, 2.0f,   2.0f, 0.0f, 2.0f,    2.0f, 2.0f, 2.0f},
			{6.0f, 0.0f, 2.0f,   2.0f, 2.0f, 2.0f,    6.0f, 2.0f, 2.0f},









			//TOP LINE TOP
			{2.0f, 10.0f, 0.0f,    2.0f, 10.0f, 2.0f,   6.0f, 10.0f, 2.0f},
			{2.0f, 10.0f, 0.0f,    6.0f, 10.0f, 2.0f,   6.0f, 10.0f, 0.0f},


			//TOP LINE WEST
			{6.0f, 10.0f, 0.0f,  6.0f, 10.0f, 2.0f,   6.0f, 8.0f, 2.0f},
			{6.0f, 10.0f, 0.0f,  6.0f, 8.0f, 2.0f,   6.0f, 8.0f, 0.0f},


			//TOP LINE SOUTH
			{6.0f, 8.0f, 0.0f,   2.0f, 8.0f, 0.0f,   2.0f, 10.0f, 0.0f},
			{6.0f, 8.0f, 0.0f,   2.0f, 10.0f, 0.0f,   6.0f, 10.0f, 0.0f,},


			//TOP LINE EAST
			{2.0f, 10.0f, 0.0f,  2.0f, 10.0f, 2.0f,    2.0f, 8.0f, 2.0f},
			{2.0f, 10.0f, 0.0f,  2.0f, 8.0f, 2.0f,    2.0f, 8.0f, 0.0f},


			//TOP LINE BOTTOM
			{2.0f, 8.0f, 0.0f,   2.0f, 8.0f, 2.0f,    6.0f, 8.0f, 2.0f},
			{3.0f, 8.0f, 0.0f,   6.0f, 8.0f, 2.0f,    6.0f, 8.0f, 0.0f},

			//TOP LINE NORTH
			{6.0f, 8.0f, 2.0f,   2.0f, 8.0f, 2.0f,    2.0f, 10.0f, 2.0f},
			{6.0f, 8.0f, 2.0f,   2.0f, 10.0f, 2.0f,    6.0f, 10.0f, 2.0f},







		};




		meshK.tris =
		{
			//MAIN PILLAR TOP
			{0.0f, 0.0f, 0.0f,     0.0f, 0.0f, 2.0f,    2.0f, 0.0f, 2.0f},
			{0.0f, 0.0f, 0.0f,      2.0f, 0.0f, 2.0f,    2.0f, 0.0f, 0.0f},

			// MAIN PILLAR BOTTOM
			{0.0f, 10.0f, 0.0f,   0.0f, 10.0f, 2.0f,    2.0f, 10.0f, 2.0f},
			{0.0f, 10.0f, 0.0f,    2.0f, 10.0f, 2.0f,   2.0f, 10.0f, 0.0f},

			// MAIN PILLAR EAST
			{2.0f, 10.0f, 0.0f,    2.0f, 0.0f, 0.0f,    2.0f, 0.0f, 2.0f},
			{2.0f, 10.0f, 0.0f,    2.0f, 0.0f, 2.0f,    2.0f, 0.0f, 0.0f},

			// MAIN PILLAR SOUTH
			{0.0f, 0.0f, 0.0f,    0.0f, 10.0f, 0.0f,    2.0f, 10.0f, 0.0f},
			{0.0f, 0.0f, 0.0f,    2.0f, 10.0f,  0.0f,   2.0f, 0.0f, 0.0f},

			//MAIN PILLAR NORTH
			{0.0f, 0.0f, 2.0f,    0.0f, 10.0f, 2.0f,    2.0f, 10.0f, 2.0f},
			{0.0f, 0.0f, 2.0f,    2.0f, 10.0f, 2.0f,    2.0f, 0.0f, 2.0f},

			//MAIN PILLAR WEST
			{0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 2.0f,    0.0f, 10.0f, 2.0f},
			{0.0f, 0.0f, 0.0f,    0.0f, 10.0f, 2.0f,   0.0f, 10.0f, 2.0f},




			//SECOND PILLAR TOP
			{2.0f, 2.0f, 0.0f,    2.0f, 2.0f, 2.0f,    4.0f, 2.0f, 2.0f},
			{2.0f, 2.0f, 0.0f,    4.0f, 2.0f, 2.0f,    4.0f, 2.0f, 0.0f},

			//SECOND PILLAR BOTTOM
			{2.0f, 8.0f, 0.0f,    2.0f, 8.0f, 2.0f,    4.0f, 8.0f, 2.0f},
			{2.0f, 8.0f, 0.0f,    4.0f, 8.0f, 2.0f,    4.0f, 8.0f, 0.0f},

			//SECOND PILLAR NORTH
			{2.0f, 2.0f, 2.0f,    2.0f, 8.0f, 2.0f,   4.0f, 8.0f, 2.0f},
			{2.0f, 2.0f, 2.0f,    4.0f, 8.0f, 2.0f,   2.0f, 8.0f, 2.0f,},


			//SECOND PILLAR SOUTH
			{2.0f, 2.0f, 0.0f,    4.0f, 2.0f, 0.0f,   4.0f, 8.0f, 0.0f},
			{2.0f, 2.0f, 0.0f,   4.0f, 8.0f, 0.0f,   2.0f, 8.0, 0.0f},


			//SECOND PILLAR EEEEEEEEEEEEEE
			{4.0f, 2.0f, 0.0f,    4.0f, 2.0f, 2.0f,   4.0f, 8.0f, 2.0f},
			{4.0f, 2.0f, 0.0f,    4.0f, 8.0f, 2.0f,   4.0f, 8.0f, 0.0f},


			//SECOND PILLAR WEST
			{2.0f, 8.0f, 0.0f,   2.0f, 8.0f, 2.0f,    2.0f, 2.0f, 2.0f},
			{2.0f, 8.0f, 0.0f,   2.0f, 2.0f, 2.0f,    2.0f, 2.0f, 0.0f},





			//TOP SQUARE TOP
			{4.0f, 0.0f, 0.0f,   4.0f, 0.0f, 2.0f,    6.0f, 0.0f, 2.0f},
			{4.0f, 0.0f, 0.0f,   6.0f, 0.0f, 2.0f,    6.0f, 0.0f, 0.0f},


			//TOP SQUARE BOTTOM
			{4.0f, 2.0f, 0.0f,   4.0f, 2.0f, 2.0f,   6.0f, 2.0f, 2.0f},
			{4.0f, 2.0f, 0.0f,   6.0f, 2.0f, 2.0f,   6.0f, 2.0f, 0.0f},


			//TOP SQUARE NORTH
			{4.0f, 0.0f, 2.0f,   4.0f, 2.0f, 2.0f,   6.0f, 2.0f, 2.0f},
			{4.0f, 0.0f, 2.0f,   6.0f, 2.0f, 2.0f,   6.0f, 0.0f, 2.0f},



			//TOP SQUARE SOUTH
			{4.0f, 0.0f, 0.0f,   6.0f, 0.0f, 0.0f,   6.0f, 2.0f, 0.0f},
			{4.0f, 0.0f, 0.0f,   6.0f, 2.0f, 0.0f,   4.0f, 2.0f, 0.0f},


			//TOP SQUARE EAST
			{6.0f, 0.0f, 0.0f,   6.0f, 0.0f, 2.0f,   6.0f, 2.0f, 2.0f},
			{6.0f, 0.0f, 0.0f,   6.0f, 2.0f, 2.0f,   6.0f, 2.0f, 0.0f},


			//TOP SQUARE WEST
			{4.0f, 0.0f, 0.0f,   4.0f, 2.0f, 0.0f,   4.0f, 2.0f, 2.0f},
			{4.0f, 0.0f, 0.0f,   4.0f, 2.0f, 2.0f,   4.0f, 2.0f, 0.0f},








			//BOTTOM SQUARE TOP
			{4.0f, 8.0f, 0.0f,   4.0f, 8.0f, 2.0f,    6.0f, 8.0f, 2.0f},
			{4.0f, 8.0f, 0.0f,   6.0f, 8.0f, 2.0f,    6.0f, 8.0f, 0.0f},


			//BOTTOM SQUARE BOTTOM
			{4.0f, 10.0f, 0.0f,   4.0f, 10.0f, 2.0f,   6.0f, 10.0f, 2.0f},
			{4.0f, 10.0f, 0.0f,   6.0f, 10.0f, 2.0f,   6.0f, 10.0f, 0.0f},


			//BOTTOM SQUARE NORTH
			{4.0f, 8.0f, 2.0f,   4.0f, 10.0f, 2.0f,   6.0f, 10.0f, 2.0f},
			{4.0f, 8.0f, 2.0f,   6.0f, 10.0f, 2.0f,   6.0f, 8.0f, 2.0f},



			//BOTTOM SQUARE SOUTH
			{4.0f, 8.0f, 0.0f,   6.0f, 8.0f, 0.0f,   6.0f, 10.0f, 0.0f},
			{4.0f, 8.0f, 0.0f,   6.0f, 10.0f, 0.0f,   4.0f, 10.0f, 0.0f},


			//BOTTOM SQUARE EAST
			{6.0f, 8.0f, 0.0f,   6.0f, 8.0f, 2.0f,   6.0f, 10.0f, 2.0f},
			{6.0f, 8.0f, 0.0f,   6.0f, 10.0f, 2.0f,   6.0f, 10.0f, 0.0f},


			//BOTTOM SQUARE WEST
			{4.0f, 8.0f, 0.0f,   4.0f, 10.0f, 0.0f,   4.0f, 10.0f, 2.0f},
			{4.0f, 8.0f, 0.0f,   4.0f, 10.0f, 2.0f,   4.0f, 10.0f, 0.0f},











		};




		//Projection Matrix
		float fNear = 0.1f;
		float fFar = 1000.0f;
		float fFov = 90.0f;
		float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
		float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);


		matProj.m[0][0] = fAspectRatio * fFovRad;
		matProj.m[1][1] = fFovRad;
		matProj.m[2][2] = fFar / (fFar - fNear);
		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matProj.m[2][3] = 1.0f;
		matProj.m[3][3] = 0.0f;




		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//Clear Screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		// Set up rotation matrices
		mat4x4 matRotZ, matRotX;
		fTheta += 1.0f * fElapsedTime;

		// Rotation Z
		matRotZ.m[0][0] = cosf(fTheta);
		matRotZ.m[0][1] = sinf(fTheta);
		matRotZ.m[1][0] = -sinf(fTheta);
		matRotZ.m[1][1] = cosf(fTheta);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;

		// Rotation X
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(fTheta * 0.5f);
		matRotX.m[1][2] = sinf(fTheta * 0.5f);
		matRotX.m[2][1] = -sinf(fTheta * 0.5f);
		matRotX.m[2][2] = cosf(fTheta * 0.5f);
		matRotX.m[3][3] = 1;
//Draw Triangles


		for (auto tri : meshK.tris)
		{
			triangle triProjected, triTranslated;

			//Offset into screen 
			triTranslated = tri;
			triTranslated.p[0].z = tri.p[0].z + 18.0f;
			triTranslated.p[1].z = tri.p[1].z + 18.0f;
			triTranslated.p[2].z = tri.p[2].z + 18.0f;


			triTranslated.p[0].x = tri.p[0].x + 11.0f;
			triTranslated.p[1].x = tri.p[1].x + 11.0f;
			triTranslated.p[2].x = tri.p[2].x + 11.0f;
		

			triTranslated.p[0].y = tri.p[0].y - 16.0f;
			triTranslated.p[1].y = tri.p[1].y - 16.0f;
			triTranslated.p[2].y = tri.p[2].y - 16.0f;

			//Project triangles from 3D to 2D
			MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);


			//scale into view
			triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
			triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[0].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[1].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[2].y *= 0.5f * (float)ScreenHeight();


			DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y,
				PIXEL_SOLID, FG_WHITE);



		}

		for (auto tri : meshC.tris) 
		{
			triangle triProjected, triTranslated;

			//Offset into screen 
			triTranslated = tri;
			triTranslated.p[0].z = tri.p[0].z + 18.0f;
			triTranslated.p[1].z = tri.p[1].z + 18.0f;
			triTranslated.p[2].z = tri.p[2].z + 18.0f;
			triTranslated.p[0].x = tri.p[0].x + 3.0f;
			triTranslated.p[1].x = tri.p[1].x + 3.0f;
			triTranslated.p[2].x = tri.p[2].x + 3.0f;
			triTranslated.p[0].y = tri.p[0].y - 16.0f;
			triTranslated.p[1].y = tri.p[1].y - 16.0f;
			triTranslated.p[2].y = tri.p[2].y - 16.0f;

			//Project triangles from 3D to 2D
			MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);


			//scale into view
			triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
			triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[0].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[1].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[2].y *= 0.5f * (float)ScreenHeight();


			DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y,
				PIXEL_SOLID, FG_WHITE);



		}

		for (auto tri : meshU.tris)
		{
			triangle triProjected, triTranslated;


			//Offset into screen 
			triTranslated = tri;
			triTranslated.p[0].z = tri.p[0].z + 18.0f;
			triTranslated.p[1].z = tri.p[1].z + 18.0f;
			triTranslated.p[2].z = tri.p[2].z + 18.0f;
			triTranslated.p[0].x = tri.p[0].x - 8.0f;
			triTranslated.p[1].x = tri.p[1].x - 8.0f;
			triTranslated.p[2].x = tri.p[2].x - 8.0f;
			triTranslated.p[0].y = tri.p[0].y - 16.0f;
			triTranslated.p[1].y = tri.p[1].y - 16.0f;
			triTranslated.p[2].y = tri.p[2].y - 16.0f;


			//Project triangles from 3D to 2D
			MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);


			//scale into view
			triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
			triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[0].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[1].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[2].y *= 0.5f * (float)ScreenHeight();


			DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y,
				PIXEL_SOLID, FG_WHITE);


		};



		for (auto tri : meshF.tris)
		{
			triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

			//// Rotate in Z-Axis
			MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
			MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
			MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

			//// Rotate in X-Axis
			MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

			// Offset into the screen
			triTranslated = tri;
			triTranslated.p[0].z = tri.p[0].z + 18.0f;
			triTranslated.p[1].z = tri.p[1].z + 18.0f;
			triTranslated.p[2].z = tri.p[2].z + 18.0f;

			triTranslated.p[0].x = tri.p[0].x - 15.0f;
			triTranslated.p[1].x = tri.p[1].x - 15.0f;
			triTranslated.p[2].x = tri.p[2].x - 15.0f;

			triTranslated.p[0].y = tri.p[0].y - 16.0f;
			triTranslated.p[1].y = tri.p[1].y - 16.0f;
			triTranslated.p[2].y = tri.p[2].y - 16.0f;

			// Project triangles from 3D --> 2D
			MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

			// Scale into view
			triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
			triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
			triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
			triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[0].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[1].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[2].y *= 0.5f * (float)ScreenHeight();

			// Rasterize triangle
			DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y,
				PIXEL_SOLID, FG_WHITE);

		}
		return true;
	}

};

int main()
{
	olcEngine3D demo;
	if (demo.ConstructConsole(256, 240, 2, 2))
		demo.Start();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
