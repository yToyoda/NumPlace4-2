
// MainFrm.cpp : CMainFrame クラスの実装
//

#include "stdafx.h"
#include "NumPlace2.h"

#include "MainFrm.h"
#include <fstream>
#include <string>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
using namespace std;
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_BN_CLICKED(IDC_BUTTON_HINT, &CMainFrame::OnBnClickedButtonHint)
	ON_BN_CLICKED(IDC_BUTTON_1Step, &CMainFrame::OnBnClickedButton1step)
	//ON_BN_CLICKED(IDC_BUTTON_All, &CMainFrame::OnBnClickedButtonAll)
	ON_BN_CLICKED(IDC_BUTTON_N1, &CMainFrame::OnBnClickedButtonN1)
	ON_BN_CLICKED(IDC_BUTTON_N2, &CMainFrame::OnBnClickedButtonN2)
	ON_BN_CLICKED(IDC_BUTTON_N3, &CMainFrame::OnBnClickedButtonN3)
	ON_BN_CLICKED(IDC_BUTTON_N4, &CMainFrame::OnBnClickedButtonN4)
	ON_BN_CLICKED(IDC_BUTTON_N5, &CMainFrame::OnBnClickedButtonN5)
	ON_BN_CLICKED(IDC_BUTTON_N6, &CMainFrame::OnBnClickedButtonN6)
	ON_BN_CLICKED(IDC_BUTTON_N7, &CMainFrame::OnBnClickedButtonN7)
	ON_BN_CLICKED(IDC_BUTTON_N8, &CMainFrame::OnBnClickedButtonN8)
	ON_BN_CLICKED(IDC_BUTTON_N9, &CMainFrame::OnBnClickedButtonN9)
	//ON_BN_CLICKED(IDC_BUTTON_Rone, &CMainFrame::OnBnClicked_Rone)
	ON_BN_CLICKED(IDC_BUTTON_R1x3, &CMainFrame::OnBnClicked_Rone)
	ON_BN_CLICKED(IDC_BUTTON_2P, &CMainFrame::OnBnClicked_2P)
	ON_BN_CLICKED(IDC_BUTTON_2N, &CMainFrame::OnBnClicked_2N)
	ON_BN_CLICKED(IDC_BUTTON_3P, &CMainFrame::OnBnClicked_3P)
	ON_BN_CLICKED(IDC_BUTTON_3N, &CMainFrame::OnBnClicked_3N)
	ON_BN_CLICKED(IDC_BUTTON_4P, &CMainFrame::OnBnClicked_4P)
	ON_BN_CLICKED(IDC_BUTTON_4N, &CMainFrame::OnBnClicked_4N)
	ON_BN_CLICKED(IDC_BUTTON_5P, &CMainFrame::OnBnClicked_5P)
	ON_BN_CLICKED(IDC_BUTTON_5N, &CMainFrame::OnBnClicked_5N)
	ON_BN_CLICKED(IDC_BUTTON_Refresh, &CMainFrame::Refresh)

	ON_BN_CLICKED(IDC_RADIO1, &CMainFrame::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMainFrame::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CMainFrame::OnBnClickedButtonDelete)
//	ON_WM_LBUTTONDOWN()
//ON_WM_NOTIFYFORMAT()
//ON_MESSAGE(WM_USER, &CMainFrame::OnUser)
//ON_WM_KEYDOWN()
ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
ON_COMMAND(ID_FILE_SAVE_AS, &CMainFrame::OnFileSaveAs)
//ON_COMMAND(IDC_COMBO1, &CMainFrame::OnCombo1)
ON_CBN_SELCHANGE(IDC_COMBO1, &CMainFrame::OnCbnSelchangeCombo1)
ON_BN_CLICKED(IDC_BUTTON5, &CMainFrame::OnBnClicked_Restart)
ON_BN_CLICKED(IDC_BUTTON_NewTrial, &CMainFrame::OnBnClickedButtonNewtrial)
ON_BN_CLICKED(IDC_BUTTON_UndoTrial, &CMainFrame::OnBnClickedButtonUndotrial)
ON_BN_CLICKED(IDC_BUTTON_1P, &CMainFrame::OnBnClickedButton1p)
ON_BN_CLICKED(IDC_BUTTON_1N, &CMainFrame::OnBnClickedButton1n)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケーター
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame コンストラクション/デストラクション

CMainFrame::CMainFrame()
{
	// TODO: メンバー初期化コードをここに追加してください。
	currentPos = { -1, -1 };
	theApp.pMainFrame = this;  //register MainFrame to pointer pMainFrame in the App
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// test and int engine
	p_Engine = & theApp.m_Engine;
	p_Engine->defineMode = true;
	p_Engine->PlaceNum(9, { 0, 0 });
	p_Engine->PlaceNum(7, { 1, 0 });
	p_Engine->PlaceNum(6, { 7, 0 });
	p_Engine->PlaceNum(4, { 8, 0 });

	p_Engine->PlaceNum(1, { 0, 1 });
	p_Engine->PlaceNum(8, { 1, 1 });
	p_Engine->PlaceNum(2, { 7, 1 });
	p_Engine->PlaceNum(7, { 8, 1 });

	p_Engine->PlaceNum(2, { 2, 2 });
	p_Engine->PlaceNum(5, { 3, 2 });
	p_Engine->PlaceNum(7, { 5, 2 });
	p_Engine->PlaceNum(9, { 6, 2 });

	p_Engine->PlaceNum(6, { 2, 3 });
	p_Engine->PlaceNum(7, { 3, 3 });
	p_Engine->PlaceNum(2, { 5, 3 });
	p_Engine->PlaceNum(1, { 6, 3 });

	p_Engine->PlaceNum(8, { 2, 5 });
	p_Engine->PlaceNum(9, { 3, 5 });
	p_Engine->PlaceNum(3, { 5, 5 });
	p_Engine->PlaceNum(7, { 6, 5 });

	p_Engine->PlaceNum(7, { 2, 6 });
	p_Engine->PlaceNum(4, { 3, 6 });
	p_Engine->PlaceNum(9, { 5, 6 });
	p_Engine->PlaceNum(2, { 6, 6 });

	p_Engine->PlaceNum(3, { 0, 7 });
	p_Engine->PlaceNum(2, { 1, 7 });
	p_Engine->PlaceNum(7, { 7, 7 });
	p_Engine->PlaceNum(9, { 8, 7 });

	p_Engine->PlaceNum(8, { 0, 8 });
	p_Engine->PlaceNum(1, { 1, 8 });
	p_Engine->PlaceNum(3, { 7, 8 });
	p_Engine->PlaceNum(5, { 8, 8 });

	p_Engine->defineMode = false;
	p_Engine->SearchInitial();

	RECT clientRect;
	GetClientRect(&clientRect);
//	m_wndStatusBarCtrl.Create(WS_VISIBLE | WS_CHILD | CCS_BOTTOM, clientRect, this, 0);

	// フレームのクライアント領域全体を占めるビューを作成します。
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("ビュー ウィンドウを作成できませんでした。\n");
		return -1;
	}
	m_wndView.p_MainFrame = this;   // set pointer to this (MainFrame)
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("ツール バーの作成に失敗しました。\n");
		return -1;      // 作成できませんでした。
	}

	/*
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("ステータス バーの作成に失敗しました。\n");
		return -1;      // 作成できない場合
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	*/

	if (!m_DialogPanel.Create(this, IDD_DIALOGBAR, CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY, IDD_DIALOGBAR))
	{
		TRACE0("Failed to create the Dialog Bar");
		return -1;
	}
	m_DialogPanel.p_MainFrame = this; // place a pointer to this (MainFrame)
	m_DialogPanel.InitControls(p_Engine->defineMode, p_Engine->protectDoubleEntry, p_Engine->showRemainder);
	// TODO: ツール バーをドッキング可能にしない場合は、これらの 3 行を削除してください。
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

//	m_wndStatusBarCtrl.Create(WS_VISIBLE | WS_CHILD | CCS_BOTTOM, clientRect, this, 0);
	/*
	int widthArray[2];
	widthArray[0] = (clientRect.right - clientRect.left ) / 2;
	widthArray[1] = widthArray[0];
	m_wndStatusBarCtrl.SetParts(2, widthArray);
	m_wndStatusBarCtrl.SetText(L"情報表示エリア", 0, 0);
	*/
	m_DialogPanel.UpdateProgress(p_Engine->nCellsLeft);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame メッセージ ハンドラー

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// ビュー ウィンドウにフォーカスを与えます。
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ビューに最初にコマンドを処理する機会を与えます。
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// それ以外の場合は、既定の処理を行います。
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnBnClickedButtonHint()
{
	// TODO: Add your control notification handler code here
	if (!p_Engine->defineMode) {
		int nHints;
		nHints = p_Engine->foundRule1.size() + p_Engine->foundRule2.size();
		for (answer ans : p_Engine->foundRule1) {
			m_wndView.ShowHints(ans.point.xi, ans.point.yi, 1);
		}
		for (answer ans : p_Engine->foundRule2) {
			m_wndView.ShowHints(ans.point.xi, ans.point.yi, 2);
		}
	}
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButton1step()
{
	// TODO: Add your control notification handler code here
	if (!p_Engine->defineMode) {
		int nHints;
		
		std::list<answer> found;
		nHints = p_Engine->foundRule1.size() + p_Engine->foundRule2.size();
		for (answer ans : p_Engine->foundRule1) {
			found.push_back(ans);
		}
		for (answer ans : p_Engine->foundRule2) {
			found.push_back(ans);
		}
		for (answer ans : found){		
			p_Engine->PlaceNum(ans.num, ans.point);
			//m_wndView.ShowSelection(ans.point.xi, ans.point.yi);
			m_wndView.RestorCurrentPos(ans.point.xi, ans.point.yi);
		}
		p_Engine->ExecuteSearch();
		for (int xi = 0; xi < xySize; ++xi) {
			for (int yi = 0; yi < xySize; ++yi) {
				m_wndView.RestorCurrentPos(xi, yi);
			}
		}
	}
	m_DialogPanel.UpdateProgress(p_Engine->nCellsLeft);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonAll()
{
	// TODO: Add your control notification handler code here
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonN1()
{
	NumSelected(1);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonN2()
{
	NumSelected(2);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonN3()
{
	NumSelected(3);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonN4()
{
	NumSelected(4);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonN5()
{
	NumSelected(5);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonN6()
{
	NumSelected(6);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonN7()
{
	NumSelected(7);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonN8()
{
	NumSelected(8);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClickedButtonN9()
{
	NumSelected(9);
	m_wndView.SetFocus();
}

void CMainFrame::SetFocusOnChildView() {
	m_wndView.SetFocus();
}

void CMainFrame::OnBnClickedRadio1()
{
	p_Engine->defineMode = true;
	m_wndView.SetFocus();

}


void CMainFrame::OnBnClickedRadio2()
{
	p_Engine->defineMode = false;
	if (!p_Engine->searchDone) p_Engine->SearchInitial();
	m_wndView.SetFocus();
}

void CMainFrame::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	NumSelected(-1);
	m_wndView.SetFocus();
}

void CMainFrame::XYSpecified(long xi, long yi) {
	if (currentPos.xi >= 0 && currentPos.yi >= 0) {
		m_wndView.RestorCurrentPos(currentPos.xi, currentPos.yi);
	}
	m_wndView.ShowSelection(xi, yi);
	currentPos.xi = xi;
	currentPos.yi = yi;
}

void CMainFrame::NumSelected(int num) {
	if (currentPos.xi >= 0 && currentPos.xi < xySize && currentPos.yi >= 0 && currentPos.yi < xySize) {
		p_Engine->NumSelected(currentPos, num);
		m_wndView.RestorCurrentPos(currentPos.xi, currentPos.yi);
		m_wndView.ShowSelection(currentPos.xi, currentPos.yi);
		m_DialogPanel.UpdateProgress(p_Engine->nCellsLeft);
	}
}

void CMainFrame::MoveSelected(int move) {
	int xi=currentPos.xi, yi = currentPos.yi;
	if (currentPos.xi >= 0 && currentPos.yi >= 0) {
		if (move == 0x23) {
			// end
			yi = 8;
			xi = 8;
		}
		else if (move == 0x24) {
			// home
			yi = 0;
			xi = 0;

		}
		else if (move == 0x25) {
			//left
			if (currentPos.xi > 0) {
				xi = currentPos.xi - 1;
				yi = currentPos.yi;
			}
			else {
				xi = 8;
				yi = currentPos.yi - 1;
				if (yi < 0) yi = 0;
			}
		}
		else if (move == 0x26 ) {
			xi = currentPos.xi;
			yi = currentPos.yi - 1;
			if (yi < 0) yi = 0;
			// up
		}
		else if (move == 0x27 || move == 0x0D) {
			// right or return
			yi = currentPos.yi;
			xi = currentPos.xi + 1;
			if (xi >= xySize) {
				xi = 0;
				yi = yi + 1;
				if (yi >= xySize) yi = 0;
			}
		}
		else if (move == 0x28) {
			// down
			xi = currentPos.xi;
			yi = currentPos.yi + 1;
			if (yi >= xySize) yi = 0;
		}

		m_wndView.RestorCurrentPos(currentPos.xi, currentPos.yi);
		m_wndView.ShowSelection(xi, yi);
		currentPos.xi = xi;
		currentPos.yi = yi;
	}
}

void CMainFrame::ShowPossibleNum(int xi, int yi) {
	TCHAR  str[4];
	CString stat;
	for (int i = 1; i <= maxNum; ++i) {
		if (p_Engine->grid.atInterSect(xi, yi).possibleNum[i]) {
			wsprintf(str, L"%d ", i);
			stat.Append(str);
		}
	}
	m_wndStatusBarCtrl.SetText(stat.GetBuffer(), 0, 0);

}

void CMainFrame::OnFileOpen()
{
	CString  fileName;
	

	static TCHAR BASED_CODE szFilter[] = _T("CSV Files (*.csv)|*.csv|Text Files (*.txt)|*.txt|");

	wchar_t* p = fileName.GetBuffer(200);
	CFileDialog fDialog(TRUE, L"*.csv", NULL, OFN_HIDEREADONLY, szFilter);
	OPENFILENAME& ofn = fDialog.GetOFN();
	ofn.lpstrFile = p;
	ofn.nMaxFile = 200;

	fDialog.DoModal();
	filePath = p;

	ReadFromFile(filePath);
}


void CMainFrame::OnFileSaveAs()
{
	CString  fileName = L"DataFile";
	static TCHAR BASED_CODE szFilter[] = L"CSV Files (*.csv)|*.csv|Text Files (*.txt)|*.txt|";
	wchar_t* p = fileName.GetBuffer(200);
	CFileDialog fDialog(FALSE, L".txt", p, OFN_HIDEREADONLY, szFilter);
	OPENFILENAME& ofn = fDialog.GetOFN();
	ofn.lpstrFile = p;
	ofn.nMaxFile = 200;
	CFile  mFile;
	

	fDialog.DoModal();
	filePath = p;
	int st = 0;
	st = mFile.Open(p, CFile::modeReadWrite);
	//stringbuf sbuff;
	string wstr;
	if (st != 0) {
		// file exist	ask user if Append
		int yesNo = MessageBox(L"The specified file exits! ",L"OPEN FILE", MB_OK);
/*		if (yesNo == IDYES) {
			// append 
			mFile.SeekToEnd();

			WriteToFile(sbuff);	
			wstr = sbuff.str();
			mFile.Write(wstr.c_str(), wstr.length());
			mFile.Close();
		}
		*/
		mFile.Close();
	}
	else {
		//st = mFile.Open(p, CFile::modeCreate | CFile::modeReadWrite);
		// write 
		WriteToFile(filePath);
		/*
		wstr = sbuff.str();
		mFile.Write(wstr.c_str(), wstr.length());
		mFile.Close();
		  */
	}
}

void CMainFrame::ReadFromFile(wstring path){

	TCHAR c;
	wfilebuf fb;
	if (fb.open(path, ios::in))
	{
		wistream is(&fb);
		wstring title;
		wstring fields[9];
		char  *c_grid;
		int		nfield = 0;
		int     nRow = 0;
		int     nError = 0;
		c_grid = new char[81];
		while (is) {
			c = (char)is.get();
			if (c == '\n') {
				while (c == '\n') c = (char)is.get();
			}
			if (is.eof()) break;
			while (c != '\n' && !is.eof()) {
				while (c != ',' && c != '\n' && !is.eof()) {
					fields[nfield].push_back(c);
					c = (char)is.get();
				}
				if (c == ',') {
					++nfield;
					c = (char)is.get();
				}
			}
			if (is.eof()) break;
			if (nfield == 0 && fields[0].length() >= 1) {
				title = fields[0];
			} if (nfield == 8) {
				for (int i = 0; i < xySize; ++i) {
					if (fields[i].length() == 0) {
						c_grid[nRow * xySize + i] = 0;
					}
					else if (fields[i].length() == 1) {
						c = (char)fields[i].front();
						if (c >= '0' && c <= '9') {
							c_grid[nRow * xySize + i] = c - '0';
						}
						else {
							++nError;
						}
					}
					else {
						++nError;
					}
				}
				++nRow;
			}
			else {
				++nError;
			}
			nfield = 0;
			for (int i = 0; i < xySize; ++i) {
				fields[i].clear();
			}
			if (nRow >= xySize) {
				// add to list
				questionTitles.push_back(title);
				questionList.push_back(c_grid);
				nRow = 0;
				c_grid = new char[81];
			}
		}
		fb.close();
		m_DialogPanel.InitComboBox(questionTitles);
	}
}

void CMainFrame::WriteToFile(wstring filePath){
	CTitleDlg dlg;
	dlg.DoModal();
	CellData cell;
	wofstream wofst(filePath, ios::out);
	wstring title(dlg.m_Title);
	wofst << title.c_str() << endl;
	for (int yi = 0; yi < xySize; ++yi) {
		for (int xi = 0; xi < xySize; ++xi){
			cell = p_Engine->grid.atInterSect(xi,yi);
			if (cell.possibleNum[0] && cell.currentNum > 0) {
				wofst << cell.currentNum;
			}
			if (xi < 8) {
				wofst << L',';
			}
		}
		wofst << endl;
	}
	wofst.close();
}

//void CMainFrame::OnCombo1()
//{
//	// TODO: ここにコマンド ハンドラー コードを追加します。
//}


void CMainFrame::OnCbnSelchangeCombo1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int selIndex, num;
	char *cArray = nullptr;
	selIndex = m_DialogPanel.GetCurSelCombo1();
	
	p_Engine->InitEngine(false);
	std::list<char *>::iterator itcp;
	itcp = questionList.begin();
	cArray = *itcp;
	for (int i = 0; i <= selIndex; i++) {
		cArray = *itcp;
		++itcp;
	}
	p_Engine->defineMode = true;
	m_wndView.ClearCanvas();
	for (int yi = 0; yi <xySize; ++yi) {
		for (int xi = 0; xi < xySize; ++xi) {
			currentPos.xi = xi; currentPos.yi = yi;
			num = (int)*(cArray + yi * xySize + xi);
			if (num > 0) {
				p_Engine->PlaceNum(num, currentPos);
			}
			m_wndView.RestorCurrentPos(xi, yi);
		}
	}
	p_Engine->defineMode = false;
	if (!p_Engine->searchDone) p_Engine->SearchInitial();
	m_DialogPanel.UpdateProgress(p_Engine->nCellsLeft);
	m_wndView.SetFocus();
}


void CMainFrame::OnBnClicked_Restart()
{
	// TODO: Add your control notification handler code here
	trial = 0;
	if (p_Engine->defineMode) {
		p_Engine->InitEngine(false);
		m_wndView.ClearCanvas();
	}
	else {
		m_wndView.ClearCanvas();
		p_Engine->ClearAnswer();
		p_Engine->defineMode = true;
		for (int yi = 0; yi < xySize; ++yi){
			for (int xi = 0; xi < xySize; ++xi){
				m_wndView.ShowText(xi, yi);
			}
		}
		p_Engine->defineMode = false;
		p_Engine->SearchInitial();
		
	}
	m_wndView.SetFocus();
	wstring name = L"";
	m_DialogPanel.DispTrialName(name);
}

void CMainFrame::OnBnClicked_Rone() {
	theApp.m_Engine.CheckRule('r', 0);
	Refresh();
	SetFocusOnChildView();
}
void CMainFrame::OnBnClicked_2P() {
	theApp.m_Engine.CheckRule('p', 2);
	Refresh();
	SetFocusOnChildView();
}
void CMainFrame::OnBnClicked_3P() {
	theApp.m_Engine.CheckRule('p', 3);
	Refresh();
	SetFocusOnChildView();
}
void CMainFrame::OnBnClicked_4P() {
	theApp.m_Engine.CheckRule('p', 4);
	Refresh();
	SetFocusOnChildView();
}
void CMainFrame::OnBnClicked_5P() {
	theApp.m_Engine.CheckRule('p', 5);
	Refresh();
	SetFocusOnChildView();
}
void CMainFrame::OnBnClicked_2N() {
	theApp.m_Engine.CheckRule('n', 2);
	Refresh();
	SetFocusOnChildView();
}
void CMainFrame::OnBnClicked_3N() {
	theApp.m_Engine.CheckRule('n', 3);
	Refresh();
	SetFocusOnChildView();
}
void CMainFrame::OnBnClicked_4N() {
	theApp.m_Engine.CheckRule('n', 4);
	Refresh();
	SetFocusOnChildView();
}
void CMainFrame::OnBnClicked_5N() {
	theApp.m_Engine.CheckRule('n', 5);
	Refresh();
	SetFocusOnChildView();
}

void CMainFrame::Refresh() {
	for (int yi = 0; yi < xySize; ++yi) {
		for (int xi = 0; xi < xySize; ++xi) {
			m_wndView.RestorCurrentPos(xi, yi);
		}
	}
	SetFocusOnChildView();
}

void CMainFrame::OnBnClickedButtonNewtrial()
{
	// TODO: Add your control notification handler code here
	++trial;
	std::wstring name (L"Trial");	
	name += std::to_wstring(trial);
	m_DialogPanel.DispTrialName(name);
	p_Engine->PushToTrialStack();
	SetFocusOnChildView();
}


void CMainFrame::OnBnClickedButtonUndotrial()
{
	// TODO: Add your control notification handler code here
	std::wstring name(L"");
	if (trial == 0) return;
	if (trial>0) --trial;
	if (trial > 0) {
		name = L"Trial" + to_wstring(trial);
	}
	
	p_Engine->PopFromTrialStack();
	m_DialogPanel.DispTrialName(name);
	Refresh();
	SetFocusOnChildView();
}


void CMainFrame::OnBnClickedButton1p()
{
	theApp.m_Engine.CheckRule('p', 1);
	Refresh();
	SetFocusOnChildView();
}


void CMainFrame::OnBnClickedButton1n()
{
	theApp.m_Engine.CheckRule('n', 1);
	Refresh();
	SetFocusOnChildView();
}
