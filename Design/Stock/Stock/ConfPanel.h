#pragma once


// ConfPanel 对话框

class ConfPanel : public CDialogEx
{
	DECLARE_DYNAMIC(ConfPanel)

public:
	ConfPanel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ConfPanel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ConfPanel_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CButton m_In;
	CButton m_Clean;
	virtual BOOL OnInitDialog();
};
