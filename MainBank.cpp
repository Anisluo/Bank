// MainBank.cpp: 实现文件

#include "stdafx.h"
#include "BankDlg.h"
#include "Bank.h"
#include "MainBank.h"
#include "afxdialogex.h"
#include "ChangePassword.h"
#include "Open.h"
#include "Draw.h"
#include "UsrHistory.h"
#include "AllHistory.h"
#include "AdminDestory.h"
#include "ModifyUsr.h"
#include <locale>
// MainBank 对话框

IMPLEMENT_DYNAMIC(MainBank, CDialogEx)

MainBank::MainBank(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BANK, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_BANK);
}

MainBank::~MainBank()
{

}

void MainBank::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAINSTATIC, m_static);
	DDX_Control(pDX, IDC_TIME, m_time);
	DDX_Control(pDX, IDC_MFCBUTTON1, m_button);
	DDX_Control(pDX, IDC_SEARCHSTATIC, m_search);
}


BEGIN_MESSAGE_MAP(MainBank, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_32774, &MainBank::On32774)
	ON_BN_CLICKED(IDC_OPEN, &MainBank::OnBnClickedOpen)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MONEY, &MainBank::OnBnClickedMoney)
	ON_BN_CLICKED(IDC_HISTORY, &MainBank::OnBnClickedHistory)
	ON_BN_CLICKED(IDC_DESTROY, &MainBank::OnBnClickedDestroy)
	ON_BN_CLICKED(IDC_ADMIN, &MainBank::OnBnClickedAdmin)
	ON_COMMAND(ID_32775, &MainBank::On32775)
	ON_WM_TIMER()
	ON_COMMAND(ID_32780, &MainBank::On32780)
	ON_COMMAND(ID_32781, &MainBank::On32781)
	ON_COMMAND(ID_32779, &MainBank::On32779)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &MainBank::OnBnClickedMfcbutton1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void MainBank::OnClose()
{
	EndDialog(IDD_BANK);
}


void MainBank::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	AnimateWindow(500, AW_CENTER);
}


BOOL MainBank::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_button.EnableWindowsTheming(1);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_menu.LoadMenuW(IDR_MENU1);
	SetMenu(&m_menu);
	searchFont.CreatePointFont(90, L"微软雅黑");
	m_search.SetFont(&searchFont);
	font.CreatePointFont(100, L"宋体");
	m_time.SetFont(&font);
	mfont.CreatePointFont(200, L"Euphemia");
	m_static.SetFont(&mfont);
	if (nowUse != "admin")//不是管理员，不可以操作对应按钮
	{
		GetDlgItem(IDC_OPEN)->ShowWindow(0);
		GetDlgItem(IDC_ADMIN)->ShowWindow(0);
	}
	COleDateTime time = COleDateTime::GetCurrentTime();
	CString hello;
	int t = time.GetHour();
	if (t > 6 && t < 11)
	{
		hello = L"上午";
	}
	else if (t >= 11 && t < 14)
	{
		hello = L"中午";
	}
	else if (t >= 14 && t < 18)
	{
		hello = L"下午";
	}
	else if (t >= 18 && t < 24 || t >= 0 && t < 6)
	{
		hello = L"晚上";
	}
	CString ti;
	ti.Format(L"%s %d:%d:%d", hello, time.GetHour(), time.GetMinute(), time.GetSecond());
	m_time.SetWindowTextW(ti);
	SetTimer(1, 1000, 0);
	ti.Format(L"   请选择服务项目\n(Please select service)");
	m_static.SetWindowTextW(ti);
	//int R, G, B;
	//R = 169;
	//G = 169;
	//B = 169;
	//m_bt2.SetFaceColor(RGB(R, G, B));
	//m_open.EnableWindowsTheming(FALSE);
	//CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	UpdateData();
	return TRUE;
}


void MainBank::On32774()//修改密码菜单
{
	ChangePassword dlg(&nowCus, nowUse);
	dlg.DoModal();
}


void MainBank::OnBnClickedOpen()//打开储蓄卡开户管理
{
	if (cusCount > 120)
	{
		AfxMessageBox(L"系统已达到最大存储量，请联系管理员！");
		return;
	}
	Open dlg;
	dlg.DoModal();
	if (dlg.judge == true)//成功开户，将信息添加至系统
	{
		cus[cusCount] = dlg.Get_Cus();
		++cusCount;
	}
}


void MainBank::OnDestroy()
{
	if (nowUse != "admin" && nowCus.cardNumber != L"")
	{
		cus[nowUsePos] = nowCus;
	}
	CDialogEx::OnDestroy();
	CStdioFile ofile;//保存客户信息文件指针
	CFileException e;
	setlocale(LC_CTYPE, ("chs"));//没有这句会读不了中文
	if (!ofile.Open(L"./data.txt", CFile::modeCreate | CFile::modeWrite, &e))
	{
#ifdef _DEBUG
		afxDump << "不能打开文件" << e.m_cause << "\n";
#endif
	}
	CString  cusC, money, errC;
	cusC.Format(L"%d", cusCount);
	ofile.WriteString(cusC);
	ofile.Write("\n", 1);
	for (int i = 0; i < cusCount; i++)//写文件 保存客户信息
	{
		ofile.WriteString(cus[i].cardNumber);
		ofile.Write("\n", 1);
		ofile.WriteString(cus[i].name);
		ofile.Write("\n", 1);
		money.Format(L"%lf", cus[i].money);
		ofile.WriteString(money);
		ofile.Write("\n", 1);
		ofile.WriteString(cus[i].id);
		ofile.Write("\n", 1);
		ofile.WriteString(cus[i].addr);
		ofile.Write("\n", 1);
		ofile.WriteString(cus[i].phone);
		ofile.Write("\n", 1);
		ofile.WriteString(cus[i].usrPwd);
		ofile.Write("\n", 1);
		ofile.WriteString(cus[i].confirmUsrPwd);
		ofile.Write("\n", 1);
		errC.Format(L"%d", cus[i].errCount);
		ofile.WriteString(errC);
		ofile.Write("\n", 1);
		int count = 0;
		for (int j = 0; j < 20; j++)
		{
			if (cus[i].dipositHistory[j].IsEmpty() != true)//不为空才写入
			{
				ofile.WriteString(cus[i].dipositHistory[j]);
				ofile.Write("\n", 1);
			}
			else //否则如果为空，这记录还应写入多少行
				count++;
			if (cus[i].fetchHistory[j].IsEmpty() != true)//不为空才写入
			{
				ofile.WriteString(cus[i].fetchHistory[j]);
				ofile.Write("\n", 1);
			}
			else //否则如果为空，这记录还应写入多少行
				count++;
		}
		for (int j = 0; j < count; j++)
			ofile.Write("\n", 1);
		ofile.Flush();
	}
	ofile.Close();
}


void MainBank::OnBnClickedMoney()
{
	if (nowUse == "admin")
	{
		AfxMessageBox(L"管理员您好！您不需要存取款！");
		return;
	}
	Draw dlg(nowCus, cusCount, cus);
	dlg.DoModal();
	nowCus = dlg.nowCus;
}


void MainBank::CopyConsumer(Consumer c[])
{
	for (int i = 0; i < cusCount; i++)
	{
		cus[i] = c[i];
	}
	int i;
	for (i = 0; i < cusCount; i++)
	{
		if (nowUse == cus[i].cardNumber || nowUse == cus[i].id)
		{
			break;
		}
	}
	nowUsePos = i;
	nowCus = cus[i];//寻找当前正在使用是哪一个用户，这个用户必定存在，因为登录成功了
}


void MainBank::OnBnClickedHistory()
{
	if (nowUse == "admin")//如果是管理员，则可以查看用户的所有记录信息
	{
		ShowAllHistory();
	}
	else//不是管理员，显示客户的自己记录
	{
		ShowUsrHistory();
	}
}


void MainBank::ShowAllHistory()
{
	AllHistory dlg(cus, cusCount);
	dlg.DoModal();
}


void MainBank::ShowUsrHistory()
{
	UsrHistory uhis(nowCus);
	uhis.DoModal();
}


void MainBank::OnBnClickedDestroy()
{
	if (nowUse != L"admin")
	{
		if (AfxMessageBox(L"确定注销您的卡号吗？", MB_YESNO) == IDYES)
		{
			if (nowCus.money != 0)
			{
				CString str;
				str.Format(L"尊敬的%s！请将您卡号中的余额取出再注销！", nowCus.name);
				AfxMessageBox(str);
				return;
			}
			AfxMessageBox(L"注销成功！请按确定退出程序！");
			nowCus.cardNumber = L"";
			for (int i = nowUsePos; i < cusCount - 1; i++)
			{
				cus[i] = cus[i + 1];
			}
			cusCount--;//总人数减少一个
			EndDialog(IDD_BANK);
		}
		else
			return;
	}
	else
	{
		AdminDestory dlg(cus, &cusCount);
		dlg.DoModal();
	}
}


void MainBank::OnBnClickedAdmin()
{
	ModifyUsr dlg(cus, cusCount);
	dlg.DoModal();
}


void MainBank::On32775()//退出程序
{
	EndDialog(IDD_BANK);
}


void MainBank::OnTimer(UINT_PTR nIDEvent)//定时器
{
	if (nIDEvent == 1)
	{
		COleDateTime time = COleDateTime::GetCurrentTime();
		CString hello;
		int t = time.GetHour();
		if (t > 6 && t < 11)
		{
			hello = L"上午";
		}
		else if (t >= 11 && t < 14)
		{
			hello = L"中午";
		}
		else if (t >= 14 && t < 18)
		{
			hello = L"下午";
		}
		else if (t >= 18 && t < 24 || t >= 0 && t < 6)
		{
			hello = L"晚上";
		}
		CString ti;
		ti.Format(L"%s %d:%d:%d", hello, time.GetHour(), time.GetMinute(), time.GetSecond());
		m_time.SetWindowTextW(ti);
	}
	if (nIDEvent == 2)
	{
		m_search.SetWindowTextW(L"");//如果搜索为空五秒后自动清空搜索内容
		KillTimer(2);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void MainBank::On32780()//访问github查看源码
{
	system("start explorer https://www.baidu.com");
}


void MainBank::On32781()//关于程序
{
	
}


void MainBank::On32779()//查看帮助菜单
{
	
}


HBRUSH MainBank::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_MAINSTATIC)
	{
		pDC->SetTextColor(RGB(184, 134, 11));
	}
	return hbr;
}


void MainBank::OnBnClickedMfcbutton1()//搜索
{
	GetDlgItem(IDC_EDIT1)->SetFocus();
	CString key;//需要搜索的字符
	GetDlgItemText(IDC_EDIT1, key);
	if (key.IsEmpty())
	{
		AfxMessageBox(L"请输入搜索内容！");
		return;
	}
	CString searchStr;//全局搜索的结果
	CString money;
	if (nowUse == L"admin")//管理员搜索结果
	{
		for (int i = 0; i < cusCount; i++)
		{
		if (cus[i].addr.Find(key) != -1)
			searchStr = searchStr + L"地址：" + cus[i].addr + L"\n";
		if (cus[i].cardNumber.Find(key) != -1)
			searchStr = searchStr + L"卡号：" + cus[i].cardNumber + L"\n";
		if (cus[i].id.Find(key) != -1)
			searchStr = searchStr + L"身份证：" + cus[i].id + L"\n";
		if (cus[i].name.Find(key) != -1)
			searchStr = searchStr + L"姓名：" + cus[i].name + L"\n";
		if (cus[i].phone.Find(key) != -1)
			searchStr = searchStr + L"电话：" + cus[i].phone + L"\n";
		if (cus[i].usrPwd.Find(key) != -1)
			searchStr = searchStr + L"密码：" + cus[i].usrPwd + L"\n";
		money.Format(L"%.2lf", cus[i].money);
		if (money.Find(key) != -1)
			searchStr = searchStr + L"余额：" + money + L"\n";
		for (int j = 0; j < 20; j++)
		{
			if (cus[i].dipositHistory[j].Find(key) != -1)
				searchStr = searchStr + cus[i].dipositHistory[j] + L"\n";
			if (cus[i].fetchHistory[j].Find(key) != -1)
				searchStr = searchStr + cus[i].fetchHistory[j] + L"\n";
		}
	}
	}
	else//用户搜索结果
	{
		if (nowCus.addr.Find(key) != -1)
			searchStr = searchStr + L"地址：" + nowCus.addr + L"\n";
		if (nowCus.cardNumber.Find(key) != -1)
			searchStr = searchStr + L"卡号：" + nowCus.cardNumber + L"\n";
		if (nowCus.id.Find(key) != -1)
			searchStr = searchStr + L"身份证：" + nowCus.id + L"\n";
		if (nowCus.name.Find(key) != -1)
			searchStr = searchStr + L"姓名：" + nowCus.name + L"\n";
		if (nowCus.phone.Find(key) != -1)
			searchStr = searchStr + L"电话：" + nowCus.phone + L"\n";
		if (nowCus.usrPwd.Find(key) != -1)
			searchStr = searchStr + L"密码：" + nowCus.usrPwd + L"\n";
		money.Format(L"%.2lf", nowCus.money);
		if (money.Find(key) != -1)
			searchStr = searchStr + L"余额：" + money + L"\n";
		for (int i = 0; i < 20; i++)
		{
			if (nowCus.dipositHistory[i].Find(key) != -1)
				searchStr = searchStr + nowCus.dipositHistory[i] + L"\n";
			if (nowCus.fetchHistory[i].Find(key) != -1)
				searchStr = searchStr + nowCus.fetchHistory[i] + L"\n";
		}
	}
	if (searchStr.IsEmpty())
	{
		searchStr = L"未找到内容";
		SetTimer(2, 5000, 0);
	}
	m_search.SetWindowTextW(searchStr);
}


void MainBank::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}


void MainBank::OnCancel()
{
	
}


void MainBank::OnOK()
{
}
