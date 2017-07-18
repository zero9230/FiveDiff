/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Spi.h
Author:	xubinbin	Version:	1.0	Date: 2016-02-25
Description: 	Spi部分通信h文件，主要定义主要的协议帧
Others:       	// 其它内容的说明
*************************************************/

#ifndef __SPI_H__
#define __SPI_H__

#define SPI_TIMEOUT		5000   

//帧头帧尾定义
#define SPI_FM_SYNC    		0x02//同步帧头
#define SPI_FM_HEADER   	0x68//起始帧头
#define SPI_FM_END       	0x16//帧尾

//------------------------------------------------
//帧类型宏定义
#define SPI_TYPE_CMD				0x00//命令帧
#define SPI_TYPE_STATE				0x01//状态帧
#define SPI_TYPE_SETTINGS			0x02//设置参数

#define SPI_TYPE_HGBRES			0x03
#define SPI_TYPE_BASORES			0x04
#define SPI_TYPE_RBCRES				0x05
#define SPI_TYPE_PLTRES				0x06
#define SPI_TYPE_LMNERES			0x07

#define SPI_TYPE_TEMRES				0x08//DSP温度信息
#define SPI_TYPE_DIFFADJUSTRES		0x09//鞘流系统调试SPI通信数据类型
#define SPI_TYPE_HGBTESTRES			0x0A//工程师维护界面->HGB测试 ，结果传送类型
#define SPI_TYPE_DSPVERSIONRES		0x0B//DSP版本号
#define SPI_TYPE_ERRORRES			0x0C//流程状态错误


//------------------------------------------------
//SPI通信命令帧宏定义

//#define    						0x00//保留为初始值，表示没有SPI命令需要响应


//Remark
//  	0x04		~	0x0B

//  	0x10		~	0x16(电机检测),	
//	0x17		~	0x1D(阀检测V34-V40)

//  	0x20		~	0x2F(阀检测V1-V16)

//  	0x30		~	0x3F(阀检测V17-V32)

//  	0x40		~	0x46(灌注)	,	
//	0x48		~	0x49(清洗),
//	0x4A		~	0x4D(接收数据)

//  	0x50		~	0x59

//  	0x60		~	0x69

//  	0x70		~	0x77

//  	0x81

//  	0x92		~	0x9D

//  	0xA0		~	0xAE

//	0xE0		~	0xE5,	
//	0xEC		~	0xEE

//	0xF4			~	0xF9


//主菜单
#define SPI_CMD_SHUTDOWN			0x04
#define SPI_CMD_SELFTEST			0x05
#define SPI_CMD_STARTUP			0x06
#define SPI_CMD_DIFFADJUST       		0x07
#define SPI_CMD_REQDSPVERSION   	0x08
#define SPI_CMD_REQDSP_STATUS		0x09
#define SPI_CMD_REQERROR			0x0A//请求错误数据
#define SPI_CMD_DILUENT_SAMPLE	0x0B//打稀释液

//维护
//电机检测命令
#define SPI_CMD_TEST_YM		0x10			
#define SPI_CMD_TEST_XM		0x11	
#define SPI_CMD_TEST_SM		0x12
#define SPI_CMD_TEST_DRM		0x13
#define SPI_CMD_TEST_CTM		0x14
#define SPI_CMD_TEST_CYM		0x15	
#define SPI_CMD_TEST_DIM        	0x16
//阀检测命令
#define SPI_CMD_TEST_V1			0x20
#define SPI_CMD_TEST_V2			0x21
#define SPI_CMD_TEST_V3			0x22
#define SPI_CMD_TEST_V4			0x23
#define SPI_CMD_TEST_V5			0x24
#define SPI_CMD_TEST_V6			0x25
#define SPI_CMD_TEST_V7			0x26
#define SPI_CMD_TEST_V8			0x27
#define SPI_CMD_TEST_V9			0x28
#define SPI_CMD_TEST_V10		0x29
#define SPI_CMD_TEST_V11		0x2A
#define SPI_CMD_TEST_V12		0x2B
#define SPI_CMD_TEST_V13		0x2C
#define SPI_CMD_TEST_V14		0x2D
#define SPI_CMD_TEST_V15		0x2E
#define SPI_CMD_TEST_V16		0x2F
#define SPI_CMD_TEST_V17		0x30
#define SPI_CMD_TEST_V18		0x31
#define SPI_CMD_TEST_V19		0x32
#define SPI_CMD_TEST_V20		0x33
#define SPI_CMD_TEST_V21		0x34
#define SPI_CMD_TEST_V22		0x35
#define SPI_CMD_TEST_V23		0x36
#define SPI_CMD_TEST_V24		0x37
#define SPI_CMD_TEST_V25		0x38
#define SPI_CMD_TEST_V26		0x39
#define SPI_CMD_TEST_V27		0x3A
#define SPI_CMD_TEST_V28		0x3B
#define SPI_CMD_TEST_V29		0x3C
#define SPI_CMD_TEST_V30		0x3D
#define SPI_CMD_TEST_V31		0x3E
#define SPI_CMD_TEST_V32		0x3F
#define SPI_CMD_TEST_TUBE		0x47	//测试穿刺模块电磁阀功能  V33
#define SPI_CMD_TEST_V34		0x17
#define SPI_CMD_TEST_V35		0x18
#define SPI_CMD_TEST_V36		0x19
#define SPI_CMD_TEST_V37		0x1A
#define SPI_CMD_TEST_V38		0x1B
#define SPI_CMD_TEST_V39		0x1C
#define SPI_CMD_TEST_V40		0x1D

//灌注命令
#define SPI_CMD_PRIME_DILUENT 				0x40            
#define SPI_CMD_PRIME_WBCRINSE			0x41
#define SPI_CMD_PRIME_LMNEFIX				0x42
#define SPI_CMD_PRIME_WBCLYSE				0x43
#define SPI_CMD_PRIME_HGBLYSE				0x44
#define SPI_CMD_PRIMEALL					0x45
#define SPI_CMD_REVERSEDPRIME				0x46

//排空命令
#define SPI_CMD_DRAIN_WASTE					0x50
#define SPI_CMD_DRAIN_RINSE					0x51
#define SPI_CMD_DRAIN_HGB						0x52
#define SPI_CMD_DRAIN_RBC						0x53
#define SPI_CMD_DRAIN_BASO					0x54
#define SPI_CMD_DRAIN_LMNE					0x55
#define SPI_CMD_DRAIN_ALL       					0x56
#define SPI_CMD_DRAIN_DILUENT_RESERVOIR		0x57
#define SPI_CMD_DRAIN_CTM						0x58
#define SPI_CMD_DRAIN_PIPE						0x59
//清洗命令
#define SPI_CMD_CLEAN_COUNTCHAMBER		0x48
#define SPI_CMD_CLEAN_SHEATHFLOWPOOL   	0x49
#define SPI_CMD_CLEAN_RINSEBASO		0x60
#define SPI_CMD_CLEAN_DILUENTINTINE   	0x61
#define SPI_CMD_CLEAN_RINSEINTINE		0x62
#define SPI_CMD_CLEAN_DILUENTEXTINE	0x63
#define SPI_CMD_CLEAN_RINSEEXTINE		0x64
#define SPI_CMD_CLEAN_SHEATFLOWPIPE	0x65
#define SPI_CMD_CLEAN_GEM				0x66
#define SPI_CMD_BACKFLUSH_LMNE		0xE3

//自动维护
#define SPI_CMD_RINSEBATHS				0x67
#define SPI_CMD_MINIPRIME				0x68
#define SPI_CMD_BACKFLUSH				0x69

//工程师维护

//恒流源命令
#define SPI_CMD_BASOCURON					0x70
#define SPI_CMD_BASOCUROFF				0x71
#define SPI_CMD_RBCCURON					0x72
#define SPI_CMD_RBCCUROFF					0x73
#define SPI_CMD_LMNECURON					0x74
#define SPI_CMD_LMNECUROFF				0x75

#define SPI_CMD_CONCENTRATE_CLEAN1		0x76//浓缩清洗第一步
#define SPI_CMD_CONCENTRATE_CLEAN2		0x77//浓缩清洗第二步

//辅助调试
#define SPI_CMD_HGB_MAINTAIN		0x81

//日常维护和保养
//#define SPI_CMD_WEEKLYMAINTAIN	0x91
#define SPI_CMD_MONTHLYMAINTAIN	0x92

//工程师维护
//定位与定量
#define SPI_CMD_SAMPLERATION		0xA0//采样定量调试
#define SPI_CMD_HGBLYSERATION		0xA1//HGBLYSE定量调试
#define SPI_CMD_RINSERATION		0xA2//RINSE采样定量调试
#define SPI_CMD_FIXRATION			0xA3//FIX采样定量调试
#define SPI_CMD_DILUETNRATION		0xA4//Diluent采样定量调试
#define SPI_CMD_WBCLYSERATION		0xA5//WBCLYSE采样定量调试
#define SPI_CMD_XYRATION			0xA6//XY位置调试

#define SPI_CMD_TEST_PUNCTURE		0xAD//检测穿刺针

//X位置调试
#define SPI_CMD_XMSET_START_RINSE		0xA7
#define SPI_CMD_XMSET_START_HGB		0xA8
#define SPI_CMD_XMSET_START_LMNE		0xA9
#define SPI_CMD_XMSET_START_RBC    	0xAA
#define SPI_CMD_XMSET_START_WBCBASO 	0xAB
#define SPI_CMD_XMSET_CUP_RADIUS 		0xAC

//稀释电机参数
#define SPI_CMD_DIMSET					0xAE

//Y位置调试
#define SPI_CMD_YMSET_REF				0x93
#define SPI_CMD_YMSET_HIGH_RINSE		0x94
#define SPI_CMD_YMSET_LOW_RINSE		0x95
#define SPI_CMD_YMSET_MID_HGB			0x96
#define SPI_CMD_YMSET_LOW_HGB		0x97
#define SPI_CMD_YMSET_HIGH_HGB		0x98
#define SPI_CMD_YMSET_WBCLMNE		0x99
#define SPI_CMD_YMSET_RBCPLT			0x9A
#define SPI_CMD_YMSET_WBCBASO		0x9B
#define SPI_CMD_YMSET_STARTSAMPLE   	0x9C

#define SPI_CMD_XYMSET_RESET			0x9D//退出电机参数设置界面时,XY电机回到复位位置

//参数，模式设定
#define SPI_CMD_CBC5DIFF_MODE   	0xE0
#define SPI_CMD_CBC_MODE			0xE1

////////////////////////////////////////////////////////////其他////////////////////////////////////////////////////////////////////////

//堵孔反冲
#define 	SPI_CMD_BACKSWING_WBCPH		0xE2
#define	SPI_CMD_BACKSWING_LMNEPH	0xE3
#define	SPI_CMD_BACKSWING_RBCPH		0xE4

#define SPI_CMD_AUTOCLEAN			0xE5
#define SPI_CMD_REQTEM				0xEC	//环境温度及孵育温度，如35.25,36.23则接受到35253623
#define SPI_CMD_REQDIFFADJUST       0xED   	//请求鞘流系统调试数据

#define SPI_CMD_REQHGB				0xEE
#define SPI_CMD_REQBASO				0xF4
#define SPI_CMD_REQRBC				0xF5
#define SPI_CMD_REQPLT				0xF6
#define SPI_CMD_REQLMNE				0xF7

#define SPI_CMD_STANDBY_IN			0xF8    //hw:20140520   
#define SPI_CMD_STANDBY_OVER		0xF9

#define SPI_CMD_REQSWITCH			0xFA//请求开关状态

#define SPI_CMD_REQBASO_2			0x4A
#define SPI_CMD_REQRBC_2			0x4B
#define SPI_CMD_REQPLT_2			0x4C
#define SPI_CMD_REQHGBTEST		0x4D	//用于HGB维护时候的命令	

//#define							0xFF		//保留为发送结束时的伪码
//------------------------------------------------
//状态帧宏定义
#define SPI_STATE_DATAISOK				0x09	//检测数据准备好
#define SPI_STATE_TESTISOVER	      	0x0A	//主测试过程结束

#define SPI_STATE_INFO_START        	0x12 	//过程开始状态信息
#define SPI_STATE_INFO_END         		0x39 	//过程结束状态信息，和TestIsOver不一样，TEST_OVER后面接复杂的后续处理，而SPI_STATE_INFO_END不需要等同于SPI_STATE_READY

#define SPI_STATE_INFO_NOTREADY				0x45//数据未准备好，鞘流池测试时用到
#define SPI_STATE_PUNCTURE_OVER				0x46//穿刺完成
#define SPI_STATE_ERROR_YM						0x47//YM电机复位故障
#define SPI_STATE_ERROR_DRM					0x48//排液超时

#define SPI_STATE_SWITCHON					0x49//

#define SPI_STATE_SYSPARAM_UNRECEIVED  		0x36//开机启动，未传送步进电机运动参数成功
#define SPI_STATE_SYSPARAM_RECEIVED  		0x37//开机启动，已传送步进电机运动参数成功

class CSpi
{
public:
	CSpi();
	~CSpi();
	BYTE byDevIndex;
	DevInfo* SPI_dev;
	DevInfo* TRIG_dev;
	unsigned char check_frame(unsigned char *pdata, unsigned int len);
	void SetSpiConfig();
	int open_spi(void);
	int close_spi(int spi_fd);
	void make_frame(unsigned char sdata[], unsigned char frametype, unsigned char *psendframe);
	int send_frame(unsigned char *sdata, unsigned char frametype);
	int receive_frame(unsigned char *rdata, unsigned char frametype);
	

private:

};


#endif
