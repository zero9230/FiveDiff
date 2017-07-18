#include "stdafx.h"
#include "RS232.h"



CRS232::CRS232()
{

	for (int i = 0; i < 10; i++)
	{
		ports[i].busy = false;
	}
}


CRS232::~CRS232()
{

}

BOOL CRS232::OpenCom(int portNo, int baudrat)
{
	
	switch (portNo){
	case 0:ports[portNo].name = "COM1"; break;
	case 1:ports[portNo].name = "COM2"; break;
	case 2:ports[portNo].name = "COM3"; break;
	case 3:ports[portNo].name = "COM4"; break;
	case 4:ports[portNo].name = "COM5"; break;
	case 5:ports[portNo].name = "COM6"; break;
	case 6:ports[portNo].name = "COM7"; break;
	case 7:ports[portNo].name = "COM8"; break;
	case 8:ports[portNo].name = "COM9"; break;
	case 9:ports[portNo].name = "COM10"; break;

	default:break;
	}
	hComm = CreateFile(ports[portNo].name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
	if (hComm == INVALID_HANDLE_VALUE)       //如果串口未打开
	{
		//m_chush1.EnableWindow(true);
		TRACE(_T("打开通信端口错误!! "));
		return FALSE;
	}
	ports[portNo].busy = true;
	return InitComConfig(baudrat);
}

BOOL CRS232::CloseCom(int portNo)
{
	//if (CloseHandle(hComm)&& (ports[portNo].busy = false))
	//{
	//	return true;
	//}
	if (CloseHandle(hComm))
		return true;
	return false;
}

BOOL  CRS232::ComRd(int portNo, unsigned char buf[], int maxCnt,int baudrat)
{
	DWORD count;
	if (!OpenCom(portNo,baudrat))
	{
		TRACE(L"ComRd打开com失败\n");
		return false;
	}
	if (!ReadFile(hComm, buf, maxCnt, &count, NULL)){
		AfxMessageBox(_T("串口关闭! "));
	}
	if (!CloseCom(portNo))
	{
		TRACE(L"ComRd关闭com失败\n");
		TRACE("Open file filed with error %d \n", GetLastError());
		return false;
	}
	return true;
}

BOOL CRS232::ComWrt(int portNo, CString buf, int maxCnt, int baudrat)
{
	unsigned long lrc;

	if (!OpenCom(portNo,baudrat))
	{
		TRACE(L"ComWrt打开com失败\n");
		return false;
	}
	if (hComm == 0) return false;					 //检查Handle值
	WriteFile(hComm, buf, maxCnt, &lrc, NULL);  //送出数据
	if (!CloseCom(portNo))
	{
		TRACE(L"ComWrt关闭com失败\n");
	}
	return true;
}

/******************可能不太对的程序*********************/
BOOL CRS232::ComWrt1(int portNo, unsigned char buf[], int maxCnt, int baudrat)
{
	unsigned long lrc;

	if (!OpenCom(portNo, baudrat))
	{
		TRACE(L"ComWrt打开com失败\n");
		return false;
	}
	if (hComm == 0) return false;					 //检查Handle值
	WriteFile(hComm, buf, maxCnt, &lrc, NULL);  //送出数据
	if (!CloseCom(portNo))
	{
		TRACE(L"ComWrt关闭com失败\n");
	}
	return true;
}

BOOL CRS232::InitComConfig(int baudrat)
{
	DCB dcb;

	SetupComm(hComm, 1024, 1024); //输入缓冲区和输出缓冲区的大小都是1024 
	//将dcb地址传入，以取得通信参数
	GetCommState(hComm, &dcb);      //得知目前串行端口的状态

	COMMTIMEOUTS TimeOuts; //设定读超时

	TimeOuts.ReadIntervalTimeout = 1000;  //两字符之间最大的延时，当读取串口数据时，一旦两个字符传输的时间差超过该时间，读取函数将返回现有的数据。设置为0表示该参数不起作用。

	TimeOuts.ReadTotalTimeoutMultiplier = 500;//读取每字符间的超时

	TimeOuts.ReadTotalTimeoutConstant = 5000; //设定写超时

	TimeOuts.WriteTotalTimeoutMultiplier = 500;//一次读取串口数据的固定超时

	TimeOuts.WriteTotalTimeoutConstant = 2000; //写入每字符间的超时

	SetCommTimeouts(hComm, &TimeOuts); //设置超时

	switch (baudrat)
	{
	case 4800:
		dcb.BaudRate = CBR_4800;	//波特率：CBR_4800,CBR_9600,CBR_19200,CBR_38400，CBR_57600，CBR_115200
		break;
	case 9600:
		dcb.BaudRate = CBR_9600;
		break;
	case 19200:
		dcb.BaudRate = CBR_19200;
		break;
	case 38400:
		dcb.BaudRate = CBR_38400;
		break;
	case 57600:
		dcb.BaudRate = CBR_57600;
		break;
	case 115200:
		dcb.BaudRate = CBR_115200;
		break;
	default:
		AfxMessageBox(L"串口波特率错误,采用默认波特率");
		break;
	}
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY; //奇偶校验：EVENPARITY,ODDPARITY,NOPARITY
	dcb.StopBits = ONESTOPBIT;     //1个停止位

	if (!SetCommState(hComm, &dcb))
	{
		AfxMessageBox(_T("通信端口设置错误!! "));
		CloseHandle(hComm);
		return FALSE;
	}
	//AfxMessageBox(_T("通信端口设置成功!! "));
	PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);   //清空输入输出缓冲区
	return TRUE;
}