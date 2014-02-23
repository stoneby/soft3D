
/***************************
 *@brief 3D数学库
 *左手坐标系  与d3d相同
 *row major  与d3d的column major相反  也就是说uvw竖着摆，vec是4x1，进行变换时矩阵在左边
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
#define  RADIAN(a)  ((a)/180.0f*3.1415927f)//角度转弧度
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
	Vector3* Vector3Orthongonlize(Vector3* v1,Vector3* v2,Vector3* v3);//输入：线性无关的3个3维向量 输出：正交化
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
	 *@brief 计算行列式
	 */
	float Matrix3x3Determinats(Matrix3x3* matrix);
	Matrix3x3* Matrix3x3Adjoint(Matrix3x3* mOut,Matrix3x3* mIn);//伴随矩阵
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
	 *@todo 未完成
	 */
	Vector* VectorOrthongonlize(Vector* v1,Vector* v2,Vector* v3);//输入：线性无关的3个3维向量 输出：正交化




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
		Matrix(const float* fArr);//以数组初始化
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
	Matrix* MatrixAdjoint(Matrix* mOut,Matrix* mIn);//伴随矩阵
	Matrix* MatrixInverse(Matrix* mOut,Matrix* mIn);//逆矩阵
	Matrix* MatrixTranspose(Matrix* mOut,Matrix* mIn);//转置矩阵
	Matrix* MatrixIdentity(Matrix* mIn);
	
	//transform
	Matrix* MatrixScale(Matrix* mIn,float _x,float _y,float _z);
	Matrix* MatrixScaleAxis(Matrix* mIn,Matrix3x3* ,float _x,float _y,float _z);//沿新的3个方向进行scale  似乎没什么用哎
	Matrix* MatrixRotationX(Matrix* mIn,float angel);//弧度，逆时针为+ 
	Matrix* MatrixRotationY(Matrix* mIn,float angel);//弧度，逆时针为+ 
	Matrix* MatrixRotationZ(Matrix* mIn,float angel);//弧度，逆时针为+ 
	Matrix* MatrixRotationAxis(Matrix* mIn ,const Vector3* _v,float angel);
	Matrix* MatrixTranslation(Matrix* mIn,float _x,float _y,float _z);
	Matrix* MatrixLookAtLH(Matrix* mIn,const Vector3* pos,const Vector3* lookat,const Vector3* up);//pos摄像机位置 lookat朝向的点 
	Matrix* MatrixPerspectiveOffCenterLH(Matrix* mOut,float l,float r,float b,float t,float n,float f);//透视矩阵lr=左右坐标tb=上下坐标 nf=远近剪裁面坐标
	Matrix* MatrixPerspectiveFovLH(Matrix* mOut,float angel,float aspect,float n,float f);//角度，纵横比，近剪裁，远剪裁
	Matrix* MatrixOrthoOffCenterLH(Matrix* mOut,float l,float r,float b,float t,float n,float f);//正交投影
	Matrix* MatrixOrthoLH(Matrix* mOut,float w,float h,float zn,float zf);//
	//
	
#define  LINE_NORMAL 0
#define  LINE_RAY 1
#define  LINE_SEGMENT 2
	struct Line//直线 射线 或者线段
	{
		Vector3 pos;//点
		Vector3 dir;//方向  normalized
		float t;
		int type;//LINE_
		
		Line(const Vector3* _pos1,const Vector3* _pos2,int _type);
	};
	float LinePointDistance(const Vector3* _pos,const Line* _line);//点到直线距离
	float LineLineDistance(const Line* _line1,const Line* _line2);//
	struct Plane//面： 法向量+原点到面的距离 ax+by+cz+d=0   N P  d=-N.P    normal方向为面的正方向  点乘结果为负表示点处在负方向那一边
	{
		Vector3 normal;//normalized
		float d;
		Plane(const Vector3* _normal,const Vector3* _pos);
		Plane(const Vector3* _va,const Vector3* _vb,const Vector3* _vc);//法线方向: (c-a)*(c-b)
		Plane(float a,float b,float c,float d);
	};
	
	float PlanePointDistance(const Plane* _plane,const Vector3* _point);//D3DXPlaneDotCoord  
	float PlaneDotNormal(const Plane* _plane,const Vector3* _pv);//D3DXPlaneDotNormal   由于plane中的normal是标准向量  返回|pv|sin
	Vector3* PlaneLineIntersection(Vector3* _coord,const Plane* _plane,const Line* _line,const float minAngel);//平行返回false 


//math
	/**
	 *@brief 线性插值
	 *@param inter插值变量
	 */
	int LineInter(float _s1,float _e1,float _c1,float* inter);
	//计算重心坐标,计算z值并返回重心坐标
	Vector3 GrivityCenterByXY(const Vector3* _p1,const Vector3* _p2,const Vector3* _p3,const Vector3* _p);
	bool isTriangle(const Vector3* _p1,const Vector3* _p2,const Vector3* _p3);
	/**
	 *@brief y轴scanLine交点计算
	 *@attention 似乎没什么用
	 *@param x 输出的x值
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