
#include "common.h"
#include "S3DX.h"
#include "test.h"
#include <stdio.h>
#include <list>
//************************************************************************/
//*                                               
//************************************************************************/
#define  PRINT_LINE  printf("\n")
#define  PRINT(a)    printf("%s\n",#a)
#define  PRINT_START  PRINT(---)
void Vector3Test()
{
	printf("3‘™œÚ¡ø≤‚ ‘\n");
	S3D::Vector3 v1(1.0f,1.0f,1.0f);
	S3D::Vector3 v2(2.0f,2.0f,2.0f);
	S3D::Vector3Normalize(&v1);
	S3D::print(&v1);PRINT_LINE;
	S3D::Vector3 v3=v1+v2;
	S3D::print(&v3);PRINT_LINE;
	S3D::Vector3 vResult;
	v2=S3D::Vector3(1.0f,2.0f,3.0f);
	printf("%f\n",S3D::Vector3DotProduct(&v1,&v2));

	Vector3CrossProduct(&vResult,&v1,&v2);
	S3D::print(&vResult);PRINT_LINE;

	printf("%f\n",S3D::Vector3DotProduct(&vResult,&v2));
	printf("%f\n",S3D::Vector3DotProduct(&vResult,&v1));
	PRINT_START;
	PRINT(proj & prep);
	S3D::Vector3Proj(&vResult,&v1,&v2);
	S3D::print(&vResult);PRINT_LINE;
	S3D::Vector3  vPerp;

	S3D::Vector3Perp(&vPerp,&v1,&v2);
	S3D::print(&vPerp);PRINT_LINE;
	printf("%f\n",S3D::Vector3DotProduct(&vResult,&vPerp));

	printf("length:proj perp v1\n %f %f %f wanted valuie %f\n",S3D::Vector3Length(&vResult),
		S3D::Vector3Length(&vPerp),S3D::Vector3Length(&v1),sqrtf(powf(S3D::Vector3Length(&vResult),2)+powf(S3D::Vector3Length(&vPerp),2)));


	{
		S3D::Vector3 v1(1.0f,2.0f,3.0f);
		S3D::Vector3 v2(-1.0f,1.0f,1.0f);
		S3D::Vector3 v3(4.0f,5.0f,6.0f);
		S3D::Vector3 vProj;
		S3D::Vector3Proj(&vProj,&v2,&v1);
		S3D::print(&vProj);PRINT_LINE;
		Vector3Orthongonlize(&v1,&v2,&v3);
		S3D::print(&v1);PRINT_LINE;
		S3D::print(&v2);PRINT_LINE;
		S3D::print(&v3);PRINT_LINE;
		printf("%f\n",S3D::Vector3DotProduct(&v1,&v2));
		printf("%f\n",S3D::Vector3DotProduct(&v2,&v3));
		float f1=S3D::Vector3DotProduct(&v1,&v2);
		float f2=S3D::Vector3DotProduct(&v2,&v3);
		printf("%f %f ",f1,f2);
		float f3=0.00000001f;
		float* pf1=&f1;
		float* pf2=&f2;

	//	Sleep(f1*f2);

		
	}
};
void matrix3x3Test()
{
	printf("33æÿ’Û≤‚ ‘\n");
	S3D::Matrix3x3 matrix1;
	S3D::Matrix3x3 matrix2(1,2,3,4,5,6,7,8,9);
	S3D::Matrix3x3 matrix3(9,8,7,6,5,4,3,2,1);
	S3D::Matrix3x3 matrix4;

	S3D::print(&matrix1);
	S3D::print(&matrix2);
	PRINT_LINE;
	S3D::print(&matrix2);
	S3D::print(&matrix3);
	PRINT_LINE;

    matrix4=matrix2*matrix3;
	S3D::print(&matrix4);

	PRINT_LINE;
	S3D::print(&matrix2);
	S3D::print(&matrix3);
	PRINT_LINE;
	matrix2*=matrix3;
	matrix2=S3D::Matrix3x3(1,2,3,4,5,6,6,80,9);
	S3D::print(&matrix2);
	{
		printf("---«ÛƒÊæÿ’Û\n");
		S3D::Matrix3x3 matrix5;
		S3D::Matrix3x3Inverse(&matrix5,&matrix2);
		matrix5=matrix5*matrix2;
		S3D::print(&matrix5);
	}	
	 

	
}

#ifdef _TEST
 
void doOnce(vector<int>* li)
{
	static int fps=-1;
	static float ti=0;
	if(fps==-1)
	{
		fps=0;
		ti=GetTickCount();
	}else
	{
		fps++;
		if(GetTickCount()-ti>1000)
		{
			ti=GetTickCount();
			printf("%d\n",fps);
			fps=0;
		}
	}

	li->clear();
	for (int i=0;i<100;i++)
	{

		li->push_back(i);
	}
}

int main()
{

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(1875);
	// Vector3Test();
	//matrix3x3Test();
	//testMatrixInverse();
//	testMatrixTranspose();
	//testTransformScale();
	//testTransformRotation();
	//testTransformTranslation();
	//testTransformView();
	//testLine();
	//testPlane();
	//testProjection();
	//testVector4();
	//testMath();
	std::vector<int> intList;

	while(true)
	{
		doOnce(&intList);
	}

	system("pause");

	 
	return 1;
}
#endif

