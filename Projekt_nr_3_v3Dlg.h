
// Projekt_nr_3_v3Dlg.h : header file
//

#pragma once


// CProjektnr3v3Dlg dialog
class CProjektnr3v3Dlg : public CDialogEx
{
// Construction
public:
	CProjektnr3v3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJEKT_NR_3_V3_DIALOG };
#endif

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
	afx_msg void OnBnClickedButton1();
	CComboBox code_currency_from;
//	double value_currency_from;
	afx_msg void OnEnChangeEdit2();
	CString cstring_value_from;
	CComboBox code_currency_to;
	afx_msg void OnEnChangeEdit1();
//	string value_currency_to;
	CString value_currency_to;
	
};
