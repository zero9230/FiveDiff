#pragma once

#define MAX_PORTS 10

struct PortInfo
{
	bool	busy;	//是否打开,1:打开  //int->bool
	CString name;	//设备名
	int		handle;		//句柄号
};



class CRS232
{
public:
	CRS232();
	~CRS232();
	BOOL OpenCom(int portNo, int baudrat);
	BOOL CloseCom(int portNo);
	BOOL ComRd(int portNo, unsigned char buf[], int maxCnt, int baudrat);//ms;
	BOOL ComWrt(int portNo, CString buf, int maxCnt, int baudrat);
	BOOL ComWrt1(int portNo, unsigned char buf[], int maxCnt, int baudrat);
	BOOL InitComConfig(int baudrat);

private:
	HANDLE hComm;//串口通信
	struct PortInfo ports[MAX_PORTS];
};
