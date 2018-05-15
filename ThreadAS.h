#pragma once
#include "Includes_app.h"

//返回错误标识
//-1 : 写错误
//-2 : 读取数据失败
//-3 : 超时
//-4 : 读数据不符合
typedef enum{ WrtErr = -1, RedErr = -2, TimeOut = -3, RedWrong = -4 } ErrorFlag;

class CThreadAS
{
public:
	CThreadAS();
	~CThreadAS();
public:
	int CompDataRead(uchar * src, const uchar *obj);
	int TryConnect(const char *AllowStart, int* ASCur_Step);
	int Step0(int* ASCur_Step);
	int Step1(const char* wtData, const char* response, int* ASCur_Step);
	int Step2(const char* CodeR, int* ASCur_Step);
	int Step4(const char* wtData, const char* response, int* ASCur_Step);
	void SendOver(int *ASCur_Step);
public :
	int getASMode(const uchar *buffRd, uchar* buffGet);
	void* ThreadAS(void);



public :

	CRS232			m_newCom;
};

