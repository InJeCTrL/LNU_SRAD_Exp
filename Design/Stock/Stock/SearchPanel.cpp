
// SearchPanel.cpp: 实现文件
//

#include "stdafx.h"
#include "Stock.h"
#include "SearchPanel.h"
#include "ConfPanel.h"
#include "afxdialogex.h"
#include "DataBaseMgr.h"
#include "DataPanel.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// SearchPanel 对话框

SearchPanel::SearchPanel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SearchPanel_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon= AfxGetApp()->LoadIcon(IDI_ICON1);

}

void SearchPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_RADIO1, m_radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_radio[2]);
	DDX_Control(pDX, IDC_RADIO4, m_radio[3]);
	DDX_Control(pDX, IDC_RADIO5, m_radio[4]);
	DDX_Control(pDX, IDC_RADIO6, m_radio[5]);
	DDX_Control(pDX, IDC_RADIO7, m_radio[6]);
	DDX_Control(pDX, IDC_COMBO1, m_combo[0]);
	DDX_Control(pDX, IDC_COMBO2, m_combo[1]);
	DDX_Control(pDX, IDC_COMBO3, m_combo[2]);
	DDX_Control(pDX, IDC_COMBO4, m_combo[3]);
	DDX_Control(pDX, IDC_COMBO5, m_combo[4]);
	DDX_Control(pDX, IDC_COMBO6, m_combo[5]);
	DDX_Control(pDX, IDC_EDIT2, m_edit[0][0]);
	DDX_Control(pDX, IDC_EDIT3, m_edit[0][1]);
	DDX_Control(pDX, IDC_EDIT4, m_edit[1][0]);
	DDX_Control(pDX, IDC_EDIT5, m_edit[1][1]);
	DDX_Control(pDX, IDC_EDIT6, m_edit[2][0]);
	DDX_Control(pDX, IDC_EDIT7, m_edit[2][1]);
	DDX_Control(pDX, IDC_EDIT8, m_edit[3][0]);
	DDX_Control(pDX, IDC_EDIT9, m_edit[3][1]);
	DDX_Control(pDX, IDC_EDIT10, m_edit[4][0]);
	DDX_Control(pDX, IDC_EDIT11, m_edit[4][1]);
	DDX_Control(pDX, IDC_EDIT12, m_edit[5][0]);
	DDX_Control(pDX, IDC_EDIT13, m_edit[5][1]);
	DDX_Control(pDX, IDC_EDIT14, m_edit_symbol);
}

BEGIN_MESSAGE_MAP(SearchPanel, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &SearchPanel::OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &SearchPanel::OnDblclkList1)
	ON_BN_CLICKED(IDOK, &SearchPanel::OnBnClickedOk)
	
	ON_COMMAND(ID_32771, &SearchPanel::On32771)
END_MESSAGE_MAP()


// SearchPanel 消息处理程序

BOOL SearchPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_list1.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加列   
	m_list1.InsertColumn(0, _T("股票代码"), LVCFMT_CENTER, rect.Width() / 2, 0);
	m_list1.InsertColumn(1, _T("公司名称"), LVCFMT_CENTER, rect.Width() / 2, 1);

	m_radio->SetCheck(1);
	//combox添加时间选项
	for (INT i = 0; i < 7; i++)
	{
		m_combo[i].AddString(L"最近一年");
		m_combo[i].AddString(L"最近五年");
		m_combo[i].AddString(L"最近十年");
	}
	m_combo[2].AddString(L"均值");
	m_combo[2].AddString(L"方差");
	m_combo[3].AddString(L"均值");
	m_combo[3].AddString(L"方差");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void SearchPanel::OnPaint()
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
HCURSOR SearchPanel::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void SearchPanel::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void SearchPanel::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;     // m_string100是控制变量
	CRect rc;
	m_Row = pNMListView->iItem;//获得选中的行  
	//m_Col = pNMListView->iSubItem;//获得选中列 
	CString Symbol = m_list1.GetItemText(m_Row, 0);
	CString Name = m_list1.GetItemText(m_Row, 1);
	if (!Symbol.IsEmpty())
	{
		//启动详细信息对话框
		DataPanel *DP = new DataPanel(Symbol, Name);
		DP->Create(IDD_DataPanel_DIALOG);
		DP->ShowWindow(SW_SHOWNORMAL);
	}
	
	*pResult = 0;
}

//单击搜索按钮
void SearchPanel::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	//UpdateData(true);
	for (INT i = 0; i < 7; i++)
	{
		if (m_radio[i].GetCheck())
		{
			SearchIndex = i;//搜索序号赋值
			//搜索范围选项赋值
			if (i < 6)
				Combo_index = m_combo[i].GetCurSel();
			//获取股票编号输入文本
			if (i == 6)
			{
				m_edit_symbol.GetWindowText(edit[0][0]);
				break;
			}
			m_edit[i][0].GetWindowText(edit[0][0]);
			m_edit[i][1].GetWindowText(edit[0][1]);
			break;
		}
	}
	//根据搜索条件所筛选出的结果放到一个数据集里，然后将数据集中的内容添加到列表项中
	DataBaseMgr db = DataBaseMgr();
	std::vector<std::array<CString,2>> result = db.SearchMainDG(SearchIndex, Combo_index, edit);
	m_list1.DeleteAllItems();
	//ListView中输出
	for (int i = 0; i < result.size(); i++)
	{
		m_list1.InsertItem(i, result[i][0]);
		for (int j = 1;j<2; j++)
		{
			m_list1.SetItemText(i, j, result[i][j]);
		}
	}
}

//单击顶部菜单
void SearchPanel::On32771()
{
	//模态启动配置面板
	ConfPanel cfp;
	cfp.DoModal();
}
