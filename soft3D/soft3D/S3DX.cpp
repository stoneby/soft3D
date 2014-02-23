
#include "S3DX.h"
#include <stdio.h>
namespace S3D
{

	float Vector3DotProduct(const Vector3* inL,const Vector3* inR)
	{
		return inL->_x*inR->_x+inL->_y*inR->_y+inL->_z*inR->_z;
	}
	Vector3* Vector3CrossProduct(Vector3* out,const Vector3* inL,const Vector3* inR)
	{
		ASSERT(out!=0&&inL!=0&&inR!=0);
		out->_x=inL->_y*inR->_z-inL->_z*inR->_y;
		out->_y=inL->_z*inR->_x-inL->_x*inR->_z;
		out->_z=inL->_x*inR->_y-inL->_y*inR->_x;
		return out;
	}
	float Vector3Length(const Vector3* pV)
	{
		return sqrtf(pV->_x*pV->_x + pV->_y*pV->_y + pV->_z*pV->_z);
	}
	Vector3* Vector3Proj( Vector3* out,const Vector3* inL,const Vector3* inR )
	{
		Vector3 tmp;
		float f1=Vector3DotProduct(inL,inR);
		*out=(*inR)*(f1/(Vector3Length(inR)*Vector3Length(inR)));
		return out;
	}
	Vector3* Vector3Perp( Vector3* out,const Vector3* inL,const Vector3* inR )
	{

		Vector3 tmp;
		Vector3Proj(&tmp,inL,inR);
		*out=*inL-tmp;
		return out;
	}
	Vector3* Vector3Normalize(Vector3* pV)
	{
		
		float sum=sqrtf(powf(pV->_x,2)+powf(pV->_y,2)+powf(pV->_z,2));
		ASSERT(sum!=0.0f);
		if(sum!=0.0f)
		{
			*pV/=sum;
		}
		return pV;


	}
	Vector3* Vector3Orthongonlize(Vector3* v1,Vector3* v2,Vector3* v3)
	{
		Vector3 vList[3];
		vList[0]=*v1;
		vList[1]=*v2-(vList[0])*(Vector3DotProduct(v2,&vList[0])/Vector3DotProduct(&vList[0],&vList[0]));

		vList[2]=*v3-(vList[0])*(Vector3DotProduct(v3,&vList[0])/Vector3DotProduct(&vList[0],&vList[0]))-
			(vList[1])*(Vector3DotProduct(v3,&vList[1])/Vector3DotProduct(&vList[1],&vList[1]));


		*v1=vList[0];
		*v2=vList[1];
		*v3=vList[2];
		return NULL;
	}


	Vector3::Vector3()
	{
		_x=_y=_z=0.0f;
	}

	Vector3::Vector3(float x,float y,float z):_x(x),_y(y),_z(z)
	{

	}
	Vector3 Vector3::operator+(const Vector3& v1) const
	{
		Vector3 t;
		t._x=_x+v1._x;
		t._y=_x+v1._y;
		t._z=_x+v1._z;
		return t;
	}
	Vector3 Vector3::operator-(const Vector3& v1) const
	{
		Vector3 t;
		t._x=_x-v1._x;
		t._y=_y-v1._y;
		t._z=_z-v1._z;
		return t;

	}
	float Vector3::operator*(const Vector3& v1)const
	{
		return _x*v1._x+_y*v1._y+_z*v1._z;
	}

	Vector3 Vector3::operator*(float f) const 
	{
		Vector3 t;
		t._x=_x*f;
		t._y=_y*f;
		t._z=_z*f;
		return t;
	}
	Vector3 Vector3::operator/(float f) const
	{
		Vector3 t;
		t._x=_x/f;
		t._y=_y/f;
		t._z=_z/f;
		return t;
	}
	Vector3& Vector3::operator+=(const Vector3& v1)
	{
		_x+=v1._x;
		_y+=v1._y;
		_z+=v1._z;
		return *this;
	}
	Vector3& Vector3::operator-=(const Vector3& v1)
	{
		_x-=v1._x;
		_y-=v1._y;
		_z-=v1._z;
		return *this;
	}
	Vector3& Vector3::operator*=(float f)
	{
		_x*=f;
		_y*=f;
		_z*=f;
		return *this;
	}
	Vector3& Vector3::operator/=(float f)
	{
		_x/=f;
		_y/=f;
		_z/=f;
		return *this;
	}
	void print(const Vector3* v)
	{
		printf("%f,%f,%f",v->_x,v->_y,v->_z);
	}
	void print(const D3DXMATRIX* dMat)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				printf("%f ",dMat->m[i][j]);
			}
			printf("\n");
		}
	}
	void print(const Matrix* mIn)
	{
		printf("%f %f %f %f\n",mIn->_11,mIn->_12,mIn->_13,mIn->_14);
		printf("%f %f %f %f\n",mIn->_21,mIn->_22,mIn->_23,mIn->_24);
		printf("%f %f %f %f\n",mIn->_31,mIn->_32,mIn->_33,mIn->_34);
		printf("%f %f %f %f\n",mIn->_41,mIn->_42,mIn->_43,mIn->_44);
	}
	void print(const Matrix3x3* matrix)
	{
		printf("%f %f %f\n",matrix->_11,matrix->_12,matrix->_13);
		printf("%f %f %f\n",matrix->_21,matrix->_22,matrix->_23);
		printf("%f %f %f\n",matrix->_31,matrix->_32,matrix->_33);

	}
	void print(const Plane* _plane)
	{	
		printf("%f %f %f %f\n",_plane->normal._x,_plane->normal._y,_plane->normal._z,_plane->d);
	}

	void print( const Vector* v )
	{
		printf("%f	%f	%f	%f\n",v->x,v->y,v->z,v->w);
	}

	void print( const D3DXVECTOR4* v )
	{
		printf("%f	%f	%f	%f\n",v->x,v->y,v->z,v->w);
	}

	
	Matrix3x3 Matrix3x3::operator+(const Matrix3x3& mi)
	{
		Matrix3x3 mr;
		for(int i=0;i<9;i++)
		{
			mr.m[i]=m[i]+mi.m[i];
		}
		return mr;
	}
	Matrix3x3 Matrix3x3::operator-(const Matrix3x3& mi)
	{
		Matrix3x3 mr;
		for(int i=0;i<9;i++)
		{
			mr.m[i]=m[i]-mi.m[i];
		}
		return mr;
	}
	Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mi)
	{
		Matrix3x3 mr;
		for(int i=0;i<9;i++)
		{
			mr.m[i]=0.0f;
			for(int j=0;j<3;j++)
			{
				mr.m[i]+=m[(i/3)*3+j]*mi.m[j*3+i%3];
			}
			
		}
		return mr;
	}
	Matrix3x3 Matrix3x3::operator*(float f)
	{
		Matrix3x3 mr;
		for(int i=0;i<9;i++)
		{
			mr.m[i]=m[i]*f;
		}
		return mr;
	}
	Matrix3x3 Matrix3x3::operator/(float f)
	{
		ASSERT(f!=0.0f);
		Matrix3x3 mr;
		for(int i=0;i<9;i++)
		{
			mr.m[i]=m[i]/f;
		}
		return mr;
	}

	Matrix3x3::Matrix3x3()
	{
		ZeroMemory(m,sizeof(m));
	}
	Matrix3x3::Matrix3x3(float _1,float _2,float _3,float _4,float _5,float _6,float _7,float _8,float _9)
	{
		_11=_1;
		_12=_2;
		_13=_3;
		_21=_4;
		_22=_5;
		_23=_6;
		_31=_7;
		_32=_8;
		_33=_9;
	}
	Matrix3x3::Matrix3x3(const Vector3* _u,const Vector3*  _v,const Vector3* _w)
	{
		_11=_u->_x;
		_21=_u->_y;
		_31=_u->_z;

		_12=_v->_x;
		_22=_v->_y;
		_32=_v->_z;

		_13=_w->_x;
		_23=_w->_y;
		_33=_w->_z;

	}

	Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& mi)
	{
		for(int i=0;i<9;i++)
		{
			m[i]+=mi.m[i];
		}
		return *this;
	}
	Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& mi)
	{
		for(int i=0;i<9;i++)
		{
			m[i]-=mi.m[i];
		}
		return *this;
	}

	Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& mi)
	{
		Matrix3x3 matrix;

		for(int i=0;i<3;i++)//行
		{
			for(int j=0;j<3;j++)//列
			{
				for(int k=0;k<3;k++)
				{
					matrix.m1[i][j]+=m1[i][k]*mi.m1[k][j];
				}
			}
		}
		*this=matrix;
		return *this;
	}
	Matrix3x3& Matrix3x3::operator*=(float f)
	{
		for(int i=0;i<9;i++)
		{
			m[i]*=f;
		}
		return *this;
	}
	Matrix3x3& Matrix3x3::operator/=(float f)
	{
		ASSERT(f!=0.0f);
		for(int i=0;i<9;i++)
		{
			m[i]/=f;
		}
		return *this;
	}


	float Matrix3x3Determinats(Matrix3x3* matrix)
	{
		ASSERT(matrix!=NULL);
		float f1=matrix->_11*(matrix->_22*matrix->_33-matrix->_23*matrix->_32);
		float f2=matrix->_12*(matrix->_21*matrix->_33-matrix->_23*matrix->_31);
		float f3=matrix->_13*(matrix->_21*matrix->_32-matrix->_22*matrix->_31);

		return f1-f2+f3;
	}
	Matrix3x3* Matrix3x3Adjoint(Matrix3x3* mOut,Matrix3x3* mIn)
	{
		
		mOut->_11=mIn->_22*mIn->_33-mIn->_23*mIn->_32;
		mOut->_12=mIn->_13*mIn->_32-mIn->_12*mIn->_33;
		mOut->_13=mIn->_12*mIn->_23-mIn->_13*mIn->_22;

		mOut->_21=mIn->_23*mIn->_31-mIn->_21*mIn->_33;
		mOut->_22=mIn->_11*mIn->_33-mIn->_13*mIn->_31;
		mOut->_23=mIn->_13*mIn->_21-mIn->_11*mIn->_23;

		mOut->_31=mIn->_21*mIn->_32-mIn->_22*mIn->_31;
		mOut->_32=mIn->_12*mIn->_31-mIn->_11*mIn->_32;
		mOut->_33=mIn->_11*mIn->_22-mIn->_12*mIn->_21;


		return mOut;
	}
	Matrix3x3* Matrix3x3Inverse(Matrix3x3* mOut,Matrix3x3* mIn)
	{
		float det=Matrix3x3Determinats(mIn);
		ASSERT(det!=0.0f);
		Matrix3x3Adjoint(mOut,mIn);
		(*mOut)*=1.0f/det;
		return mOut;
	}
	Matrix3x3* Matrix3x3Transpose(Matrix3x3* mOut,Matrix3x3* mIn)
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;i<3;j++)
			{
				mOut->m1[i][j]=mIn->m1[j][i];
			}
		}
		return mOut;
	}

	Matrix3x3* Matrix3x3Identity(Matrix3x3* mIn)
	{
		ZeroMemory(mIn,sizeof(Matrix3x3));
		mIn->_11=1.0f;
		mIn->_22=1.0f;
		mIn->_33=1.0f;
		return mIn;
	}
	Vector Vector::operator+(const Vector& v1)const
	{
		Vector v;
		v.x=x+v1.x;
		v.y=y+v1.y;
		v.z=z+v1.z;
		v.w=w+v1.w;
		return v;
	}
	Vector Vector::operator-(const Vector& v1)const
	{
		Vector v;
		v.x=x-v1.x;
		v.y=y-v1.y;
		v.z=z-v1.z;
		v.w=w-v1.w;
		return v;

	}
	float Vector::operator*(const Vector& v1)const
	{

		return x*v1.x+y*v1.y+z*v1.z+w*v1.w;
	}
	Vector Vector::operator*(float f)const 
	{
		Vector v;
		v.x=x*f;
		v.y=y*f;
		v.z=z*f;
		v.w=w*f;
		return v;
	}
	Vector Vector::operator/(float f)const 
	{
		ASSERT(f!=0.0f);
		Vector v;
		v.x=x/f;
		v.y=y/f;
		v.z=z/f;
		v.w=w/f;
		return v;
	}

	Vector& Vector::operator+=(const Vector& v1)
	{
		x+=v1.x;
		y+=v1.y;
		z+=v1.z;
		w+=v1.w;
		return *this;
	}
	Vector& Vector::operator-=(const Vector& v1)
	{
		x-=v1.x;
		y-=v1.y;
		z-=v1.z;
		w-=v1.w;
		return *this;
	}
	Vector& Vector::operator*=(float f)
	{
		x*=f;
		y*=f;
		z*=f;
		w*=f;
		return *this;
	}
	Vector& Vector::operator/=(float f)
	{
		ASSERT(f!=0.0f);
		x/=f;
		y/=f;
		z/=f;
		w/=f;
		return *this;
	}
	Vector* VectorCrossProduct(Vector* out,const Vector* inL,const Vector* inR)
	{
		return NULL;
	}
	float VectorDotProduct(const Vector* inL,const Vector* inR)
	{
		return inL->x*inR->x+inL->y*inR->y+inL->z*inR->z+inL->w*inR->w;
	}
	float VectorLength(const Vector* pV)
	{
		return sqrtf(pV->x*pV->x+pV->y*pV->y+pV->z*pV->z+pV->w*pV->w);
	}
	Vector* VectorProj(Vector* out,const Vector* inL,const Vector* inR)
	{
		return NULL;
	}
	Vector* VectorPerp(Vector* out,const Vector* inL,const Vector* inR)
	{	
		return NULL;
	}
	Vector* VectorNormalize(Vector* pV)
	{
		float length=VectorLength(pV);
		ASSERT(length!=0.0f);
		(*pV)/=length;
		return pV;
	}
	Vector* VectorTransform(Vector* pOut,const Vector* pIn,const Matrix* mat)
	{
		Vector tmp=*pIn;


		pOut->x=tmp.x*mat->_11+tmp.y*mat->_12+tmp.z*mat->_13+tmp.w*mat->_14;
		pOut->y=tmp.x*mat->_21+tmp.y*mat->_22+tmp.z*mat->_23+tmp.w*mat->_24;
		pOut->z=tmp.x*mat->_31+tmp.y*mat->_32+tmp.z*mat->_33+tmp.w*mat->_34;
		pOut->w=tmp.x*mat->_41+tmp.y*mat->_42+tmp.z*mat->_43+tmp.w*mat->_44;

		return pOut;

	}
	/**
	 *@brief 
	 *@todo 未完成
	 */
	Vector* VectorOrthongonlize(Vector* v1,Vector* v2,Vector* v3)//输入：线性无关的3个3维向量 输出：正交化
	{
		return NULL;
	}


	Matrix Matrix::operator+(const Matrix& mIn)
	{
		Matrix mat;
		for (int i=0;i<16;i++)
		{
			mat.m[i]=m[i]+mIn.m[i];
		}
		return mat;
	}
	Matrix Matrix::operator-(const Matrix& mIn)
	{
		Matrix mat;
		for (int i=0;i<16;i++)
		{
			mat.m[i]=m[i]-mIn.m[i];
		}
		return mat;
	}
	Matrix Matrix::operator*(const Matrix& mIn)
	{
		Matrix mat;

		for (int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				for (int k=0;k<4;k++)
				{
					mat.m1[i][j]+=m1[i][k]*mIn.m1[k][j];
				}

			}
		}
		return mat;
	}
	Matrix Matrix::operator*(float f)
	{
		Matrix mat;
		for (int i=0;i<16;i++)
		{
			mat.m[i]=m[i]*f;
		}
		return mat;
	}
	Matrix& Matrix::operator+=(const Matrix mi)
	{
		for (int i=0;i<16;i++)
		{
			m[i]+=mi.m[i];
		}
		return *this;
	}
	Matrix& Matrix::operator-=(const Matrix mi)
	{
		for (int i=0;i<16;i++)
		{
			m[i]-=mi.m[i];
		}
		return *this;

	}
	Matrix& Matrix::operator*=(const Matrix mi)
	{
		Matrix mat;


		for (int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				for (int k=0;k<4;k++)
				{
					mat.m1[i][j]+=m1[i][k]*mi.m1[k][j];
				}

			}
		}
		*this=mat;
		return *this;

	}
	Matrix& Matrix::operator*=(float f)
	{
		for (int i=0;i<16;i++)
		{
			m[i]*=f;
		}
		return *this;

	}
	Matrix::Matrix()
	{
		ZeroMemory(m,sizeof(m));

	}
	Matrix::Matrix(const Matrix3x3* mIn)
	{
		ZeroMemory(this,sizeof(*this));
		for (int i=0;i<3;)
		{
			for(int j=0;j<3;j++)
			{
				m1[i][j]=mIn->m1[i][j];
			}
		}
	}

	Matrix::Matrix(const float* fArr)
	{
		for (int i=0;i<16;i++)
		{
			m[i]=fArr[i];
		}

	}
	Matrix::Matrix(const Vector3* _u,const Vector3* _v,const Vector3* _w)
	{
		ZeroMemory(this,sizeof(*this));
		_44=1.0f;
		_11=_u->_x;
		_21=_u->_y;
		_31=_u->_z;
		
		_12=_v->_x;
		_22=_v->_y;
		_32=_v->_z;

		_13=_w->_x;
		_23=_w->_y;
		_33=_w->_z;

	}


	float MatrixDeterminant(Matrix* matrix)
	{
		Matrix3x3 ma(matrix->_22,matrix->_23,matrix->_24,matrix->_32,matrix->_33,matrix->_34,matrix->_42,matrix->_43,matrix->_44);
		Matrix3x3 mb(matrix->_21,matrix->_23,matrix->_24,matrix->_31,matrix->_33,matrix->_34,matrix->_41,matrix->_43,matrix->_44);
		Matrix3x3 mc(matrix->_21,matrix->_22,matrix->_24,matrix->_31,matrix->_32,matrix->_34,matrix->_41,matrix->_42,matrix->_44);
		Matrix3x3 md(matrix->_21,matrix->_22,matrix->_23,matrix->_31,matrix->_32,matrix->_33,matrix->_41,matrix->_42,matrix->_43);
		
		float fa=Matrix3x3Determinats(&ma);
		float fb=Matrix3x3Determinats(&mb);
		float fc=Matrix3x3Determinats(&mc);
		float fd=Matrix3x3Determinats(&md);

		return matrix->_11*fa-matrix->_12*fb+matrix->_13*fc-matrix->_14*fd;




	}
	Matrix* MatrixAdjoint(Matrix* mOut,Matrix* mIn)
	{
		Matrix3x3   m44[4][4];
		m44[0][0]=Matrix3x3(mIn->_22,mIn->_23,mIn->_24,    mIn->_32,mIn->_33,mIn->_34,    mIn->_42,mIn->_43,mIn->_44);
		m44[0][1]=Matrix3x3(mIn->_21,mIn->_23,mIn->_24,    mIn->_31,mIn->_33,mIn->_34,    mIn->_41,mIn->_43,mIn->_44);
		m44[0][2]=Matrix3x3(mIn->_21,mIn->_22,mIn->_24,    mIn->_31,mIn->_32,mIn->_34,    mIn->_41,mIn->_42,mIn->_44);
		m44[0][3]=Matrix3x3(mIn->_21,mIn->_22,mIn->_23,    mIn->_31,mIn->_32,mIn->_33,    mIn->_41,mIn->_42,mIn->_43);

		m44[1][0]=Matrix3x3(mIn->_12,mIn->_13,mIn->_14,    mIn->_32,mIn->_33,mIn->_34,    mIn->_42,mIn->_43,mIn->_44);
		m44[1][1]=Matrix3x3(mIn->_11,mIn->_13,mIn->_14,    mIn->_31,mIn->_33,mIn->_34,    mIn->_41,mIn->_43,mIn->_44);
		m44[1][2]=Matrix3x3(mIn->_11,mIn->_12,mIn->_14,    mIn->_31,mIn->_32,mIn->_34,    mIn->_41,mIn->_42,mIn->_44);
		m44[1][3]=Matrix3x3(mIn->_11,mIn->_12,mIn->_13,    mIn->_31,mIn->_32,mIn->_33,    mIn->_41,mIn->_42,mIn->_43);

		m44[2][0]=Matrix3x3(mIn->_12,mIn->_13,mIn->_14,    mIn->_22,mIn->_23,mIn->_24,    mIn->_42,mIn->_43,mIn->_44);
		m44[2][1]=Matrix3x3(mIn->_11,mIn->_13,mIn->_14,    mIn->_21,mIn->_23,mIn->_24,    mIn->_41,mIn->_43,mIn->_44);
		m44[2][2]=Matrix3x3(mIn->_11,mIn->_12,mIn->_14,    mIn->_21,mIn->_22,mIn->_24,    mIn->_41,mIn->_42,mIn->_44);
		m44[2][3]=Matrix3x3(mIn->_11,mIn->_12,mIn->_13,    mIn->_21,mIn->_22,mIn->_23,    mIn->_41,mIn->_42,mIn->_43);

		m44[3][0]=Matrix3x3(mIn->_12,mIn->_13,mIn->_14,    mIn->_22,mIn->_23,mIn->_24,    mIn->_32,mIn->_33,mIn->_34);
		m44[3][1]=Matrix3x3(mIn->_11,mIn->_13,mIn->_14,    mIn->_21,mIn->_23,mIn->_24,    mIn->_31,mIn->_33,mIn->_34);
		m44[3][2]=Matrix3x3(mIn->_11,mIn->_12,mIn->_14,    mIn->_21,mIn->_22,mIn->_24,    mIn->_31,mIn->_32,mIn->_34);
		m44[3][3]=Matrix3x3(mIn->_11,mIn->_12,mIn->_13,    mIn->_21,mIn->_22,mIn->_23,    mIn->_31,mIn->_32,mIn->_33);

		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				mOut->m1[i][j]=pow(-1.0f,i+j)*Matrix3x3Determinats(&m44[j][i]);
			}
		}
		

		return mOut;
	}
	Matrix* MatrixInverse(Matrix* mOut,Matrix* mIn)
	{
		float det=MatrixDeterminant(mIn);
		ASSERT(det!=0.0f);
		Matrix mat;
		MatrixAdjoint(&mat,mIn);

		*mOut=mat*(1.0f/det);
		return mOut;
	}
	Matrix* MatrixTranspose(Matrix* mOut,Matrix* mIn)
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				mOut->m1[i][j]=mIn->m1[j][i];
			}
		}
		return mOut;
	}

	Matrix* MatrixIdentity(Matrix* mIn)
	{
		ZeroMemory(mIn,sizeof(Matrix));
		for(int i=0;i<4;i++)
		{
			mIn->m1[i][i]=1.0f;
		}
		return mIn;
	}
	Matrix* MatrixScale(Matrix* mIn,float _x,float _y,float _z)
	{
		ZeroMemory(mIn,sizeof(*mIn));
		mIn->_11=_x;
		mIn->_22=_y;
		mIn->_33=_z;
		mIn->_44=1;
		return mIn;
		
	}
	Matrix* MatrixScaleAxis(Matrix* mat,Matrix3x3* m33,float _x,float _y,float _z)
	{
		Matrix3x3 mInverse;
		Matrix3x3 mabc;
		Matrix3x3 mfinal;

		Matrix3x3Inverse(&mInverse,m33);
		mabc._11=_x;
		mabc._22=_y;
		mabc._33=_z;
		mfinal=(*m33)*mabc*mInverse;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				mat->m1[i][j]=mfinal.m1[i][j];
			}
		}
		mat->_14=0;
		mat->_24=0;
		mat->_34=0;

		mat->_41=0;
		mat->_42=0;
		mat->_43=0;

		mat->_44=1;

		return mat;
		
	}
	Matrix* MatrixRotationX(Matrix* mIn,float angel)
	{
		Matrix mat;
		mat._11=1.0f;
		mat._44=1.0f;

		mat._22=cosf(angel);
		mat._23=sinf(angel);
		mat._32=-sinf(angel);
		mat._33=cosf(angel);
			
		*mIn=mat;
		return mIn;
	}
	Matrix* MatrixRotationY(Matrix* mIn,float angel)
	{
		Matrix mat;
		mat._22=1.0f;
		mat._44=1.0f;
		mat._11=cosf(angel);
		mat._13=-sinf(angel);
		mat._31=sinf(angel);
		mat._33=cosf(angel);

		*mIn=mat;
		return mIn;
	}
	Matrix* MatrixRotationZ(Matrix* mIn,float angel)
	{
		Matrix mat;
		mat._33=1.0f;
		mat._44=1.0f;
		mat._11=cosf(angel);
		mat._12=sinf(angel);
		mat._21=-sinf(angel);
		mat._22=cosf(angel);

		*mIn=mat;
		return mIn;
	}
	Matrix* MatrixRotationAxis(Matrix* mIn ,const Vector3* _v,float angel)
	{
		Vector3 v=*_v;
		Vector3Normalize(&v);
		float c=cosf(angel);
		float s=sinf(angel);
		Matrix3x3 m1;
		Matrix3x3 m2;
		Matrix3x3 m3;

		Matrix3x3Identity(&m1);
		m2._12=-v._z;
		m2._13=v._y;
		m2._21=v._z;
		m2._23=-v._x;
		m2._31=-v._y;
		m2._32=v._x;
		
		m3._11=v._x*v._x;
		m3._12=v._x*v._y;
		m3._13=v._x*v._z;
		m3._21=v._x*v._y;
		m3._22=v._y*v._y;
		m3._23=v._y*v._z;
		m3._31=v._x*v._z;
		m3._32=v._y*v._z;
		m3._33=v._z*v._z;
		
		Matrix3x3 mre;
		Matrix marRe;
		mre=m1*c-m2*s+m3*(1-c);
		for(int i=0;i<3;i++)
		{
			for (int j=0;j<3;j++)
			{
				marRe.m1[i][j]=mre.m1[i][j];
			}
		}
		marRe._44=1.0f;
		*mIn=marRe;
		
		return mIn;
	}
	Matrix* MatrixTranslation(Matrix* mIn,float _x,float _y,float _z)
	{
		MatrixIdentity(mIn);
		mIn->_14=_x;
		mIn->_24=_y;
		mIn->_34=_z;
		return mIn;
	}
	Matrix* MatrixLookAtLH(Matrix* mIn,const Vector3* _pos,const Vector3* lookat,const Vector3* _up)
	{
		
		Vector3 vT;
		Vector3 vX;
		Vector3 vY;
		Vector3 vZ;
		vZ=*lookat-*_pos;
		Vector3Normalize(&vZ);
		Vector3CrossProduct(&vX,_up,&vZ);
		Vector3Normalize(&vX);
		Vector3CrossProduct(&vY,&vZ,&vX);
//      正交矩阵的逆矩阵=转置矩阵
		Matrix3x3  mat1(&vX,&vY,&vZ);
		Matrix3x3 mat2;
		Matrix3x3Inverse(&mat2,&mat1);
// 		print(&mat1);
// 		print(&mat2);

		Matrix mat;
		mat._11=vX._x;mat._12=vX._y;mat._13=vX._z;
		mat._21=vY._x;mat._22=vY._y;mat._23=vY._z;
		mat._31=vZ._x;mat._32=vZ._y;mat._33=vZ._z;

		mat._14=-Vector3DotProduct(&vX,_pos);
		mat._24=-Vector3DotProduct(&vY,_pos);
		mat._34=-Vector3DotProduct(&vZ,_pos);
		mat._44=1;
		*mIn=mat;
		return mIn;

	}
	Matrix* MatrixPerspectiveOffCenterLH( Matrix* mOut,float l,float r,float b,float t,float n,float f )
	{
		ASSERT(l<r&&b<t&&n<f);
		ZeroMemory(mOut,sizeof(*mOut));
		mOut->_11=(2*n)/(r-l);
		mOut->_13=-(l+r)/(r-l);
		mOut->_22=2*n/(t-b);
		mOut->_23=-(t+b)/(t-b);
		mOut->_33=f/(f-n);
		mOut->_34=-f*n/(f-n);
		mOut->_43=1;

		return mOut;		
	}
	Matrix* MatrixPerspectiveFovLH(Matrix* mOut,float angel,float aspect,float n,float f)
	{
		ASSERT(n<f&&angel!=0.0f&&aspect>0);
		float r=n*tanf(angel/2.0f);
		float l=-r;
		float t=aspect*r;
		float b=-t;
		
		return MatrixPerspectiveOffCenterLH(mOut,l,r,b,t,n,f);
	}
	Matrix* MatrixOrthoOffCenterLH(Matrix* mOut,float l,float r,float b,float t,float n,float f)
	{
		ZeroMemory(mOut,sizeof(*mOut));
		mOut->_11=2/(r-l);
		mOut->_14=-(l+r)/(r-l);
		mOut->_22=2/(t-b);
		mOut->_24=-(t+b)/(t-b);
		mOut->_33=1.0f/(f-n);
		mOut->_34=-n/(f-n);
		mOut->_44=1;
		return mOut;
	}
	Matrix* MatrixOrthoLH(Matrix* mOut,float w,float h,float zn,float zf)
	{
		float r=w/2;
		float l=-r;
		float t=h/2;
		float b=-t;
		return MatrixOrthoOffCenterLH(mOut,l,r,b,t,zn,zf);
	}
	Line::Line(const Vector3* _pos1,const Vector3* _pos2,int _type)
	{
		pos=*_pos1;
		dir=*_pos2-*_pos1;
		Vector3Normalize(&dir);
		Vector3 tmp=*_pos2-*_pos1;
		t=Vector3Length(&tmp);
		type=_type;

	}
	float LinePointDistance(const Vector3* _pos,const Line* _line)
	{
		Vector3 p=*_pos-_line->pos;
		Vector3 perp;
		Vector3Perp(&perp,&p,&(_line->dir));
		return Vector3Length(&perp);

	}
	float LineLineDistance(const Line* _line1,const Line* _line2)
	{
		float t1;

		float f1=_line1->dir*_line2->dir-1;
		if (f1==0.0f)//平行
		{
			
			return LinePointDistance(&(_line1->pos),_line2);
		}
		f1=1/f1;
		t1=-((_line2->pos-_line1->pos)*_line1->dir)+(_line1->dir*_line2->dir)*((_line2->pos-_line1->pos)*_line2->dir);
		t1=f1*t1;
																		
		Vector3 v1=_line1->pos+_line1->dir*t1;
		return LinePointDistance(&v1,_line2);
	}
	Plane::Plane(const Vector3* _normal,const Vector3* _pos)
	{
		normal=*_normal;
		Vector3Normalize(&normal);
		d=-Vector3DotProduct(&normal,_pos);
		
	}
	Plane::Plane(const Vector3* _va,const Vector3* _vb,const Vector3* _vc)
	{
		Vector3 v1;
		Vector3 v2;
		Vector3 v3;
		v1=*_vc-*_va;
		v2=*_vc-*_vb;
		Vector3CrossProduct(&v3,&v1,&v2);
		Vector3Normalize(&v3);
		d=-(v3*(*_va));
		normal=v3;
	}

	Plane::Plane(float a,float b,float c,float d1)
	{
		d=d1;
		normal._x=a;
		normal._y=b;
		normal._z=c;
		Vector3Normalize(&normal);
	}

	float PlanePointDistance(const Plane* _plane,const Vector3* _point)
	{
		float d1=Vector3DotProduct(_point,&(_plane->normal));

		return d1+_plane->d;
	}
	float PlaneDotNormal(const Plane* _plane,const Vector3* _pv)
	{
		return Vector3DotProduct(&(_plane->normal),_pv);
	}
	Vector3* PlaneLineIntersection(Vector3* _coord,const Plane* _plane,const Line* _line,const float minAngel)
	{
		float c1=sinf(minAngel);
		float dot=Vector3DotProduct(&(_plane->normal),&(_line->dir));
		if(dot*dot<=c1*c1||dot==0)
		{
			return NULL;
		}
		float t1=-(PlanePointDistance(_plane,&(_line->pos))/dot);
		switch(_line->type)
		{
		case  LINE_SEGMENT:
			{
				if(_line->t>0&&(t1>_line->t||t1<0))
				{
					return false;
				}else if(_line->t<=0&&(t1<_line->t||t1>0))
				{
					return false;
				}

			}
			break;
		case LINE_NORMAL:

			break;
		case LINE_RAY:
			{
				if(_line->t>0&&t1<0)
				{
					return false;
				}else if(_line->t<0&&t1>0)
				{
					return false;
				}
			}
			break;

		}
		*_coord=_line->pos+_line->dir*t1;
		return _coord;
	}

	Vector* Vector3transform( Vector* vOut,const Vector3* vIn,const Matrix* matrix )
	{
		Vector vecIn(vIn->_x,vIn->_y,vIn->_z,1);
		
		VectorTransform(vOut,&vecIn,matrix);

		return vOut;
	}

	Vector3* Vector3transformCoord( Vector3* vOut,const Vector3* vIn,const Matrix* matrix )
	{
		Vector vecIn(vIn->_x,vIn->_y,vIn->_z,1);
		Vector v4Out;
		VectorTransform(&v4Out,&vecIn,matrix);
		float fw=v4Out.w;
		_ASSERT(fw!=0.0f);
		v4Out/=fw;
		vOut->_x=v4Out.x;
		vOut->_y=v4Out.y;
		vOut->_z=v4Out.z;
		return vOut;
	}

	int LineInter( float _s1,float _e1,float _c1,float* inter )
	{
		if(_s1==_e1)
		{
			*inter=0.0f;
			return 0;
		}else
		{
			float dis=_e1-_s1;
			*inter=1.0f-(_c1-_s1)/dis;
			return 0;
		}
	}
	inline bool isVector3SameXY(const Vector3* _p1,const Vector3* _p2)
	{
		return _p1->_x==_p2->_x&&_p1->_y==_p2->_y;
	}
	Vector3 GrivityCenterByXY( const Vector3* _p1,const Vector3* _p2,const Vector3* _p3,const Vector3* _p )
	{
		
		Vector3 res;

		res._x=((_p->_y-_p3->_y)*(_p2->_x-_p3->_x)+(_p2->_y-_p3->_y)*(_p3->_x-_p->_x))/((_p1->_y-_p3->_y)*(_p2->_x-_p3->_x)+(_p2->_y-_p3->_y)*(_p3->_x-_p1->_x));

		res._y=((_p->_y-_p1->_y)*(_p3->_x-_p1->_x)+(_p3->_y-_p1->_y)*(_p1->_x-_p->_x))/((_p1->_y-_p3->_y)*(_p2->_x-_p3->_x)+(_p2->_y-_p3->_y)*(_p3->_x-_p1->_x));

		res._z=((_p->_y-_p2->_y)*(_p1->_x-_p2->_x)+(_p1->_y-_p2->_y)*(_p2->_x-_p->_x))/((_p1->_y-_p3->_y)*(_p2->_x-_p3->_x)+(_p2->_y-_p3->_y)*(_p3->_x-_p1->_x));

	
		
		return res;
	}

	int ScanlineY( float x1,float y1,float x2,float y2,int y,int* x )
	{
		if(x1==x2)
		{
			if(y>=min(y1,y2)&&y<=max(y1,y2))
			{
				*x=x1;
				return 0;
			}
			else return 1;
			 
		}
		if(y1==y2)
		{
			return 1;
		}else 
		{
			*x=(int)(((y-y1)*(x1-x2))/(y1-y2)+x1);
			return 0;
		}

	}

	bool isTriangle( const Vector3* _p1,const Vector3* _p2,const Vector3* _p3 )
	{
		Vector3 v1=*_p3-*_p1;
		Vector3 v2=*_p2-*_p1;


		return !(v1._x*v2._y==v1._y==v2._x);
	}






}

 



