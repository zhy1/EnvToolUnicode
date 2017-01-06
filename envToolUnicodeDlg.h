// envToolUnicodeDlg.h : header file
//

#if !defined(AFX_ENVTOOLUNICODEDLG_H__06AF33E0_FB72_4CC7_BC9D_D95998C71D04__INCLUDED_)
#define AFX_ENVTOOLUNICODEDLG_H__06AF33E0_FB72_4CC7_BC9D_D95998C71D04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEnvToolUnicodeDlg dialog

class CEnvToolUnicodeDlg : public CDialog
{
// Construction
public:
	CEnvToolUnicodeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEnvToolUnicodeDlg)
	enum { IDD = IDD_ENVTOOLUNICODE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnvToolUnicodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEnvToolUnicodeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnChangeEdit1();
	afx_msg void OnButton3();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENVTOOLUNICODEDLG_H__06AF33E0_FB72_4CC7_BC9D_D95998C71D04__INCLUDED_)
