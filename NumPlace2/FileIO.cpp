#include "stdafx.h"
#include "FileIO.h"


CFileIO::CFileIO()
{
}


CFileIO::~CFileIO()
{
}


BOOL CFileIO::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: �����ɓ���ȍ쐬�R�[�h��ǉ����Ă��������B

	return TRUE;
}
