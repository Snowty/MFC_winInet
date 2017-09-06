
// postTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "postTest.h"
#include "postTestDlg.h"
#include "afxdialogex.h"
#include <afxinet.h>
#include<atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CpostTestDlg dialog



CpostTestDlg::CpostTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CpostTestDlg::IDD, pParent)
	, m_strServerName(_T(""))
	, m_strObjectName(_T(""))
	, m_strRequest(_T(""))
	, m_strHtml(_T(""))
	, m_Port(80)
	, m_StatusCode()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpostTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADDRESS, m_strServerName);
	DDX_Text(pDX, IDC_LOCATION, m_strObjectName);
	DDX_Text(pDX, IDC_REQUESTSTR, m_strRequest);
	DDX_Text(pDX, IDC_HTML, m_strHtml);
	//  DDX_Text(pDX, IDC_PORT, m_Port);
	//DDX_Text(pDX, IDC_PORT, m_Port);
	//DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT2, m_StatusCode);
	DDX_Text(pDX, IDC_CODE, m_StatusCode);
}

BEGIN_MESSAGE_MAP(CpostTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON2, &CpostTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_SUBMIT, &CpostTestDlg::OnClickedSubmit)
	ON_BN_CLICKED(IDC_RESET, &CpostTestDlg::OnClickedReset)
	ON_EN_CHANGE(IDC_ADDRESS, &CpostTestDlg::OnChangeAddress)
	ON_EN_CHANGE(IDC_LOCATION, &CpostTestDlg::OnChangeLocation)
	ON_EN_CHANGE(IDC_REQUESTSTR, &CpostTestDlg::OnChangeRequeststr)
	ON_EN_CHANGE(IDC_HTML, &CpostTestDlg::OnChangeHtml)
//	ON_EN_CHANGE(IDC_PORT, &CpostTestDlg::OnChangePort)
//ON_EN_CHANGE(IDC_PORT, &CpostTestDlg::OnChangePort)
ON_EN_CHANGE(IDC_PORT, &CpostTestDlg::OnChangePort)
ON_EN_CHANGE(IDC_CODE, &CpostTestDlg::OnChangeCode)
END_MESSAGE_MAP()


// CpostTestDlg message handlers

BOOL CpostTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	(GetDlgItem(IDC_RESET))->EnableWindow(FALSE);
	(GetDlgItem(IDC_SUBMIT))->EnableWindow(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CpostTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CpostTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CpostTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CpostTestDlg::OnClickedSubmit()
{
	// TODO: Add your control notification handler code here
	CInternetSession m_InetSession;
	CHttpConnection *pServer = NULL;
	CHttpFile *pFile = NULL;
	UpdateData(TRUE);
	try
	{
		//INTERNET_PORT nPort;
		//nPort=5000;
		//m_Port = 80;
		pServer = m_InetSession.GetHttpConnection(m_strServerName,(INTERNET_PORT)m_Port);
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST,m_strObjectName);
		
		pFile->AddRequestHeaders(_T("User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko)"));
		pFile->AddRequestHeaders(_T("Content-Type: application/x-www-form-urlencoded"));
		pFile->AddRequestHeaders(_T("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8"));
		pFile->AddRequestHeaders(_T("Accept-Encoding: gzip, deflate"));
		pFile->AddRequestHeaders(_T("Accept-Language: zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3"));
		

		USES_CONVERSION;
		#ifdef _UNICODE  
			pFile->SendRequest(NULL,0,W2A(m_strRequest),m_strRequest.GetLength());  
		#else 
			pFile->SendRequest(NULL,0,(LPVOID)(LPCTSTR)m_strRequest,m_strRequest.GetLength());  
		#endif
		
		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);
		m_StatusCode = dwRet;

		//m_Mutex.Lock();
		m_strHtml="";
		char szBuff[1024];

		if(dwRet == HTTP_STATUS_OK)
		{
			UINT nRead;
			while((nRead = pFile->Read(szBuff,1023))>0)
			{
				m_strHtml += CString(szBuff,nRead);
			}
		}
		//m_Mutex.Unlock();

		delete pFile;
		delete pServer;

	}
	catch(CInternetException *e)
	{
		CString s;
		s.Format(_T("Internet Exception/r/nm_dwError:%u,m_dwContextError:%u"),e->m_dwError,e->m_dwContext);
		AfxMessageBox(s);
	}
	UpdateData(FALSE);
	(GetDlgItem(IDC_SUBMIT))->EnableWindow(TRUE);
	(GetDlgItem(IDC_RESET))->EnableWindow(TRUE);
}


void CpostTestDlg::OnClickedReset()
{
	// TODO: Add your control notification handler code here
	m_strRequest = _T("");
	m_strObjectName = _T("");
	m_strServerName = _T("");
	m_strHtml = _T("");
	m_Port = 80;

	UpdateData(FALSE);
	(GetDlgItem(IDC_SUBMIT))->EnableWindow(TRUE);
	(GetDlgItem(IDC_RESET))->EnableWindow(FALSE);
}


void CpostTestDlg::OnChangeAddress()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	(GetDlgItem(IDC_SUBMIT))->EnableWindow(TRUE);
}


void CpostTestDlg::OnChangeLocation()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CpostTestDlg::OnChangeRequeststr()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CpostTestDlg::OnChangeHtml()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


//void CpostTestDlg::OnChangePort()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}


//void CpostTestDlg::OnChangePort()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}


void CpostTestDlg::OnChangePort()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CpostTestDlg::OnChangeCode()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
