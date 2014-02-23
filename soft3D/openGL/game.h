
#ifndef GAME_H_2012624
#define  GAME_H_2012624
 

#include "stdafx.h"
#include "..\soft3D\pipeLine.h"
 

struct VertexA//位置+颜色
{
	union
	{
		struct
		{
			float x,y,z,w;//
			float r,g,b,a;
		};
		float v[8];

	};
 
	VertexA(float _x,float _y,float _z,float _r,float _g,float _b,float _a)
	{
		x=_x;y=_y;z=_z;r=_r;g=_g;b=_b;a=_a;
		w=1.0f;
	}
	VertexA()
	{
		x=y=z=w=r=g=b=a=1.0f;
	}
};
struct VertexB//位置+纹理
{
	float x,y,z,w;
	float u,v;
};
struct VertexC//位置+纹理+向量
{
	float x,y,z,w;
	float u,v;
	float nx,ny,nz;
};

class Game
{
public:
	Game(S3D::Render*);
	void update();
	
private:
	Game(){}
	S3D::Render* m_render;
	VertexA m_verList[4];
	VertexA m_triList[3];
};



#endif