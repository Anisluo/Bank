#pragma once
class Consumer
{
public:
	Consumer();
	~Consumer();
	CString cardNumber;//����
	CString name;//�û�����
	double money;//�������
	CString id;//���֤����
	CString addr;//�û���ַ�����嵽���ƺţ�
	CString phone;//�û�����
	CString usrPwd;//�û����� ������λ
	CString confirmUsrPwd;//ȷ���û����������λ
	CString dipositHistory[20];//ֻ��������Ĵ��20����¼
	int errCount;//�������Ĵ���
	int dpos;
	int fpos;
	CString fetchHistory[20];//ֻ���������ȡ��20����¼
};