
// NumPlace2.h : NumPlace2 �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once
#include "stdafx.h"

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��
#include "NumPlaceEngine.h"


// CNumPlace2App:
// ���̃N���X�̎����ɂ��ẮANumPlace2.cpp ���Q�Ƃ��Ă��������B
//

class CNumPlace2App : public CWinApp
{
public:
	CNumPlace2App();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����

public:
	afx_msg void OnAppAbout();
	CNumPlaceEngine	m_Engine;
	CMainFrame *pMainFrame;
	DECLARE_MESSAGE_MAP()
	
//	afx_msg void On32772();
	afx_msg void LoadFrom();
};

extern CNumPlace2App theApp;
