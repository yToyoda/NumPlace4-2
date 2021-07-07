
// NumPlace2.h : NumPlace2 アプリケーションのメイン ヘッダー ファイル
//
#pragma once
#include "stdafx.h"

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル
#include "NumPlaceEngine.h"


// CNumPlace2App:
// このクラスの実装については、NumPlace2.cpp を参照してください。
//

class CNumPlace2App : public CWinApp
{
public:
	CNumPlace2App();

// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装

public:
	afx_msg void OnAppAbout();
	CNumPlaceEngine	m_Engine;
	CMainFrame *pMainFrame;
	DECLARE_MESSAGE_MAP()
	
//	afx_msg void On32772();
	afx_msg void LoadFrom();
};

extern CNumPlace2App theApp;
