
 
#include "stdafx.h"
#include "game.h"



Game::Game(S3D::Render* p)
:m_render(p)
{
	p->SetFvf((S3D::S3DFVF)(S3D::FVF_XYZ|S3D::FVF_COLOR));
	S3D::Matrix matWorld;
	S3D::Matrix matView;
	S3D::Matrix matProj;
	S3D::Vector3 pos(0,0,-5);
	S3D::Vector3 lookat(0,0,0);
	S3D::Vector3 up(0,1.0f,0);
	S3D::MatrixLookAtLH(&matView,&pos,&lookat,&up);
	S3D::MatrixPerspectiveFovLH(&matProj,RADIAN(90),1,1,100);
	S3D::MatrixIdentity(&matWorld);
	p->SetTransform(S3D::TS_WORLD,&matWorld);
	p->SetTransform(S3D::TS_VIEW,&matView);
	p->SetTransform(S3D::TS_PROJECION,&matProj);
	m_verList[0]=VertexA(0,5.0f,0,1,0,1,1);
	m_verList[1]=VertexA(0.0f,0,-1.0,0,1,0,1);
	m_verList[2]=VertexA(2.5f,0,0,0,0,1,1);
	m_verList[3]=VertexA(0,-4.0f,0,1,1,1,1);
	
	//初始化三角形顶点，测试用
	m_triList[0]=VertexA(-2.0,0,0,1,0,0,1);
	m_triList[1]=VertexA(2.0,0,0,1,0,0,1);
	m_triList[2]=VertexA(0.0,-2.0,0,1,0,0,1);
	//
	printf("%d\n",sizeof(VertexA));
	
	
	D3DXVECTOR4 dv0(0,2.5f,1,1);
	D3DXVECTOR4 dv1(0,2.5f,2,1);
	D3DXVECTOR4 dv2(0,2.5f,3,99);
	D3DXMATRIX matW,matV,matP;
	D3DXVECTOR3 pos1(0,0,-5);
	D3DXVECTOR3 lookat1(0,0,0);
	D3DXVECTOR3 up1(0,1.0f,0);
	D3DXMatrixIdentity(&matW);
	D3DXMatrixLookAtLH(&matV,&pos1,&lookat1,&up1);
	D3DXMatrixPerspectiveFovLH(&matP,RADIAN(90),1,1,100);
	S3D::print(&matWorld);printf("\n");
	S3D::print(&matView);printf("\n");
	S3D::print(&matProj);printf("\n");
	S3D::print(&matW);printf("\n");
	S3D::print(&matV);printf("\n");
	S3D::print(&matP);printf("\n");
	S3D::Vector v11(0,2.5f,1,1);
	S3D::VectorTransform(&v11,&v11,&matWorld);
	S3D::VectorTransform(&v11,&v11,&matView);
	S3D::VectorTransform(&v11,&v11,&matProj);
	S3D::print(&v11);

	D3DXVec4Transform(&dv0,&dv0,&matW);
	D3DXVec4Transform(&dv0,&dv0,&matV);
	D3DXVec4Transform(&dv0,&dv0,&matP);
	S3D::print(&dv0);

// 	D3DXVec4Transform(&dv1,&dv1,&matW);
// 	D3DXVec4Transform(&dv1,&dv1,&matV);
// 	D3DXVec4Transform(&dv1,&dv1,&matP);
// 	S3D::print(&dv1);
// 
// 	D3DXVec4Transform(&dv2,&dv2,&matW);
// 	D3DXVec4Transform(&dv2,&dv2,&matV);
// 	D3DXVec4Transform(&dv2,&dv2,&matP);
// 	S3D::print(&dv2);

	
	
	
}
void Game::update()
{
	m_render->Clear(0xffffff00,1.0f);
	m_render->BeginDraw();
	 
	//test
// 	int k=(rand()%5)*10;
// 	for (int i=0;i<5;i++)
// 	{
// 		for (int j=0;j<100;j++)
// 		{
// 			m_render->DrawPixel(i+k,j+k,S3D::MakeColor(0x00,0xff,0x00,60));
// 		}
// 	}
	
// 	m_render->DrawPrimitiveUP(S3D::PT_POINTLIST,m_verList,0,3,sizeof(VertexA));
 	m_render->DrawPrimitiveUP(S3D::PT_LINELIST,m_verList,0,4,sizeof(VertexA));
	m_render->DrawPrimitiveUP(S3D::PT_TRIANGLELIST,m_triList,0,3,sizeof(VertexA));
	m_render->EndDraw();
}