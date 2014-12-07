// the shadow part is copied from Shadow Mapping Tutorial
// his website is http://www.paulsprojects.net

// SceneEditorView.cpp : CSceneEditorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SceneEditor.h"
#endif


#include "SceneEditorDoc.h"
#include "SceneEditorView.h"
#include "DlgAddObj.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSceneEditorView

IMPLEMENT_DYNCREATE(CSceneEditorView, CView)

BEGIN_MESSAGE_MAP(CSceneEditorView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_UPDATE_COMMAND_UI(ID_MENU_ROTATION, &CSceneEditorView::OnUpdateMenuRotation)
	ON_COMMAND(ID_MENU_MOVE, &CSceneEditorView::OnMenuMove)
	ON_UPDATE_COMMAND_UI(ID_MENU_MOVE, &CSceneEditorView::OnUpdateMenuMove)
	ON_COMMAND(ID_MENU_ROTATION, &CSceneEditorView::OnMenuRotation)
	ON_COMMAND(ID_MENU_SELECT, &CSceneEditorView::OnMenuSelect)
	ON_UPDATE_COMMAND_UI(ID_MENU_SELECT, &CSceneEditorView::OnUpdateMenuSelect)
	ON_COMMAND(ID_POLYGONMODE_LINE, &CSceneEditorView::OnPolygonmodeLine)
	ON_COMMAND(ID_POLYGONMODE_FILL, &CSceneEditorView::OnPolygonmodeFill)
	ON_UPDATE_COMMAND_UI(ID_POLYGONMODE_LINE, &CSceneEditorView::OnUpdatePolygonmodeLine)
	ON_UPDATE_COMMAND_UI(ID_POLYGONMODE_FILL, &CSceneEditorView::OnUpdatePolygonmodeFill)
	ON_COMMAND(ID_CMD_ADD, &CSceneEditorView::OnCmdAdd)
	ON_COMMAND(ID_CMD_ADD_LIGHT, &CSceneEditorView::OnCmdAddLight)
	ON_COMMAND(ID_CMD_CAPTURE, &CSceneEditorView::OnCmdCapture)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_CMD_DELETE, &CSceneEditorView::OnCmdDelete)
	ON_COMMAND(ID_CMD_EXPORT_OBJ, &CSceneEditorView::OnCmdExportObj)
	ON_UPDATE_COMMAND_UI(ID_CMD_EXPORT_OBJ, &CSceneEditorView::OnUpdateCmdExportObj)
	ON_COMMAND(ID_CMD_ADJUST_XZ, &CSceneEditorView::OnCmdAdjustXz)
	ON_COMMAND(ID_CMD_ADJUST_YZ, &CSceneEditorView::OnCmdAdjustYz)
	ON_COMMAND(ID_CMD_ADJUST_XY, &CSceneEditorView::OnCmdAdjustXy)
	ON_COMMAND(ID_PROJECTION_PARALLEL, &CSceneEditorView::OnProjectionParallel)
	ON_COMMAND(ID_PROJECTION_PERSPECTIVE, &CSceneEditorView::OnProjectionPerspective)
	ON_UPDATE_COMMAND_UI(ID_PROJECTION_PARALLEL, &CSceneEditorView::OnUpdateProjectionParallel)
	ON_UPDATE_COMMAND_UI(ID_PROJECTION_PERSPECTIVE, &CSceneEditorView::OnUpdateProjectionPerspective)
	ON_COMMAND(ID_ROAMING_MODE, &CSceneEditorView::OnRoamingMode)
	ON_UPDATE_COMMAND_UI(ID_ROAMING_MODE, &CSceneEditorView::OnUpdateRoamingMode)
	ON_COMMAND(ID_SWITCH_GRID, &CSceneEditorView::OnSwitchGrid)
	ON_UPDATE_COMMAND_UI(ID_SWITCH_GRID, &CSceneEditorView::OnUpdateSwitchGrid)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CSceneEditorView 构造/析构







///////////////////////////////////////////////////////////////////////////
//阴影
//Camera & light positions
/*
VECTOR3D cameraPosition(10.0f, 10.0f, 10.0f);
VECTOR3D lightPosition(5.0f, 5.0f, 5.0f);

//Size of shadow map
const int shadowMapSize = 512;

//Textures
GLuint shadowMapTexture;

//window size
int windowWidth, windowHeight;

//Matrices
MATRIX4X4 lightProjectionMatrix, lightViewMatrix;
MATRIX4X4 cameraProjectionMatrix, cameraViewMatrix;
*/
///////////////////////////////////////////////////////////////////////////




void grid()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	//为什么没有效果?
	//深度偏移
	//glDisable(GL_POLYGON_OFFSET_FILL);	//开启面的深度偏移
	glBegin(GL_LINES);
	//x
	glColor3f(1.0, 0, 0);
	glVertex3f(3, 0, 0);
	glVertex3f(0, 0, 0);
	//y
	glColor3f(0, 1.0, 0);
	glVertex3f(0, 3, 0);
	glVertex3f(0, 0, 0);
	//z
	glColor3f(0, 0, 1.0);
	glVertex3f(0, 0, 3);
	glVertex3f(0, 0, 0);


	glEnd();
	/*
	//深度偏移
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 0.0f);
	*/

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	//z轴
	glVertex3f(0, 0, 10);
	glVertex3f(0, 0, -10);
	for (int i = -10; i <= 10; i++)
	{
		glVertex3f(10, i, 0);
		glVertex3f(-10, i, 0);
	}
	for (int i = -10; i <= 10; i++)
	{
		glVertex3f(i, 10, 0);
		glVertex3f(i, -10, 0);
	}
	glEnd();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}




CSceneEditorView::CSceneEditorView()
{
	// TODO:  在此处添加构造代码
	m_rotate_x = -90;
	m_rotate_y = 0;
	m_rotate_z = 0;

	m_move_x = 0;
	m_move_y = 10;
	m_move_z = 0;

	/*透视投影
	m_eye_x = 10;
	m_eye_y = 10;
	m_eye_z = 10;

	m_center_x = 0;
	m_center_y = 0;
	m_center_z = 0;
	*/
	m_view_op = NONE;

	m_lbutton_down = false;

	m_PolygonMode = FILL;

	m_view_op = VIEW_SELECT;
	m_obj_type = CUBE;

	m_need_update_obj_tree = true;
	m_need_update_light_tree = true;

	m_zoom = 100;

	m_selected_is_valid = false;

	m_projection_mode = PARALLEL;
	m_roaming_mode = false;

	m_grid = true;

	m_roaming_speed = 1;
}

CSceneEditorView::~CSceneEditorView()
{
}

BOOL CSceneEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSceneEditorView 绘制

void CSceneEditorView::OnDraw(CDC* pDC)
{
	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	/////////////////////////////////////////////////////////////////////
	//非阴影代码
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (m_PolygonMode == LINE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (m_PolygonMode == FILL)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glLoadIdentity();
	//////////////////////////////////	
	//平行投影
	glRotatef(m_rotate_x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_rotate_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotate_z, 0.0f, 0.0f, 1.0f);
	if (m_projection_mode == PERSPECTIVE)
		glTranslatef(m_move_x, m_move_y, m_move_z);
	if (m_projection_mode == PARALLEL)
		glTranslatef(m_move_x, m_move_y, 0);

	//透视投影
	//////////////////////////////////////////////
	//gluLookAt(m_eye_x, m_eye_y, m_eye_z, m_center_x, m_center_y, m_center_z, 0, 0, 1);
	//////////////////////////////////////////////

	RenderLight();//灯光
	RenderScene();//绘图都放在这

	SwapBuffers(m_pDC->GetSafeHdc());

	if (m_need_update_obj_tree == true)
	{
		CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		if (pFrame != NULL)
			pFrame->update_obj_tree(pDoc->m_obj_list);;
		m_need_update_obj_tree = false;
	}
	if (m_need_update_light_tree == true)
	{
		CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		if (pFrame != NULL)
			pFrame->update_light_tree(pDoc->m_light_list);
		m_need_update_light_tree = false;
	}
	if (m_selected_is_valid == false)
	{
		CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		if (pFrame != NULL)
		{
			pFrame->m_wndProperties.m_wndPropList.RemoveAll();
			pFrame->m_wndProperties.m_wndPropList.Invalidate(FALSE);
		}
	}
	
	/////////////////////////////////////////////////////////////////////
	//阴影代码
	/*

	//First pass - from light's point of view
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(lightProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(lightViewMatrix);

	//Use viewport the same size as the shadow map
	glViewport(0, 0, shadowMapSize, shadowMapSize);

	//Draw back faces into the shadow map
	glCullFace(GL_FRONT);

	//Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);

	//Draw the scene
	RenderScene();

	//Read the depth buffer into the shadow map texture
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowMapSize, shadowMapSize);

	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);




	//2nd pass - Draw from camera's point of view
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(cameraProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(cameraViewMatrix);

	glViewport(0, 0, windowWidth, windowHeight);

	//Use dim light to represent shadowed areas
	glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(lightPosition));
	glLightfv(GL_LIGHT1, GL_AMBIENT, white*0.2f);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white*0.2f);
	glLightfv(GL_LIGHT1, GL_SPECULAR, black);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	RenderScene();



	//3rd pass
	//Draw with bright light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	//Calculate texture matrix for projection
	//This matrix takes us from eye space to the light's clip space
	//It is postmultiplied by the inverse of the current view matrix when specifying texgen
	static MATRIX4X4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f);	//bias from [-1, 1] to [0, 1]
	MATRIX4X4 textureMatrix = biasMatrix*lightProjectionMatrix*lightViewMatrix;

	//Set up texture coordinate generation.
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
	glEnable(GL_TEXTURE_GEN_R);

	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
	glEnable(GL_TEXTURE_GEN_Q);

	//Bind & enable shadow map texture

	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glEnable(GL_TEXTURE_2D);

	//Enable shadow comparison
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

	//Set alpha test to discard false comparisons
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);

	RenderScene();

	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);

	//Set matrices for ortho
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//reset matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glFinish();

	SwapBuffers(m_pDC->GetSafeHdc());


	if (m_need_update_obj_tree == true)
	{
		CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		pFrame->update_obj_tree(pDoc->m_obj_list);
		m_need_update_obj_tree = false;
	}
	if (m_need_update_light_tree == true)
	{
		CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		pFrame->update_light_tree(pDoc->m_light_list);
		m_need_update_light_tree = false;
	}
	*/
	/////////////////////////////////////////////////////////////////////

}

void CSceneEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSceneEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSceneEditorView 诊断

#ifdef _DEBUG
void CSceneEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CSceneEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSceneEditorDoc* CSceneEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSceneEditorDoc)));
	return (CSceneEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CSceneEditorView 消息处理程序


int CSceneEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	SetTimer(1, 20, NULL);

	InitializeOpenGL();//初始化openGL绘图

	return 0;
}


void CSceneEditorView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	//Make the RC non-current
	if (::wglMakeCurrent(0, 0) == FALSE)
	{
		MessageBox(_T("Could not make RC non-current"));
	}

	//Delete the rendering context
	if (::wglDeleteContext(m_hRC) == FALSE)
	{
		MessageBox(_T("Could not delete RC"));
	}
	//Delete the DC
	if (m_pDC)
	{
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;
}


void CSceneEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//非阴影
	
	if (0 >= cx || 0 >= cy)
		return;

	glViewport(0, 0, cx, cy);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (m_projection_mode == PARALLEL)
	{
		/////////////////////////////////////////////////////////////////
		//平行投影
		m_cx = cx;
		m_cy = cy;
		glOrtho(-cx / m_zoom, cx / m_zoom, -cy / m_zoom, cy / m_zoom, -100, 100);
		/////////////////////////////////////////////////////////////////
	}
	else
	{
		//透视投影
		GLdouble aspect_ratio; // width/height ratio
		aspect_ratio = (GLdouble)cx / (GLdouble)cy;
		gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);//画三维
	}

	glMatrixMode(GL_MODELVIEW);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//阴影代码
	/*
	windowWidth = cx, windowHeight = cy;

	//Update the camera's projection matrix
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0f, (float)windowWidth / windowHeight, 1.0f, 100.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);
	glPopMatrix();
	*/
}


BOOL CSceneEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return true;
	//return CView::OnEraseBkgnd(pDC);
}

BOOL CSceneEditorView::InitializeOpenGL()
{
	//Get a DC for the Client Area
	m_pDC = new CClientDC(this);
	//Failure to Get DC
	if (m_pDC == NULL)
	{
		//::MessageBox("Error Obtaining DC");
		return FALSE;
	}
	//Failure to set the pixel format
	if (!SetupPixelFormat())
	{
		return FALSE;
	}
	//Create Rendering Context
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//Failure to Create Rendering Context
	if (m_hRC == 0)
	{
		//	MessageBox("Error Creating RC");
		return FALSE;
	}
	//Make the RC Current
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		//	MessageBox("Error making RC Current");
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////////
	//非阴影
	//Specify Black as the clear color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Specify the back of the buffer as clear depth
	glClearDepth(1.0f);
	//Enable Depth Testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	//自动计算法向量
	glEnable(GL_AUTO_NORMAL);
	//合成光照和纹理
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	/////////////////////////////////////////////////////////////////////
	//阴影
	/*
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Shading states
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	//We use glScale when drawing the scene
	glEnable(GL_NORMALIZE);

	//Create the shadow map texture
	glGenTextures(1, &shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glTexImage2D(	GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize, shadowMapSize, 0,
	GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//Use the color as the ambient and diffuse material
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//White specular material color, shininess 16
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

	//Calculate & save matrices
	glPushMatrix();

	glLoadIdentity();
	gluPerspective(45.0f, (float)windowWidth/windowHeight, 1.0f, 100.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);

	glLoadIdentity();
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
	0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);

	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);

	glLoadIdentity();
	gluLookAt(	lightPosition.x, lightPosition.y, lightPosition.z,
	0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);

	glPopMatrix();
	*/
	/////////////////////////////////////////////////////////////////////

	return TRUE;

}

BOOL CSceneEditorView::SetupPixelFormat()
{
	
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,                // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)
	{
		return FALSE;
	}
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

void CSceneEditorView::RenderScene()
{
	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	glPushMatrix();
	//////////////////////////////////////////////////////
	//阴影
	/*
	glRotatef(-120, 1, 1, 1);
	glRotatef(m_rotate_x, 1.0f, 1.0f, 1.0f);
	glRotatef(m_rotate_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotate_z, 0.0f, 0.0f, 1.0f);
	glTranslatef(m_move_x, m_move_y, 0);
	*/
	
	//////////////////////////////////////////////////////
	if (m_grid==true)
		grid();
	
	if (m_PolygonMode == LINE)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);

	auto v = pDoc->m_obj_list;
	for (auto i = v.begin(); i != v.end(); i++)
	{
		(*i)->draw();
	}
	glEnable(GL_LIGHTING);

	MarkSelected();

	glFlush();
	glPopMatrix();
}
void CSceneEditorView::MarkSelected()
{
	if (m_selected_is_valid == true)
	{
		if (m_cur_type == DRAW_OBJ)
		{
			m_cur_obj->m_obj->mark();
		}
		else if (m_cur_type == DRAW_LIGHT)
		{
			m_cur_light->mark();
		}
	}
}

void CSceneEditorView::RenderLight()
{
	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	glShadeModel(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	auto list = pDoc->m_light_list;
	int count = 0;
	for (auto i = list.begin(); i != list.end(); i++)
	{
		(*i)->draw_light(count);
		count++;
	}
}

void CSceneEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_lbutton_down = true;
	m_temp_x = point.x;
	m_temp_y = point.y;
	CView::OnLButtonDown(nFlags, point);
}


void CSceneEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_lbutton_down = false;
	CView::OnLButtonUp(nFlags, point);
}

int CSceneEditorView::sign(GLfloat x)
{
	if (x < 0.0)
		return -1;
	else
		return 1;
}
void CSceneEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nFlags&MK_LBUTTON)
	{
		float theta_z = m_rotate_z / 180.0*M_PI;
		float theta_x = (-m_rotate_x - 90) / 180.0*M_PI;
		int delta_x = point.x - m_temp_x;
		int delta_y = point.y - m_temp_y;
		switch (m_view_op)
		{
		case NONE:
			break;
		case VIEW_ROTATE:
			m_rotate_z = (m_rotate_z + delta_x) % 360;
			if (nFlags&MK_CONTROL)
				m_rotate_y = (m_rotate_y + delta_y) % 360;
			else
				m_rotate_x = (m_rotate_x + delta_y) % 360;
			break;
		case VIEW_MOVE:
			m_move_x = m_move_x + 0.02*(delta_x*cos(theta_z) - delta_y*sin(theta_z));
			m_move_y = m_move_y - 0.02*(delta_x*sin(theta_z) + delta_y*cos(theta_z));
			break;
		case VIEW_SELECT:
			break;
		default:
			break;
		}
		m_temp_x = point.x;
		m_temp_y = point.y;
		Invalidate(FALSE);
		/*透视投影
		GLfloat x = m_eye_x - m_center_x;
		GLfloat y = m_eye_y - m_center_y;
		GLfloat z = m_eye_z - m_center_z;
		GLfloat r = sqrt(x*x + y*y);
		GLfloat R = sqrt(x*x + y*y + z*z);
		GLfloat t_r;
		GLfloat t_R;
		GLfloat theta = atan(x / y);
		int dx = point.x - m_temp_x;
		int dy = point.y - m_temp_y;
		GLfloat delta_theta = dx*0.1 / r;
		switch (m_view_op)
		{
		case NONE:
		break;
		case VIEW_ROTATE:
		x += dx*0.05*y / r;
		y -= dx*0.05*x / r;
		t_r = sqrt(x*x + y*y);
		x = x / t_r*r;
		y = y / t_r*r;
		if (!((dy > 0 && z > 17.2) || (dy < 0 && z < -17.2)))
		{
		z += dy*0.05*r;
		x = x - z*dy*0.05*x / r;
		y = y - z*dy*0.05*y / r;
		t_R = sqrt(x*x + y*y + z*z);
		x = x / t_R*R;
		y = y / t_R*R;
		z = z / t_R*R;
		}
		m_eye_x = x + m_center_x;
		m_eye_y = y + m_center_y;
		m_eye_z = z + m_center_z;
		break;
		case VIEW_MOVE:
		break;
		default:
		break;
		}
		m_temp_x = point.x;
		m_temp_y = point.y;
		Invalidate(FALSE);
		*/
	}
	CView::OnMouseMove(nFlags, point);
}


void CSceneEditorView::OnUpdateMenuRotation(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_view_op == VIEW_ROTATE);
}


void CSceneEditorView::OnUpdateMenuMove(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_view_op == VIEW_MOVE);
}


void CSceneEditorView::OnUpdateMenuSelect(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_view_op == VIEW_SELECT);
}


void CSceneEditorView::OnMenuRotation()
{
	// TODO:  在此添加命令处理程序代码
	m_view_op = VIEW_ROTATE;
}


void CSceneEditorView::OnMenuMove()
{
	// TODO:  在此添加命令处理程序代码
	m_view_op = VIEW_MOVE;
}


void CSceneEditorView::OnMenuSelect()
{
	// TODO:  在此添加命令处理程序代码
	m_view_op = VIEW_SELECT;
}




void CSceneEditorView::OnPolygonmodeLine()
{
	// TODO:  在此添加命令处理程序代码
	m_PolygonMode = LINE;
	Invalidate(FALSE);
}


void CSceneEditorView::OnPolygonmodeFill()
{
	// TODO:  在此添加命令处理程序代码
	m_PolygonMode = FILL;
	Invalidate(FALSE);
}


void CSceneEditorView::OnUpdatePolygonmodeLine(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_PolygonMode == LINE);
}


void CSceneEditorView::OnUpdatePolygonmodeFill(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_PolygonMode == FILL);
}



void CSceneEditorView::OnCmdAdd()
{
	// TODO:  在此添加命令处理程序代码
	CDlgAddObj dlg;
	dlg.m_obj_type = m_obj_type;
	if (dlg.DoModal() == IDOK)
	{
		m_obj_type = dlg.m_obj_type;
		m_view_op = VIEW_SELECT;
		if (m_obj_type == OBJ_FILE)
			add_obj(dlg.m_add_obj_name, dlg.m_objfile_name);
		else
			add_obj(dlg.m_obj_type, dlg.m_add_obj_name);

	}
	m_need_update_obj_tree = true;
}

CDocObj* CSceneEditorView::add_obj(OBJ_TYPE type, CString name)
{
	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return NULL;
	CDocObj* pObj = pDoc->add_obj(type, name);
	Invalidate(FALSE);
	return pObj;
}

CDocObj* CSceneEditorView::add_obj(CString name, CString file_name)
{
	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return NULL;
	CDocObj* pObj = pDoc->add_obj(name, file_name);
	Invalidate(FALSE);
	return pObj;
}



void CSceneEditorView::OnCmdAddLight()
{
	// TODO:  在此添加命令处理程序代码

	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_light_list.size() == 8)
	{
		MessageBox(_T("最多只能有8个灯光!"));
		return;
	}
	else
	{
		m_view_op = VIEW_SELECT;
		add_light();
		m_need_update_light_tree = true;
	}
}

CLight* CSceneEditorView::add_light()
{
	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return NULL;
	CLight* pLight = pDoc->add_light();
	Invalidate(FALSE);
	return pLight;
}

//////////////////////////////////////////////////////////////////////
/*
* copy from http://blog.csdn.net/visualeleven/article/details/6206715
* 调用方法
* HWND hWnd = ::FindWindow(NULL, _T("XXX"));
* if(hWnd)
* {
* SaveHwndToBmpFile(hWnd, _T("F://12.bmp"));
* }
* this function can not work in dwm (maybe), causing black bmp file. 
* PrintWindow << suspector
*/
//////////////////////////////////////////////////////////////////////
void CSceneEditorView::SaveHwndToBmpFile(HWND hWnd, LPCTSTR lpszPath)
{	
	HDC hDC = ::GetWindowDC(hWnd);
	ASSERT(hDC);

	HDC hMemDC = ::CreateCompatibleDC(hDC);
	ASSERT(hMemDC);

	RECT rc;
	::GetWindowRect(hWnd, &rc);

	HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, rc.right - rc.left, rc.bottom - rc.top);
	ASSERT(hBitmap);

	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC, hBitmap);
	::PrintWindow(hWnd, hMemDC, 0);



	BITMAP bitmap = { 0 };
	::GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	BITMAPINFOHEADER bi = { 0 };
	BITMAPFILEHEADER bf = { 0 };

	CONST int nBitCount = 24;
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = nBitCount;
	bi.biCompression = BI_RGB;
	DWORD dwSize = ((bitmap.bmWidth * nBitCount + 31) / 32) * 4 * bitmap.bmHeight;

	HANDLE hDib = GlobalAlloc(GHND, dwSize + sizeof(BITMAPINFOHEADER));
	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	::GetDIBits(hMemDC, hBitmap, 0, bitmap.bmHeight, (BYTE*)lpbi + sizeof(BITMAPINFOHEADER), (BITMAPINFO*)lpbi, DIB_RGB_COLORS);

	try
	{
		CFile file;
		file.Open(lpszPath, CFile::modeCreate | CFile::modeWrite);
		bf.bfType = 0x4d42;
		dwSize += sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		bf.bfSize = dwSize;
		bf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		file.Write((BYTE*)&bf, sizeof(BITMAPFILEHEADER));
		file.Write((BYTE*)lpbi, dwSize);
		file.Close();
	}
	catch (CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}

	GlobalUnlock(hDib);
	GlobalFree(hDib);

	::SelectObject(hMemDC, hOldBmp);
	::DeleteObject(hBitmap);
	::DeleteObject(hMemDC);
	::ReleaseDC(hWnd, hDC);
	

}
//////////////////////////////////////////////////////////////////////

void CSceneEditorView::OnCmdCapture()
{
	// TODO:  在此添加命令处理程序代码

	CFileDialog dlg(FALSE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("bmp Files (*.bmp)|*.bmp|"),
		NULL);
	
	if (dlg.DoModal() == IDOK)
	{
		CString file_name = dlg.GetPathName();
		HWND hWnd = m_hWnd;
		if (hWnd)
		{
			SaveHwndToBmpFile(hWnd, file_name);
		}
	}
}


BOOL CSceneEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_projection_mode == PARALLEL)
	{
		m_zoom += zDelta / 10.0;
		if (m_zoom < 5)
			m_zoom -= zDelta / 10.0;
		if (m_zoom > 1000)
			m_zoom -= zDelta / 10.0;
	}
	else
	{
		//m_move_z += zDelta / 50.0;

		float theta_z = m_rotate_z / 180.0*M_PI;
		float theta_x = (-m_rotate_x - 90) / 180.0*M_PI;
		m_move_x -= sin(theta_z)*cos(theta_x)*zDelta / 50.0;
		m_move_y -= cos(theta_z)*cos(theta_x)*zDelta / 50.0;
		m_move_z -= sin(theta_x)*zDelta / 50.0;
	}
	//哎，最后只能这样用。到底怎么发WM_SIZE消息啊
	OnSize(0, m_cx, m_cy);
	Invalidate(FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CSceneEditorView::OnCmdDelete()
{
	// TODO:  在此添加命令处理程序代码
	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pFrame->remove_all_prop_list();
	if (m_cur_type == DRAW_OBJ)
	{
		for (auto i = pDoc->m_obj_list.begin(); i != pDoc->m_obj_list.end(); i++)
		{
			if (*i == m_cur_obj)
			{
				(*i)->~CDocObj();
				pDoc->m_obj_list.remove(*i);
				m_selected_is_valid = false;
				break;
			}
		}
		m_need_update_obj_tree = true;
	}
	else if (m_cur_type == DRAW_LIGHT)
	{
		auto list = pDoc->m_light_list;
		for (auto i = pDoc->m_light_list.begin(); i != pDoc->m_light_list.end(); i++)
		{
			if (*i == m_cur_light)
			{
				(*i)->~CLight();
				pDoc->m_light_list.remove(*i);
				m_selected_is_valid = false;
				break;
			}
		}
		m_need_update_light_tree = true;
	}
	Invalidate(FALSE);
}


void CSceneEditorView::OnCmdExportObj()
{
	// TODO:  在此添加命令处理程序代码
	CFileDialog dlg(FALSE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		_T("obj"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("obj Files (*.obj)|*.obj|"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		CString file_name = dlg.GetPathName();
		m_cur_obj->exportobj(file_name);
	}
}


void CSceneEditorView::OnUpdateCmdExportObj(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_selected_is_valid == true && m_cur_type == DRAW_OBJ && m_obj_type == OBJ_FILE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}


void CSceneEditorView::OnCmdAdjustXz()
{
	// TODO:  在此添加命令处理程序代码
	m_rotate_x = -90;
	m_rotate_y = 0;
	m_rotate_z = 0;

	m_move_x = 0;
	m_move_y = 10;
	m_move_z = 0;
	Invalidate(FALSE);
}


void CSceneEditorView::OnCmdAdjustYz()
{
	// TODO:  在此添加命令处理程序代码
	m_rotate_x = -90;
	m_rotate_y = 0;
	m_rotate_z = 90;

	m_move_x = 10;
	m_move_y = 0;
	m_move_z = 0;
	Invalidate(FALSE);
}


void CSceneEditorView::OnCmdAdjustXy()
{
	// TODO:  在此添加命令处理程序代码
	m_rotate_x = 0;
	m_rotate_y = 0;
	m_rotate_z = 0;

	m_move_x = 0;
	m_move_y = 0;
	m_move_z = -10;
	Invalidate(FALSE);
}


void CSceneEditorView::OnProjectionParallel()
{
	// TODO:  在此添加命令处理程序代码
	m_projection_mode = PARALLEL;
	m_roaming_mode = false;
	OnSize(0, m_cx, m_cy);
	Invalidate(FALSE);
}


void CSceneEditorView::OnProjectionPerspective()
{
	// TODO:  在此添加命令处理程序代码
	m_projection_mode = PERSPECTIVE;
	m_roaming_mode = false;
	OnSize(0, m_cx, m_cy);
	Invalidate(FALSE);
}


void CSceneEditorView::OnUpdateProjectionParallel(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_projection_mode == PARALLEL);
}


void CSceneEditorView::OnUpdateProjectionPerspective(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_projection_mode == PERSPECTIVE);
}


void CSceneEditorView::OnRoamingMode()
{
	// TODO:  在此添加命令处理程序代码
	m_projection_mode = PERSPECTIVE;
	m_roaming_mode = !m_roaming_mode;
	OnSize(0, m_cx, m_cy);
	Invalidate(FALSE);
}


void CSceneEditorView::OnUpdateRoamingMode(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_projection_mode == PERSPECTIVE && m_roaming_mode == true);
}



void CSceneEditorView::OnSwitchGrid()
{
	// TODO:  在此添加命令处理程序代码
	m_grid = !m_grid;
	Invalidate(FALSE);
}


void CSceneEditorView::OnUpdateSwitchGrid(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_grid == true);
}


void CSceneEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//esc
	if (m_roaming_mode == true)
	{
		float theta_z = m_rotate_z / 180.0*M_PI;
		float theta_x = (-m_rotate_x - 90) / 180.0*M_PI;
		if (nChar == 'W')
		{
			m_move_x -= sin(theta_z)*cos(theta_x)*m_roaming_speed;
			m_move_y -= cos(theta_z)*cos(theta_x)*m_roaming_speed;
			m_move_z -= sin(theta_x)*m_roaming_speed;
		}
		if (nChar == 'S')
		{
			m_move_x += sin(theta_z)*cos(theta_x)*m_roaming_speed;
			m_move_y += cos(theta_z)*cos(theta_x)*m_roaming_speed;
			m_move_z += sin(theta_x)*m_roaming_speed;
		}
		if (nChar == 'A')
		{
			m_move_x += cos(theta_z)*m_roaming_speed;
			m_move_y -= sin(theta_z)*m_roaming_speed;
		}
		if (nChar == 'D')
		{
			m_move_x -= cos(theta_z)*m_roaming_speed;
			m_move_y += sin(theta_z)*m_roaming_speed;
		}
		if (nChar == ' ')
		{
			m_move_z -= m_roaming_speed;
		}
		if (nChar == 'C')
		{
			m_move_z += m_roaming_speed;
		}
		if (nChar == VK_ESCAPE)
		{
			m_projection_mode = PERSPECTIVE;
			m_roaming_mode = false;
			OnSize(0, m_cx, m_cy);
		}
	}
	Invalidate(FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSceneEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CSceneEditorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		//Invalidate(FALSE);
	}
	CView::OnTimer(nIDEvent);
}
