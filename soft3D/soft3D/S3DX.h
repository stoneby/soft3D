
/***************************
 *@brief 3D��ѧ��
 *��������ϵ  ��d3d��ͬ
 *row major  ��d3d��column major�෴  Ҳ����˵uvw���Űڣ�vec��4x1�����б任ʱ���������
 *
 ***************************/

#ifndef  S3DX_H_322
#define S3DX_H_322
#include <assert.h>
#include <math.h>
#include <Windows.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
#include "d3dx9.h"
#include "common.h"
 
#ifndef ASSERT
#define ASSERT(expr) _ASSERT(expr)
#endif


 
#define  START_S3D namespace S3D {
#define  END_S3D }

namespace S3D
{
#define  RADIAN(a)  ((a)/180.0f*3.1415927f)//�Ƕ�ת����
#define  S3DFAILED(a) (a!=0)
	struct Matrix;
	struct Vector;

	/**
	 *@brief 
	 *
	 */
	struct Vector3
	{
		float _x;
		float _y;
		float _z;
		Vector3();

		Vector3(float x,float y,float z);

		Vector3 operator+(const Vector3& v1)const;
		Vector3 operator-(const Vector3& v1)const;
		float operator*(const Vector3& v1)const;
		Vector3 operator*(float f)const ;
		Vector3 operator/(float f)const ;

		Vector3& operator+=(const Vector3& v1);
		Vector3& operator-=(const Vector3& v1);
		Vector3& operator*=(float f);
		Vector3& operator/=(float f);
		
	};
	
	
	Vector3* Vector3CrossProduct(Vector3* out,const Vector3* inL,const Vector3* inR);
	float Vector3DotProduct(const Vector3* inL,const Vector3* inR);
	float Vector3Length(const Vector3* pV);
	Vector3* Vector3Proj(Vector3* out,const Vector3* inL,const Vector3* inR);
	Vector3* Vector3Perp(Vector3* out,const Vector3* inL,const Vector3* inR);
	Vector3* Vector3Normalize(Vector3* pV);
	Vector3* Vector3Orthongonlize(Vector3* v1,Vector3* v2,Vector3* v3);//���룺�����޹ص�3��3ά���� �����������
	Vector* Vector3transform(Vector* vOut,const Vector3* vIn,const Matrix* matrix);
	Vector3* Vector3transformCoord(Vector3* vOut,const Vector3* vIn,const Matrix* matrix);
	struct Matrix3x3
	{
		union
		{
			struct
			{
				float _11,_12,_13;
				float _21,_22,_23;
				float _31,_32,_33;
			};
			float  m[9];
			float  m1[3][3];
			
		};
		Matrix3x3();
		Matrix3x3(float _1,float _2,float _3,float _4,float _5,float _6,float _7,float _8,float _9);
		Matrix3x3(const Vector3* _u,const Vector3*  _v, const Vector3* _w);
 		Matrix3x3 operator+(const Matrix3x3& mi);
 		Matrix3x3 operator-(const Matrix3x3& mi);
		Matrix3x3 operator*(const Matrix3x3& mi);
		Matrix3x3 operator*(float f);
		Matrix3x3 operator/(float f);


		Matrix3x3& operator+=(const Matrix3x3& mi);
		Matrix3x3& operator-=(const Matrix3x3& mi);
		Matrix3x3& operator*=(const Matrix3x3& mi);
		Matrix3x3& operator*=(float f);
		Matrix3x3& operator/=(float f);

	};
	
	Matrix3x3* Matrix3x3Inverse(Matrix3x3* mOut,Matrix3x3* mIn);
	/**
	 *@brief ��������ʽ
	 */
	float Matrix3x3Determinats(Matrix3x3* matrix);
	Matrix3x3* Matrix3x3Adjoint(Matrix3x3* mOut,Matrix3x3* mIn);//�������
	Matrix3x3* Matrix3x3Inverse(Matrix3x3* mOut,Matrix3x3* mIn);
	Matrix3x3* Matrix3x3Identity(Matrix3x3* mIn);
	Matrix3x3* Matrix3x3Transpose(Matrix3x3* mOut,Matrix3x3* mIn);

	struct Vector
	{
		float x,y,z,w;
		Vector(){x=y=z=0.0f;w=1.0f;}
		Vector(float _x,float _y,float _z,float _w){x=_x;y=_y;z=_z;w=_w;}

		Vector operator+(const Vector& v1)const;
		Vector operator-(const Vector& v1)const;
		float operator*(const Vector& v1)const;
		Vector operator*(float f)const ;
		Vector operator/(float f)const ;

		Vector& operator+=(const Vector& v1);
		Vector& operator-=(const Vector& v1);
		Vector& operator*=(float f);
		Vector& operator/=(float f);
	};
	
	Vector* VectorCrossProduct(Vector* out,const Vector* inL,const Vector* inR);//todo
	float VectorDotProduct(const Vector* inL,const Vector* inR);
	float VectorLength(const Vector* pV);
	Vector* VectorProj(Vector* out,const Vector* inL,const Vector* inR);//todo
	Vector* VectorPerp(Vector* out,const Vector* inL,const Vector* inR);//todo
	Vector* VectorNormalize(Vector* pV);
	Vector* VectorTransform(Vector* pOut,const Vector* pIn,const Matrix* mat);
	/**
	 *@brief 
	 *@todo δ���
	 */
	Vector* VectorOrthongonlize(Vector* v1,Vector* v2,Vector* v3);//���룺�����޹ص�3��3ά���� �����������




	struct Matrix
	{
		union
		{
			struct
			{
				float _11,_12,_13,_14;
				float _21,_22,_23,_24;
				float _31,_32,_33,_34;
				float _41,_42,_43,_44;
			};
			float m1[4][4];
			float m[16];

		};
		Matrix();
		Matrix(const Matrix3x3* mIn);
		Matrix(const float* fArr);//�������ʼ��
		Matrix(const Vector3* _u,const Vector3* _v,const Vector3* _w);

		Matrix operator+(const Matrix& m);
		Matrix operator-(const Matrix& m);
		Matrix operator*(const Matrix& mi);
		Matrix operator*(float f);
		
		Matrix& operator+=(const Matrix mi);
		Matrix& operator-=(const Matrix mi);
		Matrix& operator*=(const Matrix mi);
		Matrix& operator*=(float f);

	};
	float MatrixDeterminant(Matrix* matrix);
	Matrix* MatrixAdjoint(Matrix* mOut,Matrix* mIn);//�������
	Matrix* MatrixInverse(Matrix* mOut,Matrix* mIn);//�����
	Matrix* MatrixTranspose(Matrix* mOut,Matrix* mIn);//ת�þ���
	Matrix* MatrixIdentity(Matrix* mIn);
	
	//transform
	Matrix* MatrixScale(Matrix* mIn,float _x,float _y,float _z);
	Matrix* MatrixScaleAxis(Matrix* mIn,Matrix3x3* ,float _x,float _y,float _z);//���µ�3���������scale  �ƺ�ûʲô�ð�
	Matrix* MatrixRotationX(Matrix* mIn,float angel);//���ȣ���ʱ��Ϊ+ 
	Matrix* MatrixRotationY(Matrix* mIn,float angel);//���ȣ���ʱ��Ϊ+ 
	Matrix* MatrixRotationZ(Matrix* mIn,float angel);//���ȣ���ʱ��Ϊ+ 
	Matrix* MatrixRotationAxis(Matrix* mIn ,const Vector3* _v,float angel);
	Matrix* MatrixTranslation(Matrix* mIn,float _x,float _y,float _z);
	Matrix* MatrixLookAtLH(Matrix* mIn,const Vector3* pos,const Vector3* lookat,const Vector3* up);//pos�����λ�� lookat����ĵ� 
	Matrix* MatrixPerspectiveOffCenterLH(Matrix* mOut,float l,float r,float b,float t,float n,float f);//͸�Ӿ���lr=��������tb=�������� nf=Զ������������
	Matrix* MatrixPerspectiveFovLH(Matrix* mOut,float angel,float aspect,float n,float f);//�Ƕȣ��ݺ�ȣ������ã�Զ����
	Matrix* MatrixOrthoOffCenterLH(Matrix* mOut,float l,float r,float b,float t,float n,float f);//����ͶӰ
	Matrix* MatrixOrthoLH(Matrix* mOut,float w,float h,float zn,float zf);//
	//
	
#define  LINE_NORMAL 0
#define  LINE_RAY 1
#define  LINE_SEGMENT 2
	struct Line//ֱ�� ���� �����߶�
	{
		Vector3 pos;//��
		Vector3 dir;//����  normalized
		float t;
		int type;//LINE_
		
		Line(const Vector3* _pos1,const Vector3* _pos2,int _type);
	};
	float LinePointDistance(const Vector3* _pos,const Line* _line);//�㵽ֱ�߾���
	float LineLineDistance(const Line* _line1,const Line* _line2);//
	struct Plane//�棺 ������+ԭ�㵽��ľ��� ax+by+cz+d=0   N P  d=-N.P    normal����Ϊ���������  ��˽��Ϊ����ʾ�㴦�ڸ�������һ��
	{
		Vector3 normal;//normalized
		float d;
		Plane(const Vector3* _normal,const Vector3* _pos);
		Plane(const Vector3* _va,const Vector3* _vb,const Vector3* _vc);//���߷���: (c-a)*(c-b)
		Plane(float a,float b,float c,float d);
	};
	
	float PlanePointDistance(const Plane* _plane,const Vector3* _point);//D3DXPlaneDotCoord  
	float PlaneDotNormal(const Plane* _plane,const Vector3* _pv);//D3DXPlaneDotNormal   ����plane�е�normal�Ǳ�׼����  ����|pv|sin
	Vector3* PlaneLineIntersection(Vector3* _coord,const Plane* _plane,const Line* _line,const float minAngel);//ƽ�з���false 


//math
	/**
	 *@brief ���Բ�ֵ
	 *@param inter��ֵ����
	 */
	int LineInter(float _s1,float _e1,float _c1,float* inter);
	//������������,����zֵ��������������
	Vector3 GrivityCenterByXY(const Vector3* _p1,const Vector3* _p2,const Vector3* _p3,const Vector3* _p);
	bool isTriangle(const Vector3* _p1,const Vector3* _p2,const Vector3* _p3);
	/**
	 *@brief y��scanLine�������
	 *@attention �ƺ�ûʲô��
	 *@param x �����xֵ
	 */
	int ScanlineY(float x1,float y1,float x2,float y2,int y,int* x);

	void print(const Vector3* v);
	void print(const Matrix3x3* matrix);
	void print(const Matrix* mIn);
	void print(const D3DXMATRIX* dMat);
	void print(const Plane* _plane);
	void print(const Vector* v);
	void print(const D3DXVECTOR4* v);
}
#endif 