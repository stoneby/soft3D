


#include "pipeLine.h"

START_S3D

Color::Color(DWORD c)
{
	//DWORD t=c;
	r=(c>>24)/255.0f;
	g=(c<<8>>24)/255.0f;
	b=(c<<16>>24)/255.0f;
	a=(c<<24>>24)/255.0f;
}
Color::Color(int _r,int _g,int _b,int _a)
{
	NumClip(_r,0,255);
	NumClip(_g,0,255);
	NumClip(_b,0,255);
	NumClip(_a,0,255);
	r=_r/255.0f;
	g=_g/255.0f;
	b=_b/255.0f;
	a=_a/255.0f;
}
DWORD  S3D::Color::ToDWORD()
{
	int ir=(int)(r*255);
	int ig=(int)(g*255);
	int ib=(int)(b*255);
	int ia=(int)(a*255);
	NumClip(ir,0,255);
	NumClip(ig,0,255);
	NumClip(ib,0,255);
	NumClip(ia,0,255);
	return MakeColor(ir,ig,ib,ia);
} 
Color S3D::Color::BlendTo(Color des)
{
	NumClip(a,0.0f,1.0f);
	Color re;
	re.r=r*a+(1-a)*des.r;
	re.g=g*a+(1-a)*des.g;
	re.b=b*a+(1-a)*des.b;
	re.a=a;
	return re;
}
DWORD S3D::MakeColor(int r,int g,int b,int a)
{
	ASSERT(r>=0&&r<=255);
	ASSERT(g>=0&&r<=255);
	ASSERT(b>=0&&r<=255);
	ASSERT(a>=0&&r<=255);
	
	return (r<<24)|(g<<16)|(b<<8)|a;	
}

void S3D::Render::GetScreenSize(int* w,int* h)
{
	*w=m_BufferWidth;
	*h=m_BufferHeight;
}
void S3D::Render::SetScreenSize(int w,int h)
{
	m_device->setWindow(w,h);
	if(m_colorBuffer)delete [] m_colorBuffer;
	m_colorBuffer=new Color[w*h];
	if(m_zBuffer)delete[] m_zBuffer;
	m_zBuffer=new float[w*h];
	m_colorBuffer2=new DWORD[w*h];
	m_BufferWidth=w;
	m_BufferHeight=h;
}
void S3D::Render::Clear(DWORD color,float z)
{
	m_device->clear(color,z);


}
void Render::SetFvf(S3DFVF f)
{
	m_fvf=f;
	if(m_curVS)m_curVS->NotifyFVFChanged();
	m_nVSOutSize=m_curVS->GetOutPutSize();
	if(m_PointBuffer)delete [] m_PointBuffer;
	m_PointBuffer=new float[m_nVSOutSize*POINT_BUFFER_COUNT];
	m_crtPointIndex=0;
}
void Render::SetTransform(S3DTRANSFORM type,Matrix* mat) 
{
	switch(type)
	{
	case TS_PROJECION:
		m_projection=*mat;
		break;
	case TS_WORLD:
		m_world=*mat;
		break;
	case  TS_VIEW:
		m_view=*mat;
		break;
	}
}
void Render::GetTransform(S3DTRANSFORM type,Matrix* mat)
{
	switch(type)
	{
	case TS_PROJECION:
		*mat=m_projection;
		break;
	case TS_WORLD:
		*mat=m_world;
		break;
	case  TS_VIEW:
		*mat=m_view;
		break;
	}
}
void Render::SetRenderState(S3DRENDERSTATE _rs,DWORD _v)
{
	switch(_rs)
	{
	case RS_FILLMODE:
		break;
	}
}
void Render::DrawPrimitiveUP(S3DPRIMITIVETYPE type,void* buffer, int startIndex,int count,int vSize)
{
	
	ASSERT(m_curPS&&m_curVS);
	ASSERT(vSize%sizeof(float)==0);
	int n1=vSize/sizeof(float);
	
	for (int i=0;i<count;i++)//添加到顶点列表
	{
// 		float* p1=new float[n1];
// 		memcpy(p1,(char*)buffer+(startIndex+i)*vSize,vSize);
		float* p1=(float*)buffer+n1*i;
		m_vertexLists.push_back(p1);
	}
	m_nVSOutSize=m_curVS->GetOutPutSize();


	for (int i=0;i<m_vertexLists.size();i++)
	{
		float* p=m_vertexLists[i];
		float* pv=m_curVS->DoVS(p);
		ASSERT(pv[3]!=0.0f);
		float w=pv[3];
		for (int i=0;i<m_nVSOutSize;i++)//变换到标准空间
		{
			float n1=pv[i];
			pv[i]=n1/w;
			n1=pv[i];
		}
		m_vsVertexLists.push_back(pv);
	}
// 
// 	BOOST_FOREACH(float* p,m_vertexLists)//顶点着色
// 	{
// 		 
// 		float* pv=m_curVS->DoVS(p);
// 		ASSERT(pv[3]!=0.0f);
// 		float w=pv[3];
// 		for (int i=0;i<m_nVSOutSize;i++)//变换到标准空间
// 		{
// 			float n1=pv[i];
// 			pv[i]=n1/w;
// 			n1=pv[i];
// 		}
// 		m_vsVertexLists.push_back(pv);
// 	}
	 
	
	//
	switch(type)
	{
	case PT_LINELIST:
		m_psVertexLists.clear();
		if(m_vsVertexLists.size()%2!=0)ASSERT(0);
		for (int i=0;i<m_vsVertexLists.size();i+=2)
		{
			CalLineFrag(m_vsVertexLists[i],m_vsVertexLists[i+1]);
			DrawFragment();
		}
		break;
	case PT_POINTLIST:
		m_psVertexLists.clear();

		for (int i=0;i<m_vertexLists.size();i++)
		{
			float* p=m_vertexLists[i];
			CalPointFrag(p);
		}

// 
// 		BOOST_FOREACH(float* p,m_vsVertexLists)
// 		{
// 			CalPointFrag(p);
// 		}
		DrawFragment();
		break;
	case PT_TRIANGLELIST:
		m_psVertexLists.clear();
		if(m_vsVertexLists.size()%3!=0)ASSERT(0);
		for (int i=0;i<m_vsVertexLists.size();i+=3)
		{
			CalTriangleFrag(m_vsVertexLists[i],m_vsVertexLists[i+1],m_vsVertexLists[i+2]);
			DrawFragment();
		}
		break;
	}
	


	m_vertexLists.clear();

	m_vsVertexLists.clear();
 
}

void S3D::Render::Present()
{

	m_device->drawScreen(m_colorBuffer2);
	
}
void Render::DrawPixel(int x,int y,DWORD color,float z)
{
	Color col(color);
	DrawPixel(x,y,col,z);
}

void Render::DrawPixel(int x,int y,Color color,float z)
{
	m_device->drawPoint(x,y,z,color.r,color.g,color.b,color.a);
	
 
}

void Render::CalTriangleFrag( float* _a, float* _b,float* _c )
{	
	float* verList[6];//转换后最多6个顶点
	int verCount=0;//转换后的
	//TODO 裁剪

	//scs
	TranslateToSCS(_a);
	TranslateToSCS(_b);
	TranslateToSCS(_c);

	CalTriangleFragAssist(_a,_b,_c);
}

void Render::CalPointFrag( float* _p )
{
	float* p1=new float[m_nVSOutSize];
	memcpy(p1,_p,m_nVSOutSize*sizeof(float));
	float x=_p[0];
	float y=_p[1];
	float z=_p[2];
	if(x>=-1.0f&&x<1.0f&&y>=-1.0f&&y<1.0f)
	{
		x=((x+1.0f)/2.0f)*m_BufferWidth;
		p1[0]=(float)((int)x);
		y=((y+1.0f)/2.0f)*m_BufferHeight;
		p1[1]=(float)((int)y);
		m_psVertexLists.push_back(p1);
	}
	//顶点属性还原（乘以z）
	ResetProperty(p1);


}
void Render::ResetProperty( float* p1 )
{
	ASSERT(p1[m_nVSOutSize]!=0.0f);
	float f1=p1[m_nVSOutSize-1];
	for(int i=4;i<m_nVSOutSize-1;i++)
	{
		p1[i]=p1[i]/f1;
	}
}
void Render::CalLineFrag( float* _p1,float* _p2 )
{
	float* p1=AllocatePoint();
	memcpy(p1,_p1,m_nVSOutSize*sizeof(float));
	float x1=_p1[0];
	float y1=_p1[1];
	float z1=_p1[2];

	float* p2=AllocatePoint();
	memcpy(p2,_p2,m_nVSOutSize*sizeof(float));
	float x2=_p2[0];
	float y2=_p2[1];
	float z2=_p2[2];
	//裁剪
	//scs
	TranslateToSCS(p1);
	TranslateToSCS(p2);

	CalLineFragAssist(p1,p2);



}

void Render::BeginDraw()
{
	m_InterList.clear();
	m_curVS->VSStart();
	m_curPS->PSStart();
	m_device->drawPointBegin();
	m_crtPointIndex=0;
}

void Render::EndDraw()
{
	m_curPS->PSEnd();
	m_curVS->VSEnd();
	m_device->drawPointEnd();
}

void Render::DrawFragment()
{
	S3D::Color col;
	for(int i=0;i<m_psVertexLists.size();i++)
	{
		float* p=m_psVertexLists[i];
		col=m_curPS->DoPS(p);

#ifdef _DEBUG
		int x1=	(int)p[0];
		int y1=(int)p[1];
		float z=p[2];
#endif
		DrawPixel((int)p[0],(int)p[1],col,p[2]);
		//	delete []p;
	}


// 	BOOST_FOREACH(float* p,m_psVertexLists)//此时x,y为屏幕坐标
// 	{
// 		
// 		col=m_curPS->DoPS(p);
// 
// #ifdef _DEBUG
// 		int x1=	(int)p[0];
// 		int y1=(int)p[1];
// 		float z=p[2];
// #endif
// 		DrawPixel((int)p[0],(int)p[1],col,p[2]);
// 	//	delete []p;
// 	}

	m_psVertexLists.clear();

}


void Render::CalTriangleFragAssist( const float* _a,const float* _b,const float* _c )
{
	 
	float*  ver[3];  
	ver[0] =AllocatePoint();
	ver[1] =AllocatePoint();
	ver[2] =AllocatePoint();
	memcpy(ver[0],_a,m_nVSOutSize*sizeof(float));
	memcpy(ver[1],_b,m_nVSOutSize*sizeof(float));
	memcpy(ver[2],_c,m_nVSOutSize*sizeof(float));
	//排序 使得y值递减
	if(ver[0][1]<ver[1][1])std::swap(ver[0],ver[1]);
	if(ver[1][1]<ver[2][1])std::swap(ver[1],ver[2]);
	if(ver[0][1]<ver[1][1])std::swap(ver[0],ver[1]);
//	printf("%f %f %f\n",ver[0][1],ver[1][1],ver[2][1]);

	if(ver[1][1]==ver[0][1])//平顶三角形
	{
		if(ver[0][0]<ver[1][0])CalTriangleFragAssistTop(ver[0],ver[1],ver[2]);
		else CalTriangleFragAssistTop(ver[1],ver[0],ver[2]);
	}else if(ver[1][1]==ver[2][1])//平底三角形
	{
		if(ver[1][0]<ver[2][0])CalTriangleFragAssistBottom(ver[0],ver[1],ver[2]);
		else CalTriangleFragAssistBottom(ver[0],ver[2],ver[1]);
	}else//普通三角形,切割成两个三角形计算
	{

	}

}
void Render::CalTriangleFragAssistTop(float* _left,float* _right,float* _bottom)
{
	ASSERT(_left[1]==_right[1]);
	//使用画直线算法绘制
	float fSlopLeft=(float)(_left[0]-_bottom[0])/(_left[1]-_bottom[1]);
	float fSlopRight=(float)(_right[0]-_bottom[0])/(_right[1]-_bottom[1]);
	float fXS=_bottom[0];
	float fXE=_bottom[0];
	
	for (int i=(int)_bottom[1];i<_left[1];i++)
	{
		float fy=_bottom[1]+i-(int)_bottom[1];
		if(fy<_left[1])
		{
			float lineLX=fXS+fSlopLeft*(i-(int)_bottom[1]);
			float lineRX=fXE+fSlopRight*(i-(int)_bottom[1]);
			//TODO  插值 现在直接使用左顶点的属性
			float* pleft=AllocatePoint();
			float* pright=AllocatePoint();
			memcpy(pleft,_left,m_nVSOutSize*sizeof(float));
			memcpy(pright,_right,m_nVSOutSize*sizeof(float));
			pleft[0]=lineLX;
			pleft[1]=fy;
			pright[0]=lineRX;
			pright[1]=fy;
			CalLineFragAssist(pleft,pright);
		}
	}
	
}
void Render::CalTriangleFragAssistBottom(float* _top,float* _left,float* _right)
{
	ASSERT(_left[1]==_right[1]);
}

void Render::CalLineFragAssist( const float* _p1,const float* _p2 )
{
	float* p1=NULL;
	p1=AllocatePoint();

	memcpy(p1,_p1,m_nVSOutSize*sizeof(float));
	 
	float* p2=AllocatePoint();
	memcpy(p2,_p2,m_nVSOutSize*sizeof(float));

	float x1=_p1[0];
	float y1=_p1[1];
	float x2=_p2[0];
	float y2=_p2[1];
	p1[0]=(float)((int)x1);
	p1[1]=(float)((int)y1);
	p2[0]=(float)((int)x2);
	p2[1]=(float)((int)y2);

	int dx=(int)(x2-x1);
	int dy=(int)(y2-y1);
	int step;
	float xIns,yIns,xStart=x1,yStart=y1;
	if(fabsf((float)dx)>fabsf((float)dy))step=fabsf((float)dx);
	else step=fabsf((float)dy);
	xIns=(float)dx/step;
	yIns=(float)dy/step;
	
	//添加start点
	m_psVertexLists.push_back(p1);
	for(int i=0;i<step;i++)
	{
		xStart+=xIns;
		yStart+=yIns;
		float* tmpP=AllocatePoint();

		tmpP[0]=(int)xStart;
		tmpP[1]=(int)yStart;
		//插值操作,注意插值参数，有可能有问题
		//TODO  全部都要插值
		float k=1.0f;
		if(xIns!=0.0f)LineInter(x1,x2,xStart,&k);
		else LineInter(y1,y2,yStart,&k);

		for (int i=0;i<m_InterList.size();i++)
		{
			int index=m_InterList[i];
#ifdef _DEBUG
			float a1=p1[index];
			float a2=p2[index];
#endif

			tmpP[index]=p1[index]*k+p2[index]*(1-k);
		}


// 		BOOST_FOREACH(int index,m_InterList)
// 		{
// #ifdef _DEBUG
// 			float a1=p1[index];
// 			float a2=p2[index];
// #endif
//  
// 			tmpP[index]=p1[index]*k+p2[index]*(1-k);
// 
// 		}
		m_psVertexLists.push_back(tmpP);
		ResetProperty(tmpP);
		
	}

}

void Render::SetVertexShader( IVertexShader* pVS)
{
	ASSERT(pVS);
	m_curVS=pVS;
	m_curVS->NotifyFVFChanged();
	m_nVSOutSize=pVS->GetOutPutSize();
	
	m_PointBuffer=new float[m_nVSOutSize*POINT_BUFFER_COUNT];
}

void Render::SetPixelShader( IPixelShader* pPS)
{
	ASSERT(pPS);
	m_curPS=pPS;

}

float* Render::AllocatePoint()
{
	if(m_crtPointIndex>=POINT_BUFFER_COUNT)ASSERT(0);
	
	float* tmp=m_PointBuffer+m_nVSOutSize*m_crtPointIndex;
	m_crtPointIndex++;
	return tmp;
}

int Render::getArraySize()
{
	return m_nVSOutSize;
}

void Render::TranslateToSCS( float* p )
{
	float a1=p[0];
	float a2=p[1];

	p[0]=((p[0]+1.0f)/2.0f)*m_BufferWidth;
	p[1]=((p[1]+1.0f)/2.0f)*m_BufferHeight;
}



void S3D::Render::Blend(vector<ColorPoint>* points)
{
	for (int i=0;i<(int)points->size();i++)
	{
		
		DrawPixel(points->at(i).x,points->at(i).y,points->at(i).color);
	}
}
S3D::Render::Render(IDevice* p,int w,int h):
m_device(p),
m_colorBuffer(NULL),
m_zBuffer(NULL),
m_bZTest(true),
m_bAlphaEnable(true),
m_curPS(NULL),
m_curVS(NULL),
m_defPS(NULL),
m_defVS(NULL),
m_nVSOutSize(0),
m_PointBuffer(NULL)
{
	m_fvf=FVF_XYZ|FVF_COLOR;

	SetScreenSize(w,h);	
	m_defVS=createDefaultVS(this);
	m_defPS=createDefaultPS(this);
	SetVertexShader(m_defVS);
	SetPixelShader(m_defPS);
	
}


 
class VSDefault:public IVertexShader
{
public:
	VSDefault(Render*);
	virtual void VSStart();	
	/**
	 *@brief 
	 *@return vs处理后的顶点列
	 */
	virtual float* DoVS(const void*);
	virtual void VSEnd();
	//输出的
	virtual int GetOutPutSize();//
	virtual void NotifyFVFChanged(){CalOutPutSize();}
protected:
	VSDefault(){}
	int CalOutPutSize();
	Render* m_Render;
	S3DFVF m_fvf;
	Matrix m_matWorld,m_matView,m_matProj;
	bool m_bHasXYZ,m_bHasColor,m_bHasUV,m_bHasNormal;
	int m_indexXYZW,m_indexColor,m_indexUV,m_indexNormal;
	int m_nOutputSize;//输出数据大小（float为单位）

	IFloatArrayAllocate* m_ArrayAllocate;
};
 
VSDefault::VSDefault(Render* p)
{
	 m_Render=p;
	 m_ArrayAllocate=m_Render;
}
void VSDefault::VSStart()
{
	m_fvf=m_Render->GetFvf();
	m_Render->GetTransform(TS_WORLD,&m_matWorld);
	m_Render->GetTransform(TS_VIEW,&m_matView);
	m_Render->GetTransform(TS_PROJECION,&m_matProj);

	CalOutPutSize();
	//刷新插值记录
	m_Render->AddInterItem(2);//zvalue
	m_Render->AddInterItem(m_nOutputSize-1);//1/z
	if(m_fvf&FVF_COLOR)//颜色插值
	{
		m_Render->AddInterItem(m_indexColor);
		m_Render->AddInterItem(m_indexColor+1);
		m_Render->AddInterItem(m_indexColor+2);
		m_Render->AddInterItem(m_indexColor+3);
	}
	if(m_fvf&FVF_UV)
	{
		m_Render->AddInterItem(m_indexUV);
		m_Render->AddInterItem(m_indexUV+1);
	}
	if(m_fvf&FVF_NORMAL)
	{
		m_Render->AddInterItem(m_indexNormal);
		m_Render->AddInterItem(m_indexNormal+1);
		m_Render->AddInterItem(m_indexNormal+2);
	}
	

}
float* VSDefault::DoVS(const void* p)
{
	const float* pIn=(float*)p;
	float* pOut=m_ArrayAllocate->AllocatePoint();
	
	memcpy(pOut,pIn,(m_nOutputSize-1)*sizeof(float));
	pOut[m_nOutputSize-1]=1.0f;
	
	//Vector3 
	Vector v(pIn[0],pIn[1],pIn[2],pIn[3]);
	
	VectorTransform(&v,&v,&m_matWorld);
	VectorTransform(&v,&v,&m_matView);
	VectorTransform(&v,&v,&m_matProj);
	pOut[0]=v.x;
	pOut[1]=v.y;
	pOut[2]=v.z;
	pOut[3]=v.w;
	float a1=pOut[3];

	return pOut;
}
void VSDefault::VSEnd()
{
	
}

int VSDefault::GetOutPutSize()
{
	return m_nOutputSize;
}

int VSDefault::CalOutPutSize()
{
	m_fvf=m_Render->GetFvf();
	m_bHasXYZ=m_fvf&FVF_XYZ;
	m_bHasColor=m_fvf&FVF_COLOR;
	m_bHasUV=m_fvf&FVF_UV;
	m_bHasNormal=m_fvf&FVF_NORMAL;

	m_nOutputSize=0;
	//设置各属性的位置偏移
	if(m_bHasXYZ)
	{
		m_indexXYZW=0;
		m_nOutputSize+=4;
	}
	else ASSERT(0);
	m_indexColor=m_indexXYZW;
	if(m_bHasColor)
	{
		m_indexColor+=4;
		m_nOutputSize+=4;
	}
	m_indexUV=m_indexColor;
	if(m_bHasUV)
	{
		m_indexUV+=m_indexColor+4;
		m_nOutputSize+=2;
	}
	m_indexNormal=m_indexUV;
	if(m_bHasNormal)
	{
		m_indexNormal+=m_indexUV+2;
		m_nOutputSize+=3;
	}
	m_nOutputSize+=1;
	return m_nOutputSize;
}


class PSDefault:public IPixelShader
{
public:
	PSDefault(Render* a);
	virtual void PSStart();
	virtual Color DoPS(void*);
	virtual void PSEnd();
protected:
	Render* m_render;
};
PSDefault::PSDefault(Render* a)
{
	m_render=a;
}
void PSDefault::PSStart()
{

}
Color PSDefault::DoPS(void* _p)
{
	S3DFVF fvf=m_render->GetFvf();
	float* p=(float*)_p;
	if(fvf&FVF_COLOR)
	{
#ifdef FLOAT_DEBUG
		for(int i=0;i<8;i++)
		{
			float p1=p[i];
			p1++;
		}
#endif
		 
		return Color(p[4],p[5],p[6],p[7]);
	}else
	{
		 
		return Color(1.0f,0.0f,0.0f,1.0f);
	}
 
}
void PSDefault::PSEnd()
{
	
}
IVertexShader* createDefaultVS(Render* p)
{
	return new VSDefault(p);
}
IPixelShader* createDefaultPS(Render* p)
{
	return new PSDefault(p);
}
END_S3D