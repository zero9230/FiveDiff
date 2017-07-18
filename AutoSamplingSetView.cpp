// AutoSamplingSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "AutoSamplingSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"


// CAutoSamplingSetView 对话框

IMPLEMENT_DYNAMIC(CAutoSamplingSetView, CDialogEx)

CAutoSamplingSetView::CAutoSamplingSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoSamplingSetView::IDD, pParent)
{
	rs = true;
	for (int i = 0; i < 10; i++)
	{
		paratemp[i] ="";
	}
	for (int i = 0; i < 5; i++)
	{
		buff[i] = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		buff2[i] = 0;
	}
	for (int i = 0; i < 20; i++)
	{
		version[i] = 0;
	}
	for (int i = 0; i < 21; i++)
	{
		sdata2[i] =  0;
	}
	for (int i = 0; i < 21; i++)
	{
		sdata[i] = 0;
	}

	
	
}

CAutoSamplingSetView::~CAutoSamplingSetView()
{
}

void CAutoSamplingSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoSamplingSetView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_AS_1_RESET, &CAutoSamplingSetView::OnAs1Reset)
	ON_BN_CLICKED(IDC_AS_2_RESET, &CAutoSamplingSetView::OnAs2Reset)
	ON_BN_CLICKED(IDC_AS_3_RESET, &CAutoSamplingSetView::OnAs3Reset)
	ON_BN_CLICKED(IDC_AS_4_RESET, &CAutoSamplingSetView::OnAs4Reset)
	ON_BN_CLICKED(IDC_AS_5_RESET, &CAutoSamplingSetView::OnAs5Reset)
	ON_BN_CLICKED(IDC_AS_6_RESET, &CAutoSamplingSetView::OnAs6Reset)
	ON_BN_CLICKED(IDC_AS_7_RESET, &CAutoSamplingSetView::OnAs7Reset)
	ON_BN_CLICKED(IDC_AS_8_RESET, &CAutoSamplingSetView::OnAs8Reset)
	ON_BN_CLICKED(IDC_AS_9_RESET, &CAutoSamplingSetView::OnAs9Reset)
	ON_BN_CLICKED(IDC_AS_10_RESET, &CAutoSamplingSetView::OnAs10Reset)
	ON_BN_CLICKED(IDC_AS_1_RUN, &CAutoSamplingSetView::OnAs1Run)
	ON_BN_CLICKED(IDC_AS_2_RUN, &CAutoSamplingSetView::OnAs2Run)
	ON_BN_CLICKED(IDC_AS_3_RUN, &CAutoSamplingSetView::OnAs3Run)
	ON_BN_CLICKED(IDC_AS_4_RUN, &CAutoSamplingSetView::OnAs4Run)
	ON_BN_CLICKED(IDC_AS_5_RUN, &CAutoSamplingSetView::OnAs5Run)
	ON_BN_CLICKED(IDC_AS_6_RUN, &CAutoSamplingSetView::OnAs6Run)
	ON_BN_CLICKED(IDC_AS_7_RUN, &CAutoSamplingSetView::OnAs7Run)
	ON_BN_CLICKED(IDC_AS_8_RUN, &CAutoSamplingSetView::OnAs8Run)
	ON_BN_CLICKED(IDC_AS_9_RUN, &CAutoSamplingSetView::OnAs9Run)
	ON_BN_CLICKED(IDC_AS_10_RUN, &CAutoSamplingSetView::OnAs10Run)
	ON_BN_CLICKED(IDC_AS_PARA_READ, &CAutoSamplingSetView::OnAsParaRead)
	ON_BN_CLICKED(IDC_AS_PARA_WRITE, &CAutoSamplingSetView::OnAsParaWrite)
	ON_BN_CLICKED(IDC_PARA_INIT, &CAutoSamplingSetView::OnParaInit)
	ON_BN_CLICKED(IDC_AS_ALL_RESET, &CAutoSamplingSetView::OnAsAllReset)
END_MESSAGE_MAP()


// CAutoSamplingSetView 消息处理程序


void CAutoSamplingSetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();

	CDialogEx::OnPaint();
}


HBRUSH CAutoSamplingSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

bool CAutoSamplingSetView::AllowAS = false;
uchar  CAutoSamplingSetView::IsMotorReseted[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned int CAutoSamplingSetView::VersionNum[3] = { 0 };
unsigned int CAutoSamplingSetView::polltimes = 0;
unsigned int CAutoSamplingSetView::ASMotorPara[10] = { 0 };
BOOL CAutoSamplingSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	AllowAS = Allow_ASOnLine;
	Allow_ASOnLine = FALSE;
	for (int i = 0; i < 10; i++)
		IsMotorReseted[i] = 1;

	WriteSystemcfgFile();
	CString temp[10];
	for (int i = 0; i < 10; i++)
	{	
		temp[i].Format(L"%d",systemcfg.Autosamplerpara[i]);
	}
	GetDlgItem(IDC_AS_1_PARA)->SetWindowText(temp[0]);
	GetDlgItem(IDC_AS_2_PARA)->SetWindowText(temp[1]);
	GetDlgItem(IDC_AS_3_PARA)->SetWindowText(temp[2]);
	GetDlgItem(IDC_AS_4_PARA)->SetWindowText(temp[3]);
	GetDlgItem(IDC_AS_5_PARA)->SetWindowText(temp[4]);
	GetDlgItem(IDC_AS_6_PARA)->SetWindowText(temp[5]);
	GetDlgItem(IDC_AS_7_PARA)->SetWindowText(temp[6]);
	GetDlgItem(IDC_AS_8_PARA)->SetWindowText(temp[7]);
	GetDlgItem(IDC_AS_9_PARA)->SetWindowText(temp[8]);
	GetDlgItem(IDC_AS_10_PARA)->SetWindowText(temp[9]);

	GetDlgItem(IDC_AS_4_PARA)->EnableWindow(FALSE);
	GetDlgItem(IDC_AS_4_RESET)->EnableWindow(FALSE);
	GetDlgItem(IDC_AS_4_RUN)->EnableWindow(FALSE);

	rs = send_asmotpara(sdata2, 0x14, ASCMD_OPPARA[3]);
	if (rs != false)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0,(uchar *)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		if (!strcmp(buff, "SCOK"))
		{
			//需设置延时重复接收，若接收过快，接收数据可能有误
			SetTimer(POLLTIME3, 1000,0);
		}
		else
		{
			if (systemcfg.language == CHINESE)
			{
				MessageBox(L"发送获取自动进样版本号命令失败",L"警告!", MB_OK | MB_ICONINFORMATION);
			}
			/*else if (systemcfg.language == ENGLISH)
				CreateWarningBoxNonCHDlg(hDlg, "Failed in sending the acquire command for the autosample version number", "Warning!");*/
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CAutoSamplingSetView::InitPara(int para[])
{
	para[0] = systemcfg.Autosamplerpara[0];
	para[1] = systemcfg.Autosamplerpara[1];
	para[2] = systemcfg.Autosamplerpara[2];     //机械手混匀样品位(X)
	para[3] = systemcfg.Autosamplerpara[5];     //机械手穿刺位(X)
	para[4] = systemcfg.Autosamplerpara[7];      //机械手放回样品位(X)
	para[5] = systemcfg.Autosamplerpara[8];   //机械手取样位(Y)
	para[6] = systemcfg.Autosamplerpara[9];     //机械手混匀位(Y)
	para[7] = systemcfg.Autosamplerpara[3];
	para[8] = systemcfg.Autosamplerpara[4];
	para[9] = systemcfg.Autosamplerpara[6];
}

void CAutoSamplingSetView::OutputPara(int para[])
{
	systemcfg.Autosamplerpara[0] = para[0];
	systemcfg.Autosamplerpara[1] = para[1];
	systemcfg.Autosamplerpara[2] = para[2];
	systemcfg.Autosamplerpara[3] = para[7];
	systemcfg.Autosamplerpara[4] = para[8];
	systemcfg.Autosamplerpara[5] = para[3];
	systemcfg.Autosamplerpara[6] = para[9];
	systemcfg.Autosamplerpara[7] = para[4];
	systemcfg.Autosamplerpara[8] = para[5];
	systemcfg.Autosamplerpara[9] = para[6];
}

void CAutoSamplingSetView::OutputVersionNum(int para[])
{

	OriVersionNum[0] = para[0];
	OriVersionNum[1] = para[1];
	OriVersionNum[2] = para[2];

}

bool CAutoSamplingSetView::send_asmotpara(uchar sdata[], uchar len, uchar cmd)
{
	bool 		nwrt = false;
	uchar		i;
	uchar 		senddata[26] = { 0x02, 0x68, 0 };
	uchar 		check = 0;
	uchar 		now = 0;
	if (systemcfg3.structure == 3)
	{
		senddata[2] = len;
		senddata[3] = cmd;
		for (i = 0; i < len; i++)
			senddata[i + 4] = sdata[i];
		now = len + 4;
		for (i = 0; i < now; i++)
			check += senddata[i];
		senddata[now] = check;
		senddata[now + 1] = 0;
		now++;
		for (i = 0; i < 6; i++)
			nwrt = m_newCom.ComWrt(0, senddata, len + 5,115200);
		return nwrt;
	}
	else
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"发送命令失败",L"警告!", MB_OK | MB_ICONINFORMATION);
	/*	else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Failed in sending command", "Warning!");*/
		return false;
	}
}

int CAutoSamplingSetView::recv_asmotpara(unsigned int * rdata, uchar len)
{
	uchar 			recvdata[100] = { 0 };
	uchar			finaldata[26] = { 0 };
	uchar 			i = 0;
	int 				nread = 1;
	uchar 			checkflag = 0;
	uchar			now = 0;
	uchar			startflag = 0;

	for (i = 0; i < 100; i++)
		recvdata[i] = 0;
	nread = m_newCom.ComRd(0, recvdata, 100,115200);
	if (nread == -1)
		return -8;
	for (i = 0; i < 99; i++)
	{
		if (recvdata[i] == 0x02){
			if (recvdata[i + 1] == 0x68)
			{
				startflag = i;
				break;
			}
		}
	}
	for (i = 0; i < 26; i++)
		finaldata[i] = 0;
	for (i = 0; i < 25; i++)
	{
		finaldata[i] = recvdata[i + startflag];
		//printf("finaldata[%d]:0x%x------------\n",i,finaldata[i]);
	}
	if (finaldata[0] != 0x02)
	{
		printf("Start flag is wrong--------\n");
		return -1;
	}
	else
	{
		if (finaldata[1] != 0x68)
		{
			printf("Second flag is wrong--------\n");
			return -2;
		}
		else
		{
			if (finaldata[3] != 0x7F)
			{
				printf("the CMD flag is wrong--------\n");
				return -3;
			}
			else
			{
				now = recvdata[startflag + 2] + 4;
				for (i = 0; i < now; i++)
					checkflag += finaldata[i];
				if (checkflag != finaldata[now])
				{
					printf("Check num is wrong!---------\n");
					return -4;
				}
				else
				{
					for (i = 0; i < 10; i++)
						rdata[i] = finaldata[2 * (i + 2)] + finaldata[2 * (i + 2) + 1] * 256;
					return 0;
				}
			}
		}
	}
}


int CAutoSamplingSetView::recv_versionnum(unsigned int * rdata, uchar len)
{
	uchar 			recvdata[100] = { 0 };
	uchar			finaldata[26] = { 0 };
	uchar 			i = 0;
	int 				nread = 1;
	uchar 			checkflag = 0;
	uchar			now = 0;
	uchar			startflag = 0;

	for (i = 0; i < 100; i++)
		recvdata[i] = 0;
	nread = m_newCom.ComRd(0, recvdata, 100,115200);
	if (nread == -1)
		return -8;
	for (i = 0; i < 99; i++)
	{
		if (recvdata[i] == 0x02){
			if (recvdata[i + 1] == 0x68)
			{
				startflag = i;
				break;
			}
		}
	}
	for (i = 0; i < 26; i++)
		finaldata[i] = 0;
	for (i = 0; i < 25; i++)
	{
		finaldata[i] = recvdata[i + startflag];
		//printf("finaldata[%d]:0x%x------------\n",i,finaldata[i]);
	}
	if (finaldata[0] != 0x02)
	{
		printf("Start flag is wrong--------\n");
		return -1;
	}
	else
	{
		if (finaldata[1] != 0x68)
		{
			printf("Second flag is wrong--------\n");
			return -2;
		}
		else
		{
			if (finaldata[3] != 0x15)
			{
				printf("the CMD flag is wrong--------\n");
				return -3;
			}
			else
			{
				now = recvdata[startflag + 2] + 4;
				for (i = 0; i < now; i++)
					checkflag += finaldata[i];
				if (checkflag != finaldata[now])
				{
					printf("Check num is wrong!---------\n");
					return -4;
				}
				else
				{
					for (i = 0; i < 3; i++)
						rdata[i] = finaldata[i + 4];
					return 0;
				}
			}
		}
	}
}

void CAutoSamplingSetView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case POLLTIME:
		polltimes++;
		//printf("polltimes:%d-------------\n",polltimes);
		TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
		rs = recv_asmotpara(&ASMotorPara[0], 20);
		if (rs == 0 || polltimes == 5)
		{
			KillTimer( POLLTIME);
			if (polltimes == 5)
			{
				if (systemcfg.language == CHINESE)
					MessageBox(L"读电机参数失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*	else if (systemcfg.language == ENGLISH)
					CreateWarningBoxNonCHDlg(hDlg, "Failed in reading motor parameters", "Warning!");*/
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					rs = m_newCom.ComWrt(0, "CDR", 3,115200);
				}
				OutputPara((int *)ASMotorPara);
		
				CString temp[10];
				for (int i = 0; i < 10; i++)
				{
					temp[i].Format(L"%d", systemcfg.Autosamplerpara[i]);
				}
				GetDlgItem(IDC_AS_1_PARA)->SetWindowText(temp[0]);
				GetDlgItem(IDC_AS_2_PARA)->SetWindowText(temp[1]);
				GetDlgItem(IDC_AS_3_PARA)->SetWindowText(temp[2]);
				GetDlgItem(IDC_AS_4_PARA)->SetWindowText(temp[3]);
				GetDlgItem(IDC_AS_5_PARA)->SetWindowText(temp[4]);
				GetDlgItem(IDC_AS_6_PARA)->SetWindowText(temp[5]);
				GetDlgItem(IDC_AS_7_PARA)->SetWindowText(temp[6]);
				GetDlgItem(IDC_AS_8_PARA)->SetWindowText(temp[7]);
				GetDlgItem(IDC_AS_9_PARA)->SetWindowText(temp[8]);
				GetDlgItem(IDC_AS_10_PARA)->SetWindowText(temp[9]);

			}
			polltimes = 0;
			key_status = TRUE;
		}
		break;
	case POLLTIME3:
	{
		polltimes++;
		//printf("polltimes:%d-------------\n",polltimes);
		TRACE("MSG_TIMER:POLLTIME2 is due -------------#\n");
		rs = recv_versionnum(&VersionNum[0], 3);
		if (rs == 0 || polltimes == 5)
		{
			KillTimer(POLLTIME2);
			if (polltimes == 5)
			{
				if (systemcfg.language == CHINESE)
					MessageBox(L"读自动进样机版本号失败",L"警告!", MB_OK | MB_ICONINFORMATION);
				//else if (systemcfg.language == ENGLISH)
				//	CreateWarningBoxNonCHDlg(hDlg, "Failed in acquiring autosampler version numble", "Warning!");
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					rs = m_newCom.ComWrt(0, "CDR", 3,115200);
				}
				OutputVersionNum((int *)VersionNum);

				strcat(version, "自动进样版本:");
				for (int i = 0; i <3; i++)
				{
					sprintf(buff2, "%d", OriVersionNum[i]);
					strcat(version, buff2);
					strcat(version, ".");
				}
				version[18] = 0;
				CString temp = version;
				GetDlgItem(IDC_VERSION_STATIC)->SetWindowText(temp);
			}
			polltimes = 0;
			key_status = TRUE;
		}
		break;
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CAutoSamplingSetView::OnAs1Reset()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_1_PARA)->GetWindowText(paratemp[0]);
	
	InitPara((int *)ASMotorPara);

	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RESET[0]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败",L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
				CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[0] = 1;
	}
	key_status = TRUE;

}


void CAutoSamplingSetView::OnAs2Reset()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_2_PARA)->GetWindowText(paratemp[1]);

	InitPara((int *)ASMotorPara);

	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RESET[1]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[1] = 1;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs3Reset()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间",L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值",L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return ;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RESET[2]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[2] = 1;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs4Reset()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CAutoSamplingSetView::OnAs5Reset()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RESET[4]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[4] = 1;
	}
	key_status = TRUE;

}


void CAutoSamplingSetView::OnAs6Reset()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_6_PARA)->GetWindowText(paratemp[5]);

	InitPara((int *)ASMotorPara);

	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RESET[5]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[5] = 1;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs7Reset()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_7_PARA)->GetWindowText(paratemp[6]);

	InitPara((int *)ASMotorPara);

	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RESET[6]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[6] = 1;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs8Reset()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_8_PARA)->GetWindowText(paratemp[7]);

	InitPara((int *)ASMotorPara);

	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RESET[7]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[7] = 1;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs9Reset()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_9_PARA)->GetWindowText(paratemp[8]);

	InitPara((int *)ASMotorPara);

	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RESET[8]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[8] = 1;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs10Reset() 
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_10_PARA)->GetWindowText(paratemp[9]);
	systemcfg.Autosamplerpara[9] = _wtoi(paratemp[9]);

	InitPara((int *)ASMotorPara);

	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RESET[9]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[9] = 1;
	}
	key_status = TRUE;

}

void CAutoSamplingSetView::OnAs1Run()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_1_PARA)->GetWindowText(paratemp[0]);
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RUN[0]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				systemcfg.Autosamplerpara[0] = _wtoi(paratemp[0]);
				break;
			}
				
		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[0] = 0;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs2Run()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_2_PARA)->GetWindowText(paratemp[1]);
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RUN[1]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				systemcfg.Autosamplerpara[0] = _wtoi(paratemp[0]);
				break;
			}

		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[1] = 0;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs3Run()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RUN[2]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				systemcfg.Autosamplerpara[2] = _wtoi(paratemp[2]);
				break;
			}

		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[2] = 0;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs4Run()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CAutoSamplingSetView::OnAs5Run()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RUN[4]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				systemcfg.Autosamplerpara[4] = _wtoi(paratemp[4]);
				break;
			}

		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[4] = 0;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs6Run()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_6_PARA)->GetWindowText(paratemp[5]);
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RUN[5]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				systemcfg.Autosamplerpara[5] = _wtoi(paratemp[5]);
				break;
			}

		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[5] = 0;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs7Run()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_7_PARA)->GetWindowText(paratemp[6]);
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RUN[6]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				systemcfg.Autosamplerpara[6] = _wtoi(paratemp[6]);
				break;
			}

		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[6] = 0;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs8Run()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_8_PARA)->GetWindowText(paratemp[8]);
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RUN[7]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				systemcfg.Autosamplerpara[7] = _wtoi(paratemp[7]);
				break;
			}

		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[7] = 0;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs9Run()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_9_PARA)->GetWindowText(paratemp[8]);
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RUN[8]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				systemcfg.Autosamplerpara[8] = _wtoi(paratemp[8]);
				break;
			}

		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[8] = 0;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAs10Run()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_10_PARA)->GetWindowText(paratemp[9]);
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}
	InitPara((int *)ASMotorPara);
	//向DSP发送步进电机运动参数
	for (int i = 0; i <10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	//防止数据异常设定的随机值
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_RUN[9]);
	if (rs != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				systemcfg.Autosamplerpara[9] = _wtoi(paratemp[9]);
				break;
			}

		}
		//Debug
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机复位参数发送失败", L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
			CreateWarningBoxNonCHDlg(hDlg, "Failed in sending motor reseting parameters", "Warning!");*/
		}
		else
			IsMotorReseted[9] = 0;
	}
	key_status = TRUE;
}


void CAutoSamplingSetView::OnAsParaRead()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	memset(sdata, 0, sizeof(sdata));
	rs = send_asmotpara(sdata, 0x14, ASCMD_OPPARA[1]);
	if (rs !=false)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		if (!strcmp(buff, "SCOK"))
		{
			//需设置延时重复接收，若接收过快，接收数据可能有误
			SetTimer( POLLTIME, 1000,0);
		}
		else
		{
			key_status = TRUE;
			if (systemcfg.language == CHINESE)
				MessageBox(L"读电机参数请求未响应",L"警告!", MB_OK | MB_ICONINFORMATION);
		/*	else if (systemcfg.language == ENGLISH)
				CreateWarningBoxNonCHDlg(hDlg, "Have not answered the reading para application", "Warning!");*/
		}
	}
	else
		key_status = TRUE;
}


void CAutoSamplingSetView::OnAsParaWrite()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_AS_1_PARA)->GetWindowText(paratemp[0]);
	GetDlgItem(IDC_AS_2_PARA)->GetWindowText(paratemp[1]);
	GetDlgItem(IDC_AS_3_PARA)->GetWindowText(paratemp[2]);
	GetDlgItem(IDC_AS_4_PARA)->GetWindowText(paratemp[3]);
	GetDlgItem(IDC_AS_5_PARA)->GetWindowText(paratemp[4]);
	GetDlgItem(IDC_AS_6_PARA)->GetWindowText(paratemp[5]);
	GetDlgItem(IDC_AS_7_PARA)->GetWindowText(paratemp[6]);
	GetDlgItem(IDC_AS_8_PARA)->GetWindowText(paratemp[7]);
	GetDlgItem(IDC_AS_9_PARA)->GetWindowText(paratemp[8]);
	GetDlgItem(IDC_AS_10_PARA)->GetWindowText(paratemp[9]);

	if ((_wtoi(paratemp[2])<300) || (_wtoi(paratemp[2])>360))
	{
		MessageBox(L"设置参数必须在范围(300,360)之间", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[2]);
		GetDlgItem(IDC_AS_3_PARA)->SetWindowText(str);
		return;
	}
	if (_wtoi(paratemp[2]) <= _wtoi(paratemp[4]))
	{
		MessageBox(L"机械手放回样品位(X)值需小于机械手混匀样品位值", L"警告!", MB_OK | MB_ICONINFORMATION);
		CString str;
		str.Format(L"%d", systemcfg.Autosamplerpara[4]);
		GetDlgItem(IDC_AS_5_PARA)->SetWindowText(str);
		return;
	}

	InitPara((int *)ASMotorPara);
	for (int i = 0; i < 10; i++)
	{
		sdata[2 * i] = ASMotorPara[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = ASMotorPara[i] >> 8;   	//高8位
	}
	sdata[20] = 0;
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_OPPARA[0]);
	if (rs != false)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs =m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
			{
				for (int i = 0; i < 10; i++)
					systemcfg.Autosamplerpara[i] = _wtoi(paratemp[i]);
				break;
			}
				
		}
		if (strcmp(buff, "SCOK") != 0)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"保存电机参数失败",L"警告!", MB_OK | MB_ICONINFORMATION);
			/*else if (systemcfg.language == ENGLISH)
				CreateWarningBoxNonCHDlg(hDlg, "Failed in saving motor parameters", "Warning!");*/
		}
	}
	key_status = TRUE;
	WriteSystemcfgFile();
}


void CAutoSamplingSetView::OnParaInit()
{
	// TODO:  在此添加控件通知处理程序代码
	CString temp[10];
	for (int i = 0; i < 10; i++)
	{
		temp[i].Format(L"%d", OriPara[i]);
	}
	GetDlgItem(IDC_AS_1_PARA)->SetWindowText(temp[0]);
	GetDlgItem(IDC_AS_2_PARA)->SetWindowText(temp[1]);
	GetDlgItem(IDC_AS_3_PARA)->SetWindowText(temp[2]);
	GetDlgItem(IDC_AS_4_PARA)->SetWindowText(temp[3]);
	GetDlgItem(IDC_AS_5_PARA)->SetWindowText(temp[4]);
	GetDlgItem(IDC_AS_6_PARA)->SetWindowText(temp[5]);
	GetDlgItem(IDC_AS_7_PARA)->SetWindowText(temp[6]);
	GetDlgItem(IDC_AS_8_PARA)->SetWindowText(temp[7]);
	GetDlgItem(IDC_AS_9_PARA)->SetWindowText(temp[8]);
	GetDlgItem(IDC_AS_10_PARA)->SetWindowText(temp[9]);
}


void CAutoSamplingSetView::OnAsAllReset()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	rs = send_asmotpara(sdata, 0x14, ASCMD_OPPARA[2]);
	if (rs != false)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
				buff[j] = 0;
			rs = m_newCom.ComRd(0, (unsigned char*)buff, 4,115200);
			buff[4] = 0;
			if (!strcmp(buff, "SCOK"))
				break;
		}
		if (strcmp(buff, "SCOK") != 0)
		{
			key_status = TRUE;
			if (systemcfg.language == CHINESE)
				MessageBox(L"电机整体复位失败",L"警告!", MB_OK | MB_ICONINFORMATION);
			//else if (systemcfg.language == ENGLISH)
			//	CreateWarningBoxNonCHDlg(hDlg, "Failed in reseting the total motors", "Warning!");
		}
	}
	key_status = TRUE;
}
