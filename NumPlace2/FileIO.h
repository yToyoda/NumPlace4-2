#pragma once
#include "afxwin.h"
class CFileIO :
	public CDocument
{
public:
	CFileIO();
	~CFileIO();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};

