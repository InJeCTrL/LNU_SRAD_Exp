// Foresee.cpp: 实现文件
//

#include "stdafx.h"
#include "Stock.h"
#include "Foresee.h"
#include "DataBaseMgr.h"
#include "afxdialogex.h"


// Foresee 对话框

IMPLEMENT_DYNAMIC(Foresee, CDialogEx)

Foresee::Foresee(CString symbol, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Foresee, pParent)
{
	_symbol = symbol;
}

Foresee::~Foresee()
{
}

void Foresee::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_cashflow);
	DDX_Control(pDX, IDC_EDIT15, m_rate1);
	DDX_Control(pDX, IDC_EDIT16, m_rate2);
	DDX_Control(pDX, IDC_EDIT17, m_rate3);
	DDX_Control(pDX, IDC_EDIT18, m_nYear);
	DDX_Control(pDX, IDC_EDIT19, m_NumS);
}


BEGIN_MESSAGE_MAP(Foresee, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Foresee::OnBnClickedButton1)
END_MESSAGE_MAP()


// Foresee 消息处理程序

INT Foresee::DoForesee(DOUBLE cashflow, DOUBLE rate1, DOUBLE rate2, DOUBLE rate3, INT nY, LONG numStock)
{
	//自由现金流求和与单个自由现金流
	DOUBLE sum_FCF = 0.0, aFCF = 0.0;
	//计算自由现金流在n年内的值，并计算折线自由现金流
	for (INT i = 1; i <= nY; i++)
	{
		aFCF = (cashflow * pow(1 + (rate3 / 100.0), i)) / pow(1 + (rate2 / 100.0), i);
		sum_FCF += aFCF;
	}
	//永续年金价值，折现值
	DOUBLE PV = (aFCF * (1 + rate1 / 100.0)) / (rate2 / 100.0 - rate1 / 100.0) / pow(1 + (rate2 / 100.0), nY);
	//所有者权益合计
	DOUBLE SUM = sum_FCF + PV;
	//每股价值
	DOUBLE FIN = SUM / (numStock + 0.0);
	CString str_FIN;
	str_FIN.Format(L"%lf", FIN);
	MessageBox(str_FIN, L"每股估计价格");

	return 0;
}

void Foresee::OnBnClickedButton1()
{
	CString str[6];
	m_cashflow.GetWindowTextW(str[0]);
	m_rate1.GetWindowTextW(str[1]);
	m_rate2.GetWindowTextW(str[2]);
	m_rate3.GetWindowTextW(str[3]);
	m_nYear.GetWindowTextW(str[4]);
	m_NumS.GetWindowTextW(str[5]);
	DoForesee(_wtof(str[0]), _wtof(str[1]), _wtof(str[2]), _wtof(str[3]), _wtol(str[4]), _wtoi(str[5]));
}


BOOL Foresee::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DataBaseMgr db = DataBaseMgr();
	CString str;
	str.Format(L"%lf", db.GetLastCashflow(_symbol));
	m_cashflow.SetWindowTextW(str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
