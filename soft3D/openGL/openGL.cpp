// openGL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "glut.h"
#include "game.h"
#include <crtdbg.h>  
#include <windows.h>
#include <d3d9.h>
#define  SCREEN_WIDTH 400
#define  SCREEN_HEIGHT 300
#define  USE_DX //使用dx绘点


class GLDevice;
class S3D::IDevice;
S3D::IDevice* g_device;
S3D::Render* g_render;
Game* g_game;


S3D::Color COL_A(0,255,0,255);
S3D::Color COL_B(255,255,0,125);
S3D::Color COL_C(0x9a,0x3d,0x32,0xff);


class GLDevice:public S3D::IDevice
{
public:
	//设置为平行投影，设置视角
	virtual void setWindow(int w,int h)
	{
		glutInitWindowSize(w, h);
		
		m_width=w;
		m_height=h;
		m_rgb=new GLubyte[h*w*3];
		
		glRasterPos2f(-1,-1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,w,0,h,-2,2);
		
	}

	virtual void drawScreen(DWORD* p)
	{
		
		 
		for (int i=0;i<m_width*m_height;i++)
		{
			m_rgb[3*i+0]=p[i]>>24;
			m_rgb[3*i+1]=(p[i]<<8)>>24;
			m_rgb[3*i+2]=(p[i]<<16)>>24;
		}

		glDrawPixels(m_width,m_height,GL_RGB,GL_UNSIGNED_BYTE,m_rgb);
		
		glFlush();
		
	}
	virtual void drawPointBegin()
	{
		glBegin(GL_POINTS);
	}
	virtual void drawPointEnd()
	{
		glEnd();
	}
	//z值用于深度测试
	virtual void drawPoint(int x,int y,float z,float r,float g,float b,float a)
	{
		if(z>=0.0f&&z<=1.0f)
		{
			glColor4f(r,g,b,a);
			glVertex3f(x,y,z);
			
		}
 
	}
	virtual void clear(DWORD col,float zValue)
	{

	}
	virtual void clear(float r,float g,float b,float a,float zValue)
	{
		glClearDepth(1.0f);
		glClearColor(r,g,b,1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}

public:
	GLubyte* m_rgb;
	int m_width;
	int m_height;
};



void myDisplay(void)
{
	static int fps=0;
	static int nTick=-1;
	fps++;
	if(-1==nTick)nTick=GetTickCount();
	else
	{
		int n=GetTickCount();
		if(n-nTick>=1000)
		{
			printf("%d\n",fps*2);
			fps=0;
			nTick=GetTickCount();
		}
	}

 
// 	
 	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	GLubyte bys[300];
	for (int i=0;i<300;i++)
	{
		bys[i]=255;
	}

	glDrawPixels(5,5,GL_RGBA,GL_UNSIGNED_BYTE,bys);
	glFlush();
// 	glBegin(GL_POINTS);
// 	glVertex3f(100,100,1);
// 	glEnd();
	
//  	g_render->Clear(S3D::MakeColor(0xd8,0xbf,0xd8,255),1.0);
//   
// 	g_game->update();
// 	
//   	g_render->Present();
	

}

void myIdle()
{
 
	Sleep(0);
	
	glutPostRedisplay();
}

#pragma region win32相关代码
//直接创建窗口
HDC            hDC=NULL;        // Private GDI Device Context
HGLRC        hRC=NULL;        // Permanent Rendering Context
HWND        hWnd=NULL;        // Holds Our Window Handle
HINSTANCE    hInstance;        // Holds The Instance Of The Application

bool    keys[256];            // Array Used For The Keyboard Routine
bool    active=TRUE;        // Window Active Flag Set To TRUE By Default
bool    fullscreen=TRUE;    // Fullscreen Flag Set To Fullscreen Mode By Default
LRESULT    CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);    // Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)        // Resize And Initialize The GL Window
{
	if (height==0)                                        // Prevent A Divide By Zero By
	{
		height=1;                                        // Making Height Equal One
	}

	glViewport(0,0,width,height);                        // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                    // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
	glLoadIdentity();                                    // Reset The Modelview Matrix
}

int InitGL(GLvoid)                                        // All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                // Black Background
	glClearDepth(1.0f);                                    // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations
	return TRUE;                                        // Initialization Went OK
}

int DrawGLScene(GLvoid)                                    // Here's Where We Do All The Drawing
{
//	glClearColor(1,0,0,1);
// 	g_render->Clear(S3D::MakeColor(0xd8,0xbf,0xd8,255),1.0);
// 	
// 
// 	g_game->update();
	
//	g_render->Present();

	glClearDepth(1);
 	glClearColor(0,1,1,1);
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear Screen And Depth Buffer
// 	GLubyte bys[300];
// 	for (int i=0;i<300;i++)
// 	{
// 		bys[i]=255;
// 	}
// 	
// 	glDrawPixels(5,5,GL_RGBA,GL_UNSIGNED_BYTE,bys);

	//g_render->Present();

	glFinish();
// 	glLoadIdentity();                                    // Reset The Current Modelview Matrix
	return TRUE;                                        // Everything Went OK
}
GLvoid KillGLWindow(GLvoid)                                // Properly Kill The Window
{
	if (fullscreen)                                        // Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);                    // If So Switch Back To The Desktop
		ShowCursor(TRUE);                                // Show Mouse Pointer
	}

	if (hRC)                                            // Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))                    // Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))                        // Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;                                        // Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))                    // Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;                                        // Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))                    // Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;                                        // Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))            // Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;                                    // Set hInstance To NULL
	}
}
 

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint        PixelFormat;            // Holds The Results After Searching For A Match
	WNDCLASS    wc;                        // Windows Class Structure
	DWORD        dwExStyle;                // Window Extended Style
	DWORD        dwStyle;                // Window Style
	RECT        WindowRect;                // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;            // Set Left Value To 0
	WindowRect.right=(long)width;        // Set Right Value To Requested Width
	WindowRect.top=(long)0;                // Set Top Value To 0
	WindowRect.bottom=(long)height;        // Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;            // Set The Global Fullscreen Flag

	hInstance            = GetModuleHandle(NULL);                // Grab An Instance For Our Window
	wc.style            = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;    // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc        = (WNDPROC) WndProc;                    // WndProc Handles Messages
	wc.cbClsExtra        = 0;                                    // No Extra Window Data
	wc.cbWndExtra        = 0;                                    // No Extra Window Data
	wc.hInstance        = hInstance;                            // Set The Instance
	wc.hIcon            = LoadIcon(NULL, IDI_WINLOGO);            // Load The Default Icon
	wc.hCursor            = LoadCursor(NULL, IDC_ARROW);            // Load The Arrow Pointer
	wc.hbrBackground    = NULL;                                    // No Background Required For GL
	wc.lpszMenuName        = NULL;                                    // We Don't Want A Menu
	wc.lpszClassName    = "OpenGL";                                // Set The Class Name

	if (!RegisterClass(&wc))                                    // Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;                                            // Return FALSE
	}

	if (fullscreen)                                                // Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;                                // Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));    // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);        // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth    = width;                // Selected Screen Width
		dmScreenSettings.dmPelsHeight    = height;                // Selected Screen Height
		dmScreenSettings.dmBitsPerPel    = bits;                    // Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card.Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)        
			{
				fullscreen=FALSE;        // Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;                                    // Return FALSE
			}
		}
	}

	if (fullscreen)                                                // Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;                                // Window Extended Style
		dwStyle=WS_POPUP;                                        // Windows Style
		ShowCursor(FALSE);                                        // Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;            // Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;                            // Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);        // Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(    dwExStyle,                            // Extended Style For The Window
		"OpenGL",                            // Class Name
		title,                                // Window Title
		dwStyle |                            // Defined Window Style
		WS_CLIPSIBLINGS |                    // Required Window Style
		WS_CLIPCHILDREN,                    // Required Window Style
		0, 0,                                // Window Position
		WindowRect.right-WindowRect.left,    // Calculate Window Width
		WindowRect.bottom-WindowRect.top,    // Calculate Window Height
		NULL,                                // No Parent Window
		NULL,                                // No Menu
		hInstance,                            // Instance
		NULL)))                                // Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();                                // Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;                                // Return FALSE
	}

	static    PIXELFORMATDESCRIPTOR pfd=                // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),                // Size Of This Pixel Format Descriptor
		1,                                            // Version Number
		PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
		PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
		PFD_DRAW_TO_WINDOW ,                            // Must Support Double Buffering
		PFD_TYPE_RGBA,                                // Request An RGBA Format
		bits,                                        // Select Our Color Depth
		0, 0, 0, 0, 0, 0,                            // Color Bits Ignored
		0,                                            // No Alpha Buffer
		0,                                            // Shift Bit Ignored
		0,                                            // No Accumulation Buffer
		0, 0, 0, 0,                                    // Accumulation Bits Ignored
		16,                                            // 16Bit Z-Buffer (Depth Buffer)  
		0,                                            // No Stencil Buffer
		0,                                            // No Auxiliary Buffer
		PFD_MAIN_PLANE,                                // Main Drawing Layer
		0,                                            // Reserved
		0, 0, 0                                        // Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))                            // Did We Get A Device Context?
	{
		KillGLWindow();                                // Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;                                // Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))    // Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();                                // Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;                                // Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))        // Are We Able To Set The Pixel Format?
	{
		KillGLWindow();                                // Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;                                // Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))                // Are We Able To Get A Rendering Context?
	{
		KillGLWindow();                                // Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;                                // Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))                    // Try To Activate The Rendering Context
	{
		KillGLWindow();                                // Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;                                // Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);                        // Show The Window
	SetForegroundWindow(hWnd);                        // Slightly Higher Priority
	SetFocus(hWnd);                                    // Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);                    // Set Up Our Perspective GL Screen

	if (!InitGL())                                    // Initialize Our Newly Created GL Window
	{
		KillGLWindow();                                // Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;                                // Return FALSE
	}

	return TRUE;                                    // Success
}
LRESULT CALLBACK WndProc(    HWND    hWnd,            // Handle For This Window
						 UINT    uMsg,            // Message For This Window
						 WPARAM    wParam,            // Additional Message Information
						 LPARAM    lParam)            // Additional Message Information
{
	switch (uMsg)                                    // Check For Windows Messages
	{
	case WM_ACTIVATE:                            // Watch For Window Activate Message
		{
			if (!HIWORD(wParam))                    // Check Minimization State
			{
				active=TRUE;                        // Program Is Active
			}
			else
			{
				active=FALSE;                        // Program Is No Longer Active
			}

			return 0;                                // Return To The Message Loop
		}

	case WM_SYSCOMMAND:                            // Intercept System Commands
		{
			switch (wParam)                            // Check System Calls
			{
			case SC_SCREENSAVE:                    // Screensaver Trying To Start?
			case SC_MONITORPOWER:                // Monitor Trying To Enter Powersave?
				return 0;                            // Prevent From Happening
			}
			break;                                    // Exit
		}

	case WM_CLOSE:                                // Did We Receive A Close Message?
		{
			PostQuitMessage(0);                        // Send A Quit Message
			return 0;                                // Jump Back
		}

	case WM_KEYDOWN:                            // Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;                    // If So, Mark It As TRUE
			return 0;                                // Jump Back
		}

	case WM_KEYUP:                                // Has A Key Been Released?
		{
			keys[wParam] = FALSE;                    // If So, Mark It As FALSE
			return 0;                                // Jump Back
		}

	case WM_SIZE:                                // Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;                                // Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
#pragma endregion 
#ifndef USE_DX
 
int WINAPI _tWinMain(    HINSTANCE    hInstance,            // Instance
				   HINSTANCE    hPrevInstance,        // Previous Instance
				   LPSTR        lpCmdLine,            // Command Line Parameters
				   int            nCmdShow)            // Window Show State
{
	MSG        msg;                                    // Windows Message Structure
	BOOL    done=FALSE;                                // Bool Variable To Exit Loop

	//创建console

	AllocConsole();
	freopen("CONIN$","r",stdin);
	freopen("CONOUT$","w",stdout);
	freopen("CONOUT$","w",stderr);
	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;                            // Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's OpenGL Framework",SCREEN_WIDTH,SCREEN_HEIGHT,32,fullscreen))
	{
		return 0;                                    // Quit If Window Was Not Created
	}
	//在这里进行一些初始化
	//glutInitDisplayMode(GLUT_RGBA| GLUT_SINGLE|GLUT_ALPHA|GLUT_DEPTH);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,-2,2);
	g_device=new GLDevice();
	g_render=new S3D::Render(g_device,SCREEN_WIDTH,SCREEN_HEIGHT);
	g_game=new Game(g_render);
	while(!done)                                    // Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))    // Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)                // Have We Received A Quit Message?
			{
				done=TRUE;                            // If So done=TRUE
			}
			else                                    // If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);                // Translate The Message
				DispatchMessage(&msg);                // Dispatch The Message
			}
		}
		else                                        // If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)                                // Program Active?
			{
				if (keys[VK_ESCAPE])                // Was ESC Pressed?
				{
					done=TRUE;                        // ESC Signalled A Quit
				}
				else                                // Not Time To Quit, Update Screen
				{
					static int nFPS=0;
					static int lastTime=0;

					if(lastTime==0)lastTime=GetTickCount();
					if(GetTickCount()-lastTime>=1000)
					{
						printf("fps: %d\n",nFPS);
						nFPS=0;
						lastTime=GetTickCount();
					}else nFPS++;
					DrawGLScene();                    // Draw The Scene
					//SwapBuffers(hDC);                // Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])                        // Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;                    // If So Make Key FALSE
				KillGLWindow();                        // Kill Our Current Window
				fullscreen=!fullscreen;                // Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe's OpenGL Framework",SCREEN_WIDTH,SCREEN_HEIGHT,32,fullscreen))
				{
					return 0;                        // Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();                                    // Kill The Window
	return (msg.wParam);                            // Exit The Program
}
#endif
#ifdef USE_DX
LRESULT CALLBACK WndProc2(    HWND    hWnd,            // Handle For This Window
						 UINT    uMsg,            // Message For This Window
						 WPARAM    wParam,            // Additional Message Information
						 LPARAM    lParam)            // Additional Message Information
{
	switch (uMsg)                                    // Check For Windows Messages
	{
	case WM_ACTIVATE:                            // Watch For Window Activate Message
		{
			if (!HIWORD(wParam))                    // Check Minimization State
			{
				active=TRUE;                        // Program Is Active
			}
			else
			{
				active=FALSE;                        // Program Is No Longer Active
			}

			return 0;                                // Return To The Message Loop
		}

	case WM_SYSCOMMAND:                            // Intercept System Commands
		{
			switch (wParam)                            // Check System Calls
			{
			case SC_SCREENSAVE:                    // Screensaver Trying To Start?
			case SC_MONITORPOWER:                // Monitor Trying To Enter Powersave?
				return 0;                            // Prevent From Happening
			}
			break;                                    // Exit
		}

	case WM_CLOSE:                                // Did We Receive A Close Message?
		{
			PostQuitMessage(0);                        // Send A Quit Message
			return 0;                                // Jump Back
		}

	case WM_KEYDOWN:                            // Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;                    // If So, Mark It As TRUE
			return 0;                                // Jump Back
		}

	case WM_KEYUP:                                // Has A Key Been Released?
		{
			keys[wParam] = FALSE;                    // If So, Mark It As FALSE
			return 0;                                // Jump Back
		}

	case WM_SIZE:                                // Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;                                // Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
IDirect3DDevice9* g_iDXDevice;
struct dxVertex
{
	float x,y,z;
	DWORD col;//argb
};
class DXDevice:public S3D::IDevice
{
private:
#define  VER_BUFFER_SIZE  (16*1024*1024) //128M的顶点内存，足以应付了！
public:
	DXDevice()
	{
		m_pointCount=0;
		int n=VER_BUFFER_SIZE;
		m_Buffer=new dxVertex[n];
	}
	~DXDevice()
	{
		delete []m_Buffer;
	}
	 
	virtual void drawPoint( int x,int y,float z,float r,float g,float b,float a ) 
	{
		if(m_pointCount==VER_BUFFER_SIZE)
		{
			g_iDXDevice->DrawPrimitiveUP(D3DPT_POINTLIST,m_pointCount,m_Buffer,sizeof(dxVertex));
			m_pointCount=0;
			return;
		}else
		{
			m_Buffer[m_pointCount].x=x;
			m_Buffer[m_pointCount].y=y;
			m_Buffer[m_pointCount].z=z;
			m_Buffer[m_pointCount].col=S3D::MakeColor(255*a,255*r,255*g,255*b);
			m_pointCount++;
		}
		 
	}
	
	virtual void drawPointBegin() 
	{
		g_iDXDevice->BeginScene();
	}
	//废弃
	virtual void drawScreen( DWORD* ) 
	{

	}
	virtual void clear(DWORD col,float zValue)
	{
		g_iDXDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, col, zValue, 0);
	}
	virtual void clear( float r,float g,float b,float a,float zValue ) 
	{
		DWORD col= S3D::MakeColor(a*255,r*255,g*255,b*255);
		g_iDXDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, col, zValue, 0);
	}
	//动态改变dx窗口太复杂废弃
	virtual void setWindow( int w,int h ) 
	{
		
	}

	virtual void drawPointEnd() 
	{
		g_iDXDevice->DrawPrimitiveUP(D3DPT_POINTLIST,m_pointCount,m_Buffer,sizeof(dxVertex));
		m_pointCount=0;
		g_iDXDevice->EndScene();
		
	}
 
	dxVertex* m_Buffer;
	int m_pointCount;
};

void initGfx()//dx初始化
{
	g_iDXDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
	g_iDXDevice->LightEnable(0,FALSE);
	g_iDXDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	g_iDXDevice -> SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	g_iDXDevice -> SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	D3DXMATRIX tmp;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	
	D3DXMatrixTranslation(&matProj, 0.5f, 0.5f, 0.0f);
	D3DXMatrixOrthoOffCenterLH(&tmp, 0, (float)SCREEN_WIDTH, 0, (float)SCREEN_HEIGHT, -1.0f, 1.0f);
	D3DXMatrixMultiply(&matProj,&matProj,&tmp);
	
	
	g_iDXDevice->SetTransform(D3DTS_WORLD,&matWorld);
	g_iDXDevice->SetTransform(D3DTS_VIEW,&matView);
	g_iDXDevice->SetTransform(D3DTS_PROJECTION,&matProj);

	g_iDXDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

	g_iDXDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	g_iDXDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
	

	
	g_iDXDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	D3DCAPS9 _d3dcaps;
	g_iDXDevice->GetDeviceCaps(&_d3dcaps);
	printf("最大绘制顶点数%d\n",_d3dcaps.MaxPrimitiveCount);

}
void drawDXScene()
{
	g_game->update();
#pragma  region 测试代码
	
// 	int w=20;
// 	int h=20;
// 	dxVertex* vlist=new dxVertex[w*h];
// 	for(int i=0;i<w*h;i++)
// 	{
// 		int x=i%w+380-1;
// 		int y=i/h+280;
// 		vlist[i].x=x;
// 		vlist[i].y=y;
// 		vlist[i].z=0.0f;
// 		vlist[i].col=S3D::MakeColor(255,0,255,255);
// 
// 	}
// 	dxVertex v2[3];
// 	v2[0].x=0.0;
// 	v2[0].y=299.5;
// 	v2[0].z=0.0f;
// 	v2[0].col=D3DCOLOR_ARGB(255,255,0,0);
// 	v2[1].x=0;
// 	v2[1].y=100;
// 	v2[1].z=0.0f;
// 	v2[1].col=D3DCOLOR_ARGB(255,255,0,0);
// 	v2[2].x=100;
// 	v2[2].y=300-0.5;
// 	v2[2].z=0.0f;
// 	v2[2].col=D3DCOLOR_ARGB(255,255,0,0);
// 
// 
// 
// 	g_iDXDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
// 	g_iDXDevice->BeginScene();
// 	g_iDXDevice->DrawPrimitiveUP(D3DPT_POINTLIST,w*h,vlist,sizeof(dxVertex));
// 	g_iDXDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,3,v2,sizeof(dxVertex));
// 	g_iDXDevice->EndScene();
// 	g_iDXDevice->Present(0,0,0,0);
//	delete []vlist;
#pragma  endregion
	 

	g_iDXDevice->Present(0,0,0,0);
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WNDCLASS		winclass;
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WndProc2;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= GetModuleHandle(0);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL; 
	winclass.lpszClassName	= "soft3D_window";
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	DWORD iWindowType=WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_VISIBLE;
	
	if (!RegisterClass(&winclass)) {
		ASSERT(0);
		return false;
	}

	int nWidth =SCREEN_WIDTH+6;//宽+6  高+28  得到窗口大小
	int nHeiht =SCREEN_HEIGHT+28;
	HWND hWnd = CreateWindowEx(0, "soft3D_window", "foo!", iWindowType,
		100, 200,nWidth,nHeiht,
		0, NULL, GetModuleHandle(0), NULL);
	ShowWindow(hWnd,SW_SHOW);
	//创建console

	AllocConsole();
	freopen("CONIN$","r",stdin);
	freopen("CONOUT$","w",stdout);
	freopen("CONOUT$","w",stderr);
	//dx init
	HRESULT hr=0;
	IDirect3D9* d3d9=0;
	d3d9	=	Direct3DCreate9(D3D_SDK_VERSION);
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT ,D3DDEVTYPE_HAL,&caps);
	int vp	=	D3DCREATE_SOFTWARE_VERTEXPROCESSING;//D3DCREATE_HARDWARE_VERTEXPROCESSING
	D3DPRESENT_PARAMETERS	d3dppW;
	ZeroMemory(&d3dppW, sizeof(d3dppW));
	d3dppW.BackBufferWidth	=SCREEN_WIDTH;
	d3dppW.BackBufferHeight	=SCREEN_HEIGHT;
	d3dppW.BackBufferFormat	=D3DFMT_A8R8G8B8;
	d3dppW.BackBufferCount	=1;
	d3dppW.MultiSampleQuality	=0;
	d3dppW.MultiSampleType	= D3DMULTISAMPLE_NONE ;
	d3dppW.SwapEffect	=D3DSWAPEFFECT_DISCARD;
	d3dppW.hDeviceWindow		=hWnd;
	d3dppW.Windowed			=1;
	d3dppW.EnableAutoDepthStencil	=1;
	d3dppW.AutoDepthStencilFormat		=D3DFMT_D24S8;
	d3dppW.Flags					=0;
	d3dppW.FullScreen_RefreshRateInHz	=D3DPRESENT_RATE_DEFAULT;
	d3dppW.PresentationInterval		 =	D3DPRESENT_INTERVAL_IMMEDIATE;
	 
	if(FAILED(d3d9->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,vp,&d3dppW,&g_iDXDevice)))
	{
		printf("ERROR  CreateDevice\n");
	}else
	{
		printf(" CreateDevice\n");
	}
	RECT clientRec;
	GetClientRect(hWnd,&clientRec);
	printf("客户区大小：%d %d %d %d \n",clientRec.left,clientRec.right,clientRec.bottom,clientRec.top);
	initGfx();
	g_device=new DXDevice();
	g_render=new S3D::Render(g_device,SCREEN_WIDTH,SCREEN_HEIGHT);
	g_game=new Game(g_render);
	//主循环
	MSG msg;
	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			if (msg.message == WM_QUIT)	break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		static int fps=0;
		static int nTick=-1;
		if(nTick==-1)nTick=GetTickCount();
		else 
		{
			if(GetTickCount()-nTick>=500)
			{
				printf("fps:%d\n",fps*2);
				fps=0;
				nTick=GetTickCount();
			}
			else fps++;
		}
		drawDXScene();
	}
	delete g_device;
	delete g_render;
	delete g_game;
}
#endif
 


int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	





	if(timeBeginPeriod(1)==TIMERR_NOERROR);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA| GLUT_SINGLE |GLUT_ALPHA|GLUT_DEPTH);//|GLUT_ALPHA|GLUT_DEPTH

	glutInitWindowPosition(200, 100);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	glutCreateWindow("foo!");
	
	glutDisplayFunc(&myDisplay);

	glutIdleFunc(&myIdle);
	glClearColor(1,0,0,1);
	glClearDepth(1.0f);
	g_device=new GLDevice();
	g_render=new S3D::Render(g_device,SCREEN_WIDTH,SCREEN_HEIGHT);
	g_game=new Game(g_render);
	

	glutMainLoop();
	return 0;
}

