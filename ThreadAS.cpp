#include "stdafx.h"
#include "ThreadAS.h"
#include "TestmainView.h"
//#include "Includes_app.h"

#define		SMAX_AS			20
#define		LMAX_AS			50

bool Allow_ASOnLine;
bool AS_OnLine;				//自动进样系统与主机建立连接-1(START)，未建立连接-0(OVER)
bool ASCur_EN;				//当前测试使能。1有效才能工作。请求血样，否则不请求血样(执行自动维护或提示数据库满，需临时暂停)

CThreadAS::CThreadAS()
{

}


CThreadAS::~CThreadAS()
{
}

//判断接收到的字符串是否符合
int CThreadAS::CompDataRead(uchar * src, const uchar *obj)
{
	uchar*	smove = src;
	uchar*	omove = const_cast<uchar *>( obj);

	while (smove != src + SMAX_AS - 4 && omove != obj + 4)
	{
		if (*smove == *omove && *(smove + 1) == *(omove + 1))
		{
			if (*(smove + 2) == *(omove + 2) && *(smove + 3) == *(omove + 3))
				return 0;
		}

		smove++;
	}

	return RedWrong;
}

//建立连接,开始测试
int CThreadAS::TryConnect(const char *AllowStart, int* ASCur_Step)
{
	int		m_nwt = 0;
	int		m_nrd = 0;
	int		i;
	uchar	buffRd[SMAX_AS] = { 0 };

	m_nwt = m_newCom.ComWrt(2, AllowStart, 3,115200);	//发送允许自动进样系统建立连接

	if (m_nwt ==false)
	{
		fprintf(stderr, "write AllowStart to ThreadAS failed---------!\n");
		return WrtErr;
	}

	timeFrKd9 = 0;
	while (1)		//循环1s等待
	{
		if (timeFrKd9 > 0)
			return TimeOut;

		for (i = 0; i < SMAX_AS; i++)
			buffRd[i] = 0;
		if (Allow_ASOnLine)
		{
			m_nrd = m_newCom.ComRd(0, buffRd, SMAX_AS,115200);
			if (m_nrd ==false)
				continue;

			if (0 == CompDataRead(buffRd, (const unsigned char*)"STAT"))	//应答信号Start，建立连接
			{
				key_status = FALSE;		//有应答信号后，禁止操作，进行自动操作
				AS_OnLine = TRUE;
				ASCur_EN = TRUE;
				*ASCur_Step = 0;

				//若开始测试时处于待机状态，则点亮屏幕	
				if (timeFrKd >= 60 * systemcfg.sleeptime) //60
				{
					fprintf(stderr, "..........active in the ThrsAS   tryconnect..............\n");
					//SendMessage(MainWindowhDlg, MSG_COMMAND, MSG_ACTIVATESCREEN, 0L);
				}
				return 0;
			}
		}
	}
}

int CThreadAS::Step0(int* ASCur_Step)
{
	int		i;
	int		m_nrd = 0;
	uchar	buffRd[SMAX_AS] = { 0 };

	//判断是否OVER，如果OVER则跳出
	for (i = 0; i < SMAX_AS; i++)
		buffRd[i] = 0;

	m_nrd = m_newCom.ComRd(0, buffRd, SMAX_AS,115200);
	if (m_nrd == false)
		return RedErr;

	if (0 == CompDataRead(buffRd, (const unsigned char*)"OVER"))     //Over
	{
		SendOver(ASCur_Step);
	}

	//判断是否进入下一步
	if (ASCur_EN)
	{
		if (Free == DSP_status || Clean == DSP_status)//不在通信中(意味可进行自动进样系统吸样测试)
		{
			*ASCur_Step = 1;
		}
	}

	return 0;
}

int CThreadAS::Step1(const char* wtData, const char* response, int* ASCur_Step)
{
	int		m_nwt = 0;
	int		m_nrd = 0;
	int		i;
	uchar	buffRd[SMAX_AS] = { 0 };

	m_nwt = m_newCom.ComWrt(0, wtData, 3,115200);	//发送请求样本信号
	if (m_nwt == false)
	{
		fprintf(stderr, "write AskSample to ThreadAS failed---------!\n");
		return -1;
	}

	timeFrKd9 = 0;
	while (1)		//循环1s等待
	{
		if (timeFrKd9 > 0)
			return TimeOut;

		for (i = 0; i < SMAX_AS; i++)		//buffRe[4]字符截止位
			buffRd[i] = 0;

		if (Allow_ASOnLine)
		{
			m_nrd = m_newCom.ComRd(0, buffRd, SMAX_AS,115200);
			if (m_nrd =false)
				continue;

			//判断是否应答
			if (0 == CompDataRead(buffRd, (const uchar*)response))	//应答信号
			{
				key_status = FALSE;		//有应答信号后，锁键盘
				*ASCur_Step = 2;

				break;
			}
			//判断是否OVER，如果OVER则跳出
			else if (0 == CompDataRead(buffRd, (const unsigned char*) "OVER"))
			{
				SendOver(ASCur_Step);

				break;
			}
			else
				return RedWrong;
		}
	}
	return 0;
}

int CThreadAS::Step2(const char* CodeR, int* ASCur_Step)
{
	int		m_nwt = 0;
	int		m_nrd = 0;
	int		i;
	int		ASMode = -1;
	uchar	buffRd[LMAX_AS] = { 0 };
	uchar	buffGet[30] = { 0 };

	for (i = 0; i < LMAX_AS; i++)      //数据长度:24 + 5
		buffRd[i] = 0;
	m_nrd = m_newCom.ComRd(0, buffRd, LMAX_AS,115200);
	if (m_nrd = false)
		return RedErr;

	ASMode = getASMode(buffRd, buffGet);

	if (0x08 == ASMode || 0x0F == ASMode || 0x7F == ASMode)			//自动或急诊或手工模式
	{
		//SendMessage(MainWindowhDlg, MSG_COMMAND, IDM_MAIN_TEST, 0L);//
		if (0x08 == ASMode)
		{
			CTestmainView::GetASBarcode((char*)buffGet);//自动进样模式获得条形码，急诊手工模式无需获得条形码
		}
		for (i = 0; i < 6; i++)
		{
			m_nwt = m_newCom.ComWrt(0, CodeR, 3,115200);		//发送应答信号，发送6次
			if (m_nwt == false)
			{
				fprintf(stderr, "write CodeR to ThreadAS failed---------!\n");
				return WrtErr;
			}
		}
		*ASCur_Step = 3;
	}//else未传输或传输出错，再次传输
	else
		return RedWrong;

	return 0;
}

int CThreadAS::Step4(const char* wtData, const char* response, int* ASCur_Step)
{
	int		m_nwt = 0;
	int		m_nrd = 0;
	int		i;
	uchar	buffRd[SMAX_AS] = { 0 };

	m_nwt = m_newCom.ComWrt(0, wtData, 3,115200);		//发送测试完成信号
	if (m_nwt == false)
	{
		fprintf(stderr, "write SampleOver to ThreadAS failed---------!\n");
		return WrtErr;
	}

	timeFrKd9 = 0;
	while (1)//循环1s等待
	{
		if (timeFrKd9 > 0)
			return TimeOut;

		for (i = 0; i < SMAX_AS; i++)		//buffRe[4]字符截止位
			buffRd[i] = 0;

		if (Allow_ASOnLine)
		{
			m_nrd = m_newCom.ComRd(0, buffRd, SMAX_AS,115200);
			if (m_nrd =false)
				continue;

			if (0 == CompDataRead(buffRd, (const uchar*)response))	//应答信号
			{
				*ASCur_Step = 0;
				return 0;
			}
			else
				return RedWrong;
		}
	}
}

inline void CThreadAS::SendOver(int *ASCur_Step)
{
	int 			i;
	int			m_nwt;

	for (i = 0; i < 6; i++)
	{
		m_nwt = m_newCom.ComWrt(0, "OVR", 3,115200);	//发送应答信号，发送6次
		if (m_nwt ==false)
			fprintf(stderr, "write OverR to ThreadAS failed---------!\n");
	}
	AS_OnLine = FALSE;
	ASCur_EN = FALSE;
	*ASCur_Step = 0;
}

//解析测试模式
int CThreadAS::getASMode(const uchar *buffRd, uchar* buffGet)
{
	uchar 	i;
	uchar 	checknum = 0;
	int		Mode = 0;

	const uchar* 	move = buffRd;

	while (move != buffRd + LMAX_AS - 29)
	{
		if (*move == 0x02)
		{
			if (*(move + 1) == 0x68)
			{
				if (*(move + 3) == 0x08)
				{
					//校验和检验
					checknum = 0;
					for (i = 0; i < 28; i++)
						checknum += *(move + i);

					if (*(move + 28) == checknum)//自动模式
					{
						fprintf(stderr, "AutoSample Automatical Model\n");
						Mode = 0x08;
						break;         //接收数据正确
					}
					else
					{
						fprintf(stderr, "ThreadAS->checknum error:%0X---------#\n", *(move + 28));
						Mode = -4;
					}
				}
				else if (*(move + 3) == 0x0F)//急诊模式
				{
					fprintf(stderr, "AutoSample Emergency model\n");
					Mode = 0x0F;
					break;
				}
				else if (*(move + 3) == 0x7F)//手工模式
				{
					fprintf(stderr, "AutoSample Manual model\n");
					Mode = 0x7F;
					break;
				}
				else
				{
					fprintf(stderr, "ThreadAS->0x0F or 0x08 error:%0X---------#\n", *(move + 3));
					Mode = -3;
				}
			}
			else
			{
				fprintf(stderr, "ThreadAS->0x68 error:%0X---------#\n", *(move + 1));
				Mode = -1;
			}
		}
		else
		{
			Mode = 0;
		}

		move++;
	}

	memset(buffGet, 0, 29);

	if (Mode == 0x08 || Mode == 0x0F || Mode == 0x7F)
		for (i = 0; i < 29; i++)
			*(buffGet + i) = *(move + i);

	return Mode;
}

/***********************************************************
*Function:	ThreadAS
*Description:	自动进样串口线程入口函数
*Called by:
*Params illustration:
*Other:
*History:
************************************************************/
void *CThreadAS::ThreadAS(void)
{
	int 			ASCur_Step;
	int			Flag;

	const char 	AllowStart[] = "AST";	//命令:允许自动进样系统建立连接Allow Start	
	const char 	OverR[] = "OVR";		//接收到自动进样系统的"OVER"回复一个应答，断开连接即AS_OnLine置0
	const char 	AskSample[] = "ASK";	//命令:请求样本	
	const char 	SampleOver[] = "SOK";	//命令:吸样完成，移走试管
	const char 	CodeR[] = "CDR";		//条形码应答信号

	Allow_ASOnLine = FALSE;
	AS_OnLine = FALSE;
	ASCur_EN = FALSE;
	ASCur_Step = -1;

	while (1)
	{
		//允许连接?
		if (!Allow_ASOnLine)
		{
			Sleep(100);//单位us，不能一直将Allow_ASOnLine与1比较，易出问题
			continue;
		}
		if (!AS_OnLine)
		{
			Flag = TryConnect(AllowStart, &ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Connecting Error info: Flag %d \n", Flag);
				Sleep(100);
			}
		}
		//本次吸样所处于的状态	
		if (AS_OnLine && 0 == ASCur_Step)
		{
			Flag = Step0(&ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Step0 Error info: Flag %d \n", Flag);
				Sleep(1);    //0.1s
			}
		}
		//请求样本
		if (AS_OnLine && 1 == ASCur_Step)
		{
			Flag = Step1(AskSample, "ASKR", &ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Step1 Error info: Flag %d \n", Flag);
				Sleep(1);    //0.1s
			}
		}
		//接收模式条码信息
		if (AS_OnLine && 2 == ASCur_Step)
		{
			static int TimesofStep2 = 0;

			Flag = Step2(CodeR, &ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Step2 Error info: Flag %d \n", Flag);
				TimesofStep2++;
				Sleep(1);     // 1ms
			}
			else
				TimesofStep2 = 0;

			if (TimesofStep2 == 9)
			{
				int i;
				for (i = 0; i < 6; i++)
					m_newCom.ComWrt(0, CodeR, 3,115200);
				SendOver(&ASCur_Step);
			}
		}
		//等待测试结束
		if (AS_OnLine && 3 == ASCur_Step)
		{
			if (WAITING_DATA == PC_status)//表明穿刺已结束进入等待数据状态
				ASCur_Step = 4;
		}
		//通知AS装置测试结束
		if (AS_OnLine && 4 == ASCur_Step)
		{
			Flag = Step4(SampleOver, "SOKR", &ASCur_Step);
			if (Flag < 0)
			{
				fprintf(stderr, "Step4 Error info: Flag %d \n", Flag);
				Sleep(1);    // 1ms
			}
		}
	}
}
