#include "stdafx.h"
#include "TitleDlg.h"


/*
CTitleDlg::CTitleDlg(CWnd *pParentWnd){
	CDialog(IDD_TITLEDIALOG, pParentWnd);
}
*/
CTitleDlg::~CTitleDlg()
{
}

void CTitleDlg::OnOK(){
	GetDlgItemText(IDC_EDIT_TITLE, m_Title);
	CDialog::OnOK();
}
