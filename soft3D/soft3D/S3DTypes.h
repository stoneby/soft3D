

#ifndef S3DTYPES_H_2012625
#define  S3DTYPES_H_2012625

 #pragma warning( disable : 4018 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4800 )

#include "S3DX.h"
START_S3D
enum S3DTRANSFORM{
	TS_WORLD=1,
	TS_VIEW,
	TS_PROJECION
};
enum S3DPRIMITIVETYPE {
	PT_POINTLIST       = 1,
	PT_LINELIST        = 2,
	//PT_LINESTRIP       = 3,
	PT_TRIANGLELIST    = 4,
	//PT_TRIANGLESTRIP   = 5,
	//PT_TRIANGLEFAN     = 6,
};

enum S3DFVF{
	FVF_XYZ=0x1,//float*3
	FVF_COLOR=0x2,//float*4
	FVF_UV=0x4,//float*3
	FVF_NORMAL=0x8,//float*3
 
};
enum TEXTUREADDRESS{
	TADDRESS_WRAP          = 1,
	TADDRESS_MIRROR        = 2,
	TADDRESS_CLAMP         = 3,
	TADDRESS_BORDER        = 4,
	TADDRESS_MIRRORONCE    = 5,

};
enum FILLMODE {
	FILL_POINT         = 1,//点渲染模式
	FILL_WIREFRAME     = 2,//线
	FILL_SOLID         = 3,//面
};


enum ALPHABLEND{
	AB_NORMAL,//正常混合
	AB_ADD,//加法混合
};
enum CULLMODE{
	CM_CW,//裁掉顺时针的
	CM_CCW,//裁掉逆时针的
	CM_NULL,
};

enum S3DRENDERSTATE{
	RS_FILLMODE=1,
	RS_CULLMODE,
	RS_ALPHABLEND,
	

};

#define  ERROR_1 1;



END_S3D

#endif