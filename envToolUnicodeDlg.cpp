// envToolUnicodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "envToolUnicode.h"
#include "envToolUnicodeDlg.h"

#include <windows.h>
#include <malloc.h>
#include <stdio.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TOTALBYTES    8192
#define BYTEINCREMENT 4096
/////////////////////////////////////////////////////////////////////////////
// CEnvToolUnicodeDlg dialog

CEnvToolUnicodeDlg::CEnvToolUnicodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEnvToolUnicodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnvToolUnicodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnvToolUnicodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnvToolUnicodeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEnvToolUnicodeDlg, CDialog)
	//{{AFX_MSG_MAP(CEnvToolUnicodeDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnvToolUnicodeDlg message handlers

BOOL CEnvToolUnicodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEnvToolUnicodeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEnvToolUnicodeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 打开reg.读取path信息
void CEnvToolUnicodeDlg::OnButton1() 
{

	DWORD BufferSize = TOTALBYTES; 

    HKEY hKEY;
    HKEY hKeyRoot = HKEY_LOCAL_MACHINE;

	// 如果使用  KEY_READ权限就是可读但是不能写，不需要管理员权限
	// 如果使用  KEY_ALL_ACCESS/KEY_READ|KEY_WRITE 权限就是可写，需要管理员权限
    long ret0 = (::RegOpenKeyEx(
		hKeyRoot,
		_T("System\\CurrentControlSet\\Control\\Session Manager\\Environment"),
		0,
		KEY_ALL_ACCESS,//KEY_ALL_ACCESS, //KEY_READ|KEY_WRITE, 
		&hKEY));

    if (ret0 != ERROR_SUCCESS)//如果无法打开hKEY,则中止程序的执行
    {
        // AfxMessageBox(_T("错误：无法打开有关的hKEY，请使用管理员模式运行！"));
        AfxMessageBox(_T("错误：无法打开Path，请使用管理员模式运行！"));
        return;
    }

    DWORD cbData;
    // DWORD dwRet;

    VOID* PerfData = malloc( BufferSize );
    BufferSize += 4096;
    PerfData = realloc( PerfData, BufferSize );
	cbData = BufferSize; //定义数据长度


    DWORD keyType = REG_EXPAND_SZ;//定义数据类型 REG_EXPAND_SZ 如果是path
    //DWORD keyType = REG_EXPAND_SZ;//定义数据类型 REG_EXPAND_SZ 2 如果是path 
    //DWORD keyType = REG_EXPAND_SZ;//定义数据类型 REG_EXPAND_SZ 如果是path

    // CString whichKey = _T("OS");//要查询的键名称
     CString whichKey = _T("Path");//要查询的键名称
    // CString whichKey = _T("fanteng");//要查询的键名称

    CEdit *pEdit = (CEdit *) GetDlgItem(IDC_EDIT1);
    pEdit->SetWindowText(_T("to\r\nbe\r\nready\nshow:"));

    long ret1 = ::RegQueryValueEx(hKEY, whichKey, NULL, NULL, (LPBYTE)PerfData, &cbData);
    if (ret1 != ERROR_SUCCESS) {
        AfxMessageBox(_T("错误：打开了却无法读取，检查系统状态！")+whichKey);
        return;
    }
    // pEdit->SetWindowText((LPCTSTR)PerfData);
	CEnvToolUnicodeApp *app = (CEnvToolUnicodeApp *)AfxGetApp(); //生成指向应用程序类的指针 
	app->GPerfData = PerfData;
	app->GcbData = cbData;
	app->ghKEY= hKEY;
	app->pathString= (LPBYTE)PerfData;
    pEdit->SetWindowText((LPCTSTR)app->GPerfData);

}

void CEnvToolUnicodeDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}


// 保存到全局
void CEnvToolUnicodeDlg::OnButton3() 
{
	//(LPCTSTR)
	//下面的保存
	CEnvToolUnicodeApp *app = (CEnvToolUnicodeApp *)AfxGetApp(); //生成指向应用程序类的指针 
    CEdit *pEdit = (CEdit *) GetDlgItem(IDC_EDIT2);
    // 	LPTSTR*  testChar;
	pEdit->GetWindowText(app->inputString);

	if(0>= app->inputString.GetLength()){
		return;
	}

	//app->inputString= _T(";")+app->inputString;

    // #include <atlconv.h>
    // USES_CONVERSION;
    // char * pca = W2A( cstr );
	// TODO DEBUG AfxMessageBox(app->inputString);

	// USES_CONVERSION;
	 // testChar = W2A(m_cstr);
    app->inputText  = app->inputString.GetBuffer(app->inputString.GetLength()+1);   //m_cstr.GetLength()
    //pEdit->SetWindowText(app->inputText);
	// AfxMessageBox(testChar);
	AfxMessageBox(app->inputString);
    // m_cstr.ReleaseBuffer();
	/*
	LPTSTR javaHome = _T(";%JAVA_HOME%\\bin;");
 
    TCHAR *temp = new TCHAR[cbData+sizeof(javaHome)];
 
    _tcscpy_s(temp, cbData, (LPTSTR)PerfData);
 
    LPTSTR path = _tcscat(temp, javaHome);
 
    RegSetValueEx(hkResult, 
        L"Path",        
        0,                        
        REG_SZ,                
        (LPBYTE) path, 
        _tcsclen(path)*sizeof(TCHAR))
 
         DWORD dwResult;
 */
}

// 合并path和全局变量
void CEnvToolUnicodeDlg::OnButton2() 
{
	CEnvToolUnicodeApp *app = (CEnvToolUnicodeApp *)AfxGetApp(); //生成指向应用程序类的指针 

	if(app->GPerfData == NULL || app->inputText == NULL ||  app->GcbData ==NULL ){
		return;
	}
    CEdit *pEdit = (CEdit *) GetDlgItem(IDC_EDIT1);

	// LPTSTR javaHome = _T(";%JAVA_HOME%\\bin;");


	CString newStr = _T(";")+app->inputString;
	LPTSTR newChar=  newStr.GetBuffer(newStr.GetLength()+1);
    // TCHAR *temp = new TCHAR[app->GcbData + sizeof(javaHome)];
    // TCHAR *temp = new TCHAR[app->GcbData + sizeof(app->inputText)];
     TCHAR *temp = new TCHAR[app->GcbData +  sizeof(newChar)];
 
    // _tcscpy_s(temp, app->GcbData, (LPCTSTR)app->GPerfData);  //vs 2005 
    //_tcscpy(temp, (LPCTSTR)app->GPerfData);  //vs 2005 
    _tcscpy(temp, (LPCTSTR)app->GPerfData);  //vc 6 改为只接受2个参数

	LPTSTR path = _tcscat(temp, _T(newChar));
	// LPTSTR path = _tcscat(temp, _T(app->inputText));
	// LPTSTR path = _tcscat(_T(";"), _T(app->inputText));
	// path = _tcscat(temp, path);
	// LPTSTR path = _tcscat(temp, javaHome);

    pEdit->SetWindowText(path);


	/*

CEnvToolUnicodeApp *app = (CEnvToolUnicodeApp *)AfxGetApp(); //生成指向应用程序类的指针 
app->x = 123; //访问变量x 
int z = app->f(1); //访问函数f() 
CString str;
str.Format(_T("%d"),z);
AfxMessageBox( str);
*/

}

//  读取保存的全局变量
void CEnvToolUnicodeDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CEnvToolUnicodeApp *app = (CEnvToolUnicodeApp *)AfxGetApp(); //生成指向应用程序类的指针 
	AfxMessageBox(app->inputText);
	
}

void CEnvToolUnicodeDlg::OnButton5() 
{
	CEnvToolUnicodeApp *app = (CEnvToolUnicodeApp *)AfxGetApp(); //生成指向应用程序类的指针 

	if(app->GPerfData == NULL || app->GcbData ==NULL ){
		return;
	}
    CEdit *pEdit = (CEdit *) GetDlgItem(IDC_EDIT1);

	// LPTSTR javaHome = _T(";%JAVA_HOME%\\bin;");


	
	CString newStr;
	LPTSTR newChar; 
	TCHAR *temp;
	LPTSTR path;

	pEdit->GetWindowText(app->pathString);
/*
	if( app->inputText != NULL){

		newStr = _T(";")+app->pathString;
		//newChar=  newStr.GetBuffer(newStr.GetLength()+1);
		// TCHAR *temp = new TCHAR[app->GcbData + sizeof(javaHome)];
		// TCHAR *temp = new TCHAR[app->GcbData + sizeof(app->inputText)];
		//temp = new TCHAR[app->GcbData +  sizeof(newChar)];
 
		// _tcscpy_s(temp, app->GcbData, (LPCTSTR)app->GPerfData);  //vs 2005 
		//_tcscpy(temp, (LPCTSTR)app->GPerfData);  //vs 2005 
		//_tcscpy(temp, (LPCTSTR)app->GPerfData);  //vc 6 改为只接受2个参数


		// path = _tcscat(temp, _T(newChar));
		// LPTSTR path = _tcscat(temp, _T(app->inputText));
		// LPTSTR path = _tcscat(_T(";"), _T(app->inputText));
		// path = _tcscat(temp, path);
		// LPTSTR path = _tcscat(temp, javaHome);
		
		//temp = new TCHAR[newStr.GetLength()];
		//_tcscpy(temp, (LPCTSTR)newStr);
		//path = temp;
	}else{
		//temp = new TCHAR[app->GcbData];
		//_tcscpy(temp, (LPCTSTR)app->GPerfData);
		// path = temp;
		newStr = app->pathString;
	}*/
		newStr = app->pathString;
		newChar=  newStr.GetBuffer(newStr.GetLength()+1 );
		temp = new TCHAR[newStr.GetLength()+1];
		_tcscpy(temp, (LPCTSTR)newStr);
		path = temp;
     // pEdit->SetWindowText(path);

	AfxMessageBox(path);



      long ret1 =   RegSetValueEx(app->ghKEY, 
        _T("Path"),        
        0,                        
        REG_EXPAND_SZ,                
        (LPBYTE) path, 
        _tcsclen(path)*sizeof(TCHAR));
    if (ret1 != ERROR_SUCCESS) {
		CString str;
		str.Format(_T("%d"),ret1);
        AfxMessageBox(str);
	str.Format(_T("%lu"), GetLastError());
	MessageBox(str);
        return;
    }

         DWORD dwResult;
		 SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0,LPARAM("Environment"), SMTO_ABORTIFHUNG, 5000, &dwResult);
 
}
