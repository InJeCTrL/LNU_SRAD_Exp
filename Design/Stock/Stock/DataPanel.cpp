// DataPanel.cpp: 实现文件
//

#include "stdafx.h"
#include "Stock.h"
#include "DataPanel.h"
#include "Foresee.h"
#include "DataBaseMgr.h"
#include "afxdialogex.h"
#include "Resource.h"


// DataPanel 对话框

IMPLEMENT_DYNAMIC(DataPanel, CDialogEx)

DataPanel::DataPanel(CString symbol, CString Name, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DataPanel_DIALOG, pParent)
{
	money_number = symbol;
	_Name = Name;
}

DataPanel::~DataPanel()
{
	
}

void DataPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4_Data, static_table);
	DDX_Control(pDX, IDC_CUSTOM2_Data, my_chart);
	DDX_Control(pDX, IDC_RADIO1_Data, m_Year);
	DDX_Control(pDX, IDC_RADIO2_Data, m_Season);
	DDX_Control(pDX, IDC_RADIO3_Data, m_Pub);
}

BEGIN_MESSAGE_MAP(DataPanel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2_Data, &DataPanel::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1_Data, &DataPanel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3_Data, &DataPanel::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4_Data, &DataPanel::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5_Data, &DataPanel::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6_Data, &DataPanel::OnBnClickedButton6)
	//ON_BN_CLICKED(IDC_RADIO3_Data, &DataPanel::OnBnClickedRadio3)
	//ON_BN_CLICKED(IDC_RADIO2_Data, &DataPanel::OnBnClickedRadio2)
	//ON_BN_CLICKED(IDC_RADIO1_Data, &DataPanel::OnBnClickedRadio1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST4_Data, &DataPanel::OnLvnColumnclickList4)
	ON_BN_CLICKED(IDC_RADIO1_Data, &DataPanel::OnBnClickedRadio1Data)
	ON_BN_CLICKED(IDC_RADIO2_Data, &DataPanel::OnBnClickedRadio2Data)
	ON_BN_CLICKED(IDC_RADIO3_Data, &DataPanel::OnBnClickedRadio3Data)
END_MESSAGE_MAP()

//刷新显示
INT DataPanel::UpdateShow()
{
	static_table.DeleteAllItems();
	while (static_table.DeleteColumn(0));
	WriteTableColumnTitle(flag_table);
	//WriteTableTime(flag_time);
	WriteTable(flag_table, m_Season.GetCheck() + m_Pub.GetCheck() * 2, money_number);
	my_chart.GetTitle()->RemoveAll();
	//改变柱状图标题
	switch (flag_table)
	{
	case 0:
		my_chart.GetTitle()->AddString(TChartString(L"主要指标"));
		break;
	case 1:
		my_chart.GetTitle()->AddString(TChartString(L"综合分析"));
		break;
	case 2:
		my_chart.GetTitle()->AddString(TChartString(L"资产负债表"));
		break;
	case 3:
		my_chart.GetTitle()->AddString(TChartString(L"现金流量表"));
		break;
	case 4:
		my_chart.GetTitle()->AddString(TChartString(L"利润表"));
		break;
	default:
		break;
	}
	return 0;
}

//设置表格网格线
void DataPanel::SetListLine() {
	DataPanel::DwStyle = DataPanel::static_table.GetExtendedStyle();
	DwStyle |= LVS_EX_FULLROWSELECT;
	DwStyle |= LVS_EX_GRIDLINES;
	static_table.SetExtendedStyle(DwStyle);
}

//填入表格列标题
void DataPanel::WriteTableColumnTitle(int table_flag)
{
	CString MainDG[] = { L"时间", L"营业利润", L"营业净现金流", L"净资产收益率", L"盈利增长率", L"自由现金流", L"每股收益", L"投资回报率" };
	CString LotsofInfo[] = { L"时间", L"合并报表其他应收款", L"合并报表预付款项", L"合并报表总资产", L"母公司其他应收款", L"母公司预付款项", L"母公司总资产", L"应收票据", L"应收账款",
							L"应付账款", L"应付票据", L"存货", L"预收账款", L"母公司比率", L"合并报表比率", L"差额比率", L"应收票据账款比率", L"应付票据账款比率", L"差额其他应收款", L"差额预付款项", L"差额总资产", L"应收票据+应收款", L"应付票据+应付款", L"固定资产+在建工程", L"比率" };
	CString balance[] = { L"时间",L"货币资金",L"应收票据",L"应收账款",L"预付款项",L"应收利息",L"其他应收款",L"存货",L"一年内到期的非流动资产",L"其他流动资产",L"流动资产合计",L"可供出售金融资产",L"长期股权投资",L"投资性房地产",L"固定资产",L"在建工程",L"无形资产",L"商誉",L"长期待摊费用",L"递延所得税资产",L"其他非流动资产",L"非流动资产合计",L"短期借款",L"应付票据",L"应付账款",L"预收账款",L"应付职工薪酬",L"应交税费",L"应付利息",L"应付股利",L"一年内到期的非流动负债",L"其他流动负债",L"流动负债合计",L"长期借款",L"递延所得税负债",L"其他非流动负债",L"非流动负债合计",L"负债合计",L"实收资本（或股本）",L"资本公积金",L"其他综合收益" };
	CString income[] = { L"时间",L"营业总收入",L"营业收入",L"营业总成本",L"营业成本",L"营业税金及附加",L"销售费用",L"管理费用",L"财务费用",L"利息收入",L"（其中）对联营企业和合营企业的投资收益",L"营业利润",L"加：营业外收入",L"（其中）非流动资产处置利得",L"减：营业外支出",L"（其中）非流动资产处置损失",L"利润总额",L"减：所得税费用",L"基本每股收益",L"稀释每股收益",L"归属于母公司股东的综合收益总额",L"归属于少数股东的综合收益总额" };
	CString cashflow[] = { L"时间",L"销售商品、提供劳务收到的现金",L"收到的税费返还",L"收到其他与经营活动有关的现金",L"经营活动现金流入小计",L"支付给职工以及为职工支付的现金",L"支付的各项税费",L"支付其他与经营活动有关的现金",L"经营活动现金流出小计",L"经营活动产生的现金流量净额",L"收回投资收到的现金",L"取得投资收益收到的现金",L"处置固定资产、无形资产和其他长期资产收回的现金净额",L"处置子公司及其他营业单位收到的现金净额",L"收到其他与投资活动有关的现金",L"投资活动现金流入小计",L"购建固定资产、无形资产和其他长期资产支付的现金",L"投资支付的现金",L"取得子公司及其他营业单位支付的现金净额",L"支付其他与投资活动有关的现金",L"投资活动现金流出小计",L"投资活动产生的现金流量净额",L"吸收投资收到的现金",L"子公司吸收少数股东投资收到的现金",L"取得借款收到的现金",L"收到其他与筹资活动有关的现金",L"筹资活动现金流入小计",L"偿还债务支付的现金",L"分配股利、利润或偿付利息支付的现金",L"子公司支付给少数股东的股利",L"支付其他与筹资活动有关的现金",L"筹资活动现金流出小计",L"筹资活动产生的现金流量净额",L"汇率变动对现金及现金等价物的影响",L"现金及现金等价物净增加额",L"现金等价物的期初余额",L"期末现金及现金等价物余额",L"现金流量表 - 净利润",L"资产减值准备",L"固定资产折旧、油气资产折耗、生产性生物资产折旧",L"无形资产摊销",L"长期待摊费用摊销",L"处置固定资产、无形资产和其他长期资产的损失",L"固定资产报废损失",L"现金流量表 - 财务费用",L"投资损失",L"递延所得税资产减少",L"递延所得税负债增加",L"存货的减少",L"经营性应收项目的减少",L"经营性应付项目的增加",L"其他",L"间接法-经营活动产生的现金流量净额",L"现金的期末余额",L"现金的期初余额",L"间接法 - 现金及现金等价物净增加额" };

	switch (table_flag)
	{
	case 0:
		for (INT i = 0; i < 8; i++)
		{
			static_table.InsertColumn(i, MainDG[i], LVCFMT_CENTER, 80, 60);
		}
		break;
	case 1:
		for (INT i = 0; i < 25; i++)
		{
			static_table.InsertColumn(i, LotsofInfo[i], LVCFMT_CENTER, 80, 60);
		}
		break;
	case 2:
		for (INT i = 0; i < 41; i++)
		{
			static_table.InsertColumn(i, balance[i], LVCFMT_CENTER, 80, 60);
		}
		break;
	case 3:
		for (INT i = 0; i < 56; i++)
		{
			static_table.InsertColumn(i, cashflow[i], LVCFMT_CENTER, 80, 60);
		}
		break;
	case 4:
		for (INT i = 0; i < 22; i++)
		{
			static_table.InsertColumn(i, income[i], LVCFMT_CENTER, 80, 60);
		}
		break;
	default:
		break;
	}
}

//填入表格内容
void DataPanel::WriteTable(int flag_table, int flag_time, CString symbol)
{
	//static_table.SetItemText(0, 1, _T("内容测试"));
	DataBaseMgr db = DataBaseMgr();
	result = db.GetDetail(flag_table, flag_time, money_number);
	for (LONG i = 0; i < result.size(); i++)
	{
		INT f = 0;
		for (LONG j = 1; j < result[i].size(); j++)
		{
			if (flag_time == 2 && j == 1)
			{
				static_table.InsertItem(i, result[i][j]);
				j = 2;
				f = 1;
				continue;
			}
			else if ((flag_time == 0 || flag_time == 1) && j == 2)
			{
				static_table.InsertItem(i, result[i][j]);
				f = 1;
				continue;
			}
			else
			{
				if (f)
					static_table.SetItemText(i, j - 2, result[i][j]);
			}
		}
	}
}

// DataPanel 消息处理程序

//主要指标
void DataPanel::OnBnClickedButton2()
{
	flag_table = 0;
	UpdateShow();
}

//综合分析
void DataPanel::OnBnClickedButton1()
{
	flag_table = 1;
	UpdateShow();
}

//资产负债表
void DataPanel::OnBnClickedButton3()
{
	flag_table = 2;
	UpdateShow();
}

//现金流量表
void DataPanel::OnBnClickedButton4()
{
	flag_table = 3;
	UpdateShow();
}

//利润表
void DataPanel::OnBnClickedButton5()
{
	flag_table = 4;
	UpdateShow();
}

//估值
void DataPanel::OnBnClickedButton6()
{
	//模态启动估值界面
	Foresee fse(money_number);
	fse.DoModal();
}

BOOL DataPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(money_number + L" " + _Name);
	m_Year.SetCheck(1);
	SetListLine();
	WriteTableColumnTitle(0);
	//DataPanel::WriteTableTime(DataPanel::flag_time);
	WriteTable(0, 0, money_number);

	//my_chart.EnableRefresh(false);
	//建立坐标系
	COleDateTime Min(2005, 1, 1, 0, 0, 0);
	COleDateTime Max(2019, 6, 1, 0, 0, 0);
	CChartAxis *pAxis = NULL;
	pAxis = my_chart.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);
	CChartDateTimeAxis* pDateAxis = NULL;
	pDateAxis = NULL;
	pDateAxis = my_chart.CreateDateTimeAxis(CChartCtrl::BottomAxis);
	//pDateAxis->SetAutomatic(true);
	pDateAxis->SetTickLabelFormat(false, _T("%y-%m-%d"));
	pDateAxis->SetMinMax(Min, Max);
	pDateAxis->SetAutomatic(true);
	pAxis->SetAutomatic(true);
	//pAxis->SetMinMax(0, 100);

	//柱状图标题
	my_chart.GetTitle()->AddString(TChartString(L"主要指标"));
	//柱状图
	pBarSeries = my_chart.CreateBarSerie();
	
	/*
	COleDateTime TimeVal1(2008, 1, 1, 0, 0, 0);
	int a = 51;
	pBarSeries->AddPoint(TimeVal1, a);
	*/

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void DataPanel::OnLvnColumnclickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nItem = -1;

	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		nItem = lpNMItemActivate->iSubItem;
	}
	if (nItem > 0)
	{
		my_chart.EnableRefresh(false);
		pBarSeries->ClearSerie();
		//my_chart.RemoveAllSeries();
		static_table.GetItemCount();
		for (LONG i = 0; i < static_table.GetItemCount(); i++)
		{
			INT* x_value = GetTime(static_table.GetItemText(i, 0));
			DOUBLE y_value = GetData(static_table.GetItemText(i, nItem));
			COleDateTime tv(x_value[0], x_value[1], x_value[2], 0, 0, 0);
			pBarSeries->AddPoint(tv, y_value);
		}
		my_chart.EnableRefresh(true);
		my_chart.RefreshCtrl();
		//my_chart.EnableRefresh(true);
	}
	*pResult = 0;
}

//将列处理成3个时间
int* DataPanel::GetTime(CString cs) {
	int temp;
	TCHAR seps[] = _T("/"); //分割字符
	TCHAR* token = _tcstok((LPTSTR)(LPCTSTR)cs, seps);
	for (int i = 0; i < 3; i++) {
		temp = _wtoi(token);
		time_array[i] = temp;
		token = _tcstok(NULL, seps);
	}
	return time_array;
}
//将表格中内容转化为数字
double DataPanel::GetData(CString cs) {
	double temp;
	temp = _tstof(cs);
	return temp;
}

void DataPanel::OnBnClickedRadio1Data()
{
	flag_time = 0;
	UpdateShow();
}

void DataPanel::OnBnClickedRadio2Data()
{
	flag_time = 1;
	UpdateShow();
}

void DataPanel::OnBnClickedRadio3Data()
{
	flag_time = 2;
	UpdateShow();
}
