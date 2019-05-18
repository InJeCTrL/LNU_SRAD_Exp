
// SearchPanel.h: 头文件
//

#pragma once

// SearchPanel 对话框
class SearchPanel : public CDialogEx
{
	// 构造
public:
	SearchPanel(CWnd* pParent = nullptr);	// 标准构造函数
	//listview中选中行号
	INT m_Row = -1, m_Col = -1;
	//搜索条件项序号
	INT SearchIndex;
	/*表示下拉框中选择的序号
	-1:未选择
	0:最近一年
	1:最近五年
	2:最近十年
	3:均值
	4:方差
	*/
	INT Combo_index = 0;
	//存储编辑框中的值
	CString edit[1][2];



	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SearchPanel_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	HICON m_hIcon1;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_list1;
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	//顶部菜单
	CMenu m_Menu;
	//是否使用查询控件数组
	CButton m_radio[7];
	//查询范围combox
	CComboBox m_combo[6];
	//查询范围textbox
	CEdit m_edit[6][2];
	//查询股票编号
	CEdit m_edit_symbol;
	afx_msg void OnBnClickedOk();
	afx_msg void On32771();
	
};