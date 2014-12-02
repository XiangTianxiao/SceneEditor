#pragma once


// CLightTree

class CLightTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CLightTree)

public:
	CLightTree();
	virtual ~CLightTree();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


