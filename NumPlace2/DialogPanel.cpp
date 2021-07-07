#include "stdafx.h"
#include "DialogPanel.h"
#include "NumPlace2.h"


CDialogPanel::CDialogPanel()
{
}


CDialogPanel::~CDialogPanel()
{

}

void CDialogPanel::InitControls(bool radio, bool check1, bool check2) {
	
	p_Radio1 = (CButton*)GetDlgItem(IDC_RADIO1);
	p_Radio2 = (CButton*)GetDlgItem(IDC_RADIO2);
	p_checkL1 = (CButton*)GetDlgItem(IDC_CHECK1);
	p_checkL2 = (CButton*)GetDlgItem(IDC_CHECK2);
	if (radio) {
		p_Radio1->SetCheck(1);
		p_Radio2->SetCheck(0);
	}
	else {
		p_Radio1->SetCheck(0);
		p_Radio2->SetCheck(1);
	}
	p_checkL1->SetCheck(check1);
	p_checkL2->SetCheck(check2);
	CButton* pb;
	pb = (CButton*)GetDlgItem(IDC_CHECK_1P);
	pb->SetCheck(theApp.m_Engine.searchOp1p);
	pb = (CButton*)GetDlgItem(IDC_CHECK_1N);
	pb->SetCheck(theApp.m_Engine.searchOp1n);
	pb = (CButton*)GetDlgItem(IDC_CHECK_2P);
	pb->SetCheck(theApp.m_Engine.searchOp2p);
	pb = (CButton*)GetDlgItem(IDC_CHECK_2N);
	pb->SetCheck(theApp.m_Engine.searchOp2n);
	pb = (CButton*)GetDlgItem(IDC_CHECK_3P);
	pb->SetCheck(theApp.m_Engine.searchOp3p);
	pb = (CButton*)GetDlgItem(IDC_CHECK_3N);
	pb->SetCheck(theApp.m_Engine.searchOp3n);
	pb = (CButton*)GetDlgItem(IDC_CHECK_4P);
	pb->SetCheck(theApp.m_Engine.searchOp4p);
	pb = (CButton*)GetDlgItem(IDC_CHECK_4N);
	pb->SetCheck(theApp.m_Engine.searchOp4n);
	pb = (CButton*)GetDlgItem(IDC_CHECK_5P);
	pb->SetCheck(theApp.m_Engine.searchOp5p);
	pb = (CButton*)GetDlgItem(IDC_CHECK_5N);
	pb->SetCheck(theApp.m_Engine.searchOp5n);
	pb = (CButton*)GetDlgItem(IDC_CHECK_EDITR);
	pb->SetCheck(theApp.m_Engine.editRemainder);


}

void CDialogPanel::DoDataExchange(CDataExchange* pDX) {

}

BEGIN_MESSAGE_MAP(CDialogPanel, CDialogBar)

	//	ON_WM_KEYDOWN()
	//ON_WM_KEYDOWN()
	ON_COMMAND(IDC_CHECK1, &CDialogPanel::OnCheck1)
	ON_COMMAND(IDC_CHECK2, &CDialogPanel::OnCheck2)
	// ON_CBN_SELCHANGE(IDC_COMBO1, &CDialogPanel::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CHECK_1P, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_1N, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_R13, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_2P, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_2N, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_3P, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_3N, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_4P, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_4N, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_5P, &CDialogPanel::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK_5N, &CDialogPanel::OnBnClickedCheck3)

	ON_BN_CLICKED(IDC_CHECK_EDITR, &CDialogPanel::OnBnClickedCheckEditRemainder)
END_MESSAGE_MAP()


void CDialogPanel::OnCheck1()
{
	p_checkL1 = (CButton*)GetDlgItem(IDC_CHECK1);
	if (p_checkL1->GetCheck()) {
		theApp.m_Engine.protectDoubleEntry = true;
		theApp.m_Engine.protectFalseEntry = true;
	}
	else {
		theApp.m_Engine.protectDoubleEntry = false;
		theApp.m_Engine.protectFalseEntry = false;
	}
	p_MainFrame->SetFocusOnChildView();
}


void CDialogPanel::OnCheck2()
{
	p_checkL2 = (CButton*)GetDlgItem(IDC_CHECK2);
	if (p_checkL2->GetCheck()) {
		theApp.m_Engine.showRemainder = true;
	}
	else {
		theApp.m_Engine.showRemainder = false;
	}
	p_MainFrame->SetFocusOnChildView();
}

void CDialogPanel::InitComboBox(std::list<std:: wstring> list) {
	CComboBox * p_combo;
	p_combo = (CComboBox *)GetDlgItem(IDC_COMBO1);
	p_combo->ResetContent();
	for (wstring ws : list) {
		p_combo->InsertString(-1, ws.c_str());
	}
}
int CDialogPanel::GetCurSelCombo1()
{	
	CComboBox *p_combo = (CComboBox *)GetDlgItem(IDC_COMBO1);
	return p_combo->GetCurSel();
}

void CDialogPanel::UpdateProgress(short progress) {
	CEdit *pEdit;
	TCHAR  text[4];
	wsprintf(text, L"%d", progress);
	pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	pEdit->SetWindowTextW(text);
	if (progress == 0) {
		MessageBox(L"You've all done. Congratulation!", L"FINISH", MB_OK);
	}
}

void CDialogPanel::DispTrialName(std::wstring name) {
	CEdit *pEdit;
	//name = "Trial1";
	pEdit = (CEdit *)GetDlgItem(IDC_EDIT_TN);
	pEdit->SetWindowTextW(name.c_str());
}


void CDialogPanel::OnBnClickedCheck3()
{
	// TODO: Add your control notification handler code here
	CButton *p_check;
	theApp.m_Engine.searchOp1p = ((CButton*)GetDlgItem(IDC_CHECK_1P))->GetCheck();
	theApp.m_Engine.searchOp1n = ((CButton*)GetDlgItem(IDC_CHECK_1N))->GetCheck();

	theApp.m_Engine.searchOpR13 = ((CButton*)GetDlgItem(IDC_CHECK_R13))->GetCheck();
	theApp.m_Engine.searchOp2p = ((CButton*)GetDlgItem(IDC_CHECK_2P))->GetCheck();
	theApp.m_Engine.searchOp2n = ((CButton*)GetDlgItem(IDC_CHECK_2N))->GetCheck();
	theApp.m_Engine.searchOp3p = ((CButton*)GetDlgItem(IDC_CHECK_3P))->GetCheck();
	theApp.m_Engine.searchOp3n = ((CButton*)GetDlgItem(IDC_CHECK_3N))->GetCheck();
	theApp.m_Engine.searchOp4p = ((CButton*)GetDlgItem(IDC_CHECK_4P))->GetCheck();
	theApp.m_Engine.searchOp4n = ((CButton*)GetDlgItem(IDC_CHECK_4N))->GetCheck();
	theApp.m_Engine.searchOp5p = ((CButton*)GetDlgItem(IDC_CHECK_5P))->GetCheck();
	theApp.m_Engine.searchOp5n = ((CButton*)GetDlgItem(IDC_CHECK_5N))->GetCheck();

	p_MainFrame->SetFocusOnChildView();
}


void CDialogPanel::OnBnClickedCheckEditRemainder()
{
	// TODO: Add your control notification handler code here
	theApp.m_Engine.editRemainder = ((CButton*)GetDlgItem(IDC_CHECK_EDITR))->GetCheck();
	p_MainFrame->SetFocusOnChildView();
}
