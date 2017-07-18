
#pragma once
//#include <stdafx.h>
#include "Includes_app.h"
class CCommonFunc
{
public:
	CCommonFunc();
	~CCommonFunc();
	bool GetFriday();													//判断当天是否周五
	//void SaveMaintenanceParas(sMaintain * temp_sMaintain);     				//保存保养相关参数

	//测试相关
	//void RepeatTest(HWND hDlg, uchar* en_repeat, sample_info* CurSample);     	//重新测试

	//数据处理相关
	inline double Fabs(double Item);		//取非负数
	//void IsBlocking_RBC(HWND, sample_info*);

	//数据通信相关
	void SendSysPara(void);		//向DSP发送电机参数等数据
private:

};
