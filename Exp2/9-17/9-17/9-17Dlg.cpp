
// 9-17Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "9-17.h"
#include "9-17Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy917Dlg 对话框



CMy917Dlg::CMy917Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY917_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy917Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_COMBO1, m_PenColor);
	DDX_Control(pDX, IDC_COMBO2, m_BrushColor);
	DDX_Control(pDX, IDC_RADIO1, m_LineType[0]);
	DDX_Control(pDX, IDC_RADIO2, m_LineType[1]);
	DDX_Control(pDX, IDC_RADIO3, m_LineType[2]);
	DDX_Control(pDX, IDC_RADIO4, m_LineType[3]);
	DDX_Control(pDX, IDC_RADIO5, m_FillType[0]);
	DDX_Control(pDX, IDC_RADIO6, m_FillType[1]);
	DDX_Control(pDX, IDC_RADIO7, m_FillType[2]);
	DDX_Control(pDX, IDC_RADIO8, m_FillType[3]);
}

BEGIN_MESSAGE_MAP(CMy917Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy917Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy917Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMy917Dlg 消息处理程序

BOOL CMy917Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//radio初始
	m_LineType[0].SetCheck(1);
	m_FillType[0].SetCheck(1);
	//ListView填充
	m_List.AddString(_T("Line"));
	m_List.AddString(_T("Circle"));
	m_List.AddString(_T("Rectangle"));
	m_List.AddString(_T("RoundRectangle"));
	//Combo_PenColor填充
	m_PenColor.AddString(_T("Red"));
	m_PenColor.AddString(_T("Green"));
	m_PenColor.AddString(_T("Blue"));
	//Combo_BrushColor填充
	m_BrushColor.AddString(_T("Red"));
	m_BrushColor.AddString(_T("Green"));
	m_BrushColor.AddString(_T("Blue"));
	//初始化画笔
	pen[0][0].CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pen[1][0].CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pen[2][0].CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pen[0][1].CreatePen(PS_DASH, 1, RGB(0, 0, 255));
	pen[1][1].CreatePen(PS_DASH, 1, RGB(0, 255, 0));
	pen[2][1].CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	pen[0][2].CreatePen(PS_DOT, 1, RGB(0, 0, 255));
	pen[1][2].CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	pen[2][2].CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	pen[0][3].CreatePen(PS_DASHDOT, 1, RGB(0, 0, 255));
	pen[1][3].CreatePen(PS_DASHDOT, 1, RGB(0, 255, 0));
	pen[2][3].CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
	//初始化画刷
	brush[0][0].CreateSolidBrush(RGB(0, 0, 255));
	brush[1][0].CreateSolidBrush(RGB(0, 255, 0));
	brush[2][0].CreateSolidBrush(RGB(255, 0, 0));
	brush[0][1].CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
	brush[1][1].CreateHatchBrush(HS_CROSS, RGB(0, 255, 0));
	brush[2][1].CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));
	brush[0][2].CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 255));
	brush[1][2].CreateHatchBrush(HS_FDIAGONAL, RGB(0, 255, 0));
	brush[2][2].CreateHatchBrush(HS_FDIAGONAL, RGB(255, 0, 0));
	brush[0][3].CreateHatchBrush(HS_BDIAGONAL, RGB(0, 0, 255));
	brush[1][3].CreateHatchBrush(HS_BDIAGONAL, RGB(0, 255, 0));
	brush[2][3].CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy917Dlg::OnPaint()
{
	CPaintDC myDrawDC(this);

	//选择画笔
	myDrawDC.SelectObject(pen[m_PenColor.GetCurSel()][m_LineType[1].GetState() +
													m_LineType[2].GetState() * 2 + 
													m_LineType[3].GetState() * 3]);
	//选择画刷
	myDrawDC.SelectObject(brush[m_BrushColor.GetCurSel()][m_FillType[1].GetState() +
													m_FillType[2].GetState() * 2 +
													m_FillType[3].GetState() * 3]);
	switch (m_List.GetCurSel())
	{
	//画圆
	case 0:
		myDrawDC.Ellipse(&RedrawRt);
		break;
	//画线
	case 1:
		myDrawDC.MoveTo(320, 150);
		myDrawDC.LineTo(420, 50);
		break;
	//画矩形
	case 2:
		myDrawDC.Rectangle(&RedrawRt);
		break;
	//画圆角矩形
	case 3:
		myDrawDC.RoundRect(&RedrawRt, RRCT);
		break;
	default:
		break;
	}

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
HCURSOR CMy917Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy917Dlg::OnBnClickedButton1()
{
	InvalidateRect(&RedrawRt);
}


void CMy917Dlg::OnBnClickedButton2()
{
	//清除画笔画刷DC
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pen[i][j].DeleteObject();
			brush[i][j].DeleteObject();
		}
	}
	exit(0);
}
