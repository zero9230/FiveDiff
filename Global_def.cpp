#include "stdafx.h"
#include "Includes_app.h"
syscfg3 systemcfg3;
syscfg2 systemcfg2;
syscfg systemcfg;
lgfi logfile;
sMaintain m_sMaintain;
int cfg3_fd, cfg2_fd, cfg_fd, lgfi_fd;
int gpio_fd;
//extern sqlite3 *db;

unsigned int framelen[13];			//各类型帧长度
//unsigned char key_status;  			//0:按键无效；1:按键有效
bool key_status;  			//0:按键无效；1:按键有效
unsigned int timeFrKd;					//键盘按下置0，然后开始计时间，单位为秒，自动休眠用
unsigned int DSPFreeTime;				//记录DSP空闲时间，单位为秒
unsigned int timeFrKd9;				//用于自动进样
unsigned int NumFromBoot;			//开机以后做的测试总数执行完自动清洗后置0
unsigned char sdata_cmd[1];
unsigned char rdata_state[1];

status DSP_status;
// 0(free):DSP空闲，不在通信中(ARM可发送任何命令给DSP) 
// 1(busy):DSP忙碌，通信中(不能发送任何命令给DSP)。等于1的时候，可进行查询操作库等操作即不涉及DSP的操作(暂时没这么用，暂时都不可操作)	
// 2(clean):DSP正在主测试清洗(能发送测试命令给DSP，其它命令都不能发给DSP)
unsigned char PC_status;


time_t systime;		//宿主机时间
struct tm rtm;  		//目标机时间
struct tm *caltime;	//时间

unsigned char hgbgraph[4];		//DSP传上来的HGB值并且乘以10
//第二组数据
unsigned char basograph_2[256];
unsigned char rbcgraph_2[512];
unsigned char pltgraph_2[256];

//错误信息
// 1-X电机，2-Y电机，3-SM电机，4-DIM电机，5-DRM电机，6-CTM电机，7-CYM电机，8-WBC堵孔，9-RBC堵孔，10-废液时间过长
unsigned char errorShowMess;		//当前要显示的错误类型,0:没错误
unsigned char errorShowNum;		//当前要显示的错误类型在数组errorMessage中的下标
unsigned char errorNumber;		//所有错误的个数
unsigned char errorMessage[ERRNUM];	//需要显示的错误类型编码，数组长度为错误类型数
unsigned char errorReceive[ERRNUM + 1];	//从DSP接收到的数据，错误类型数+1，errorReceive[0]用不到
//状态信息
unsigned char statusShowMess;		//仪器状态在RECT STATUS区域显示 0-就绪 1-运行 2-清洗3-等待升温4-自动清洗中

unsigned int		operator_right;

bool IsMainTop;

unsigned char 		PLTRightBorderStylus;
unsigned char		PLTRightBorderQuery;

unsigned int  Controltype;//L-J质控：0；X质控：1； X-R质控：2；
unsigned int  Controlfile;//0,1,2,3,4,5,6,7,8对应文件1,2,3,4,5,6,7,8,9

int				CurView;//当前界面
HANDLE			SendMutex;//互斥锁，控制发送消息
HANDLE			SendEvent;//互斥量，控制发送消息
HANDLE			 TestmainEvent = NULL;//轮询条形码线程控制事件
HANDLE			hEvent = NULL;//轮询条形码线程控制事件

bool			Reconnection=FALSE;//判断是否在进行重连中

uchar		temp = 0;
uchar* 		pIsSuper=&temp;

int ListFocusItem;
//char	PC_status;