
// BankDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Bank.h"
#include "BankDlg.h"
#include "MainBank.h"
#include "afxdialogex.h"
#include <locale>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CBankDlg::CBankDlg(CWnd* pParent ):CDialogEx(IDD_BANK_DIALOG, pParent), savePwd(false)
{
	CStdioFile ifile;//打开输入文件
	if (!ifile.Open(L"./data.txt", CFile::modeRead | CFile::shareDenyNone))
		cusCount = 0;/*如果不存在保存文件，初始化系统人数为0*/
					 //读取当前系统人数
	else
	{
		CString str;
		CString errC;
		setlocale(LC_CTYPE, ("chs"));
		CString  cusC, money;
		ifile.ReadString(cusC);
		cusCount = _wtoi(cusC);
		for (int i = 0; i < cusCount; i++)
		{
			cus[i].dpos = 0;//初始为0，下面如果存在记录，则会改变
			cus[i].fpos = 0;
			ifile.ReadString(cus[i].cardNumber);
			ifile.ReadString(cus[i].name);
			ifile.ReadString(money);
			cus[i].money = _wtof(money);
			ifile.ReadString(cus[i].id);
			ifile.ReadString(cus[i].addr);
			ifile.ReadString(cus[i].phone);
			ifile.ReadString(cus[i].usrPwd);
			ifile.ReadString(cus[i].confirmUsrPwd);
			ifile.ReadString(errC);
			cus[i].errCount = _wtoi(errC);
			for (int j = 0; j < 40; j++)
			{
				ifile.ReadString(str);
				if ((!str.IsEmpty()) && (str.Find(L"存款", 0) != -1))//直到最后一条记录不为空，则知道有多少条记录
				{
					cus[i].dipositHistory[cus[i].dpos] = str;
					cus[i].dpos++;
				}
				else if ((!str.IsEmpty()) && (str.Find(L"取款", 0) != -1))//直到最后一条记录不为空，则知道有多少条记录
				{
					cus[i].fetchHistory[cus[i].fpos] = str;
					cus[i].fpos++;
				}
			}
		}
		ifile.Close();
	}
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BANK);
}

void CBankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CBankDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBankDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBankDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()



BOOL CBankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CString numStr, repwd, alogin, pwdStr;
	numStr = theApp.GetProfileStringW(L"LOGIN", L"NUM");//获取上次账号
	SetDlgItemText(IDC_COUNTER, numStr);//设置上次的账号
	repwd = theApp.GetProfileStringW(L"LOGIN", L"REPWD");//读取是否记住密码
	alogin = theApp.GetProfileStringW(L"LOGIN", L"ALOGIN");
	if (repwd == "1")//设置复选框为勾选或者不勾选
	{
		CButton *pwd = (CButton*)GetDlgItem(IDC_REPWD);
		pwd->SetCheck(1);
		if (numStr == L"admin")
			pwdStr = theApp.GetProfileStringW(L"LOGIN", L"PWD");
		else
			pwdStr = theApp.GetProfileStringW(L"USRLOGIN", L"PWD");
		SetDlgItemText(IDC_PWD, pwdStr);
	}

	if (alogin == "1")
	{
		CButton *ato = (CButton*)GetDlgItem(IDC_AUTO);
		ato->SetCheck(1);
		if (!pwdStr.IsEmpty() && !numStr.IsEmpty())
		SetTimer(100, 1500, NULL);
	}
	return TRUE;
}


void CBankDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CBankDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBankDlg::OnBnClickedOk()
{
	int flag;
	CString num, pwd;
	CString havedChangePwd;
	CString pwdChange;
	havedChangePwd = theApp.GetProfileStringW(L"LOGIN", L"HAVEDCHANGEPWD");//是否已经更改过管理员密码
	pwdChange = theApp.GetProfileStringW(L"LOGIN", L"CHANGEPWD");//如果更改了密码，则获取更改的密码
	if (havedChangePwd.IsEmpty())//是否是第一次使用此软件
	{
		pwdChange = "admin";
	}
	GetDlgItemText(IDC_COUNTER, num);
	if (num.IsEmpty())
	{
		AfxMessageBox(L"请输入账号！");
		GetDlgItem(IDC_COUNTER)->SetFocus();
		return;
	}
	GetDlgItemText(IDC_PWD, pwd);
	if (pwd.IsEmpty())
	{
		AfxMessageBox(L"请输入密码！");
		GetDlgItem(IDC_PWD)->SetFocus();
		return;
	}
	if (num == L"admin" && pwd == pwdChange)//如果管理员则直接登录
	{
		savePwd = true;
		nowUse = num;//目前使用是是哪个用户
		EndDialog(IDD_BANK_DIALOG);
		return;
	}
	flag = SearchConsumer(num);//查找定位下标
	if (flag == -1)
	{
		AfxMessageBox(L"账户不存在！");
		return;
	}
	if (cus[flag].errCount > 3)
	{
		AfxMessageBox(L"您的账户已被冻结，请联系管理员！");
		return;
	}
	if (ConfirmLogin(num, pwd) && cusCount > 0)//用户可以根据身份证与卡号进行登录
	{
		savePwd = true;
		nowUse = num;//目前使用是是哪个用户
		cus[flag].errCount = 0;//成功登陆 错误次数置0
		EndDialog(IDD_BANK_DIALOG);
	}
	else
	{
		AfxMessageBox(L"密码错误！请重新输入！");
		if (num != L"admin")//如果输入密码错误的不是管理员
		{
			
			//用户输入错误次数加1
			cus[flag].errCount++;
		}
	}
}


void CBankDlg::OnBnClickedCancel()
{
	EndDialog(IDD_BANK_DIALOG);
}


void CBankDlg::OnClose()
{
	CBankDlg::OnOK();
}

void CBankDlg::OnDestroy()
{
	CString pwdStr, numStr;
	CButton *pwd = (CButton*)GetDlgItem(IDC_REPWD);//记住密码复选框
	CButton *ato = (CButton*)GetDlgItem(IDC_AUTO);//自动登录复选框
	int state;
	state = pwd->GetCheck();
	GetDlgItemText(IDC_COUNTER, numStr);
	theApp.WriteProfileStringW(L"LOGIN", L"NUM", numStr);//保存当前用户名
	if (state == 1 && savePwd)//可以成功登录 保存密码
	{
		GetDlgItemText(IDC_PWD, pwdStr);
		theApp.WriteProfileStringW(L"LOGIN", L"PWD", pwdStr);
		theApp.WriteProfileStringW(_T("LOGIN"), _T("REPWD"), _T("1"));
	}
	else
	{
		theApp.WriteProfileStringW(_T("LOGIN"), _T("REPWD"), _T("0"));
	}

	state = ato->GetCheck();
	if (state == 0)
	{
		theApp.WriteProfileStringW(_T("LOGIN"), _T("ALOGIN"), _T("0"));//下次执行自动登录
	}
	else
	{
		theApp.WriteProfileStringW(_T("LOGIN"), _T("ALOGIN"), _T("1"));//下次执行自动登录
	}
	CDialogEx::OnDestroy();
}


void CBankDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 100)
	{
		OnBnClickedOk();
		KillTimer(100);
	}
	CDialogEx::OnTimer(nIDEvent);
}


// 查看是否存在此用户 存在返回true
bool CBankDlg::ConfirmLogin(CString& num, CString& pwd)
{
	for (int i = 0; i < cusCount; i++)
	{
		if (num == cus[i].id || num == cus[i].cardNumber)//存在此用户
		{
			if (pwd == cus[i].usrPwd)//验证密码是否正确
			{
				return true;
			}
		}
	}
	return false;
}


// 查找用户返回数组下标,查找失败返回-1
int CBankDlg::SearchConsumer(const CString& num)
{
	int i;
	for (i = 0; i < cusCount; i++)
	{
		if (num == cus[i].cardNumber || num == cus[i].id)
		{
			break;
		}
	}
	if (i > cusCount)
	{
		return -1;
	}
	return i;
}
