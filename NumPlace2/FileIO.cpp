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

	// TODO: ここに特定な作成コードを追加してください。

	return TRUE;
}
