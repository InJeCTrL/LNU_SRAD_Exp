// ConfPanel.cpp: 实现文件
//

#include "stdafx.h"
#include "Stock.h"
#include "ConfPanel.h"
#include "afxdialogex.h"
#include "DataBaseMgr.h"

// ConfPanel 对话框

IMPLEMENT_DYNAMIC(ConfPanel, CDialogEx)

ConfPanel::ConfPanel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ConfPanel_DIALOG, pParent)
{
	DataBaseMgr db = DataBaseMgr();
	if (db.TestDB() == ERR)
	{
		m_In.EnableWindow(FALSE);
		m_Clean.EnableWindow(FALSE);
		MessageBox(L"数据库连接失败！", L"初始化失败");
	}
}

ConfPanel::~ConfPanel()
{
}

void ConfPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_In);
	DDX_Control(pDX, IDC_BUTTON2, m_Clean);
}


BEGIN_MESSAGE_MAP(ConfPanel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &ConfPanel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &ConfPanel::OnBnClickedButton1)
END_MESSAGE_MAP()


// ConfPanel 消息处理程序


//单击清空数据库
void ConfPanel::OnBnClickedButton2()
{
	DataBaseMgr db = DataBaseMgr();
	db.CleanDB();
}

//单击导入
void ConfPanel::OnBnClickedButton1()
{
	DataBaseMgr db = DataBaseMgr();
	TCHAR szFolderPath[MAX_PATH] = { 0 };
	CString strFolderPath = TEXT("");
	BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("请选择所有CSV文件所在目录");
	sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	sInfo.lpfn = NULL;

	// 显示文件夹选择对话框  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名  
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
		}
	}
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}

	db.CSV2DB(strFolderPath);
}