#pragma once
#include "afxext.h"
//#include "stdafx.h"
#include <list>
#include <string>

class CMainFrame;

class CDialogPanel :
	public CDialogBar
{
public:
	CDialogPanel();
	~CDialogPanel();
	CMainFrame *p_MainFrame;
	void InitControls(bool radio1, bool check1, bool check2);
	void InitComboBox(std::list<std::wstring> lt);
	int GetCurSelCombo1();
	void UpdateProgress(short progress);
	void DispTrialName(std::wstring name);

	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);


	CButton		*p_Radio1, *p_Radio2, *p_checkL1, *p_checkL2;

public :
	// CMainFrame  *p_MainFrame;

	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheckEditRemainder();
};

