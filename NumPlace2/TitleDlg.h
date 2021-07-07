#pragma once
#include "afxwin.h"
#include "resource.h"
class CTitleDlg :
	public CDialog
{
public:
	CTitleDlg(CWnd *pParentWnd = NULL) :CDialog(IDD_TITLEDIALOG, pParentWnd){};
	~CTitleDlg();
	CString m_Title;
protected:
	virtual void OnOK();
};

