// SelftestView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "SelftestView.h"
//#include "TestmainView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include  "Resource.h"
// CSelftestView 对话框

BOOL ErrFlag;
BOOL ErrorTimer_Flag;
BOOL BlockErr_Flag;
int IsBlocking;
int BlockErrStore;
IMPLEMENT_DYNAMIC(CSelftestView, CDialogEx)

CSelftestView::CSelftestView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSelftestView::IDD, pParent)
{
	//m_Font.CreatePointFont(300,Arial,NULL);
	VERIFY(m_Font.CreateFont(
		20,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		GB2312_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		L"宋体"));                 // lpszFacename
}

CSelftestView::~CSelftestView()
{
}

void CSelftestView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelftestView, CDialogEx)

	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CSelftestView::OnAckspi)
	ON_MESSAGE(WM_BLOCKER, &CSelftestView::OnBlocker)
	ON_BN_CLICKED(IDC_MECHINIT_OK, &CSelftestView::OnBnClickedMechinitOk)
	ON_BN_CLICKED(IDC_MECHINIT_CANCEL, &CSelftestView::OnBnClickedMechinitCancel)
END_MESSAGE_MAP()


// CSelftestView 消息处理程序





void CSelftestView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
//	@TG
//#3073
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()
	

	//CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为白色背景
	dc.Rectangle(50,30,rect.right-50,rect.bottom-50);
	dc.SelectObject(&m_Font);
	dc.TextOutW(rect.left+rect.Width()/2-80,rect.top+rect.Height()/2-80,"是否进行自检？？");

}


void CSelftestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case POLLTIME2:
			TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
			sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
			PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);

			TRACE(_T("rdata_sate[0]=%X\n"), rdata_state[0]);
			PostMessage(WM_ACKSPI, rdata_state[0], 0);
			break;
		case ERROR_TIMER:
		{
							errorShowNum++;
							if (errorShowNum >= errorNumber)
							{
								errorShowNum = 0;
								ErrFlag = FALSE;
								ErrorTimer_Flag = FALSE;
								KillTimer(ERROR_TIMER);
							}
							else
								DisplayErrMess();
							break;
		}
		case CHECKERR_TIMER:
		{
							   if (ErrorTimer_Flag == FALSE)    //若ErrorTimer关闭    
							   {
								   BlockErr_Flag = FALSE;
								   KillTimer(CHECKERR_TIMER);
								   errorShowMess = BlockErrStore;

								   if (errorShowMess > 0)
								   {

								   }
							   }
							   break;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CSelftestView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case SPI_STATE_INFO_END:
		KillTimer(POLLTIME);
		DSP_status = Free;
		GetDlgItem(IDC_MECHINIT_OK)->EnableWindow(TRUE);
		GetDlgItem(IDC_MECHINIT_CANCEL)->EnableWindow(TRUE);
		//SendMessage(MainWindowhDlg,MSG_GETERRORS, 0, 0L);
		//GetErrInfo();
		int		i;

		for (i = 0; i < ERRNUM + 1; i++)
		{
			errorReceive[i] = 0;
		}
		sdata_cmd[0] = SPI_CMD_REQERROR;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(errorReceive, SPI_TYPE_ERRORRES);
		errorNumber = 0;

		for (i = 1; i < ERRNUM + 1; i++)
		if (1 == errorReceive[i])
		{
			logfile.alertnum[i]++;
			errorMessage[errorNumber] = i;
			errorNumber++;
		}
		if (errorNumber > 0)
		{
			ErrFlag = TRUE;
			errorShowNum = 0;
			ErrorTimer_Flag = TRUE;

			DisplayErrMess();
			
			SetTimer( ERROR_TIMER, 2000,0);
		}
		
		key_status = TRUE;
		break;
	default:
		break;
	}

	return 0;
}


void CSelftestView::DisplayErrMess()
{
	errorShowMess = errorMessage[errorShowNum];
	if (errorShowMess == 8)       //WBC堵孔
	{
		SendMessage(WM_BLOCKER, (WPARAM)1, 0L);
	}
	else if (errorShowMess == 13)		  //鞘流堵孔
	{
		SendMessage(WM_BLOCKER, (WPARAM)2, 0L);
	}
	else if (errorShowMess == 9)		  //RBC堵孔
	{
		SendMessage(WM_BLOCKER, (WPARAM)3, 0L);
	}
	else
	{

	}
	//AfxMessageBox(_T("3435"));
}


afx_msg LRESULT CSelftestView::OnBlocker(WPARAM wParam, LPARAM lParam)
{

	switch (wParam){

	case 1:
	{
			  IsBlocking = 1;
			  DealwithBlockErr(SPI_CMD_BACKSWING_WBCPH, 8);
			  //DealwithBlockErr(hDlg, SPI_CMD_BACKSWING_WBCPH, 8);

			  break;
	}
	case 2:
	//	DealwithBlockErr(SPI_CMD_BACKSWING_LMNEPH, 13);
		break;
	case 3:
	{
			  IsBlocking = 3;
			  DealwithBlockErr( SPI_CMD_BACKSWING_RBCPH, 9);
			  break;
	}
	default:
		break;
	}
	//AfxMessageBox(_T("4243"));
	return 0;
}


void CSelftestView::DealwithBlockErr(uchar CMD_Name, uchar ErrNum)
{

	if (!BlockErr_Flag)
	{
		BlockErr_Flag = TRUE;

		BlockErrStore = ErrNum;
		SetTimer(CHECKERR_TIMER, 200, 0);
	}
	else
		puts("CHECKERR_TIMER is open!");

	//SendCmdToDSP(CMD_Name);
	char Mess[50];

	sdata_cmd[0] = CMD_Name;

	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME2, SPI_POLL_TIME3000, 0);
	//AfxMessageBox(_T("3637"));
}


void CSelftestView::OnBnClickedMechinitOk()
{
	// TODO:  在此添加控件通知处理程序代码
	char *mess;
	mess = "mech initialization and check mech\n";
	//CommonExecution(mess, SPI_CMD_SELFTEST, SPI_POLL_TIME3000);

	CString str = "ERROR!";
	//MessageBox(str, str, MB_OKCANCEL);
	MessageBoxEx(NULL, L"English", L"Error", MB_OKCANCEL, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	TRACE(mess);
	key_status = FALSE;
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_SELFTEST;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
	{
		MessageBox(L"命令发送不成功", L"Error", MB_OKCANCEL);
	}
	else{
		GetDlgItem(IDC_MECHINIT_OK)->EnableWindow(FALSE);
		GetDlgItem(IDC_MECHINIT_CANCEL)->EnableWindow(FALSE);
		SetTimer(POLLTIME, 3000, 0);

	}
}


void CSelftestView::OnBnClickedMechinitCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
