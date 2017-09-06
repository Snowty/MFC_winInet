
// postTestDlg.h : header file
//

#pragma once
#include <afxinet.h>

// CpostTestDlg dialog
class CpostTestDlg : public CDialogEx
{
// Construction
public:
	CpostTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_POSTTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CString m_strServerName;
	CString m_strObjectName;
	CString m_strRequest;
	afx_msg void OnClickedSubmit();
	afx_msg void OnClickedReset();
	afx_msg void OnChangeAddress();
	afx_msg void OnChangeLocation();
	afx_msg void OnChangeRequeststr();
//	CString m_Result;
//	CString m_strHtml;
	CString m_strHtml;
//	INTERNET_PORT m_Port;
	afx_msg void OnChangeHtml();
//	CString m_Port;
//	afx_msg void OnChangePort();
	
//	INTERNET_PORT m_Port;
//	afx_msg void OnChangePort();
	DWORD m_Port;
	afx_msg void OnChangePort();
//	DWORD m_StatusCode;
	DWORD m_StatusCode;
	afx_msg void OnChangeCode();
};
