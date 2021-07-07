
// MainFrm.h : CMainFrame クラスのインターフェイス
//

#pragma once
#include "ChildView.h"
#include "NumPlaceEngine.h"
#include "FileIO.h"
#include "TitleDlg.h"
// #include "DialogPanel.h"


class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 属性
public:

// 操作
public:

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 実装
public:
	virtual ~CMainFrame();
	CDialogPanel   m_DialogPanel;
	PointIndex currentPos ;

	list<wstring> questionTitles;
	list<char *>  questionList;
	wstring		  filePath;

	void XYSpecified(long xi, long yi);
	void NumSelected(int num);
	void MoveSelected(int move);
	void SetFocusOnChildView();
	void ShowPossibleNum(int xi, int yi);
	void ReadFromFile(wstring path);
//	void WriteToFile(CFile file);
//	void WriteToFile(streambuf &wsbuf);
	void WriteToFile(wstring path);
	void Refresh();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // コントロール バー用メンバー
	CToolBar      m_wndToolBar;
	CStatusBar    m_wndStatusBar;
	CStatusBarCtrl m_wndStatusBarCtrl;
	ChildView    m_wndView;
	int trial = 0;

public:
	CNumPlaceEngine	*p_Engine;

// 生成された、メッセージ割り当て関数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonHint();
	afx_msg void OnBnClickedButton1step();
	afx_msg void OnBnClickedButtonAll();
	afx_msg void OnBnClickedButtonN1();
	afx_msg void OnBnClickedButtonN2();
	afx_msg void OnBnClickedButtonN3();
	afx_msg void OnBnClickedButtonN4();
	afx_msg void OnBnClickedButtonN5();
	afx_msg void OnBnClickedButtonN6();
	afx_msg void OnBnClickedButtonN7();
	afx_msg void OnBnClickedButtonN8();
	afx_msg void OnBnClickedButtonN9();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClicked_Rone();
	afx_msg void OnBnClicked_2P();
	afx_msg void OnBnClicked_2N();
	afx_msg void OnBnClicked_3P();
	afx_msg void OnBnClicked_3N();
	afx_msg void OnBnClicked_4P();
	afx_msg void OnBnClicked_4N();
	afx_msg void OnBnClicked_5P();
	afx_msg void OnBnClicked_5N();
	/*
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	*/
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg UINT OnNotifyFormat(CWnd *pWnd, UINT nCommand);
protected:
//	afx_msg LRESULT OnUser(WPARAM wParam, LPARAM lParam);
public:
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
//	afx_msg void OnCombo1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClicked_Restart();
	afx_msg void OnBnClickedButtonNewtrial();
	afx_msg void OnBnClickedButtonUndotrial();
	afx_msg void OnBnClickedButton1p();
	afx_msg void OnBnClickedButton1n();
};


