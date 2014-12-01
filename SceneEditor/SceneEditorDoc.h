
// SceneEditorDoc.h : CSceneEditorDoc 类的接口
//


#pragma once

#include <list>
using namespace std;
#include "DocObj.h"

#include "PropertiesWnd.h"

class CSceneEditorDoc : public CDocument
{
protected: // 仅从序列化创建
	CSceneEditorDoc();
	DECLARE_DYNCREATE(CSceneEditorDoc)

// 特性
public:
	list<CDocObj*> m_obj_list;
// 操作
public:
	CDocObj* draw_property(CString name, CPropertiesWnd* pProperties);
	CDocObj* add_obj(OBJ_TYPE type, CString name);
	CDocObj* add_obj(CString name, CString file_name);
	CString case_name_overlap(CString name, int num);

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CSceneEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
