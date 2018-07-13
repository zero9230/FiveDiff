/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Includes_app.h
Author:	xubinbin	Version:	1.0	Date: 2016-02-25
Description: 	自定义结构体
Struct List:
Others:      	// 其它内容的说明
设定因子的一些量的类型的要根据实际情况考
SPI通信的传送给ARM的数据都未经过处理，可以参照老版本的进行处
通信数据量，图形变量数组的大小的定义，数组类型的定义都根据具体情况
*************************************************/
#ifndef _STRUCTDEFINE_H_
#define _STRUCTDEFINE_H_

#define ERRNUM 		20		//错误的类型数。与DSP保持一致
#define MATRIX_POINT_MAX		3500
#define MATRIX_DATA_MAX		(MATRIX_POINT_MAX<<1)

typedef  unsigned char uchar;
typedef enum{ Free = 0, Busy = 1, Clean = 2 } status;

//----------------------------------------
//实时时钟结构体
struct rtc_time
{
	int sec;	//秒
	int min;	//分
	int hour;//时
	int day;	//日
	int mon;	//月
	int year;//年
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

//----------------------------------------
//质控白细胞参数数据结构
struct qc_wbc_data
{
	 char  wbc[6];		//白细胞计数 正常范围：4.0-10.0 G/L
	 char  lymp[6];	//淋巴细胞百分比正常范围：1.0-3.3 G/L
	 char  neup[6];	//中性粒细胞百分比 正常范围：1.8-6.4 G/L
	 char  monop[6];	//中值细百分比 正常范围：0.2-0.9 G/L 
	 char  eosp[6];	//嗜酸性粒百分比正常范围：20.0-40.0 %
	 char  basp[6];	//嗜碱性粒百分比 正常范围：3.0-8.0 %
	 char  licp[6];		//巨大不成熟百分比 正常范围：3.0-8.0 %
	 char  alyp[6];		//异形淋巴百分比 正常范围：3.0-8.0 %
	 char  lym[6];		//淋巴细胞计数 正常范围：1.0-3.3 G/L  
	 char  neu[6];		//中性粒细胞计数 正常范围：1.8-6.4 G/L
	 char  mono[6];	//中值细胞计数 正常范围：0.2-0.9 G/L
	 char  eos[6];		//嗜酸性粒细胞计数 正常范围：20.0-40.0 %
	 char  bas[6];		//嗜碱性粒细胞计数 正常范围：3.0-8.0 %
	 char  lic[6];		//巨大不成熟细胞计数 正常范围：3.0-8.0 %
	 char  aly[6];		//异形淋巴细胞计数 正常范围：3.0-8.0 % 
};

//质控红细胞参数数据结构
struct qc_rbc_data
{
	 char rbc[6]; 		//红细胞计数 正常范围：3.50-5.50 T/L
	 char hgb[6]; 		//血红蛋白浓度 正常范围：110.0-160.0g/L
	 char hct[6]; 		//红细胞压积 正常范围： 37.0-49.0 %
	 char mcv[6]; 		//平均红细胞体积  正常范围：80.0-100.0 fl
	 char mch[6]; 		//平均红细胞血红蛋白含量  正常范围：27.0-33.0 Pg
	 char mchc[6];	//平均红细胞血红蛋白浓度  正常范围：320-360  g/l
	 char rdw[6]; 		//红细胞体积分布宽度 正常范围：1.0-14.0 %
};

//质控血小板参数数据结构
struct qc_plt_data
{
	 char plt[6]; 		//血小板计数 正常范围：120-300 G/L
	 char mpv[6]; 		//平均血小板体积 正常范围：9.4-12.5 fl
	 char pct[6]; 		//血小板比积  正常范围：0.108-0.282 %
	 char pdw[6]; 		//血小板体积分布宽度 正常范围：15.0-18.0 fl  	
};

//质控测试结果
struct qc_result_data
{
	unsigned int row;		//记录号

	struct qc_wbc_data wbcdata;
	struct qc_rbc_data rbcdata;
	struct qc_plt_data pltdata;

	unsigned char lmnegraph[MATRIX_DATA_MAX];
	unsigned char basograph[256];
	unsigned char rbcgraph[512];
	unsigned char pltgraph[256];

	 char lmneflg[9];	//正常存1，异常存2
	 char basoflg[1];
	 char rbcflg[2];
	 char pltflg[2];

	 char qctype;			//对应于质控编辑里边质控类型
	 char filenum;			//对应于质控编辑里边文件号
	 int time;				//时间
	 char date[11];
};
typedef struct qc_result_data qcresult_info;

//质控参数，质控品参数
struct qc_edit_data
{
	 char qctype;			//质控类型，1:L-J质控，2:X质控，3:X-R质控
	 char filenum;			//文件号
	 char Number[13];		//批号	
	 char Deadline[11];	//截止时间
	struct qc_wbc_data wbctarget;
	struct qc_rbc_data rbctarget;
	struct qc_plt_data plttarget;
	struct qc_wbc_data wbcsd;
	struct qc_rbc_data rbcsd;
	struct qc_plt_data pltsd;
};
typedef struct qc_edit_data qc_edit_data_info;

//----------------------------------------
//打印机配置参数
struct printer_config
{
	unsigned char mode;	//0x00:手动打印,0x01:自动打印
	unsigned char format;	//0x00:带图,0x01:不带图		//xx22 暂时没用上
	unsigned char size;	//0x00:A4,0x01:A5
};

//上传设置
struct com_config
{
	unsigned char baudrate;	//串口配置选项  0:9600  1:19200 2:57600  3:115200 
	unsigned char upload;    	//上传方式      0:automatic   1:manual
	//数据格式选项
};

//范围及阈值设置
struct range_config
{
	//范围设置
	unsigned char type;				//测试样本默认范围类型	
	float normal[8][56]; 			//类型正常范围，[8][56]分别为 通用，成男，成女，新生儿，儿童，自定义1,2,3
	//阈值	
	unsigned char thresholds[25];	//阈值
	unsigned char	thresholds_qc[3];
};

//温度控制
struct temperature_param	//xx22 搞成不带小数的，太精确没意义。暂时没用用到，温度控制。DSP的温度传上来
{
	float env;				//环境温度设定值(计数杯温度)
	float incub;			//孵育池温度设定值，各种温度控制值(里边被包着的管路的温度)
};

struct regent_fullamount  	//试剂每瓶的容量
{
	unsigned int diluent;	//单位0.1ml
	unsigned int rinse;			
	unsigned int hgblyse;
	unsigned int eoslyse;
	unsigned int baslyse;
};

struct regent_date
{	
	int startyear[5];
	int startmonth[5];
	int startday[5];
	int endyear[5];
	int endmonth[5];
	int endday[5];
};
//修正因子
struct modify_param
{
	//修正因子（具体包括WBC, PLT, RBC, BASO ,HGB, LYM, MON, NEU, EOS, LAY, LIC）
	float a[11];
	float b[11];
	float c[11];
};

//质控系统参数
struct qualitycontrol_config	//质控只有全血+5Diff模式，其它模式不需要
{
	//X-B质控参数
	unsigned char XB_on;		//XB质控，1:打开；0:关闭
	unsigned int XB_group_num;	//每组数目,范围20-200
	unsigned char mcvtarget[6];
	unsigned char mchtarget[6];
	unsigned char mchctarget[6];
	unsigned char mcvsd[6];
	unsigned char mchsd[6];
	unsigned char mchcsd[6];
};

//特权用户系统配置参数
struct system_config3
{
	unsigned char first_use;		//非零表示开机

	unsigned char structure;		//仪器结构，1:不穿刺,2:穿刺,3:自动进样
	unsigned char screen;			//屏幕，    1:非触摸屏,2:触摸屏
	unsigned char diluent;			//取样量:1->20UL;	2->50UL
};
typedef struct system_config3 syscfg3;

//超级用户系统配置参数
struct system_config2
{
	unsigned char first_use;		//非零表示开机

	char company[31];	//公司名称
	char model[16];		//仪器型号
	//unsigned char regentwarn_on;	//试剂软件报警，1:打开；0:关闭
	bool warn_diluent;
	bool warn_rinse;
	bool warn_hgb;
	bool warn_fix;
	bool warn_baso;
	bool warn_waste;
	unsigned char PcConMode;		// 1-串口，2-网口
	char ipaddr[16];
	int netport;
	int rsspeed;					//单位us上传设置，包与包之间传输的时间间隔，如果联机软件用网口的话就不需要这个变量了
};
typedef struct system_config2 syscfg2;

//普通用户系统配置参数
struct system_config
{
	unsigned char first_use;		//非零表示开机

	unsigned char hospital[41];		//医院名称设置,40个英文字符或20个汉字
	unsigned char cleanperiod;		//自动清洗时间间隔，超过多长时间未进行DSP操作则做自动清洗
	unsigned char washfrequency;	//自动清洗次数(即测试满多少次自动清洗)，关机以后重算
	unsigned char sleeptime;		//休眠时间，sleep_time30,40,50,60分钟
	unsigned char miniprimetime;	//微灌注，30,40,50,60分钟，长时间不做测试，若再测试提示做MiniPrime	//xx22 miniprime 不要单独搞个定时器，定时prime，只需要在AutoClean的时候顺带执行以下prime就可以(即将prime流程放入到AutoClean流程中去)
	unsigned char datetype;		//日期格式

	unsigned char mode;			//测试模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC
	unsigned char language;		//语言选择	
	unsigned char unitWBC;		//单位选项:0、1、2、3
	unsigned char unitRBC;
	unsigned char unitHGB;
	unsigned char unitMCVRDWSD;
	unsigned char unitMCH;
	unsigned char unitMCHC;
	unsigned char unitPLT;
	unsigned char unitMPV;

	struct printer_config printercfg;//打印设置
	struct com_config com;		//上传设置
	struct range_config range;		//范围设置及阈值设置
	struct temperature_param tmp;	//温度参数
	struct regent_fullamount regentfull;	//试剂容量
	struct regent_date regentdate;
	struct modify_param modify[4];//修正因子，全血+CBC5DIFF，全血+CBC，稀释血+CBC5DIFF，稀释血+CBC
	struct qualitycontrol_config qualitycontrol;		//质控参数，需要记录的，主要是X-B质控

	unsigned char lmnepeak1;		//散点图电阻抗峰值1
	unsigned char lmnepeak2;

	unsigned char PltRightThresholdMode;	//PLT右阈值模式，0:手动,1:自动
	unsigned char LMNEMarkMode;				//LMNE各界标移动模式,0:手动,1:自动

	unsigned int mstp[17];					//电机参数
	float calibration[4][5];				//定标因子，全血+CBC5DIFF，全血+CBC，稀释血+CBC5DIFF，稀释血+CBC

	unsigned int Autosamplerpara[10];//自动进样电机参数
};
typedef struct system_config syscfg;

struct regent_amount  	//the amount of regent 试剂剩余量
{
	unsigned int diluent;	//单位0.1ml
	unsigned int rinse;		
	unsigned int hgblyse;
	unsigned int eoslyse;
	unsigned int baslyse;
};

//日志文件参数
struct log_file
{
	unsigned char first_use;		//非零表示开机
	unsigned char totaltimesoftest;

	struct regent_amount regent;
	struct regent_date	regentdate;
	//故障统计
	unsigned int alertnum[ERRNUM + 1];	//alertnum[0]用不到
};
typedef struct log_file lgfi;

struct Maintenance{
	int			first_use;
	int			TimesOfFriday;   		//周五的次数
	bool		m_bIs2ndFriday;
	int			TestedDay;
};
typedef struct Maintenance sMaintain;

//----------------------------------------
//病人信息数据结构，成员主要包括系统信息与人工输入信息
struct Patient_data_struct
{
	int			 row;				//数据库记录数
	int			 number;			//编号=日期加当天编号
	 char		 name[21];		//姓名长度，可以输10个汉字，或20个英文字符
     char		 sex;			//性别，0:男,1:女,2:空
	 char		 rangetype;		//数据范围类别
	 char		 age[4];			//年龄，用int型不能节约空间，直接用char型，显示打印时可以免于判断
	 char		 code[22];		//可输入21位长度的条码
	 char		 technician[31];	//科室长度，可以输15个汉字，或30个英文字符
	 char		 doctor[21];		 //医生姓名，可输入10个汉字，或20个英文字符
};
typedef struct Patient_data_struct patient_info;

//医生信息数据结构，成员主要包括系统信息与人工输入信息
struct Doctor_data_struct
{
	long			 id;				//id
	//int			 row;			//行号
	
	char		 name[21];		//姓名长度，可以输10个汉字，或20个英文字符
	char		 memo[100];		//备注，100个字节

};
typedef struct Doctor_data_struct doctor_info;


//----------------------------------------
//白细胞参数数据结构
struct wbc_data
{
	char		wbc[6];		//白细胞计数 正常范围：4.0-10.0 G/L
	char		lymp[6];	//淋巴细胞百分比正常范围：
	char		neup[6];	//中性粒细胞百分比 正常范围：
	char		monop[6];	//中值细百分比 正常范围：
	char		eosp[6];	//嗜酸性粒百分比正常范围：20.0-40.0 %
	char		basp[6];	//嗜碱性粒百分比 正常范围：3.0-8.0 %
	char		alyp[6];		//异形淋巴百分比 正常范围：3.0-8.0 %
	char		licp[6];		//巨大不成熟百分比 正常范围：3.0-8.0 %
	char		lym[6];		//淋巴细胞计数 正常范围：1.0-3.3 G/L  
	char		neu[6];		//中性粒细胞计数 正常范围：1.8-6.4 G/L
	char		mono[6];	//中值细胞计数 正常范围：0.2-0.9 G/L
	char		eos[6];		//嗜酸性粒细胞计数 正常范围：
	char		bas[6];		//嗜碱性粒细胞计数 正常范围：
	char		aly[6];		//异形淋巴细胞计数 正常范围：
	char		lic[6];		//巨大不成熟细胞计数 正常范围：
};

//红细胞参数数据结构
struct rbc_data
{
	char		rbc[6];		//红细胞计数 正常范围：3.50-5.50 T/L
	char		hgb[6];		//血红蛋白浓度 正常范围：110.0-160.0g/L
	char		hct[6];		//红细胞压积 正常范围： 37.0-49.0 %
	char		mcv[6];		//平均红细胞体积  正常范围：80.0-100.0 fl
	char		mch[6];		//平均红细胞血红蛋白含量  正常范围：27.0-33.0 Pg
	char		mchc[6];	//平均红细胞血红蛋白浓度  正常范围：320-360  g/l
	char		rdwcv[6];	//红细胞体积分布宽度 正常范围：1.0-14.0 %
	char		rdwsd[6];	//红细胞体积分布宽度标准差    参考:  35～45fl 
};

//血小板参数数据结构
struct plt_data
{
	char		plt[6];		//血小板计数 正常范围：120-300 G/L
	char		mpv[6];		//平均血小板体积 正常范围：9.4-12.5 fl	
	char		pdw[6];		//血小板体积分布宽度 正常范围：15.0-18.0 fl
	char		pct[6];		//血小板比积  正常范围：0.108-0.282 %	
	char		plcr[12];		//12fL以上大型血小板比率 % 	
};

//样本信息结构体
struct blood_data
{
	int				row;			//数据库记录数
	struct wbc_data wbcdata;		//白细胞参数信息
	struct rbc_data rbcdata;		//红细胞参数信息
	struct plt_data pltdata;		//血小板参数参数	

	unsigned char			lmnegraph[MATRIX_DATA_MAX];	//散点图直方图2011.1.27 wsm,先是体积，然后吸光率
	unsigned char			basograph[256];	//白细胞直方图
	unsigned char			rbcgraph[512];	//红细胞直方图
	unsigned char			pltgraph[256];	//血小板直方图

	char			lmneflg[9];		//NO, LL, LL1, NL, MN, RM, LN, RN, NE界标
	char			basoflg[1];		//L1界标
	char			rbcflg[2];		//MIC, MAC界标
	char			pltflg[4];		//预留界标,警示标志

	 int			number;			//编号=日期加当天编号
	int				time;				//时间
	char			mode;			//测试模式
	char			flag_wrp[4];         //判断wbc,rbc & plt两次测试是否相差较大的标志 add:20150104
	float			coeoflmne;	//存放float型
};
typedef struct blood_data sample_info;

//任务结构体
struct task_data
{
	int				number;
	int				row;			//数据库记录数
	char			sex;			//性别，0:空,1:男,2:女
	char			age[4];
	char			mode;			//测量模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC
	char			name[21];		//姓名长度，可以输10个汉字，或20个英文字符
	char			doctor[21];		//医生姓名，可输入10个汉字，或20个英文字符
	char			status[10];		//任务状态
	char			time[10];		//测量时间
	char			barcode[15];	//条形码
	char			department[20];	//科室
	int				taskmode;	    //任务形式：0：测试任务 1：清洗任务
};
typedef struct task_data task_info;

//Yes_No对话框
typedef struct{
	const char* 	caption;    //对话框标题
	const char* 	message;	//显示信息
	uchar 		type;			//MBOX_YESNO | MBOX_OKCANCEL
}MesBox;
typedef MesBox* pMesBox;

//查询数据库
typedef struct{
	char*	sqlque;			//SQL语句
	char**	dbResult;		//存储数据内容
	int		nRow;			//数据行数
	int		nColumn;		//数据列数
	char*	zErrMsg;		//错误信息
}SqliteQue;
typedef SqliteQue*	pSqliteQue;

//LMNE散点图各区间界标
typedef struct{
	uchar	X_NOL;
	uchar	X_NON;
	uchar	X_LL;
	uchar	X_LN;
	uchar	X_NOE;
	uchar	X_AL;
	uchar	X_LMN;
	uchar	X_LMU;
	uchar	X_MN;
	uchar	X_LMD;
	uchar	X_RM;
	uchar	X_RN;
	uchar	Y_NL;
	uchar	Y_RMN;
	uchar	Y_NE;
} B_LMNE;

/*
typedef struct{
uchar 	ErrRecv[ERRNUM+1];
uchar 	ErrMess[ERRNUM];
uchar	ErrNum;
uchar	ErrMessShow;
} ErrorInfo;
typedef ErrorInfo* pErrorInfo;
*/

#endif
