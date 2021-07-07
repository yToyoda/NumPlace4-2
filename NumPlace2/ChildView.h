
// ChildView.h : ChildView クラスのインターフェイス
// Oct26 2016


#pragma once
#include "stdafx.h"

// ChildView ウィンドウ
class CMainFrame;

class ChildView : public CWnd
{
// コンストラクション
public:
	ChildView();
	CClientDC *pdc;

	CMainFrame *p_MainFrame;

	COLORREF colSpace{ RGB(200, 200, 200) },  // light gray
		colCanvas{ RGB(255, 255, 255) },  // white
		colSelection {RGB(209,232,255)},  // light blue
		colHint1 {RGB(198,244,180)},     // light green
		colHint2 {RGB(244,176,132)},      // orange
		colNumDefined{ RGB(0,0,0)},       // blcak
		colNumAnswer {RGB (0,0,255)},   // blue
		colAxis{ RGB(0, 0, 0) }, // black
		colVlz{ RGB(0, 187, 0) },  // green
		colVly{ RGB(200, 0, 0) },  // red
		colCh2{ RGB(255, 0, 0) };  // red 
	struct RScaling{
		double xmin;
		double xmax;
		double ymin;
		double ymax;
	} rscaling;
	struct SBsize{
		int bottm;
		int x1;
		int x2;
	} sbSize;

	CFont m_font, m_fontsmall;
	RECT	canvas, gridArea;
	long	tickSize;
	bool    fontCreated = false;
	void ShowSelection(int xi, int yi);
	void ShowHints(int xi, int yi, int rule);
	void RestorCurrentPos(int xi, int yi);
	void SetBgColor(int xi, int yi, COLORREF color);
	void ShowText(int xi, int yi);    // routine of writing text to canvus
	void ClearCanvas();
	

// 属性
public:

// 操作
public:

// オーバーライド
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 実装
public:
	virtual ~ChildView();

	// 生成された、メッセージ割り当て関数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

