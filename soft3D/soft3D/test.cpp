#include "test.h"

void testMatrixInverse()
{
	printf("-----------Matrix类求逆测试\n");
	float fArr1[]={1,2,2,4  ,6,6,7,8   ,9,10,11,12  ,11,14,15,16};
	S3D::Matrix sMat(fArr1);
	S3D::Matrix sMat1;
	S3D::Matrix sMat2;

	S3D::print(&sMat);
	D3DXMATRIX dMat(fArr1);
	D3DXMATRIX dMat2;
	D3DXMATRIX dMat3;
	
	S3D::print(&dMat);
	//行列式测试
	float fDet=S3D::MatrixDeterminant(&sMat);
	printf("%f\n",fDet);
	float fDet1=D3DXMatrixDeterminant(&dMat);
	printf("%f\n",fDet1);
	//逆矩阵
	S3D::MatrixInverse(&sMat1,&sMat);
	S3D::print(&sMat1);
	printf("\n");
	sMat2=sMat*sMat1;
	S3D::print(&sMat2);
	printf("\n");
	D3DXMatrixInverse(&dMat2,NULL,&dMat);
	S3D::print(&dMat2);
	dMat3=dMat*dMat2;
	S3D::print(&dMat3);



}
void testMatrixTranspose()
{
	printf("-----------Matrix类转置测试\n");
	float fArr1[]={1,2,2,4  ,6,6,7,8   ,9,10,11,12  ,11,14,15,16};
	S3D::Matrix sMat(fArr1);
	S3D::Matrix sMat1;
	S3D::print(&sMat);
	printf("转置后\n");
	S3D::MatrixTranspose(&sMat1,&sMat);
	S3D::print(&sMat1);
}
void testTransformScale()
{
	printf("-----------transformScale测试\n");
	S3D::Matrix mat1;
	S3D::MatrixScale(&mat1,1,2,3);
		
	S3D::Vector3 u(1,0,0);
	S3D::Vector3 v(0,1,0);
	S3D::Vector3 w(0,0,1);
	S3D::Matrix3x3  mat2(&u,&v,&w);
	S3D::Matrix mat3;
	S3D::MatrixScaleAxis(&mat3,&mat2,1,2,3);
	S3D::print(&mat1);
	S3D::print(&mat3);
	printf("\n");

	D3DXMATRIX mat4;
	D3DXMatrixScaling(&mat4,1,2,3);
	S3D::print(&mat4);
}
void testTransformRotation()
{
	printf("-----------transformRotation测试\n");

	S3D::Matrix  mat1;
	S3D::Matrix  mat2;
	S3D::Matrix  mat3;
	S3D::MatrixRotationX(&mat1,1);
	S3D::MatrixRotationY(&mat2,2);
	S3D::MatrixRotationZ(&mat3,3);

	D3DXMATRIX m1;
	D3DXMATRIX m2;
	D3DXMATRIX m3;
	D3DXMatrixRotationX(&m1,1);
	D3DXMatrixRotationY(&m2,2);
	D3DXMatrixRotationZ(&m3,3);
	S3D::print(&mat1);
	printf("\n");
	S3D::print(&mat2);
	printf("\n");
	S3D::print(&mat3);
	printf("\n");
	S3D::print(&m1);
	printf("\n");
	S3D::print(&m2);
	printf("\n");
	S3D::print(&m3);
	printf("\n");
	printf("围绕指定轴旋转\n");


	S3D::Matrix mat5;
	D3DXMATRIX m5;
	S3D::Vector3  v1(1,2,3);
	D3DXVECTOR3  v2(1,2,3);
	S3D::MatrixRotationAxis(&mat5,&v1,1);
	D3DXMatrixRotationAxis(&m5,&v2,1);
	S3D::print(&mat5);
	printf("\n");
	S3D::print(&m5);
	printf("\n");

}
void testTransformTranslation()
{
	S3D::Matrix mat1;
	D3DXMATRIX m1;
	S3D::MatrixTranslation(&mat1,1,2,3);
	D3DXMatrixTranslation(&m1,1,2,3);
	S3D::print(&mat1);
	printf("\n");
	S3D::print(&m1);

}
void testTransformView()
{
	S3D::Vector3 vPos(1,1,1);
	S3D::Vector3 vLookat(0,0,0);
	S3D::Vector3 vUp(0,1,0);
	S3D::Matrix mat1;
	S3D::MatrixLookAtLH(&mat1,&vPos,&vLookat,&vUp);
	S3D::print(&mat1);
	printf("\n");
	D3DXVECTOR3 vPos1(1,1,1);
	D3DXVECTOR3 vLookat1(0,0,0);
	D3DXVECTOR3 vUp1(0,1,0);
	D3DXMATRIX mat2;
	D3DXMatrixLookAtLH(&mat2,&vPos1,&vLookat1,&vUp1);
	S3D::print(&mat2);
}
void testLine()
{
	S3D::Vector3 v1(0,0,0);
	S3D::Vector3 v2(2,0,0);
	S3D::Vector3 v3(0,0,-1);
	S3D::Line line1(&v1,&v2,LINE_NORMAL);	
	float f1=S3D::LinePointDistance(&v3,&line1);
	printf("%f\n",f1);
	S3D::Vector3 v4(0,1,1);
	S3D::Vector3 v5(2,1,1);

	S3D::Line line2(&v4,&v5,LINE_NORMAL);	
	f1=S3D::LineLineDistance(&line1,&line2);
	printf("%f\n",f1);
}
void testPlane()
{
	S3D::Vector3  v1(1,0,0);
	S3D::Vector3 v2(0,1,0);
	S3D::Vector3 v3(0,0,1);
	S3D::Plane p1(&v1,&v2,&v3);
	S3D::print(&p1);

	S3D::Vector3 v4(1,1,1);
	S3D::Vector3 v5(1,0,0);
	S3D::Plane p2(&v4,&v5);
	S3D::print(&p2);

	S3D::Vector3 v6(0,0,0);
	printf("%f\n",S3D::PlanePointDistance(&p2,&v6));
	v4=S3D::Vector3(0.1f,0.1f,0.1f);
	S3D::Line l1(&v6,&v4,LINE_SEGMENT);
	S3D::Vector3 v7;
	
	if(S3D::PlaneLineIntersection(&v7,&p2,&l1,0))
	{
		printf("交点:");
		S3D::print(&v7);
	}else
	{
		printf("没有交点\n");
	}

}
void testProjection()
{
	S3D::Matrix m1;
	S3D::MatrixPerspectiveOffCenterLH(&m1,-10,100,-10,100,100,200);
	
	D3DXMATRIX m2;
	D3DXMatrixPerspectiveOffCenterLH(&m2,-10,100,-10,100,100,200);
	 
	S3D::print(&m1);
	printf("\n");
	S3D::print(&m2);
	
	S3D::MatrixPerspectiveFovLH(&m1,RADIAN(90),1,100,200);
	D3DXMatrixPerspectiveFovLH(&m2,RADIAN(90),1,100,200);
	printf("\n");
	S3D::print(&m1);
	printf("\n");
	S3D::print(&m2);
	
	S3D::MatrixOrthoOffCenterLH(&m1,-100,100,-100,100,100,2000);
	D3DXMatrixOrthoOffCenterLH(&m2,-100,100,-100,100,100,2000);
	printf("\n");
	S3D::print(&m1);
	printf("\n");
	S3D::print(&m2);
}

void testVector4()
{
	float res,res1;
	S3D::Vector vec1(1,1,1,1);
	D3DXVECTOR4 vecd1(1,1,1,1);
	D3DXVECTOR4 vecd3;
	printf("v v1\n");
	S3D::print(&vec1);
	S3D::print(&vecd1);
	printf("+\n");
	S3D::Vector vec2=vec1+vec1;
	printf("-\n");
	vec2=vec1-vec1;
	S3D::print(&vec2);
	res=vec1*vec1;
	printf("%f\n",res);
	res=S3D::VectorLength(&vec1);
	res1=D3DXVec4Length(&vecd1);
	printf("%f	%f\n",res,res1);
	
	vec1=S3D::Vector(1,2,3,4);
	float fArr1[]={1,2,2,4  ,6,6,7,8   ,9,10,11,12  ,11,14,15,16};
	S3D::Matrix mat1(fArr1);

	vecd1=D3DXVECTOR4(1,2,3,4);
	D3DXMATRIX mat2(fArr1);
	VectorTransform(&vec1,&vec1,&mat1);
	D3DXVec4Transform(&vecd1,&vecd1,&mat2);
	S3D::print(&mat1);
	S3D::print(&mat2);
	S3D::print(&vec1);
	S3D::print(&vecd1);

	printf("测试vec3的transform\n");
	S3D::Vector3 v3a(1,2,3);
	S3D::Vector3transform(&vec1,&v3a,&mat1);
	D3DXVECTOR3 v3da(1,2,3);
	D3DXVec3Transform(&vecd1,&v3da,&mat2);

	S3D::print(&vec1);
	S3D::print(&vecd1);

	
}

void testMath()
{
	printf("线性插值\n");
	float s=1.0f;
	float e=3.0f;
	float vp1=2.5f;
	float k=1.0f;
	S3D::LineInter(e,s,vp1,&k);
	printf("%f\n",k);
	printf("重心坐标\n");
	S3D::Vector3 v1(1,1,1);
	S3D::Vector3 v2(3,1,1);
	S3D::Vector3 v3(2,5,1);
	S3D::Vector3 vc(1,1,1);
	S3D::Vector3 coord;
	bool isT=isTriangle(&v1,&v2,&v3);
	if(isT)printf("是三角形\n");else printf("不是三角形\n");
	coord=S3D::GrivityCenterByXY(&v1,&v2,&v3,&vc);
	S3D::print(&coord);


}
