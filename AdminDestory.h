#pragma once
#include "Consumer.h"

// AdminDestory 对话框

class AdminDestory :public CDialogEx
{
	DECLARE_DYNAMIC(AdminDestory)

public:
	AdminDestory(Consumer*, int*, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AdminDestory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINDESTORY };
#endif

protected:
	int *cusCount;
	int Count[120];
	int countPos;
	Consumer * cus;
	CListCtrl m_list;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
};
