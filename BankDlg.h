
// BankDlg.h: 头文件
//

#pragma once
#include "Consumer.h"

// CBankDlg 对话框
class CBankDlg : public CDialogEx
{
// 构造
public:
	CBankDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BANK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString nowUse;//判断是哪个登录
	int cusCount;//当前系统人数
	Consumer cus[120];//系统能注册120人
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool savePwd;
	// 查看是否存在此用户 存在返回true
	bool ConfirmLogin(CString&, CString&);
	// 查找用户返回数组下标
	int SearchConsumer(const CString&);
};
