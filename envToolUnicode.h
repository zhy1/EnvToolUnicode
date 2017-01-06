// envToolUnicode.h : main header file for the ENVTOOLUNICODE application
//

#if !defined(AFX_ENVTOOLUNICODE_H__D858BFBF_0044_4036_9E95_2B368E81FFE5__INCLUDED_)
#define AFX_ENVTOOLUNICODE_H__D858BFBF_0044_4036_9E95_2B368E81FFE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEnvToolUnicodeApp:
// See envToolUnicode.cpp for the implementation of this class
//

class CEnvToolUnicodeApp : public CWinApp
{
public:
	CEnvToolUnicodeApp();

	CString pathString;
	HKEY ghKEY;
	CString inputString;
	LPTSTR inputText;
    DWORD GcbData;
	VOID* GPerfData;
	int x; //全局变量 
	int f(int y); //全局函数 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnvToolUnicodeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEnvToolUnicodeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENVTOOLUNICODE_H__D858BFBF_0044_4036_9E95_2B368E81FFE5__INCLUDED_)
