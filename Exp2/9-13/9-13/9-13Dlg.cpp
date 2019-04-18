
// 9-13Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "9-13.h"
#include "9-13Dlg.h"
#include "afxdialogex.h"

#define RGB_MIN 0
#define RGB_MAX 255

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy913Dlg 对话框



CMy913Dlg::CMy913Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY913_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy913Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_RedScroll);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_GreenScroll);
	DDX_Control(pDX, IDC_SCROLLBAR3, m_BlueScroll);
	DDX_Control(pDX, IDC_EDIT1, m_RedShow);
	DDX_Control(pDX, IDC_EDIT2, m_GreenShow);
	DDX_Control(pDX, IDC_EDIT3, m_BlueShow);
}

BEGIN_MESSAGE_MAP(CMy913Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR1, &CMy913Dlg::OnNMThemeChangedScrollbar1)
//ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR1, &CMy913Dlg::OnNMThemeChangedScrollbar1)
ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMy913Dlg 消息处理程序

BOOL CMy913Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	initScrollBars();	//初始化各个水平滚动条

	//RGB值初始为0
	m_RedShow.SetWindowTextW(_T("0"));
	m_GreenShow.SetWindowTextW(_T("0"));
	m_BlueShow.SetWindowTextW(_T("0"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy913Dlg::initScrollBars()
{
	m_RedScroll.SetScrollRange(RGB_MIN, RGB_MAX);
	m_GreenScroll.SetScrollRange(RGB_MIN, RGB_MAX);
	m_BlueScroll.SetScrollRange(RGB_MIN, RGB_MAX);
}

void CMy913Dlg::DrawOval()
{
	CPaintDC dc(this);
	CBrush brush(RGB(R, G, B));

	dc.SelectObject(&brush);//选择画刷
	dc.Ellipse(&OvalRect);//画椭圆
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy913Dlg::OnPaint()
{
	DrawOval();	//画椭圆

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
HCURSOR CMy913Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy913Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UINT nowPos = pScrollBar->GetScrollPos();//获取当前滚动条轴位置
	switch (nSBCode)
	{
	//拖动事件
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos(nPos);
		UpdateData(FALSE);
		break;
	//单击左箭头
	case SB_LINEUP:
		if (nowPos > RGB_MIN)
		{
			pScrollBar->SetScrollPos(nowPos - 1);
		}
		break;
	//单击右箭头
	case SB_LINEDOWN:
		if (nowPos < RGB_MAX)
		{
			pScrollBar->SetScrollPos(nowPos + 1);
		}
		break;
	//单击左空白
	case SB_PAGEUP:
		if (nowPos > RGB_MIN)
		{
			pScrollBar->SetScrollPos(nowPos - 1);
		}
		break;
	//单击右空白
	case SB_PAGEDOWN:
		if (nowPos < RGB_MAX)
		{
			pScrollBar->SetScrollPos(nowPos + 1);
		}
		break;
	default:
		break;
	}
	//某RGB的字符串形式
	CString str_RGB;
	//转换UINT2CString
	str_RGB.Format(_T("%d"), nowPos);
	//设置EditBox
	//本次设置了红色
	if (pScrollBar == &m_RedScroll)
	{
		R = nowPos;
		m_RedShow.SetWindowTextW(str_RGB);
	}
	//本次设置了绿色
	else if (pScrollBar == &m_GreenScroll)
	{
		G = nowPos;
		m_GreenShow.SetWindowTextW(str_RGB);
	}
	//本次设置了蓝色
	else if (pScrollBar == &m_BlueScroll)
	{
		B = nowPos;
		m_BlueShow.SetWindowTextW(str_RGB);
	}
	InvalidateRect(&OvalRect);//重绘椭圆区域防止整个界面闪烁

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
