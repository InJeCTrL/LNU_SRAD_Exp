
// 9-13Dlg.h: 头文件
//

#pragma once


// CMy913Dlg 对话框
class CMy913Dlg : public CDialogEx
{
// 构造
public:
	CMy913Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY913_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	UINT R = 0, G = 0, B = 0;//RGB参数
	RECT OvalRect = { 150, 150, 400, 250 };//椭圆绘图区域

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//初始化各个水平滚动条
	void initScrollBars();
	//绘制填充的椭圆
	void DrawOval();
	DECLARE_MESSAGE_MAP()
public:
	CScrollBar m_RedScroll;
	CScrollBar m_GreenScroll;
	CScrollBar m_BlueScroll;
	CEdit m_RedShow;
	CEdit m_GreenShow;
	CEdit m_BlueShow;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
