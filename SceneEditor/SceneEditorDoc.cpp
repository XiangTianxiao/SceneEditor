
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
	ON_COMMAND(ID_FILE_MY_OPEN, &CSceneEditorDoc::OnFileMyOpen)
	ON_COMMAND(ID_FILE_MY_SAVE, &CSceneEditorDoc::OnFileMySave)
END_MESSAGE_MAP()


// CSceneEditorDoc 构造/析构

CSceneEditorDoc::CSceneEditorDoc()
{
	// TODO:  在此添加一次性构造代码
	/*
	{
		CDocObj* pObj = new CDocObj(L"圆柱", CUBE);
		m_obj_list.push_back(pObj);
	}
	
	{
		CDocObj* pObj = new CDocObj(L"棱柱", PRISM);
		pObj->m_obj->m_x = 3.0;
		m_obj_list.push_back(pObj);
	}
	*/
	{
		CLight* pLight = new CLight();
		pLight->m_name = CString("light_0");
		pLight->m_light_pos[0] = 0;
		pLight->m_light_pos[1] = 0;
		pLight->m_light_pos[2] = 5;
		m_light_list.push_back(pLight);
	}
	{
		CLight* pLight = new CLight();
		pLight->m_name = CString("light_1");
		pLight->m_light_pos[0] = 0;
		pLight->m_light_pos[1] = 0;
		pLight->m_light_pos[2] = -5;
		m_light_list.push_back(pLight);
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
	m_light_list.clear();
	m_obj_list.clear();
	CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if (pFrame == NULL)
		return TRUE;
	CSceneEditorView* pView = (CSceneEditorView*)pFrame->GetActiveView();
	if (pView == NULL)
		return TRUE;
	pFrame->remove_all_prop_list();
	pView->m_selected_is_valid = false;
	pView->m_need_update_light_tree = true;
	pView->m_need_update_obj_tree = true;
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
			pProperties->m_type = DRAW_OBJ;
			(*i)->draw_property(&pProperties->m_wndPropList);
			return *i;
		}
	}
	throw CString("CDocObj* CSceneEditorDoc::draw_property(CString name, CPropertiesWnd* pProperties)");

}

CLight* CSceneEditorDoc::draw_light_property(CString name, CPropertiesWnd* pProperties)
{
	for (auto i = m_light_list.begin(); i != m_light_list.end(); i++)
	{
		if ((*i)->m_name == name)
		{
			pProperties->m_pLight = *i;
			pProperties->m_type = DRAW_LIGHT;
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

CLight* CSceneEditorDoc::add_light()
{
	CLight* pLight = new CLight();
	if (pLight == NULL)
		throw CString("CLight* CSceneEditorDoc::add_light()");
	/////////////////////////////////////////////////
	//名字
	CString newname;
	if (m_light_list.size() == 0)
		newname = _T("light_0");
	else
	{
		auto pLastLight = m_light_list.rbegin();//最后一个
		CString lastname = (*pLastLight)->m_name;
		int find = lastname.Find(_T('_'));
		lastname = lastname.Right(lastname.GetLength() - find - 1);
		int a = _ttoi(lastname);
		newname.Format(_T("light_%d"), a + 1);
	}
	pLight->m_name = newname;
	/////////////////////////////////////////////////
	m_light_list.push_back(pLight);
	return pLight;
}

void CSceneEditorDoc::save_file(string filename)
{
	ofstream file;
	file.open(filename);
	if (!file)
		throw "void CSceneEditorDoc::save_file(string filename)";

	for (auto i = m_obj_list.begin(); i != m_obj_list.end(); i++)
	{
		switch ((*i)->m_type)
		{
		case CUBE:
			file << *((CCube*)((*i)->m_obj));
			break;
		case CYLINDER:
			file << *((CCylinder*)((*i)->m_obj));
			break;
		case PRISM:
			file << *((CPrism*)((*i)->m_obj));
			break;
		case SPHERE:
			file << *((CSphere*)((*i)->m_obj));
			break;
		case OBJ_FILE:
			file << *((CObjFile*)((*i)->m_obj));
			break;
		default:
			break;
		}
	}
	for (auto i = m_light_list.begin(); i != m_light_list.end(); i++)
	{
		file << *(*i);
	}


	file.close();
}
void CSceneEditorDoc::open_file(string filename)
{
	ifstream file;
	file.open(filename);
	if (!file)
		throw "void CSceneEditorDoc::open_file(string filename)";

	string temp;
	file >> temp;
	while (file.eof() == false)
	{
		if (temp == "<light>")
		{
			CLight* light;
			light = new CLight(file);
			m_light_list.push_back(light);
		}
		else
		{
			CObj* obj;
			CDocObj* pDocObj = new CDocObj();
			OBJ_TYPE type;
			if (temp == "<cube>")
			{
				obj = new CCube(file);
				type = CUBE;
			}
			else if (temp == "<cylinder>")
			{
				obj = new CCylinder(file);
				type = CYLINDER;
			}
			else if (temp == "<objfile>")
			{
				obj = new CObjFile(file);
				type = OBJ_FILE;
			}
			else if (temp == "<prism>")
			{
				obj = new CPrism(file);
				type = PRISM;
			}
			else if (temp == "<sphere>")
			{
				obj = new CSphere(file);
				type = SPHERE;
			}
			else
				throw "void CSceneEditorDoc::open_file(string filename)";
			CString name = case_name_overlap(CString(temp.c_str()));
			pDocObj->m_name = name;
			pDocObj->m_type = type;
			pDocObj->m_obj = obj;
			m_obj_list.push_back(pDocObj);
		}
		file >> temp;
	}
	CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CSceneEditorView* pView = (CSceneEditorView*)pFrame->GetActiveView();
	pView->m_need_update_light_tree = true;
	pView->m_need_update_obj_tree = true;
}

void CSceneEditorDoc::OnFileMyOpen()
{
	// TODO:  在此添加命令处理程序代码
	CString c_filename;
	string filename;
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		_T("3se"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("3d scene editor Files (*.3se)|*.3se|"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		c_filename = dlg.GetPathName(); //文件名保存在了FilePathName里
		string filename = cstring_to_string(c_filename);
		open_file(filename);
	}
}


void CSceneEditorDoc::OnFileMySave()
{
	// TODO:  在此添加命令处理程序代码
	CString c_filename;
	string filename;
	CFileDialog dlg(FALSE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		_T("3se"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("3d scene editor Files (*.3se)|*.3se|"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		c_filename = dlg.GetPathName(); //文件名保存在了FilePathName里
		string filename = cstring_to_string(c_filename);
		save_file(filename);
	}
}

string cstring_to_string(CString cstring)
{
	//M$，良心大大地坏了
	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	int n = cstring.GetLength();    // n = 14, len = 18
	//获取宽字节字符的大小，大小是按字节计算的
	int len = WideCharToMultiByte(CP_ACP, 0, cstring, cstring.GetLength(), NULL, 0, NULL, NULL);
	//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
	char * pFileName = new char[len + 2];  //以字节为单位
	//宽字节编码转换成多字节编码
	WideCharToMultiByte(CP_ACP, 0, cstring, cstring.GetLength(), pFileName, len, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, cstring, cstring.GetLength() + 1, pFileName, len + 1, NULL, NULL);
	pFileName[len + 1] = 0;  //多字节字符以'/0'结束

	string s(pFileName);
	delete[] pFileName;
	return s;
}

