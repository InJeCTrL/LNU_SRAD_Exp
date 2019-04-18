
// 9-17Dlg.h: 头文件
//

#pragma once


// CMy917Dlg 对话框
class CMy917Dlg : public CDialogEx
{
// 构造
public:
	CMy917Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY917_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	RECT RedrawRt = { 320, 50, 420, 150 };//重绘区
	CPen pen[3][4];//3颜色*4线型
	CBrush brush[3][4];//3颜色*4填充类型
	POINT RRCT = { 5, 5 };//圆角矩形参数


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	CComboBox m_PenColor;
	CComboBox m_BrushColor;
	CButton m_LineType[4];
	CButton m_FillType[4];
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
