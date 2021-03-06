#pragma once
#include "Consumer.h"

// Draw 对话框

class Draw : public CDialogEx
{
	DECLARE_DYNAMIC(Draw)

public:
	Draw(Consumer,int, Consumer*, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Draw();
	double drawMoney;//取款
	double depositMoney;//存款
	Consumer nowCus;
	Consumer *cus;
	int cusCount;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnClose();
};
