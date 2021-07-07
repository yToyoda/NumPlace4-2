
// ChildView.cpp : ChildView クラスの実装
//

#include "stdafx.h"
#include "NumPlace2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ChildView

ChildView::ChildView()
{
}

ChildView::~ChildView()
{
}


BEGIN_MESSAGE_MAP(ChildView, CWnd)
	ON_WM_PAINT()
//	ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONDOWN()
ON_WM_KEYDOWN()
ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// ChildView メッセージ ハンドラー

BOOL ChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void ChildView::OnPaint()
{
	CPaintDC dc(this); // 描画のデバイス コンテキスト

	RECT	clientArea;
	long	shorterAxis, diff;

	pdc = new CClientDC(this);
	this->GetClientRect(&clientArea);
	shorterAxis = clientArea.bottom - clientArea.top;
	if (clientArea.right - clientArea.left < shorterAxis) {
		shorterAxis = clientArea.right - clientArea.left;
		diff = clientArea.bottom - clientArea.top - shorterAxis;
		canvas.left = clientArea.left;
		canvas.right = clientArea.right;
		canvas.top = clientArea.top + diff / 2;
		canvas.bottom = clientArea.bottom - diff / 2;
	}
	else {
		shorterAxis -= 20;
		diff = clientArea.right - clientArea.left - shorterAxis;
		canvas.left = clientArea.left + diff / 2;
		canvas.right = clientArea.right - diff / 2;
		canvas.top = clientArea.top;
		canvas.bottom = clientArea.bottom-20;
	}
	CBrush newBrush(colSpace);
	pdc->SelectObject(newBrush);
	pdc->Rectangle(clientArea.left, clientArea.top, clientArea.right, clientArea.bottom);

	long leftMargine, rightMargine, x, y;
	tickSize = (shorterAxis - 11) / 9;
	leftMargine = (shorterAxis - tickSize * 9 - 1) / 2;
	rightMargine = shorterAxis - tickSize * 9 - 1 - leftMargine;

	gridArea.top = canvas.top + leftMargine;
	gridArea.left = canvas.left + leftMargine;
	gridArea.bottom = canvas.bottom - rightMargine;
	gridArea.right = canvas.right - rightMargine;

	ClearCanvas();

	long xa, ya;
	xa = (int) tickSize * 0.3;
	ya = (int) tickSize *0.1;
	if (!fontCreated) {
		m_font.CreateFontW(tickSize * 0.8, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
		m_fontsmall.CreateFontW(tickSize / 3 * 0.8, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
		fontCreated = true;
	}
	for (int j = 0; j < 9; ++j){
		y = gridArea.top + tickSize * j;
		for (int i = 0; i < 9; ++i) {
			x = gridArea.left + tickSize*i;
			pdc->SelectStockObject(WHITE_PEN);
			pdc->Rectangle(x + tickSize *0.1, y + tickSize *0.1, x + tickSize*0.9, y + tickSize *0.9);
			ShowText(i, j);
		}
	}

	//m_font.DeleteObject();


}

void ChildView::ClearCanvas() {

	pdc->SelectStockObject(WHITE_BRUSH);
	pdc->SelectStockObject(WHITE_PEN);
	pdc->Rectangle(canvas.left, canvas.top, canvas.right, canvas.bottom);

	CPen normalPen(PS_SOLID, 1, colAxis);
	CPen boldPen(PS_SOLID, 3, colAxis);

	long x, y;
	for (int i = 0; i <= 9; ++i) {
		y = gridArea.top + tickSize * i;
		if (i % 3 == 0) {
			pdc->SelectObject(boldPen);
		}
		else {
			pdc->SelectObject(normalPen);
		}
		pdc->MoveTo(gridArea.left, y);
		pdc->LineTo(gridArea.right, y);
	}
	for (int i = 0; i <= 9; ++i) {
		x = gridArea.left + tickSize*i;
		if (i % 3 == 0) {
			pdc->SelectObject(boldPen);
		}
		else {
			pdc->SelectObject(normalPen);
		}
		pdc->MoveTo(x, gridArea.top);
		pdc->LineTo(x, gridArea.bottom);
	}

}

void ChildView::ShowSelection(int xi, int yi) {
	SetBgColor(xi, yi, colSelection);
	ShowText(xi, yi);
}

void ChildView::ShowHints(int xi, int yi, int rule) {
	if (rule == 1) {
		SetBgColor(xi, yi, colHint1);
	}
	else if (rule == 2) {
		SetBgColor(xi, yi, colHint2);
	}
	ShowText(xi, yi);
}

void ChildView::RestorCurrentPos(int xi, int yi) {
	SetBgColor(xi, yi, colCanvas);
	ShowText(xi, yi);
}

void ChildView::SetBgColor(int xi, int yi, COLORREF color) {
	long x, y;
	x = gridArea.left + tickSize * xi;
	y = gridArea.top + tickSize *yi;

	CBrush newBrush(color); 
	pdc->SelectStockObject(WHITE_PEN);
	pdc->SelectObject(newBrush);
	pdc->Rectangle(x + 2, y + 2, x + tickSize - 2, y + tickSize - 2);
}

void ChildView::ShowText(int xi, int yi) {
	long x, y, xa, ya, xofs,yofs;
	TCHAR str[4];
	x = gridArea.left + tickSize * xi;
	y = gridArea.top + tickSize *yi;
	xa = (long) tickSize * 0.3;
	ya = (long) tickSize *0.1;
	pdc->SelectObject(&m_font);
	pdc->SetBkMode(TRANSPARENT);
	CellData cell = p_MainFrame->p_Engine->grid.atInterSect(xi, yi);
	/*
	if (xi >= 7 && yi == 0) {
		int n = cell.currentNum;
	}
	*/
	if (cell.currentNum > 0) {
		pdc->SelectObject(&m_font);
		if (cell.possibleNum[0]) {  // Question Definition
			pdc->SetTextColor(colNumDefined);
		}
		else {		// Answer
			pdc->SetTextColor(colNumAnswer);
		}
		wsprintf(str, L"%d", cell.currentNum);
		pdc->TextOutW(x + xa, y + ya, str);
	}
	else if (theApp.m_Engine.showRemainder && ! theApp.m_Engine.defineMode) {
		// Num is not finalized
		pdc->SelectObject(&m_fontsmall);
		pdc->SetTextColor(colNumAnswer);
		xofs = (long)tickSize / 3 * 0.3;
		yofs = (long)tickSize / 3 * 0.1;
		for (int i = 0; i < 9; ++i) {
			xa = ((long)tickSize / 3)* (i % 3) + xofs;
			ya = ((long)tickSize / 3)* (i / 3) + yofs;
			if (cell.possibleNum[i + 1]) {
				wsprintf(str, L"%d", i+1);
				pdc->TextOutW(x + xa, y + ya, str);
			}
		}
	}

}



void ChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	int gx, gy;
	if (point.x >= gridArea.left && point.x <= gridArea.right
		&& point.y >= gridArea.top && point.y < gridArea.bottom) {
		gx = (point.x - gridArea.left) / tickSize;
		gy = (point.y - gridArea.top) / tickSize;
		p_MainFrame->XYSpecified(gx, gy);
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void ChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	int num =0;
	if (nChar == 0x08 || nChar == 0x0C || nChar == 0x2E) { 
		num = -1;
		p_MainFrame->NumSelected(num);
	}// B.S.  or Clear or Del pressed
	if (nChar == 0x0D || nChar >= 0x21 && nChar <= 0x29) {
		// move key selected
		p_MainFrame->MoveSelected(nChar);
	}
	if (nChar >= 0x30 && nChar <= 0x39) {
		num = nChar - 0x30;
		p_MainFrame->NumSelected(num);
	}
	else if (nChar >= 0x60 && nChar <= 0x69) {
		num = nChar - 0x60;
		p_MainFrame->NumSelected(num);
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void ChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	int gx, gy;
	if (point.x >= gridArea.left && point.x <= gridArea.right
		&& point.y >= gridArea.top && point.y < gridArea.bottom) {
		gx = (point.x - gridArea.left) / tickSize;
		gy = (point.y - gridArea.top) / tickSize;
		p_MainFrame->ShowPossibleNum(gx, gy);
	}
	CWnd::OnRButtonDown(nFlags, point);
}
