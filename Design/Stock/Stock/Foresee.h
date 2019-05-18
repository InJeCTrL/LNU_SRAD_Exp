#pragma once


// Foresee 对话框

class Foresee : public CDialogEx
{
	DECLARE_DYNAMIC(Foresee)

public:
	Foresee(CString symbol, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Foresee();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Foresee };
#endif

protected:
	CString _symbol;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	INT DoForesee(DOUBLE cashflow, DOUBLE rate1, DOUBLE rate2, DOUBLE rate3, INT nY, LONG numStock);
	virtual BOOL OnInitDialog();
	CEdit m_cashflow;
	CEdit m_rate1;
	CEdit m_rate2;
	CEdit m_rate3;
	CEdit m_nYear;
	CEdit m_NumS;
};
