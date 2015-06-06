
// BATPackageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BATPackage.h"
#include "BATPackageDlg.h"
#include "afxdialogex.h"

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


// CBATPackageDlg dialog




CBATPackageDlg::CBATPackageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBATPackageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBATPackageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBATPackageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CBATPackageDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CBATPackageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDTEST, &CBATPackageDlg::OnBnClickedTest)
	ON_BN_CLICKED(IDBUILD, &CBATPackageDlg::OnBnClickedBuild)
END_MESSAGE_MAP()

// CBATPackageDlg message handlers

// BATPackage.exe = 14 chars
#define MY_NAME_LEN 14

BOOL CBATPackageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Store program directory
	GetModuleFileName(NULL, m_BUF_myDir, sizeof(m_BUF_myDir));
	ZeroMemory(m_BUF_myDir+strlen(m_BUF_myDir)-MY_NAME_LEN, MY_NAME_LEN);

	// Init load dialog
	ZeroMemory(&m_OFN_loadBatch, sizeof(OPENFILENAME));
	m_OFN_loadBatch.lStructSize = sizeof(OPENFILENAME);
	m_OFN_loadBatch.hwndOwner = NULL;
	m_OFN_loadBatch.lpstrFile = m_BUF_batchFilename;
	m_OFN_loadBatch.lpstrFile[0] = 0;
	m_OFN_loadBatch.nMaxFile = sizeof(m_BUF_batchFilename);
	m_OFN_loadBatch.lpstrFilter = "Batch files\0*.BAT\0All files\0*.*\0";
	m_OFN_loadBatch.nFilterIndex = 1;
	m_OFN_loadBatch.lpstrFileTitle = NULL;
	m_OFN_loadBatch.nMaxFileTitle = 0;
	m_OFN_loadBatch.lpstrInitialDir = NULL;
	m_OFN_loadBatch.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	m_OFN_loadBatch.lpstrTitle = "Open batch file";

	// Init save dialog
	ZeroMemory(&m_OFN_saveEXE, sizeof(OPENFILENAME));
	m_OFN_saveEXE.lStructSize = sizeof(OPENFILENAME);
	m_OFN_saveEXE.hwndOwner = NULL;
	m_OFN_saveEXE.lpstrFile = m_BUF_EXEFilename;
	m_OFN_saveEXE.lpstrFile[0] = 0;
	m_OFN_saveEXE.nMaxFile = sizeof(m_BUF_EXEFilename);
	m_OFN_saveEXE.lpstrFilter = "Microsoft Windows executable file\0*.exe";
	m_OFN_saveEXE.nFilterIndex = 1;
	m_OFN_saveEXE.lpstrFileTitle = NULL;
	m_OFN_saveEXE.nMaxFileTitle = 0;
	m_OFN_saveEXE.lpstrInitialDir = NULL;
	m_OFN_saveEXE.lpstrTitle = "Save packaged EXE file";
	m_OFN_saveEXE.lpstrDefExt = "exe";

	// Get UI items
	m_CED_batchBox = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT1));

	// Style the UI
	m_CFN_codeFont.CreatePointFont(100, "Courier"); // 10 point Courier
	m_CED_batchBox->SetFont(&m_CFN_codeFont);

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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBATPackageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBATPackageDlg::OnPaint()
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
HCURSOR CBATPackageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBATPackageDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

#define BATCH_MAX 32000

void CBATPackageDlg::OnBnClickedButton1()
{
	char errbuf[128];
	char filedata[BATCH_MAX];
	HANDLE batchFile;
	DWORD bytesRead;

	ZeroMemory(filedata, BATCH_MAX);

	GetOpenFileName(&m_OFN_loadBatch);
	if(strlen(m_OFN_loadBatch.lpstrFile) < 2)
		return;
	//MessageBox(loadBatch.lpstrFile, "BATCH FILE", MB_OK);
	batchFile = CreateFile(m_OFN_loadBatch.lpstrFile, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if(GetLastError()) {
		sprintf(errbuf, "Could not open file - Error 0x%08X", GetLastError());
		MessageBox(errbuf, "Error loading", MB_OK|MB_ICONERROR);
		return;
	}
	if(!ReadFile(batchFile, filedata, BATCH_MAX, &bytesRead, NULL)) {
		sprintf(errbuf, "Could not read file data - Error 0x%08X", GetLastError());
		MessageBox(errbuf, "Error reading", MB_OK|MB_ICONERROR);
		return;
	}
	m_CED_batchBox->SetWindowText(filedata);

	CloseHandle(batchFile);
}

void CBATPackageDlg::OnBnClickedTest()
{
	const char* TEMP_FILE = "temp.bat";
	const char* TEMP_FILE_COMMAND = "CMD /C temp.bat & pause";
	char errbuf[128];
	HANDLE tempBatchFile;
	DWORD bytesWritten;
	char batchData[BATCH_MAX];

	// Get batch script data
	ZeroMemory(batchData, BATCH_MAX);
	m_CED_batchBox->GetWindowText(batchData, BATCH_MAX);

	// Create temp file
	tempBatchFile = CreateFile(TEMP_FILE, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(!WriteFile(tempBatchFile, batchData, strlen(batchData), &bytesWritten, NULL)) {
		sprintf(errbuf, "Could not write temporary file data - Error 0x%08X", GetLastError());
		MessageBox(errbuf, "Error writing temp file", MB_OK|MB_ICONERROR);
		return;
	}
	CloseHandle(tempBatchFile);

	// Run script
	system(TEMP_FILE_COMMAND);
	
	// Delete temp file
	DeleteFile(TEMP_FILE);
}

void CBATPackageDlg::OnBnClickedBuild()
{
	const char* LOADER_NAME = "loader.exe";
	char errbuf[128];
	FILE* output;
	char batchData[BATCH_MAX];
	char* p_batchData = batchData;
	char loaderPath[256];

	// Get batch script data
	ZeroMemory(batchData, BATCH_MAX);
	m_CED_batchBox->GetWindowText(batchData, BATCH_MAX);

	// Get path to loader
	ZeroMemory(loaderPath, sizeof(loaderPath));
	memcpy(loaderPath, m_BUF_myDir, sizeof(m_BUF_myDir));
	memcpy(loaderPath+strlen(loaderPath), LOADER_NAME, strlen(LOADER_NAME));

	// Prompt for output filename
	GetSaveFileName(&m_OFN_saveEXE);
	if(strlen(m_OFN_saveEXE.lpstrFile) < 2)
		return;

	// Copy loader
	if(!CopyFile(loaderPath, m_OFN_saveEXE.lpstrFile, FALSE)) {
		sprintf(errbuf, "Could not copy loader - Error 0x%08X", GetLastError());
		MessageBox(errbuf, "Error writing executable", MB_OK|MB_ICONERROR);
		return;
	}

	// Open output file
	output = fopen(m_OFN_saveEXE.lpstrFile, "a");
	if(!output) {
		sprintf(errbuf, "Could not open output file - C Error %d", GetLastError());
		MessageBox(errbuf, "Error writing executable", MB_OK|MB_ICONERROR);
		return;
	}

	// Seek to end of output file
	if(fseek(output, 0, SEEK_END) != 0) {
		sprintf(errbuf, "Could not seek to end of output file - C Error %d", GetLastError());
		MessageBox(errbuf, "Error writing executable", MB_OK|MB_ICONERROR);
		return;
	}

	// Append batch script data
	while(*p_batchData != 0) {
		fputc(*p_batchData, output);
		if(ferror(output)) {
			sprintf(errbuf, "Could not write to output file - C Error %d", GetLastError());
			MessageBox(errbuf, "Error writing executable", MB_OK|MB_ICONERROR);
			return;
		}
		p_batchData++;
	}

	fclose(output);
	MessageBox("Executable saved.", "OK", MB_ICONINFORMATION|MB_OK);
}
