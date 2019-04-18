
// 9-20Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "9-20.h"
#include "9-20Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy920Dlg 对话框



CMy920Dlg::CMy920Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY920_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy920Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Data[0]);
	DDX_Control(pDX, IDC_EDIT2, m_Data[1]);
	DDX_Control(pDX, IDC_EDIT3, m_Data[2]);
	DDX_Control(pDX, IDC_EDIT4, m_Data[3]);
	DDX_Control(pDX, IDC_EDIT5, m_Data[4]);
	DDX_Control(pDX, IDC_LIST1, m_List);
}

BEGIN_MESSAGE_MAP(CMy920Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDOK, &CMy920Dlg::OnBnClickedOk)
ON_BN_CLICKED(IDC_BUTTON1, &CMy920Dlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CMy920Dlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON4, &CMy920Dlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON5, &CMy920Dlg::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON3, &CMy920Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMy920Dlg 消息处理程序

BOOL CMy920Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy920Dlg::OnPaint()
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
HCURSOR CMy920Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//设置临时数据
BOOL CMy920Dlg::SetTempDatas()
{
	CString InputStrs[5] = { 0 };//输入的5个数据字符串形式

	//检查空输入
	for (int i = 0; i < 5; i++)
	{
		m_Data[i].GetWindowTextW(InputStrs[i]);
		if (InputStrs[i] == "")
		{
			CString ErrTip;//错误提示信息
			ErrTip.Format(_T("Data %d is blank!"), i);
			MessageBox(ErrTip, _T("No Blank Data"));
			return false;
		}
	}
	//没有空输入
	//数据临时保存
	for (int i = 0; i < 5; i++)
	{
		tDatas[i + 1] = _wtol(InputStrs[i]);
	}
	return true;
}

//单击新增按钮
void CMy920Dlg::OnBnClickedButton1()
{
	//设置临时数据数组成功
	if (SetTempDatas() == TRUE)
		AddDatas();//添加数据到list

	return;
}

//添加数据到list
void CMy920Dlg::AddDatas()
{
	//第一个被插入的数据组合
	if (DataSets.empty() == true)
	{
		tDatas[0] = 0;
	}
	//不是第一个被插入的数据组合
	else
	{
		tDatas[0] = DataSets.back()[0] + 1;
	}
	DataSets.push_back(tDatas);//插入list
	CString str_Pos;//字符串形式的序号
	str_Pos.Format(_T("%d"), tDatas[0]);
	m_List.AddString(str_Pos);//添加序号到列表

	return;
}

//根据选定的列表框项目设置控件数据到临时数组
BOOL CMy920Dlg::SetTempDatasByListView()
{
	LONG index;//列表框中选定的下标
	CString str_Pos;//字符串形式序号

	index = m_List.GetCurSel();//获取列表框选定下标
	//没有选定列表框的项目
	if (index == CB_ERR)
	{
		MessageBox(_T("You haven't selected one item!"), _T("Error"));
		return false;
	}
	m_List.GetText(index, str_Pos);//获取选定的数据组合序号
	for (list<array<LONG, 6>>::iterator i = DataSets.begin(); i != DataSets.end(); i++)
	{
		//序号相等，临时数组赋值并跳出
		if (_wtol(str_Pos) == (*i)[0])
		{
			tDatas = *i;
			break;
		}
	}
	return true;
}

//单击显示按钮
void CMy920Dlg::OnBnClickedButton2()
{
	if (SetTempDatasByListView() == TRUE)
	{
		//EditBox中显示信息
		CString OutStrs[5] = { 0 };//待输出的5个数据字符串形式
		for (int i = 1; i <= 5; i++)
		{
			OutStrs[i - 1].Format(_T("%ld"), tDatas[i]);//LtoA
			m_Data[i - 1].SetWindowTextW(OutStrs[i - 1]);//显示
		}
	}

	return;
}

//单击计算按钮
void CMy920Dlg::OnBnClickedButton4()
{
	if (SetTempDatasByListView() == TRUE)
	{
		LONG min = LONG_MAX, max = LONG_MIN;
		INT pos_min = 0, pos_max = 0;

		for (int i = 1; i <= 5; i++)
		{
			if (min > tDatas[i])
			{
				pos_min = i;
				min = tDatas[i];
			}
			if (max < tDatas[i])
			{
				pos_max = i;
				max = tDatas[i];
			}
		}
		CString ShowTip;//用于显示计算结果
		ShowTip.Format(_T("Max[ %d ] = %ld\nMin[ %d ] = %ld"), pos_min, min, pos_max, max);
		MessageBox(ShowTip, _T("Result"));
	}

	return;
}

//单击删除按钮
void CMy920Dlg::OnBnClickedButton5()
{
	if (SetTempDatasByListView() == TRUE)
	{
		for (list<array<LONG, 6>>::iterator i = DataSets.begin(); i != DataSets.end(); i++)
		{
			//序号相等，删除数据组合并跳出
			if (tDatas[0] == (*i)[0])
			{
				DataSets.erase(i);
				m_List.DeleteString(m_List.GetCurSel());
				break;
			}
		}
	}
}

//单击修改按钮
void CMy920Dlg::OnBnClickedButton3()
{
	//设置临时数据数组
	if (SetTempDatas() == TRUE)
	{
		for (list<array<LONG, 6>>::iterator i = DataSets.begin(); i != DataSets.end(); i++)
		{
			//序号相等，赋值数据组合并跳出
			if (tDatas[0] == (*i)[0])
			{
				*i = tDatas;
				break;
			}
		}
		MessageBox(_T("Modified!"), _T("Tip"));
	}

	return;
}
