// AdminDestory.cpp: 实现文件
//

#include "stdafx.h"
#include "Bank.h"
#include "AdminDestory.h"
#include "afxdialogex.h"

// AdminDestory 对话框

IMPLEMENT_DYNAMIC(AdminDestory, CDialogEx)

AdminDestory::AdminDestory(Consumer* c, int *count, CWnd* pParent /*=nullptr*/) 
	: CDialogEx(IDD_ADMINDESTORY, pParent)
{
	cusCount = count;
	countPos = 0;
	cus = c;
}

AdminDestory::~AdminDestory()
{
}

void AdminDestory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


BEGIN_MESSAGE_MAP(AdminDestory, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &AdminDestory::OnClickList)
	ON_BN_CLICKED(IDOK2, &AdminDestory::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK, &AdminDestory::OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// AdminDestory 消息处理程序



BOOL AdminDestory::OnInitDialog()
{
	CString str;
	CDialogEx::OnInitDialog();
	m_list.InsertColumn(0, L"姓名", LVCFMT_CENTER, 75);
	m_list.InsertColumn(1, L"余额", LVCFMT_CENTER, 85);
	m_list.InsertColumn(2, L"卡号", LVCFMT_CENTER, 150);
	m_list.InsertColumn(3, L"身份证", LVCFMT_CENTER, 150);
	m_list.SetExtendedStyle(1 | LVS_EX_CHECKBOXES);
	for (int i = 0; i < *cusCount; i++)
	{
		m_list.InsertItem(i, cus[i].name);
		str.Format(L"%.2lf元", cus[i].money);
		m_list.SetItemText(i, 1, str);
		m_list.SetItemText(i, 2, cus[i].cardNumber);
		m_list.SetItemText(i, 3, cus[i].id);
	}
	return TRUE;
}


void AdminDestory::OnClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	DWORD dwPos = GetMessagePos();//获取光标在整个屏幕位置
	CPoint pt(dwPos);
	m_list.ScreenToClient(&pt);//屏幕位置变为对话框相对位置
	UINT nFlag;
	int nItem = m_list.HitTest(pt, &nFlag);//获取选中哪一项 返回参数pHitTestInfo指定位置的项的索引
	if (nFlag == LVHT_ONITEMSTATEICON)
	{
		BOOL bCheckState = m_list.GetCheck(nItem);
		if (bCheckState)//勾选为false,不勾为true
		{
			for (int i = nItem; i < countPos - 1; i++)
			{
				Count[i] = Count[i + 1];
				countPos--;
			}
		}
		else//勾选
		{
			Count[countPos++] = nItem;
		}
	}
	*pResult = 0;
}


void AdminDestory::OnBnClickedOk2()
{
	if (countPos == 0)
	{
		AfxMessageBox(L"您未选中需要注销的账户！");
		return;
	}
	if (AfxMessageBox(L"确定注销吗？", MB_YESNO) == IDNO)
	{
		return;
	}
	for (int i = 0; i < countPos; i++)
	{
		if (cus[Count[i]].money != 0)
		{
			AfxMessageBox(L"选项中存在余额不为0的账户！");
			return;
		}
		for (int j = Count[i]; j < *cusCount - 1; j++)
		{
			cus[j] = cus[j + 1];
		}
	}
	*cusCount -= countPos;
	AfxMessageBox(L"注销成功！");
	EndDialog(IDD_ADMINDESTORY);
}


void AdminDestory::OnBnClickedOk()
{
	EndDialog(IDD_ADMINDESTORY);
}


void AdminDestory::OnClose()
{
	EndDialog(IDD_ADMINDESTORY);
}
