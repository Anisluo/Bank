#pragma once
#include "Consumer.h"

// AllHistory 对话框
class Position
{
public:
	int i;//第几个用户
	int j;//第几条记录
	BOOL type;//哪种类型，存款取款，存款为true,取款为false
};

class AllHistory : public CDialogEx
{
	DECLARE_DYNAMIC(AllHistory)

public:
	AllHistory(Consumer*, int, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AllHistory();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINHISTORY };
#endif

protected:
	Position pos[120];//最多存储插入的120条记录
	int nPos;//存储pos的下标
	int Count[120];//获取管理员选择了哪几项
	int countPos;//哪几项最后的下标
	int cusCount;
	Consumer * cus;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CListCtrl m_list;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListall(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
};
