// Open.cpp: 实现文件
//

#include "stdafx.h"
#include "Bank.h"
#include "Open.h"
#include "afxdialogex.h"


// Open 对话框

IMPLEMENT_DYNAMIC(Open, CDialogEx)

Open::Open(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USROPEN, pParent), judge(false)
{

}

Open::~Open()
{
}

void Open::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Open, CDialogEx)
	ON_BN_CLICKED(IDOK, &Open::OnBnClickedOk)
END_MESSAGE_MAP()


// Open 消息处理程序


Consumer Open::Get_Cus()
{
	return cus;
}

void Open::OnBnClickedOk()//确认开户
{
	CString money;
	GetDlgItemText(IDC_EDIT1, cus.cardNumber);
	GetDlgItemText(IDC_EDIT2, cus.name);
	GetDlgItemText(IDC_EDIT3, money);
	GetDlgItemText(IDC_EDIT4, cus.id);
	GetDlgItemText(IDC_EDIT5, cus.addr);
	GetDlgItemText(IDC_EDIT6, cus.phone);
	GetDlgItemText(IDC_EDIT8, cus.usrPwd);
	GetDlgItemText(IDC_EDIT9, cus.confirmUsrPwd);
	if (cus.cardNumber.IsEmpty())
	{
		AfxMessageBox(L"请输入卡号！");
		return;
	}
	if (cus.name.IsEmpty())
	{
		AfxMessageBox(L"请输入姓名！");
		return;
	}
	if (money.IsEmpty())
	{
		AfxMessageBox(L"请输入开户金额！");
		return;
	}
	if (cus.id.IsEmpty())
	{
		AfxMessageBox(L"请输入身份证号！");
		return;
	}
	if (cus.addr.IsEmpty())
	{
		AfxMessageBox(L"请输入地址！");
		return;
	}
	if (cus.phone.IsEmpty())
	{
		AfxMessageBox(L"请输入电话！");
		return;
	}
	if (cus.usrPwd.IsEmpty())
	{
		AfxMessageBox(L"请输入密码	！");
		return;
	}
	if (cus.confirmUsrPwd.IsEmpty())
	{
		AfxMessageBox(L"请输入确认密码！");
		return;
	}	
	if (cus.cardNumber.GetLength() != 16)
	{
		AfxMessageBox(L"卡号格式错误，卡号为16位数字！");
		return;
	}
	if (cus.id.GetLength() != 18)
	{
		AfxMessageBox(L"身份证格式错误！");
		return;
	}

	if (cus.usrPwd != cus.confirmUsrPwd)
	{
		AfxMessageBox(L"两次输入密码不一致！");
		return;
	}
	cus.money = _wtof(money);
	cus.errCount = 0;//用户密码错误次数初始化为0
	AfxMessageBox(L"开户成功！");
	judge = true;
	CDialogEx::OnOK();
}


BOOL Open::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_editFont.CreatePointFont(150, L"微软雅黑");//设置样卡字体
	GetDlgItem(IDC_YK)->SetFont(&m_editFont);
	return TRUE;
}
