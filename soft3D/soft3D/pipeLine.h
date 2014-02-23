/***************************
 *@brief 渲染管线实现 
 *
 ***************************/

#ifndef  S3D_PIPELINE_2012622
#define  S3D_PIPELINE_2012622
#define  FLOAT_DEBUG //输出一些float值以便debug

#include "S3DTypes.h"
#include "S3DX.h"
template <typename T> 
void NumClip(T a,T s, T b)
{
	if(a<s)a=s;
	if(a>b)a=b;
}
/**
 *@brief memset升级版,不安全的
 *@param nCount 拷贝的对象数量
 */
template<typename T>
void MemSet( T* dst,const T* v,int nCount)
{
	if(nCount==0)return;
	memcpy(dst,v,sizeof(T));
	int nCopySize;
	for(int i=1;;i=i*2)
	{
		if(2*i<=nCount)
		{
			nCopySize=i;
			memcpy(dst+i,dst,nCopySize*sizeof(T));
		}else
		{
			nCopySize=nCount-i;
			memcpy(dst+i,dst,nCopySize*sizeof(T));
			break;
		}
	}
}

START_S3D
inline DWORD MakeColor(int r,int g,int b,int a);
 
 

struct Color
{

	Color(DWORD c);
	Color(int r,int g,int b,int a);
	Color(float _r,float _g,float _b,float _a){r=_r;g=_g;b=_b;a=_a;}
	Color()
	{
		r=g=b=a=1.0f;
	}
	DWORD ToDWORD();
	//混合到目标颜色
	Color BlendTo(Color des);
	float r,g,b,a;
};


/**
 *@brief  绘制接口，笛卡尔坐标系
 */
class IDevice
{
public:
	virtual void setWindow(int w,int h)=0;

	/**
	 *@brief 绘制整个屏幕，绘制w*h个像素，初始点是原点，横向增长
	 *@attention 效率很低,以后直接在设备上面绘制点
	 */
	virtual void drawScreen(DWORD* )=0;
	/**
	 *@brief 画点系列函数
	 */
	virtual void drawPointBegin()=0;
	virtual void drawPointEnd()=0;
	virtual void drawPoint(int x,int y,float z,float r,float g,float b,float a)=0;//包含颜色混合
	virtual void clear(float r,float g,float b,float a,float zValue)=0;//清屏
	virtual void clear(DWORD col,float zValue)=0;//清屏
}; 
struct ColorPoint//
{
	int x;
	int y;
	Color color;
};
class IVertexShader;
class IPixelShader;
class IRender// 以后将接口函数移入
{
public:

};
/**
 *@brief render提供给shader的顶点内存分配器，略糙
 */
struct IFloatArrayAllocate
{
	virtual float* AllocatePoint()=0;
	virtual int getArraySize()=0;
};

class Render:public IRender,public IFloatArrayAllocate
{
	enum
	{
		VERTEX_BUFFER_SIZE=1024*1024*64,//64M的顶点缓存,超出会报错
		POINT_BUFFER_COUNT=1024*1024//顶点缓存用于分配临时需要的顶点区块,一百万个顶点
	};
public:
	Render(IDevice* p,int w,int h);
	void GetScreenSize(int* w,int* h);
	void SetScreenSize(int w,int h);
	void Clear(DWORD color,float z);
	//
	void SetFvf(S3DFVF f);
	S3DFVF GetFvf(){return (S3DFVF)m_fvf;}
	
	void SetRenderState(S3DRENDERSTATE _rs,DWORD _v);
	void SetTransform(S3DTRANSFORM type,Matrix* mat);
	void GetTransform(S3DTRANSFORM type,Matrix* mat);
	void SetVertexShader(IVertexShader* );
	void SetPixelShader(IPixelShader* );
	void BeginDraw();
	void EndDraw();
	virtual inline float* AllocatePoint();
	virtual inline int getArraySize();
	/**
	 *@brief 
	 *@param  vSize 单个顶点数据的字节大小 
	 *@attention 注意buffer的内容
	 */
	void DrawPrimitiveUP(S3DPRIMITIVETYPE type,void* buffer, int stratIndex,int count,int vSize);//buffer是一个float数组
	
	//输出到设备
	void Present();
	//将要转为private成员
	void DrawPixel(int x,int y,DWORD color,float z=0.0f);
	void Blend(vector<ColorPoint> *points);//渲染图元到页面
	//
	void AddInterItem(int n){m_InterList.push_back(n);}
	
protected:
	inline void DrawPixel(int x,int y,Color color,float z=0.0f);
	//cal系列，输入：标准空间,vsVertex 输出：屏幕空间的点集合
	void CalTriangleFrag(float* _a, float* _b, float* _c);
	/**
	 *@brief 输入必须保证是三角形,标准控件
	 */
	void CalTriangleFragAssist(const float* _a,const float* _b,const float* _c);
	/**
	 *@brief scs空间,平顶三角形
	 */
	void CalTriangleFragAssistTop(float* _left,float* _right,float* _bottom);//
	/**
	 *@brief scs空间，平底三角形
	 */
	void CalTriangleFragAssistBottom(float* _top,float* _left,float* _right);//
	inline void TranslateToSCS(float* p);


	void CalPointFrag(float* _p);
	/**
	 *@brief 输入为标准空间
	 */
	void CalLineFrag(float* _p1,float* _p2);
	void ResetProperty(float* p);//重置被z除的属性值
	/**
	 *@brief 输入为scs空间，输入必须保证能够构成直线,DDA算法
	 */
	void CalLineFragAssist(const float* _p1,const float* _p2);
	/**
	 *@brief  绘制图元，包括：像素着色，merge
	 */
	void DrawFragment();

	 

	/**
	 *@brief 分配顶点内存
	 */
	 

	IDevice* m_device;
	Color* m_colorBuffer;///显示缓存
	float* m_zBuffer;///zBuffer
	DWORD* m_colorBuffer2;//数据缓存
	
	int m_BufferWidth;
	int m_BufferHeight;
	bool m_bAlphaEnable;///alpha混合开启
	bool m_bZTest;//
	FILLMODE m_fillMode;
	int m_fvf;
	//transform
	Matrix m_world;
	Matrix m_view;
	Matrix m_projection;
	//点缓存
	float* m_PointBuffer;
	int m_crtPointIndex;//当前分配的是第几个顶点
	//
	int m_vertexSize;//顶点数据的大小（float数）
	IVertexShader* m_defVS;
	IPixelShader* m_defPS;
	IVertexShader* m_curVS;
	IPixelShader* m_curPS;
	
	//char m_vertexBuffer[VERTEX_BUFFER_SIZE];
	vector<float*> m_vertexLists;//输入的顶点数据，每次调用draw都会被清空
	vector<float*> m_vsVertexLists;//顶点着色器输出的顶点格式
	int m_nVSOutSize;//vs输出的数据大小
	vector<float*> m_psVertexLists;//图元，每次渲染图元都会被清空
	vector<int> m_InterList;//插值项索引表，由vs进行注册
	
};
 
IVertexShader* createDefaultVS(Render* p);
IPixelShader* createDefaultPS(Render* p);

class IVertexShader
{
public:
	virtual void VSStart()=0;	
	virtual float* DoVS(const void* )=0;//根据fvf判断格式,返回的内存需要PS外部删除，注意输出的float首部格式一定是归一化空间的xyzVS
	virtual int GetOutPutSize()=0;//float数
	virtual void VSEnd()=0;
	virtual void NotifyFVFChanged()=0;
 

};
class IPixelShader
{
public:
	virtual void PSStart()=0;
	virtual Color DoPS(void* )=0;//输出颜色
	virtual void PSEnd()=0;
};
class ITexture
{
public:
	
};



END_S3D

#endif