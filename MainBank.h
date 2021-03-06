#pragma once
#include "afxbutton.h"
#include "Consumer.h"
// MainBank 对话框

class MainBank : public CDialogEx
{
	DECLARE_DYNAMIC(MainBank)

public:
	MainBank(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainBank();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BANK };
#endif

protected:
	CFont searchFont;
	CMFCButton m_button;
	CStatic m_search;
	int nowUsePos;//目前登录的用户的下标
	CStatic m_time;//设置时间
	CFont font;//时间的字体
	CStatic m_static;//主界面标题
	CFont mfont;//主界面标题字体
	Consumer nowCus;//当前使用软件的客户
	Consumer cus[120];//系统能注册120人
	CMenu m_menu;//菜单
	CFont m_editFont;
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CString nowUse;//当前是哪个用户在使用
	int cusCount;//当前系统人数
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg void On32774();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedMoney();
	void CopyConsumer(Consumer c[]);
	afx_msg void OnBnClickedHistory();
	void ShowAllHistory();
	void ShowUsrHistory();
	afx_msg void OnBnClickedDestroy();
	afx_msg void OnBnClickedAdmin();
	afx_msg void On32775();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void On32780();
	afx_msg void On32781();
	afx_msg void On32779();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnPaint();
	virtual void OnCancel();
	virtual void OnOK();
};
