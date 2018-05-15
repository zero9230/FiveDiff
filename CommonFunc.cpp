#include "stdafx.h"
#include "CommonFunc.h"
//#include "Includes_app.h"

CCommonFunc::CCommonFunc()
{

}


CCommonFunc::~CCommonFunc()
{

}

////////////////////////判断今天是不是星期五//////////////////////
bool CCommonFunc::GetFriday()
{
	CTime m_time;
	CString m_strDate, m_strTime, m_strDateTime;
	m_time = CTime::GetCurrentTime();             //获取当前时间日期  
	//m_strDate = m_time.Format(_T("%x"));          //格式化日期  
	//m_strTime = m_time.Format(_T("%X"));          //格式化时间  
	m_strDateTime = m_time.Format(_T("%A"));   //格式化日期时间  
	if (m_strDateTime == "Friday")
	{
		return true;
	}
	return false;
}


void CCommonFunc::SendSysPara(void)
{
	int i = 0;
	uchar sdata[50] = { 0 };

	//向DSP发送步进电机运动参数
	for (i = XM_START_RINSE; i <= YM_STARTSAMPLE; i++)
	{
		sdata[2 * i] = systemcfg.mstp[i] & 0x00FF; 	//低8位
		sdata[2 * i + 1] = systemcfg.mstp[i] >> 8;   	//高8位
	}
	//温度参数
	sdata[34] = (int)(systemcfg.tmp.env * 100) / 1000;
	sdata[35] = ((int)(systemcfg.tmp.env * 100) / 100) % 10;
	sdata[36] = ((int)(systemcfg.tmp.env * 100) / 10) % 10;
	sdata[37] = (int)(systemcfg.tmp.env * 100) % 10;
	//试剂温度
	sdata[38] = (int)(systemcfg.tmp.incub * 100) / 1000;
	sdata[39] = ((int)(systemcfg.tmp.incub * 100) / 100) % 10;
	sdata[40] = ((int)(systemcfg.tmp.incub * 100) / 10) % 10;
	sdata[41] = (int)(systemcfg.tmp.incub * 100) % 10;

	sdata[42] = (systemcfg3.diluent == 1) ? 0 : 1;
	sdata[43] = (systemcfg.mode > 1) ? 0 : 1;

	//防止数据异常设定的随机值
	for (i = 44; i < 50; i++)
		sdata[i] = 0x01;

	CSpi m_spidev1;
	m_spidev1.send_frame(sdata, SPI_TYPE_SETTINGS);
}