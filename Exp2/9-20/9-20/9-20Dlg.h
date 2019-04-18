
// 9-20Dlg.h: 头文件
//

#pragma once
#include<list>
#include<array>
using namespace std;

// CMy920Dlg 对话框
class CMy920Dlg : public CDialogEx
{
// 构造
public:
	CMy920Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY920_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	list<array<LONG, 6>> DataSets;//数据组合集（第一位为序号）
	array<LONG, 6> tDatas;//临时保存某一数据集的5个数据（第一位为序号）

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//添加数据到list
	void AddDatas();
	//设置控件数据到临时数组
	BOOL SetTempDatas();
	//根据选定的列表框项目设置控件数据到临时数组
	BOOL SetTempDatasByListView();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_Data[5];//输入框控件数组
	CListBox m_List;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
};
