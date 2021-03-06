// ChangePassword.cpp: 实现文件
//

#include "stdafx.h"
#include "Bank.h"
#include "ChangePassword.h"
#include "afxdialogex.h"


// ChangePassword 对话框

IMPLEMENT_DYNAMIC(ChangePassword, CDialogEx)

ChangePassword::ChangePassword(Consumer* c, CString nowUse ,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHANGEPWD, pParent), nowCus(c)
{
	this->nowUse = nowUse;
}

ChangePassword::~ChangePassword()
{
}

void ChangePassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangePassword, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChangePassword::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ChangePassword::OnBnClickedButton2)
END_MESSAGE_MAP()


// ChangePassword 消息处理程序


void ChangePassword::OnBnClickedButton1()
{
	CString pwd;//密码
	CString comfirmPwd;//确认密码
	GetDlgItemText(IDC_EDIT1, pwd);
	GetDlgItemText(IDC_EDIT2, comfirmPwd);
	if (pwd.IsEmpty())
	{
		AfxMessageBox(L"请输入新密码！");
		GetDlgItem(IDC_EDIT1)->SetFocus();
		return;
	}
	if (comfirmPwd.IsEmpty())
	{
		AfxMessageBox(L"请输入确认密码！");
		GetDlgItem(IDC_EDIT2)->SetFocus();
		return;
	}
	if (pwd != comfirmPwd)
	{
		AfxMessageBox(L"输入的两次密码不一致！");
		GetDlgItem(IDC_EDIT1)->SetFocus();
		return;
	}
	if (nowUse == L"admin")
	{
	theApp.WriteProfileStringW(L"LOGIN", L"CHANGEPWD", pwd);//保存已更改的密码
	theApp.WriteProfileStringW(L"LOGIN", L"HAVEDCHANGEPWD", L"TRUE");//设置已经修改过密码
	theApp.WriteProfileStringW(L"LOGIN", L"PWD", pwd);//保存修改后的密码
	}
	else
	{
		if (pwd.GetLength() != 6)
		{
			AfxMessageBox(L"密码长度为6位！");
			return;
		}
		nowCus->usrPwd = pwd;
		nowCus->confirmUsrPwd = pwd;
		theApp.WriteProfileStringW(L"USRLOGIN", L"PWD", pwd);//保存修改后的用户密码
	}
	AfxMessageBox(L"密码修改成功！");
	EndDialog(IDD_CHANGEPWD);
}


void ChangePassword::OnBnClickedButton2()
{
	EndDialog(IDD_CHANGEPWD);
}
