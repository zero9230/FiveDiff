#ifndef DEV_INFO_H
#define DEV_INFO_H

//#include "stdafx.h"

#define ST_MANUAL
#define ST_TIMER
#define ST_TRIGER


#define SPI_RW_SIZE     64

typedef enum
{
 DEV_I2C = 0,
 DEV_SPI ,
 DEV_HDQ,
 DEV_CAN,
 DEV_GPIO,
 DEV_ADC,
 DEV_PWM,
 DEV_TRIG = 13,
 DEV_ALL = 14,
 NUM_OF_DEV,
}enu_dev;

typedef struct
{
 BYTE byMask;
 BYTE byReserved;
 BYTE byIoSelect[4];
 WORD wValue[4];
}ADCInfo;


typedef struct
{
 BYTE byNum;
 BYTE byIndex;
 WORD byDuty[4];
}PWMInfo;

class DevInfo
{
 public:
	DevInfo(enu_dev id);
	~DevInfo();
 private:
	enu_dev devID;
	DWORD dwReadCnt;
	BYTE* pReadBuf;
	DWORD dwWriteCnt;
	BYTE* pWriteBuf;
 public:
	bool bRunning;
	void* pMyData;
	BYTE byDevAddr;
	BYTE byRateIndex;
	DWORD dwTimeout;
	DWORD reserved1;
	enu_dev GetDevId();
	DWORD GetReadCnt();
	DWORD GetWriteCnt();
	BYTE* GetReadBuf();
	BYTE* GetWriteBuf();
	void* GetData();
	void  SetData(void* pData);
	void PutReadBuf(BYTE* pStr,DWORD dwLen);
	void WriteBufUpdate(BYTE* pStr,DWORD dwLen);
	void ReadBufClear();
	void WriteBufClear();
};

#endif

