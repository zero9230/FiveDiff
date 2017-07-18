/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Global_def.h
Author:	xubinbin	Version:	1.0	Date: 2016-02-25
Description: 	全局变量定义头文件
Others:       	// 其它内容的说明
*************************************************/
#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_


#define SYSCFG3_PATH  	"/Config/syscfg_3.dat"       //75ha:配置文件命名为syscfg_*.dat仅为与三分类配置文件相区别
#define SYSCFG2_PATH  	"/Config/syscfg_2.dat"
#define SYSCFG_PATH  	"/Config/syscfg_1.dat" 
#define MAINTAIN_PATH	"/Config/maintain.ini"
//#define LOGFILE_PATH  "/Config/logfile.dat"
#define DATABASE_PATH 	"/Config/appdata.db"
#define DEBUG_PATH  	"/debug/rdata.txt"


//Message Define



//LMNE thresholds
#define 	NoL		0
#define 	NoN		1
#define 	LL		2
#define 	LN		3
#define	NoE		4
#define	LMN		5
#define	AL		6
#define 	LMU		7
#define	LMD		8
#define	MN		9
#define	RM		10
#define	RN		11
#define	NL		12
#define	RMN		13
#define	NE		14
#define	FLN		15
#define	FNE		16
#define	FMN		17
//BASO thresholds
#define	BA1		18
#define	BA2		19
#define	BA3		20
//RBC thresholds
#define 	RB1		21
#define	RB2		22
//PLT thresholds
#define	PLT1	23
#define	PLT2	24

#define	QCBA1	0
#define	QCBA2	1
#define	QCBA3	2

//28个参数
#define WBCS	0
#define	LYMP	1
#define	NEUP	2
#define	MONOP	3
#define	EOSP	4
#define	BASOP	5
#define	ALYP	6
#define	LICP	7
#define	LYMS	8
#define NEUS	9
#define	MONOS	10
#define	EOSS	11
#define	BASOS	12
#define ALYS	13
#define	LICS	14
#define	RBCS	15
#define	HGBS	16
#define	HCTS	17
#define	MCVS	18
#define	MCHS	19
#define	MCHCS	20
#define	RDWCVS	21
#define	RDWSDS	22
#define	PLTS	23
#define	MPVS	24
#define	PDWS	25
#define	PCTS	26
#define PLCRS    27

//定标因子，医院用
#define CAL_WBCF 		0
#define CAL_RBCF 		1
#define CAL_HGBF 		2
#define CAL_MCVF 		3
#define CAL_PLTF 		4

//修正因子，内部工程师用
#define MOD_WBCF 		0
#define MOD_RBCF 		1
#define MOD_HGBF 		2
#define MOD_MCVF 		3
#define MOD_RDWCVF 	4
#define MOD_RDWSDF 	5
#define MOD_PLTF 		6
#define MOD_MPVF 		7
#define MOD_PDWF 		8
#define MOD_PCTF 		9
#define MOD_PLCRF 		10

//测试模式选择
#define   WHOLEDIFF		0x00
#define	WHOLECBC  		0x01
#define   DILUENTDIFF	0x02
#define	DILUENTCBC  	0x03

//语言选项
#define CHINESE  	0x01
#define ENGLISH  	0x02
#define FRENCH  		0x04
#define RUSSIAN  	0x08
#define SPANISH  	0x10

//范围选项
#define RANGE_UNIVERSAL		0x00//通用
#define RANGE_MAN			0x01//成男
#define RANGE_WOMAN			0x02//成女
#define RANGE_CHILD			0x03//儿童
#define RANGE_BABY			0x04//婴儿
#define RANGE_OLD			0x05//老人
#define RANGE_USERDEFINE1	0x06//自定义1	
#define RANGE_USERDEFINE2	0x07//自动以2

//日期时间格式
#define YYYYMMDD 0
#define MMDDYYYY 1
#define DDMMYYYY 2

//参数
//电机参数 					//sdata[0]-sdata[31]
#define XM_START_RINSE  	0x00
#define XM_START_HGB		0x01
#define XM_START_LMNE    	0x02
#define XM_START_RBC		0x03
#define XM_START_WBCBASO 	0x04
#define XM_CUP_RADIUS       	0x05

#define DIM_DILUENT			0x06

#define YM_REF                     	0x07
#define YM_HIGH_RINSE        	0x08
#define YM_LOW_RINSE          	0x09
#define YM_MID_HGB              	0x0A
#define YM_LOW_HGB           	0x0B
#define YM_HIGH_HGB           	0x0C
#define YM_WBCLMNE            	0x0D
#define YM_RBCPLT              	0x0E
#define YM_WBCBASO            	0x0F
#define YM_STARTSAMPLE     	0x10

#define PUSH_SHELF     	0x00
#define  J_MOTOR  		0x01
#define  HAND_X			0x02
#define  HAND_Y  		0x03
#define  HAND_MIXER  	0x04
#define  FLAT			0x05
#define  POP_SHELF  		0x06
#define  HAND_TAKETOROUNG  	0x07
#define  HAND_ENDTOTEST  		0x08
#define  HAND_Y_UPTOROUNG  		0x09

//试剂
#define DILUENT		0
#define Rinse		1
#define HGBLyse		2	
#define EOSLyse		3
#define BASLyse		4


//环境及孵育温度参数	//sdata[32]-sdata[39]
extern syscfg3 systemcfg3;
extern syscfg2 systemcfg2;
extern syscfg systemcfg;
extern lgfi logfile;
extern sMaintain m_sMaintain;
extern int cfg3_fd, cfg2_fd, cfg_fd, lgfi_fd;
extern int gpio_fd;
//extern sqlite3 *db;

extern uchar* 	pIsSuper;
//extern char	PC_status;

 extern unsigned int framelen[13];			//各类型帧长度
//unsigned char key_status;  			//0:按键无效；1:按键有效
 extern bool key_status;  			//0:按键无效；1:按键有效
 extern unsigned int timeFrKd;					//键盘按下置0，然后开始计时间，单位为秒，自动休眠用
 extern unsigned int DSPFreeTime;				//记录DSP空闲时间，单位为秒
 extern unsigned int timeFrKd9;				//用于自动进样
 extern  unsigned char sdata_cmd[1];
 extern unsigned char rdata_state[1];
 extern unsigned int NumFromBoot;			//开机以后做的测试总数执行完自动清洗后置0

 extern status DSP_status;
// 0(free):DSP空闲，不在通信中(ARM可发送任何命令给DSP) 
// 1(busy):DSP忙碌，通信中(不能发送任何命令给DSP)。等于1的时候，可进行查询操作库等操作即不涉及DSP的操作(暂时没这么用，暂时都不可操作)	
// 2(clean):DSP正在主测试清洗(能发送测试命令给DSP，其它命令都不能发给DSP)
extern unsigned char PC_status;

//ARM的状态
#define WAITING_PUNCTURE_OVER		0x01
#define WAITING_DATA    			0x02//可用于很多地方，只要可以用于接收下位机部分的都可以用
#define WAITING_TEST_OVER    		0x08
#define TEST_OVER                   0x09

extern time_t systime;			//宿主机时间
extern struct tm rtm;  			//目标机时间
extern struct tm *caltime;		//时间

//定时器宏定义
#define SYSPARAM_TIMER 	    99	//向DSP传输参数的定时器
#define POLL_TIMER		    115
#define WAIT_TIMER		 	101	//开机等待输入密码定时器
#define SYSTIME				103	//系统时钟定时器
#define SLEEP_TIMER1		105	//休眠定时器1，用于时间较长的流程
#define SLEEP_TIMER2		105
#define POLLTIME			107	//轮询定时器
#define POLLTIME2			108
#define ERROR_TIMER 		109	//用于错误报警
#define UPDATE_STATUS		111 //刷新主测试界面状态栏
#define CHECKERR_TIMER		113
#define POLLTIME3			114

#define PROGRESS_TIMER		116//进度条定时器
#define CLOCK_TIMER			117//始终定时器

#define CHECK_BARCODEINPUT  118//条码枪定时器

#define SPI_POLL_TIME500			500	//轮询间隔时间0.5s，主要用于实时的接收数据，如鞘流池检测模块、RBCPLT、BASO液路检测
#define SPI_POLL_TIME1000			1000	//轮询间隔时间1s，主要用于除主测试流程以外的流程,如电机测试，HGB检测等，时间相对较短
#define SPI_POLL_TIME3000			3000	//轮询间隔时间3s，用于主测试流程，以及其他一些时间稍长的控制过程

extern unsigned char hgbgraph[4];		//DSP传上来的HGB值并且乘以10
//第二组数据
extern unsigned char basograph_2[256];
extern unsigned char rbcgraph_2[512];
extern unsigned char pltgraph_2[256];

//错误信息
// 1-X电机，2-Y电机，3-SM电机，4-DIM电机，5-DRM电机，6-CTM电机，7-CYM电机，8-WBC堵孔，9-RBC堵孔，10-废液时间过长
extern unsigned char errorShowMess;		//当前要显示的错误类型,0:没错误
extern unsigned char errorShowNum;		//当前要显示的错误类型在数组errorMessage中的下标
extern unsigned char errorNumber;		//所有错误的个数
extern unsigned char errorMessage[ERRNUM];	//需要显示的错误类型编码，数组长度为错误类型数
extern unsigned char errorReceive[ERRNUM + 1];	//从DSP接收到的数据，错误类型数+1，errorReceive[0]用不到
//状态信息
extern unsigned char statusShowMess;		//仪器状态在RECT STATUS区域显示 0-就绪 1-运行 2-清洗3-等待升温4-自动清洗中

extern bool IsMainTop;

extern unsigned char 	PLTRightBorderStylus;
extern unsigned char	PLTRightBorderQuery;

extern unsigned int		operator_right;

extern unsigned int  Controltype;//L-J质控：0；X质控：1； X-R质控：2；
extern unsigned int  Controlfile;//0,1,2,3,4,5,6,7,8对应文件1,2,3,4,5,6,7,8,9

extern int ListFocusItem;

extern int CurView;

extern	HANDLE		SendMutex;//互斥量，控制发送消息；
extern	HANDLE		SendEvent;//互斥量，控制发送消息；
extern  HANDLE		TestmainEvent;//轮询条形码线程控制事件
extern  HANDLE		hEvent;
extern bool			Reconnection;

#define	TableColor		PIXEL_darkgray
#define	TableColor_QC 	PIXEL_lightwhite


#define		MBOX_YESNO		0
#define		MBOX_OKCANCEL		1

#define          SetBkColor_LightGray()		//SetWindowBkColor(hDlg,PIXEL_lightgray)
#define          SetBkColor_LightGray_2()	//SetWindowBkColor(hDlg,PIXEL_lightgray)                //Include GroupBox
#define          SetBkColor_LightGray_3()			//SetWindowBkColor(hDlg,PIXEL_lightgray)      //Only Buttons



#endif


//extern sqlite3 *db;