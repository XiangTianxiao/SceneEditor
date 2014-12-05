// DlgAddObj.cpp : 实现文件
//

#include "stdafx.h"
#include "SceneEditor.h"
#include "DlgAddObj.h"
#include "afxdialogex.h"


// CDlgAddObj 对话框

IMPLEMENT_DYNAMIC(CDlgAddObj, CDialogEx)

CDlgAddObj::CDlgAddObj(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAddObj::IDD, pParent)
	, m_add_obj_name(_T("默认名称"))
{

}

CDlgAddObj::~CDlgAddObj()
{
}

void CDlgAddObj::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADD_OBJ_NAME, m_add_obj_name);
}


BEGIN_MESSAGE_MAP(CDlgAddObj, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_ADD_CUBE, &CDlgAddObj::OnBnClickedRadioAddCube)
	ON_BN_CLICKED(IDC_RADIO_ADD_CYLINDER, &CDlgAddObj::OnBnClickedRadioAddCylinder)
	ON_BN_CLICKED(IDC_RADIO_ADD_PRISM, &CDlgAddObj::OnBnClickedRadioAddPrism)
	ON_BN_CLICKED(IDC_RADIO_ADD_SPHERE, &CDlgAddObj::OnBnClickedRadioAddSphere)
	ON_BN_CLICKED(IDC_RADIO_ADD_OBJFILE, &CDlgAddObj::OnBnClickedRadioAddObjfile)
END_MESSAGE_MAP()


// CDlgAddObj 消息处理程序


void CDlgAddObj::OnBnClickedRadioAddCube()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_obj_type = CUBE;
	if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
		m_add_obj_name = "cube";
	UpdateData(FALSE);
}



void CDlgAddObj::OnBnClickedRadioAddCylinder()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_obj_type = CYLINDER;
	if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
		m_add_obj_name = "cylinder";
	UpdateData(FALSE);
}


void CDlgAddObj::OnBnClickedRadioAddPrism()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_obj_type = PRISM;
	if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
		m_add_obj_name = "prism";
	UpdateData(FALSE);
}


void CDlgAddObj::OnBnClickedRadioAddSphere()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_obj_type = SPHERE;
	if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
		m_add_obj_name = "sphere";
	UpdateData(FALSE);
}


BOOL CDlgAddObj::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	switch (m_obj_type)
	{
	case CUBE:
		CheckDlgButton(IDC_RADIO_ADD_CUBE, BST_CHECKED);
		if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
			m_add_obj_name = "cube";
		break;
	case CYLINDER:
		CheckDlgButton(IDC_RADIO_ADD_CYLINDER, BST_CHECKED);
		if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
			m_add_obj_name = "cylinder";
		break;
	case PRISM:
		CheckDlgButton(IDC_RADIO_ADD_PRISM, BST_CHECKED);
		if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
			m_add_obj_name = "prism";
		break;
	case SPHERE:
		CheckDlgButton(IDC_RADIO_ADD_SPHERE, BST_CHECKED);
		if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
			m_add_obj_name = "sphere";
		break;
	case OBJ_FILE:
		//这样写是没有错误的，因为第二次添加的时候，如果不重新打开文件的话，会导致file_name为空，报错
		CheckDlgButton(IDC_RADIO_ADD_CUBE, BST_CHECKED);
		if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
			m_add_obj_name = "cube";
		m_obj_type = CUBE;
		break;
	default:
		CheckDlgButton(IDC_RADIO_ADD_CUBE, BST_CHECKED);
		if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
			m_add_obj_name = "cube";
		break;
	}
	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgAddObj::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


void CDlgAddObj::OnBnClickedRadioAddObjfile()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("obj Files (*.obj)|*.obj|"),
		NULL);

	if (dlg.DoModal() == IDOK)
	{
		m_objfile_name = dlg.GetPathName(); //文件名保存在了FilePathName里
	}
	else
	{
		CheckDlgButton(IDC_RADIO_ADD_OBJFILE, BST_UNCHECKED);
		switch (m_obj_type)
		{
		case CUBE:
			CheckDlgButton(IDC_RADIO_ADD_CUBE, BST_CHECKED);
			break;
		case CYLINDER:
			CheckDlgButton(IDC_RADIO_ADD_CYLINDER, BST_CHECKED);
			break;
		case PRISM:
			CheckDlgButton(IDC_RADIO_ADD_PRISM, BST_CHECKED);
			break;
		case SPHERE:
			CheckDlgButton(IDC_RADIO_ADD_SPHERE, BST_CHECKED);
			break;
		case OBJ_FILE:
			CheckDlgButton(IDC_RADIO_ADD_OBJFILE, BST_CHECKED);
			break;
		default:
			break;
		}

		return;
	}

	m_obj_type = OBJ_FILE;
	if (m_add_obj_name == "默认名称" || m_add_obj_name == "cube" || m_add_obj_name == "cylinder" || m_add_obj_name == "prism" || m_add_obj_name == "sphere" || m_add_obj_name == "obj_file")
		m_add_obj_name = "obj_file";
	UpdateData(FALSE);
}
