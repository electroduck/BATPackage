
// BATPackageDlg.h : header file
//

#pragma once


// CBATPackageDlg dialog
class CBATPackageDlg : public CDialogEx
{
// Construction
public:
	CBATPackageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BATPACKAGE_DIALOG };

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
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();

	
private:
	OPENFILENAME m_OFN_loadBatch;
	char m_BUF_batchFilename[256];
	char m_BUF_EXEFilename[256];
	CEdit* m_CED_batchBox;
	CFont m_CFN_codeFont;
	OPENFILENAME m_OFN_saveEXE;
	char m_BUF_myDir[256];

public:
	afx_msg void OnBnClickedTest();
	afx_msg void OnBnClickedBuild();
};
