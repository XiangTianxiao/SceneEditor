
// SceneEditorDoc.cpp : CSceneEditorDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SceneEditor.h"
#endif

#include "SceneEditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSceneEditorDoc

IMPLEMENT_DYNCREATE(CSceneEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CSceneEditorDoc, CDocument)
END_MESSAGE_MAP()


// CSceneEditorDoc 构造/析构

CSceneEditorDoc::CSceneEditorDoc()
{
	// TODO:  在此添加一次性构造代码
	{
		CDocObj* pObj = new CDocObj(L"圆柱", CUBE);
		m_obj_list.push_back(pObj);
	}
	
	{
		CDocObj* pObj = new CDocObj(L"棱柱", PRISM);
		pObj->m_obj->m_x = 3.0;
		m_obj_list.push_back(pObj);
	}
	
	{
		//cube 不过还不能使用，因为使用了glut库
		//CDocObj* pObj = new CDocObj(L"圆柱", CYLINDER);
		//m_obj_list.push_back(pObj);
	}
}

CSceneEditorDoc::~CSceneEditorDoc()
{
}

BOOL CSceneEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CSceneEditorDoc 序列化

void CSceneEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSceneEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CSceneEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSceneEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSceneEditorDoc 诊断

#ifdef _DEBUG
void CSceneEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSceneEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSceneEditorDoc 命令

CDocObj* CSceneEditorDoc::draw_property(CString name, CPropertiesWnd* pProperties)
{
	for (auto i = m_obj_list.begin(); i != m_obj_list.end(); i++)
	{
		if ((*i)->m_name == name)
		{
			pProperties->m_pObj = *i;
			(*i)->draw_property(&pProperties->m_wndPropList);
			return *i;
		}
	}
	throw CString("CDocObj* CSceneEditorDoc::draw_property(CString name, CPropertiesWnd* pProperties)");
}

CDocObj* CSceneEditorDoc::add_obj(OBJ_TYPE type, CString name)
{
	CDocObj* pObj = new CDocObj(case_name_overlap(name, 0), type);
	if (pObj == NULL)
		throw CString("CDocObj* CSceneEditorDoc::add_obj(OBJ_TYPE type, CString name)");

	m_obj_list.push_back(pObj);
	return pObj;
}

CDocObj* CSceneEditorDoc::add_obj(CString name, CString file_name)
{
	CDocObj* pObj = new CDocObj(case_name_overlap(name, 0), file_name);
	if (pObj == NULL)
		throw CString("CDocObj* CSceneEditorDoc::add_obj(CString name, CString file_name)");

	m_obj_list.push_back(pObj);
	return pObj;
}

CString CSceneEditorDoc::case_name_overlap(CString name, int num)
{
	CString return_name;
	CString t_name;
	if (num == 0)
		t_name = name;
	else
		t_name.Format(_T("%s_%d"), name, num);

	for (auto i = m_obj_list.begin(); i != m_obj_list.end(); i++)
	{
		if ((*i)->m_name == t_name)
			return return_name = case_name_overlap(name, num + 1);
	}
	return t_name;
}