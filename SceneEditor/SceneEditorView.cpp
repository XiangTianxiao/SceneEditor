
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
END_MESSAGE_MAP()

// CSceneEditorView 构造/析构

CSceneEditorView::CSceneEditorView()
{
	// TODO:  在此处添加构造代码
	m_eye_x = 10;
	m_eye_y = 10;
	m_eye_z = 10;

	m_center_x = 0;
	m_center_y = 0;
	m_center_z = 0;

	m_view_op = NONE;

	m_lbutton_down = false;

	m_PolygonMode = FILL;

	m_view_op = VIEW_SELECT;
	m_obj_type = CUBE;

	m_need_update_obj_tree = true;
	m_need_update_light_tree = true;
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

void CSceneEditorView::OnDraw(CDC* /*pDC*/)
{
	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (m_PolygonMode == LINE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (m_PolygonMode == FILL)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glLoadIdentity();
	
	gluLookAt(m_eye_x, m_eye_y, m_eye_z, m_center_x, m_center_y, m_center_z, 0, 0, 1);

	RenderLight();
	RenderScene();//绘图都放在这

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
	if (0 >= cx || 0 >= cy)
		return;

	glViewport(0, 0, cx, cy);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLdouble aspect_ratio; // width/height ratio
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;
	
	gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);//画三维

	glMatrixMode(GL_MODELVIEW);
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
	//Specify Black as the clear color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Specify the back of the buffer as clear depth
	glClearDepth(1.0f);
	//Enable Depth Testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
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
		16,                             // 16-bit z-buffer
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


	auto v = pDoc->m_obj_list;

	for (auto i = v.begin(); i != v.end(); i++)
	{
		(*i)->draw();
	}

	glFlush();
}

void CSceneEditorView::RenderLight()
{
	CSceneEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	glEnable(GL_LIGHTING);
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
	if (m_lbutton_down == true)
	{
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