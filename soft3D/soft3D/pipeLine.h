/***************************
 *@brief ��Ⱦ����ʵ�� 
 *
 ***************************/

#ifndef  S3D_PIPELINE_2012622
#define  S3D_PIPELINE_2012622
#define  FLOAT_DEBUG //���һЩfloatֵ�Ա�debug

#include "S3DTypes.h"
#include "S3DX.h"
template <typename T> 
void NumClip(T a,T s, T b)
{
	if(a<s)a=s;
	if(a>b)a=b;
}
/**
 *@brief memset������,����ȫ��
 *@param nCount �����Ķ�������
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
	//��ϵ�Ŀ����ɫ
	Color BlendTo(Color des);
	float r,g,b,a;
};


/**
 *@brief  ���ƽӿڣ��ѿ�������ϵ
 */
class IDevice
{
public:
	virtual void setWindow(int w,int h)=0;

	/**
	 *@brief ����������Ļ������w*h�����أ���ʼ����ԭ�㣬��������
	 *@attention Ч�ʺܵ�,�Ժ�ֱ�����豸������Ƶ�
	 */
	virtual void drawScreen(DWORD* )=0;
	/**
	 *@brief ����ϵ�к���
	 */
	virtual void drawPointBegin()=0;
	virtual void drawPointEnd()=0;
	virtual void drawPoint(int x,int y,float z,float r,float g,float b,float a)=0;//������ɫ���
	virtual void clear(float r,float g,float b,float a,float zValue)=0;//����
	virtual void clear(DWORD col,float zValue)=0;//����
}; 
struct ColorPoint//
{
	int x;
	int y;
	Color color;
};
class IVertexShader;
class IPixelShader;
class IRender// �Ժ󽫽ӿں�������
{
public:

};
/**
 *@brief render�ṩ��shader�Ķ����ڴ���������Բ�
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
		VERTEX_BUFFER_SIZE=1024*1024*64,//64M�Ķ��㻺��,�����ᱨ��
		POINT_BUFFER_COUNT=1024*1024//���㻺�����ڷ�����ʱ��Ҫ�Ķ�������,һ���������
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
	 *@param  vSize �����������ݵ��ֽڴ�С 
	 *@attention ע��buffer������
	 */
	void DrawPrimitiveUP(S3DPRIMITIVETYPE type,void* buffer, int stratIndex,int count,int vSize);//buffer��һ��float����
	
	//������豸
	void Present();
	//��ҪתΪprivate��Ա
	void DrawPixel(int x,int y,DWORD color,float z=0.0f);
	void Blend(vector<ColorPoint> *points);//��ȾͼԪ��ҳ��
	//
	void AddInterItem(int n){m_InterList.push_back(n);}
	
protected:
	inline void DrawPixel(int x,int y,Color color,float z=0.0f);
	//calϵ�У����룺��׼�ռ�,vsVertex �������Ļ�ռ�ĵ㼯��
	void CalTriangleFrag(float* _a, float* _b, float* _c);
	/**
	 *@brief ������뱣֤��������,��׼�ؼ�
	 */
	void CalTriangleFragAssist(const float* _a,const float* _b,const float* _c);
	/**
	 *@brief scs�ռ�,ƽ��������
	 */
	void CalTriangleFragAssistTop(float* _left,float* _right,float* _bottom);//
	/**
	 *@brief scs�ռ䣬ƽ��������
	 */
	void CalTriangleFragAssistBottom(float* _top,float* _left,float* _right);//
	inline void TranslateToSCS(float* p);


	void CalPointFrag(float* _p);
	/**
	 *@brief ����Ϊ��׼�ռ�
	 */
	void CalLineFrag(float* _p1,float* _p2);
	void ResetProperty(float* p);//���ñ�z��������ֵ
	/**
	 *@brief ����Ϊscs�ռ䣬������뱣֤�ܹ�����ֱ��,DDA�㷨
	 */
	void CalLineFragAssist(const float* _p1,const float* _p2);
	/**
	 *@brief  ����ͼԪ��������������ɫ��merge
	 */
	void DrawFragment();

	 

	/**
	 *@brief ���䶥���ڴ�
	 */
	 

	IDevice* m_device;
	Color* m_colorBuffer;///��ʾ����
	float* m_zBuffer;///zBuffer
	DWORD* m_colorBuffer2;//���ݻ���
	
	int m_BufferWidth;
	int m_BufferHeight;
	bool m_bAlphaEnable;///alpha��Ͽ���
	bool m_bZTest;//
	FILLMODE m_fillMode;
	int m_fvf;
	//transform
	Matrix m_world;
	Matrix m_view;
	Matrix m_projection;
	//�㻺��
	float* m_PointBuffer;
	int m_crtPointIndex;//��ǰ������ǵڼ�������
	//
	int m_vertexSize;//�������ݵĴ�С��float����
	IVertexShader* m_defVS;
	IPixelShader* m_defPS;
	IVertexShader* m_curVS;
	IPixelShader* m_curPS;
	
	//char m_vertexBuffer[VERTEX_BUFFER_SIZE];
	vector<float*> m_vertexLists;//����Ķ������ݣ�ÿ�ε���draw���ᱻ���
	vector<float*> m_vsVertexLists;//������ɫ������Ķ����ʽ
	int m_nVSOutSize;//vs��������ݴ�С
	vector<float*> m_psVertexLists;//ͼԪ��ÿ����ȾͼԪ���ᱻ���
	vector<int> m_InterList;//��ֵ����������vs����ע��
	
};
 
IVertexShader* createDefaultVS(Render* p);
IPixelShader* createDefaultPS(Render* p);

class IVertexShader
{
public:
	virtual void VSStart()=0;	
	virtual float* DoVS(const void* )=0;//����fvf�жϸ�ʽ,���ص��ڴ���ҪPS�ⲿɾ����ע�������float�ײ���ʽһ���ǹ�һ���ռ��xyzVS
	virtual int GetOutPutSize()=0;//float��
	virtual void VSEnd()=0;
	virtual void NotifyFVFChanged()=0;
 

};
class IPixelShader
{
public:
	virtual void PSStart()=0;
	virtual Color DoPS(void* )=0;//�����ɫ
	virtual void PSEnd()=0;
};
class ITexture
{
public:
	
};



END_S3D

#endif