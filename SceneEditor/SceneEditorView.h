
// SceneEditorView.h : CSceneEditorView 类的接口
//

#pragma once

enum VIEW_OP
{
	NONE,
	VIEW_ROTATE,
	VIEW_MOVE,
	
};

class CSceneEditorView : public CView
{
public:
	HGLRC m_hRC;    //Rendering Context着色描述表
	CDC* m_pDC;        //Device Context设备描述表
	BOOL InitializeOpenGL();    //Initialize OpenGL
	BOOL SetupPixelFormat();    //Set up the Pixel Format
	void RenderScene();            //Render the Scene
	//视图
	bool m_lbutton_down;
	GLfloat m_eye_x;
	GLfloat m_eye_y;
	GLfloat m_eye_z;

	GLfloat m_center_x;
	GLfloat m_center_y;
	GLfloat m_center_z;
	VIEW_OP m_view_op;

	int m_temp_x;
	int m_temp_y;

protected: // 仅从序列化创建
	CSceneEditorView();
	DECLARE_DYNCREATE(CSceneEditorView)

// 特性
public:
	CSceneEditorDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CSceneEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnUpdateMenuRotation(CCmdUI *pCmdUI);
	afx_msg void OnMenuMove();
	afx_msg void OnUpdateMenuMove(CCmdUI *pCmdUI);
	afx_msg void OnMenuRotation();
	afx_msg void OnMenuSelect();
	afx_msg void OnUpdateMenuSelect(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // SceneEditorView.cpp 中的调试版本
inline CSceneEditorDoc* CSceneEditorView::GetDocument() const
   { return reinterpret_cast<CSceneEditorDoc*>(m_pDocument); }
#endif

