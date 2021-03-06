#pragma once
#include "HS-Charting/ChartCtrl.h"
#include "HS-Charting/ChartTitle.h"
#include "HS-Charting/ChartBarSerie.h"

//各个时间的行数
#define BAO 7
#define JI 7
#define NIAN 7
//各个表的列数
#define ZHU 12
#define ZONG 12
#define ZI 12
#define XIAN 12
#define LI 12
// DataPanel 对话框


class DataPanel : public CDialogEx
{
	DECLARE_DYNAMIC(DataPanel)

public:
	DataPanel(CString symbol, CString Name, CWnd* pParent = nullptr);
	// 标准构造函数
	virtual ~DataPanel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DataPanel_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//YYYYMMDD三部分
	int time_array[3];
	CChartBarSerie* pBarSeries;
	//返回数据集合
	std::vector<std::vector<CString>> result;
	//股票编号
	CString money_number;
	CString _Name;
	CListCtrl static_table;
	DWORD DwStyle;
	//默认是主要指标
	//int flag_table = 0;
	//默认是报告期
	//int flag_time = 2;  
	void SetListLine();
	//填写列表表头
	void WriteTableColumnTitle(int table_flag);
	//void WriteTableTime(int time_flag);
	//填写列表数据
	void WriteTable(int flag_table, int flag_time, CString symbol);
	//按钮单击相应函数
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	virtual BOOL OnInitDialog();
	CChartCtrl my_chart;
	//afx_msg void OnHdnItemclickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickList4(NMHDR *pNMHDR, LRESULT *pResult);
	//字符串时间转整型时间数组
	int* GetTime(CString cs);
	double GetData(CString cs);
	CButton m_Year;
	CButton m_Season;
	CButton m_Pub;
	INT flag_table = 0;
	INT flag_time = 0;
	INT UpdateShow();
	afx_msg void OnBnClickedRadio1Data();
	afx_msg void OnBnClickedRadio2Data();
	afx_msg void OnBnClickedRadio3Data();
};
