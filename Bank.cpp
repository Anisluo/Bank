
// Bank.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Bank.h"
#include "BankDlg.h"
#include "MainBank.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBankApp

BEGIN_MESSAGE_MAP(CBankApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBankApp 构造

CBankApp::CBankApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// 唯一的 CBankApp 对象

CBankApp theApp;


// CBankApp 初始化

BOOL CBankApp::InitInstance()
{
	SetRegistryKey(L"Bank");
	CBankDlg dlg1;
	dlg1.DoModal();	
	if (dlg1.savePwd == true)
	{
		MainBank dlg;
		dlg.cusCount = dlg1.cusCount;
		dlg.nowUse = dlg1.nowUse;
		dlg.CopyConsumer(dlg1.cus);//将目前用户复制到主类中
		dlg.DoModal();
	}
	return FALSE;
}
