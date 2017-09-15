
// HardwareInfoObtainerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HardwareInfoObtainer.h"
#include "HardwareInfoObtainerDlg.h"
#include "afxdialogex.h"
#include "HardwareInfoHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::string ConverCStringToStdString( CString & cstrValue )
{
	std::string strRet;
	strRet.clear();
	int nSize = ::WideCharToMultiByte(CP_UTF8, 0, cstrValue.GetBuffer(), -1, NULL, 0, NULL, NULL);
	char * szcSrc = new char[nSize];
	memset(szcSrc, 0, sizeof(char) * nSize);
	::WideCharToMultiByte(CP_UTF8, 0, cstrValue.GetBuffer(), -1, szcSrc, nSize, NULL, NULL);
	strRet = szcSrc;
	delete[] szcSrc;
	szcSrc = NULL;
	return strRet;
}

std::string ConverCStringToStdString( CString & cstrValue, DWORD dwFormatW)
{
	std::string strRet;
	strRet.clear();
	int nSize = ::WideCharToMultiByte(dwFormatW, 0, cstrValue.GetBuffer(), -1, NULL, 0, NULL, NULL);
	char * szcSrc = new char[nSize];
	memset(szcSrc, 0, sizeof(char) * nSize);
	::WideCharToMultiByte(dwFormatW, 0, cstrValue.GetBuffer(), -1, szcSrc, nSize, NULL, NULL);
	strRet = szcSrc;
	delete[] szcSrc;
	szcSrc = NULL;
	return strRet;
}

CString ConvertStdStringToCString( const std::string & strValue )
{
	CString cstrRet;
	cstrRet.Empty();
	int nLength = ::MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), -1, NULL,0);
	TCHAR * szText1 = new TCHAR[nLength+1];
	::MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), -1, szText1, nLength+1);
	cstrRet = szText1;
	delete[] szText1;
	szText1 = NULL;
	return cstrRet;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CHardwareInfoObtainerDlg 对话框




CHardwareInfoObtainerDlg::CHardwareInfoObtainerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHardwareInfoObtainerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHardwareInfoObtainerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHardwareInfoObtainerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHardwareInfoObtainerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHardwareInfoObtainerDlg 消息处理程序

BOOL CHardwareInfoObtainerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHardwareInfoObtainerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHardwareInfoObtainerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHardwareInfoObtainerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHardwareInfoObtainerDlg::OnBnClickedOk()
{
	std::string strMotherBoardID = HardwareInfoHelper::GetMotherBoardID();
	std::string strCPUID = HardwareInfoHelper::GetCPUID();
	std::string strHarddiskID = HardwareInfoHelper::GetHarddiskID();
	std::string strNetMacID = HardwareInfoHelper::GetNetMacID();

	//测试代码
#if 0
	CStdioFile file;
	if (file.Open(_T("e:\\info.txt"), CFile::modeCreate | CFile::modeWrite))
	{
		int i = 0;
		while (i++ < 999)
		{
			CString strInfo;
			strInfo.Format(_T("MotherBoard:\r\n%s\r\nCPUID:\r\n%s\r\nHarddisk:\r\n%s\r\nNetMacID:\r\n%s\r\n"),
				ConvertStdStringToCString(strMotherBoardID),
				ConvertStdStringToCString(strCPUID),
				ConvertStdStringToCString(strHarddiskID),
				ConvertStdStringToCString(strNetMacID));
			file.WriteString(_T("\r\n"));
			file.WriteString(strInfo);
			file.WriteString(_T("\r\n"));
		}
		file.Close();
	}
#endif
}
