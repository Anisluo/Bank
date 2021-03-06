#pragma once
#include "Consumer.h"

// ModifyUsr 对话框

class ModifyUsr : public CDialogEx
{
	DECLARE_DYNAMIC(ModifyUsr)

public:
	ModifyUsr(Consumer* , int, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ModifyUsr();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL judge;
	CString str;//判断前后列表中的项是否被改变
    Consumer *cus;
	int cusCount;
	CListCtrl m_list;
	CEdit m_edit;
	int m_Row;//行
	int m_Col;//列
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnDblclkModifyedit(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusTempedit();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
