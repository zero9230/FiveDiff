#include "stdafx.h"
#include "BCGPChartExample.h"
#include "Includes_app.h"




DataProcess::DataProcess()
{
}


DataProcess::~DataProcess()
{
}


/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	DataProcess.c
Author:	liguoqing	Version:	1.0	Date: 2010-07-07
Description: 	数据处理
Others:     	待改进: ResultsAnalysis只分析了原始数据
考虑查询的时候没有散点图
画图函数为一期调用，可以和平，其静态全局变量用于其共享
2011.1.1数据库中存放的都是原始数据(影响效率，但方便日后改动)
Important:
必须将存储到数据库的0x00做特殊处理，否则一旦遇到0x00存到数据库
并认为是字符串截止符，处理方式，所有的数据存入的时候统一加1
从数据库取出记录来的时候，统一减去1
Function List:
History:
create	wsm 	2010.11.4
*************************************************/

//分析计算参数宏定义
#define VOLAMP_WBCBASO 	0.0015 	//WBCBASO体积和放大相关倍数
#define VOL_RBCPLT			0.00027	//采样体积相关系数
#define AMP_RBC				0.97		//RBC放大倍数相关
#define AMP_PLT				0.125	//PLT放大倍数相关

//画图相关宏定义
#define LMNE_LEFT		340
#define LMNE_BOTTOM 	365
#define LMNE_WIDTH		200//540-340  [0,255]->[340,540]
#define LMNE_HEIGHT		200

#define BASO_LEFT		570
#define BASO_BOTTOM	305
#define BASO_WIDTH		204//774-570	[0,255]->[570,774]
#define BASO_HEIGHT		105

#define RBC_LEFT			340
#define RBC_BOTTOM		525
#define RBC_WIDTH		204//544-340
#define RBC_HEIGHT		105

#define PLT_LEFT			570
#define PLT_BOTTOM		525
#define PLT_WIDTH		204    //774-570
#define PLT_HEIGHT		105    //525-420

#define COECALNUM		10

//HWND MainTestDlg;

//int  PLTGraphEnd = 133;
extern int PLTGraphEnd=133;

float		wbc_lmne = 0.0;

//用于开机测试流程与 TestWin.c 进行变量交互
extern bool StartupBlankTestsflag;
extern float StartupBlankTestswbc;
extern float StartupBlankTestsrbc;
extern float StartupBlankTestsplt;
extern bool IsBlankTest;

extern char 	studyPara[8][6];



static char 		wbc_hided_1[6], wbc_hided_2[6];	//用于记录两次WBC的结果	
static char 		rbc_hided_1[6], rbc_hided_2[6];
static char 		plt_hided_1[6], plt_hided_2[6];


//从接受的数据帧中解析的各种细胞的个数，可以直接用sample_info中的结构体代替
//画散点图用，此变量定义比较特殊，使用时要注意
//访问函数列表:
//从接受的数据帧中解析的散射的细胞数据
static const char *static_param[28] =
{
	"WBC",
	"LYM%",
	"NEU%",
	"MONO%",
	"EOS%",
	"BASO%",
	"ALY%",
	"LIC%",
	"LYM#",
	"NEU#",
	"MONO#",
	"EOS#",
	"BASO#",
	"ALY#",
	"LIC#",
	"RBC",
	"HGB",
	"HCT",
	"MCV",
	"MCH",
	"MCHC",
	"RDW-CV",
	"RDW-SD",
	"PLT",
	"MPV",
	"PDW",
	"PCT",
	"P-LCR"
};
//中文
static const char *static_sampinfo_cn[6] =
{
	"编号:",
	"姓名:",
	"性别:",
	"科室:",
	"年龄:",
	"条码:"
};
//英文
static const char *static_sampinfo_en[6] =
{
	"No.:",
	"Name:",
	"Sex:",
	"Dept.:",
	"Age:",
	"Code:"
};
static const char *static_unit_WBC[4] =
{
	"10^9/L",
	"10^3/uL",
	"10^2/uL",
	"/nL"
};
static const char *static_unit_RBC[4] =
{
	"10^12/L",
	"10^6/uL",
	"10^4/uL",
	"/pL"
};
static const char *static_unit_HGB[3] =
{
	"g/L",
	"g/dL",
	"mmol/L"
};
static const char *static_unit_MCVRDWSD[2] =
{
	"fL",
	"um^3"
};
static const char *static_unit_MCH[2] =
{
	"pg",
	"fmol"
};
static const char *static_unit_MCHC[3] =
{
	"g/L",
	"g/dL",
	"mmol/L"
};
static const char *static_unit_PLT[4] =
{
	"10^9/L",
	"10^3/uL",
	"10^4/uL",
	"/nL"
};
static const char *static_unit_MPV[2] =
{
	"fL",
	"um^3"
};
double DataProcess::WbcForCompare = 0.0;
/***********************************************************
*Function:
*Description:对WBC  RBC  PLT 俩组数据进行比较
*Called by:
*Params illustration:
*Data Access:
*History:
************************************************************/
void DataProcess::BasoLmneRbcPlt_2Analyse(sample_info *psampledata)
{
	unsigned short int i = 0;
	unsigned char start = 0, end = 0;
	signed int count_1, count_2;
	float countResult = 0.0;

	//count_wbc_flag = 0;
	//count_rbc_flag = 0;
	//count_plt_flag = 0;
	TRACE("\nTwoGroupResultsAnalysis()====================\n");
	//BASO
	count_1 = 0;
	count_2 = 0;
	start = systemcfg.range.thresholds[BA1];
	end = systemcfg.range.thresholds[BA3];
	for (i = start; i <= end; i++)
	{
		count_1 += (*psampledata).basograph[i];//白细胞直方图数据[256]
		count_2 += basograph_2[i];//第二组数据
	}
	TRACE("WbcBaso->wbc_count_1=%d----------#\n", count_1);
	TRACE("WbcBaso->wbc_count_2=%d----------#\n", count_2);

	if (count_1 >= 200)				//对应wbc >= 0.3，即不是空白测试
	{
		if (count_1 <= 2666)		//对应wbc < 4.0
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)			//FDparam 0.50,0.20,0.15参数确定
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.50)
			{
				(*psampledata).flag_wrp[0] = 2;
				//count_wbc_flag = 1;
			}
		}
		else if (count_1 <= 6666)	//对应wbc <= 10.0
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.20)

			{
				//count_wbc_flag = 1;
				(*psampledata).flag_wrp[0] = 2;
			}
		}
		else
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.15)
			{
				//count_wbc_flag = 1;
				(*psampledata).flag_wrp[0] = 2;
			}
		}
	}

	if (count_1 <= 66666)		//确保测试结果<100.00，然后使用sprintf转换格式存到数据库中没有问题
	{
		countResult = count_1*VOLAMP_WBCBASO;
		sprintf(wbc_hided_1, "%.2f", countResult);
	}

	if (count_2 <= 66666)		//确保测试结果<100.00，然后使用sprintf转换格式存到数据库中没有问题
	{
		countResult = count_2*VOLAMP_WBCBASO;
		sprintf(wbc_hided_2, "%.2f", countResult);
	}
	//RBC
	count_1 = 0;
	count_2 = 0;
	start = systemcfg.range.thresholds[RB1];
	end = systemcfg.range.thresholds[RB2];
	for (i = start; i <= end; i++)
	{
		count_1 += (((psampledata->rbcgraph[(i << 1) + 1]) << 8) + psampledata->rbcgraph[i << 1]);
		count_2 += (((rbcgraph_2[(i << 1) + 1]) << 8) + rbcgraph_2[i << 1]);
	}
	TRACE("Rbc->rbc_count_1=%d\n", count_1);
	TRACE("Rbc->rbc_count_2=%d\n", count_2);

	if (count_1 >= 186)					//对应rbc >= 0.05，即认为不是空白测试	
	{
		if (count_1 <= 14814)			//对应rbc < 4.0
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)				//FDparam 0.50,0.20,0.15参数确定
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.50)
				//count_rbc_flag = 1;
				(*psampledata).flag_wrp[1] = 2;
		}
		else if (count_1 <= 20370)		//对应wbc <= 5.5
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.20)
				//count_rbc_flag = 1;
				(*psampledata).flag_wrp[1] = 2;
		}
		else
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.15)
				//count_rbc_flag = 1;
				(*psampledata).flag_wrp[1] = 2;
		}
	}

	if (count_1 <= 370370)
	{
		countResult = count_1*VOL_RBCPLT;
		sprintf(rbc_hided_1, "%.2f", countResult);
	}

	if (count_2 <= 370370)
	{
		countResult = count_2*VOL_RBCPLT;
		sprintf(rbc_hided_2, "%.2f", countResult);
	}
	//PLT
	count_1 = 0;
	count_2 = 0;
	start = systemcfg.range.thresholds[PLT1];
	end = systemcfg.range.thresholds[PLT2];
	for (i = start; i <= end; i++)
	{
		count_1 += (*psampledata).pltgraph[i];
		count_2 += pltgraph_2[i];
	}
	TRACE("Plt->plt_count_1=%d\n", count_1);
	TRACE("Plt->plt_count_2=%d\n", count_2);

	if (count_1 >= 38)				//对应PLT >= 10 即不是空白测试
	{
		if (count_1 <= 370)			//对应PLT < 100
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)				//FDparam 0.50,0.20,0.15参数确定
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.50)
				//count_plt_flag = 1;
				(*psampledata).flag_wrp[2] = 2;

		}
		else if (count_1 <= 1111)	//对应PLT <= 300
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2)) / count_1 >= 0.20)
				//count_plt_flag = 1;
				(*psampledata).flag_wrp[2] = 2;
		}
		else
		{
			//if(1.0*fabs(count_1 - count_2)/count_1 > 1.00)
			if (1.0*fabs((double)(count_1 - count_2))/ count_1 >= 0.15)
				//count_plt_flag = 1;
				(*psampledata).flag_wrp[2] = 2;
		}
	}

	if (count_1 <= 37037)
	{
		countResult = count_1*1000.0*VOL_RBCPLT;
		sprintf(plt_hided_1, "%.0f", countResult);
	}

	if (count_2 <= 37037)
	{
		countResult = count_2*1000.0*VOL_RBCPLT;
		sprintf(plt_hided_2, "%.0f", countResult);
	}
}

/***********************************************************
*Function:
*Description:	对接收的数据帧的数据(rdata所指空间)进行
分析(解析判断，并存入sampledata.basograph所指向的空间)
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:	create	wsm		2010.12.31
************************************************************/
void DataProcess::WbcBasoAnalysis(sample_info *psampledata, uchar * pIsSuper)
{
	unsigned short int i, j;
	unsigned short int pointnum = 0;
	float dist_temp = 0.0;
	unsigned char tempbuff[256] = { 0 };
	unsigned char start = 0, mid = 0, end = 0;
	unsigned char maxval = 0;
	unsigned char threshold = 0;
	unsigned short int count_baso = 0;
	unsigned short int count_wbc = 0;
	unsigned short int temp0_BA1 = 0;	//[0,BA1)之间的计数
	float a = 0, b = 1.0, c = 0;
	float cal = 1.0;
	float wbc = 0;
	float baso = 0;
	float basop = 0;
	TRACE("\nBasoAnalysis()====================\n");

	for (i = 0; i < 256; i++)	//BASO数据，共256通道
		tempbuff[i] = ((*psampledata).basograph[i] + basograph_2[i]) / 2;   // hw:20140521

	//取有效数据段(幅值滤波)
	start = systemcfg.range.thresholds[BA1];
	mid = systemcfg.range.thresholds[BA2];
	end = systemcfg.range.thresholds[BA3];

	//求BASO总数
	count_baso = 0;
	for (i = mid; i <= end; i++)
		count_baso += tempbuff[i];
	TRACE("count_baso=%d---------#\n", count_baso);

	//求WBC总数
	count_wbc = count_baso;
	for (i = start; i < mid; i++)
		count_wbc += tempbuff[i];
	TRACE("count_wbc=%d---------#\n", count_wbc);

	//求[0,BA1)之间的总数
	temp0_BA1 = 0;
	for (i = 0; i < start; i++)
		temp0_BA1 += tempbuff[i];
	TRACE("temp0_BA1=%d---------#\n", temp0_BA1);

	if (count_wbc > 0)//保证不为0
	{
		//L1
		if ((float)temp0_BA1 / (temp0_BA1 + count_wbc) > 0.03)	//FDparam 参考ABX
			(*psampledata).basoflg[0] = 2;
	}

	if (count_wbc <= 66666 && count_wbc > 0)	//确保测试结果<100.00，然后使用sprintf转换格式存到数据库中没有问题
	{
		//baso
		basop = (100.0*count_baso) / count_wbc;
		//baso#
		baso = count_baso*VOLAMP_WBCBASO;
		//wbc
		a = systemcfg.modify[systemcfg.mode].a[MOD_WBCF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_WBCF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_WBCF];
		wbc = count_wbc*VOLAMP_WBCBASO;
		WbcForCompare = wbc;
		wbc = systemcfg.calibration[systemcfg.mode][CAL_WBCF] * fabs(a*wbc*a*wbc + b*wbc + c);
	}

	maxval = tempbuff[start];
	for (i = start + 1; i <= end; i++)
		if (tempbuff[i] > maxval)
			maxval = tempbuff[i];
	TRACE("BASO->maxval=%d---------#\n", maxval);

	//threshold = (int)(maxval*(BASO_HEIGHT)/(BASO_HEIGHT+55.0));
	threshold = (int)((float)maxval*(BASO_HEIGHT) / (BASO_HEIGHT + 58.33));	//58.33有什么依据没  xx22
	if (threshold != 0)
		cal = (float)BASO_HEIGHT / threshold;
	else
		cal = 1.0;

	//图形调整
	for (i = start; i <= end; i++)
	{
		if (tempbuff[i] > threshold)
			tempbuff[i] = BASO_HEIGHT;
		else
			tempbuff[i] *= cal;
	}

	//WBC值小于0.3图形不显示
	if (wbc < 0.3)
	{
		for (i = 0; i < 256; i++)
			tempbuff[i] = 0;
	}
	else
	{
		//hw_temp:
		//	pointnum = 4;
		//	for(i = 0;i < 63;i++)
		//	{
		//		dist_temp = tempbuff[1 + pointnum*(i+1)] -tempbuff[1 + pointnum*i];
		//		for(j = 2; j <= pointnum; j++)
		//			tempbuff[j + pointnum*i] = dist_temp*(j-1)/pointnum + tempbuff[1 + pointnum*i] ; 
		//	}
		//	tempbuff[254] = tempbuff[253]*2/3;
		//	tempbuff[255] = tempbuff[253]*1/3;
		//------------------------------------
		//加权滤波
		for (i = start + 1; i <= end - 1; i++)
			tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
		for (i = start + 3; i <= end - 3; i++)
			tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];
	}

	//加1处理，消除0x00截止符,否则以TEXT格式存入数据库会有问题
	for (i = 0; i < start; i++)
		(*psampledata).basograph[i] = 1;
	for (i = start; i <= end; i++)
		(*psampledata).basograph[i] = tempbuff[i] + 1;
	for (i = end + 1; i < 255; i++)
		(*psampledata).basograph[i] = 1;
	psampledata->basograph[255] = 0;

	//------------------------------------------------
	//如果进行开机测试则对原始数据进行保存
	if (StartupBlankTestsflag)
	{
		StartupBlankTestswbc = wbc;
	}

	//----------------------------------------
	//判断并格式转换
	if (*pIsSuper == 0 && (!IsBlankTest))     //非密码进入非空白
	{
		if (wbc < 0.5)
		{
			if (wbc < 0.3)
				wbc = 0;
			sprintf((*psampledata).wbcdata.wbc, "%.2f", wbc);

			//其它相关参数都是初始化的值即"*"号
			(*psampledata).basoflg[0] = 1;
		}
		else if (basop < 8.0)    //BASO不超过8%      hw_temp:20141231
		{
			sprintf((*psampledata).wbcdata.wbc, "%.2f", wbc);
			sprintf((*psampledata).wbcdata.basp, "%.1f", basop);
			sprintf((*psampledata).wbcdata.bas, "%.2f", baso);
		}
		else
		{
			printf("basop:%.2f\n", basop);
		}
	}
	else
	{
		if (wbc < 0.5)
		{
			if (wbc < 0.3)
				wbc = 0;
			sprintf((*psampledata).wbcdata.wbc, "%.2f", wbc);
			//其它相关参数都是初始化的值即"*"号
			(*psampledata).basoflg[0] = 1;
		}
		else
		{
			sprintf((*psampledata).wbcdata.wbc, "%.2f", wbc);
			sprintf((*psampledata).wbcdata.basp, "%.1f", basop);
			sprintf((*psampledata).wbcdata.bas, "%.2f", baso);
		}
	}
}

/***********************************************************
*Function:
*Description:	对接受到散点图的电阻抗放大
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:
1.信号放大部分
2.若不是工程师进入	，则电阻抗值进行自动调整或者工程师可以设置要不要自动调整
************************************************************/
void DataProcess::LmneAmpRes(sample_info *psampledata)	//xx22 暂时没用到
{
	unsigned int i;
	unsigned char res = 0;		//电阻抗信号

	unsigned char mark1 = 0;
	unsigned char mark2 = 0;
	unsigned short int resb[256] = { 0 };
	unsigned short int numtemp = 0;

	unsigned short int max1num = 0;
	unsigned short int max2num = 0;
	unsigned char max1res = 0;
	unsigned char max2res = 0;

	float amp1 = 0.0, amp3 = 0.0;
	unsigned char max1res_amped = 0;	//放大后的峰值电阻抗
	unsigned char max2res_amped = 0;

	mark1 = systemcfg.lmnepeak1;
	mark2 = systemcfg.lmnepeak2;
	for (i = 0; i < 256; i++)
		resb[i] = 0;
	for (i = 0; i < MATRIX_POINT_MAX; i++)
	{
		res = (*psampledata).lmnegraph[(i << 1)];
		resb[res]++;
	}

	//[mark1-10,mark1+10]	//10 xx22
	max1num = resb[mark1 - 10 - 2] + resb[mark1 - 10 - 1] + resb[mark1 - 10] + resb[mark1 - 10 + 1] + resb[mark1 - 10 + 2];	//先不除5，避免精度损失
	max1res = mark1 - 10;
	for (i = mark1 - 9; i <= mark1 + 10; i++)
	{
		numtemp = resb[i - 2] + resb[i - 1] + resb[i] + resb[i + 1] + resb[i + 2];
		if (numtemp > max1num)
		{
			max1num = numtemp;
			max1res = i;
		}
	}

	//[mark2-10,mark2+10]	//10 xx22
	max2num = resb[mark2 - 10 - 2] + resb[mark2 - 10 - 1] + resb[mark2 - 10] + resb[mark2 - 10 + 1] + resb[mark2 - 10 + 2];//先不除5，避免精度损失
	max2res = mark2 - 10;
	for (i = mark2 - 9; i <= mark2 + 10; i++)
	{
		numtemp = resb[i - 2] + resb[i - 1] + resb[i] + resb[i + 1] + resb[i + 2];
		if (numtemp > max2num)
		{
			max2num = numtemp;
			max2res = i;
		}
	}

	if (mark1 / max1res < 0.7)
		amp1 = 0.7;
	else if (mark1 / max1res > 1.3)
		amp1 = 1.3;
	else
		amp1 = mark1 / max1res;
	max1res_amped = amp1*max1res;

	if (mark2 / max2res < 0.7)
		amp3 = 0.7;
	else if (mark1 / max1res > 1.3)
		amp3 = 1.3;
	else
		amp3 = mark2 / max1res;
	max2res_amped = amp3*max2res;

	//保证max1res < max2res
	for (i = 0; i < MATRIX_POINT_MAX; i++)
	{
		res = (*psampledata).lmnegraph[(i << 1)];
		if (res <= max1res)
			(*psampledata).lmnegraph[(i << 1)] = res*amp1;
		else if (res >= max2res)
			(*psampledata).lmnegraph[(i << 1)] = max2res_amped + (res - max2res)*(255 - max2res_amped) / (255 - max2res);
		else
			(*psampledata).lmnegraph[(i << 1)] = max1res_amped + (res - max1res)*(max2res_amped - max1res_amped) / (max2res - max1res);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////	
//Description:	计算散点图界标移动系数						  					//
//Called by: LmneAnalysis																	//
//Params illustration:																		//
//Data Access:																			//
//Other:																					//
//*History:																				//
//	(1)Created:20150127																	//
//////////////////////////////////////////////////////////////////////////////////////////
void DataProcess::LmneCoeCalculate(sample_info *psampledata)	//xx22 暂时没用到
{
	unsigned int i;
	unsigned char res = 0;		//电阻抗信号

	unsigned char mark1 = 0;
	unsigned short int resb[256] = { 0 };
	unsigned short int numtemp = 0;

	unsigned short int max1num = 0;
	unsigned char max1res = 0;

	float coe = 1.0;
	int	board = 3 * systemcfg.lmnepeak1 / 10;
	int	calboard = 2 * systemcfg.lmnepeak1 / 10;

	printf("board:%d  calboard:%d\n", board, calboard);

	mark1 = systemcfg.lmnepeak1;

	for (i = 0; i < 256; i++)
		resb[i] = 0;
	for (i = 0; i < MATRIX_POINT_MAX; i++)
	{
		res = (*psampledata).lmnegraph[(i << 1)];
		resb[res]++;
	}

	//[mark1-10,mark1+10]	//10 xx22
	max1num = resb[mark1 - board - 2] + resb[mark1 - board - 1] + resb[mark1 - board] + resb[mark1 - board + 1] + resb[mark1 - board + 2];	//先不除5，避免精度损失
	max1res = mark1 - board;
	for (i = mark1 - board + 1; i <= mark1 + board; i++)
	{
		numtemp = resb[i - 2] + resb[i - 1] + resb[i] + resb[i + 1] + resb[i + 2];
		if (numtemp > max1num)
		{
			max1num = numtemp;
			max1res = i;
		}
	}

	printf("mark1:%d  res:%d\n", mark1, max1res);

	if ((max1res < (mark1 - calboard)) || (max1res >(mark1 + calboard)))
		coe = (float)max1res / mark1;     //返回系数

	printf("coe:%.2f\n", coe);

	if (coe < (1.0 - 0.3))
		coe = 1.0 - 0.3;
	else if (coe > 1.0 + 0.3)
		coe = 1.0 + 0.3;

	psampledata->coeoflmne = coe;
}

//////////////////////////////////////////////////////////////////////////////////////////	
//Description:	动态初始化LMNE散点图各区域界标值						  				//
//Called by: LmneAnalysis																//
//Params illustration:																	//
//Data Access:																			//
//Other:																				//
//*History:																				//
//	(1)Created:20150121																	//
//////////////////////////////////////////////////////////////////////////////////////////
void DataProcess::Init_B_LMNE(float	coefficient, B_LMNE* p_blmne)
{
	float		coe_rtoabs;

	//Resistance
	p_blmne->X_NOL = (uchar)systemcfg.range.thresholds[NoL] * coefficient;
	p_blmne->X_NON = (uchar)systemcfg.range.thresholds[NoN] * coefficient;
	p_blmne->X_LL = (uchar)systemcfg.range.thresholds[LL] * coefficient;
	p_blmne->X_LN = (uchar)systemcfg.range.thresholds[LN] * coefficient;
	p_blmne->X_AL = (uchar)systemcfg.range.thresholds[AL] * coefficient;
	p_blmne->X_LMN = (uchar)systemcfg.range.thresholds[LMN] * coefficient;
	p_blmne->X_LMU = (uchar)systemcfg.range.thresholds[LMU] * coefficient;
	p_blmne->X_MN = (uchar)systemcfg.range.thresholds[MN] * coefficient;
	p_blmne->X_LMD = (uchar)systemcfg.range.thresholds[LMD] * coefficient;

	p_blmne->X_NOE = (uchar)systemcfg.range.thresholds[NoE] * 1.0;
	p_blmne->X_RM = (uchar)systemcfg.range.thresholds[RM] * 1.0;
	p_blmne->X_RN = (uchar)systemcfg.range.thresholds[RN] * 1.0;

	coe_rtoabs = coefficient * 1.0;
	//Absorbance
	p_blmne->Y_NL = (uchar)systemcfg.range.thresholds[NL] * coe_rtoabs;
	p_blmne->Y_RMN = (uchar)systemcfg.range.thresholds[RMN] * coe_rtoabs;
	p_blmne->Y_NE = (uchar)systemcfg.range.thresholds[NE] * coe_rtoabs;
}

/***********************************************************
*Function:
*Description:	对接受数据的matrix_lmen[MATRIX_POINT_MAX]处理
*Called by:
*Params illustration:
*Data Access:
*Other:
1、测试时，将接受的LMNE数据 解析，获得所需参数并画出散点图
2、查询数据库时，将数据库中的LMNE数据解析，画出散点图
*History:	create	lgq		2010.7.20
mod		wsm		2010.11.5
************************************************************/
int DataProcess::LmneAnalysis(sample_info *psampledata, uchar* pIsSuper)
{
	unsigned int i;
	unsigned char res = 0, scatter = 0;		//电阻抗信号、光散射信号

	unsigned short int count_eos = 0;
	unsigned short int count_neu = 0;
	unsigned short int count_lneu = 0;
	unsigned short int count_rneu = 0;
	unsigned short int count_lym = 0;
	unsigned short int count_llym = 0;
	unsigned short int count_rlym = 0;
	unsigned short int count_mono = 0;
	unsigned short int count_rmono = 0;

	unsigned short int count_fln = 0;	//报警区的计数
	unsigned short int count_fne = 0;	//报警区的计数
	unsigned short int count_fmn = 0;	//报警区的计数

	unsigned short int count_aly = 0;
	unsigned short int count_lic = 0;
	unsigned short int count_noise = 0;
	unsigned short int count_blood = 0;

	float coefficient = 0.0;
	float wbc = 0.0;
	float lymp = 0.0;
	float neup = 0.0;
	float monop = 0.0;
	float eosp = 0.0;
	float alyp = 0.0;
	float licp = 0.0;

	float lym = 0.0;
	float neu = 0.0;
	float mono = 0.0;
	float eos = 0.0;
	float aly = 0.0;
	float lic = 0.0;
	//研究参数
	unsigned short int count_blasts = 0;
	float blastsp = 0.0;
	float leftp = 0.0;
	float nrbcp = 0.0;
	float blasts = 0.0;
	float left = 0.0;
	float nrbc = 0.0;

	int		retn = 0;
	B_LMNE	m_blmne;

	TRACE("\nLmneAnalysis()====================\n");
	for (i = 0; i < MATRIX_DATA_MAX; i++)
	{
		if ((*psampledata).lmnegraph[i] != 0)
		{
			retn++;
			if (255 == (*psampledata).lmnegraph[i])
				(*psampledata).lmnegraph[i] = 254;
		}
	}
	if (retn == 0)
		return -1;

	//判断，计算psampledata->coeoflmne值(普通用户模式非空白测试)
	if (*pIsSuper == 0 && (!IsBlankTest) && systemcfg.LMNEMarkMode == 1)
	{
		LmneCoeCalculate(psampledata);
	}

	//printf("coeoflmne:%.1f\n",psampledata->coeoflmne);

	Init_B_LMNE(psampledata->coeoflmne, &m_blmne);

	for (i = 0; i < MATRIX_POINT_MAX; i++)
	{
		res = (*psampledata).lmnegraph[(i << 1)];
		scatter = (*psampledata).lmnegraph[(i << 1) + 1];
		if (scatter >= m_blmne.Y_NE)
		{
			if (res < m_blmne.X_NOE)
				count_noise++;
			else
			{
				count_eos++;
				if (scatter < m_blmne.Y_NE + systemcfg.range.thresholds[FNE])
					count_fne++;
			}
			if (res >= 250)//研究参数	//xx21 250只是一个暂时的变量，其它也是
			{
				count_blasts++;
			}
		}
		else if (scatter >= m_blmne.Y_RMN)
		{
			if (res < m_blmne.X_NON)
				count_noise++;
			else if (res < m_blmne.X_LN)
				count_lneu++;
			else if (res < m_blmne.X_RN)
				count_neu++;
			else
				count_rneu++;
			if (res >= 250)//研究参数
			{
				count_blasts++;
			}
		}
		else if (scatter >= m_blmne.Y_NL)
		{
			if (res < m_blmne.X_NON)
				count_noise++;
			else if (res < m_blmne.X_LN)
			{
				count_lneu++;
				if (scatter < m_blmne.Y_NL + systemcfg.range.thresholds[FLN])
					count_fln++;
			}
			else if (res < m_blmne.X_LMN)
			{
				count_neu++;
				if (scatter < m_blmne.Y_NL + systemcfg.range.thresholds[FLN])
					count_fln++;
			}
			else if (res < m_blmne.X_MN)
			{
				if ((res - m_blmne.X_LMN)*(m_blmne.Y_RMN - m_blmne.Y_NL) <
					(m_blmne.X_MN - m_blmne.X_LMN)*(scatter - m_blmne.Y_NL))
				{
					count_neu++;
					if (scatter <= m_blmne.Y_NL + systemcfg.range.thresholds[FMN] || res >= m_blmne.X_MN - systemcfg.range.thresholds[FMN] ||
						((res - m_blmne.X_LMN)*(m_blmne.Y_RMN - m_blmne.Y_NL - systemcfg.range.thresholds[FMN]) >
						(m_blmne.X_MN - m_blmne.X_LMN - systemcfg.range.thresholds[FMN])*(scatter - m_blmne.Y_NL - systemcfg.range.thresholds[FMN])))
						count_fmn++;
				}
				else
					count_mono++;
			}
			else if (res < m_blmne.X_RM)
				count_mono++;
			else
				count_rmono++;
			if (res >= 250)//研究参数
			{
				count_blasts++;
			}
		}
		else
		{
			if (res < m_blmne.X_NOL)
				count_noise++;
			else if (res < m_blmne.X_LL)
				count_llym++;
			else if (res < m_blmne.X_AL)
				count_lym++;
			else if (res < m_blmne.X_LMU)
				count_rlym++;
			else if (res < m_blmne.X_LMD)
			{
				if ((m_blmne.X_LMD - res)*m_blmne.Y_NL >
					(m_blmne.X_LMD - m_blmne.X_LMU)*scatter)
					count_rlym++;
				else
					count_mono++;
			}
			else if (res < m_blmne.X_RM)
				count_mono++;
			else
				count_rmono++;
			if (res >= 250)//研究参数
			{
				count_blasts++;
			}
		}
	}

	count_blood = count_llym + count_rlym + count_lym + count_lneu + count_rneu + count_neu + count_rmono + count_mono + count_eos;
	count_lic = count_rneu + count_rmono;
	count_aly = count_rlym;
	//blood	
	TRACE("count_blood=%d---------#\n", count_blood);

	//lym
	TRACE("count_llym=%d---------#\n", count_llym);
	TRACE("count_rlym=%d---------#\n", count_rlym);
	TRACE("count_lym=%d---------#\n", count_lym);
	//neu
	TRACE("count_lneu=%d---------#\n", count_lneu);
	TRACE("count_rneu=%d---------#\n", count_rneu);
	TRACE("count_neu=%d---------#\n", count_neu);
	//mono
	TRACE("count_rmono=%d---------#\n", count_rmono);
	TRACE("count_mono=%d---------#\n", count_mono);
	//eos
	TRACE("count_eos=%d---------#\n", count_eos);

	//aly
	TRACE("count_aly=%d---------#\n", count_aly);
	//lic
	TRACE("count_lic=%d---------#\n", count_lic);

	//nosie
	TRACE("count_noise=%d---------#\n", count_noise);

	//研究参数
	//blasts
	TRACE("count_blasts=%d---------#\n", count_blasts);
	//left
	TRACE("count_left=%d---------#\n", count_lneu);
	//nrbc
	TRACE("count_nrbc=%d---------#\n", count_llym);

	if (count_blood > 0)//除数不为0
	{
		//NO
		if (count_noise > 120)				//FDparam 及下面几个，参考ABX
			(*psampledata).lmneflg[0] = 2;
		//LL
		if (count_llym > 50)
			(*psampledata).lmneflg[1] = 2;
		//LL1
		if (count_llym > 45 && (float)count_llym / count_blood > 0.05)
			(*psampledata).lmneflg[2] = 2;
		//NL
		if (count_fln > 120 || (float)count_fln / count_blood > 0.03)
			(*psampledata).lmneflg[3] = 2;
		//MN
		if (count_fmn > 120)
			(*psampledata).lmneflg[4] = 2;
		//RM
		if (count_rmono > 999 || (float)count_rmono / count_blood > 0.011)
			(*psampledata).lmneflg[5] = 2;
		//LN
		if (count_lneu > 999 || (float)count_lneu / count_blood > 0.025)
			(*psampledata).lmneflg[6] = 2;
		//RN
		if (count_rneu > 999 || (float)count_rneu / count_blood > 0.011)
			(*psampledata).lmneflg[7] = 2;
		//NE
		if (count_fne > 60 || (float)count_fne / count_blood > 0.011)
			(*psampledata).lmneflg[8] = 2;
	}

	//加1处理，消除0x00截止符,否则以TEXT格式存入数据库会有问题
	for (i = 0; i < MATRIX_DATA_MAX - 1; i++)
		(*psampledata).lmnegraph[i] += 1;
	(*psampledata).lmnegraph[MATRIX_DATA_MAX - 1] = 0;

	if (count_blood > 0)	//如果count_bloos为0，除法运算会出现异常
	{
		int 		cal_blood = count_blood * VOLAMP_WBCBASO * 1.19;

		wbc = atof(psampledata->wbcdata.wbc);
		wbc_lmne = cal_blood;

		//非密码进入需要判断
		if (*pIsSuper == 0 && (!IsBlankTest))
		{
			if (WbcForCompare > 0.5 || cal_blood > 0.5)
			{
				if (cal_blood > 2 * WbcForCompare)             //若WBC堵孔，则所有数据不显示
				{
					wbc = 0.0;
					strcpy((*psampledata).wbcdata.wbc, "**.**");
					strcpy((*psampledata).wbcdata.basp, "*.*");
					strcpy((*psampledata).wbcdata.bas, "*.**");

					CView* pActiveView = ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
					HWND testwnd = pActiveView->GetSafeHwnd();
					SendMessage(testwnd, WM_BLOCKER, (WPARAM)1, 0L);
				}
				//20150427Del
				//else if(WbcForCompare > 2 * cal_blood)      //若LMNE堵孔，则正常显示
				//{
				//wbc = 0.0;
				//strcpy((*psampledata).wbcdata.basp,"*.*");
				//strcpy((*psampledata).wbcdata.bas,"*.**");
				//	SendMessage(MainWindowhDlg,MSG_BLOCKERR,(WPARAM)2,0L);
				//}
			}
		}

		if (wbc >= 0.3)       //wbc >= 0.3才有意义
		{
			coefficient = (100 - atof(psampledata->wbcdata.basp)) / count_blood;

			lymp = coefficient*(count_llym + count_lym);
			neup = coefficient*(count_lneu + count_neu);
			monop = coefficient*(count_mono);
			eosp = coefficient*count_eos;

			alyp = coefficient*count_aly;
			licp = coefficient*count_lic;
			//研究参数
			blastsp = coefficient*count_blasts;
			leftp = coefficient*count_lneu;
			nrbcp = coefficient*count_llym;

			//lym#
			lym = wbc*lymp / 100;
			//neu#
			neu = wbc*neup / 100;
			//mon#
			mono = wbc*monop / 100;
			//eos#
			eos = wbc*eosp / 100;

			//aly#
			aly = wbc*alyp / 100;
			//lic#
			lic = wbc*licp / 100;
			//研究参数
			blasts = wbc*blastsp / 100;
			left = wbc*leftp / 100;
			nrbc = wbc*nrbcp / 100;
		}
	}

	if (wbc < 0.3)		//wbc < 0.3,display *****
	{
		(*psampledata).lmneflg[0] = 1;
		(*psampledata).lmneflg[1] = 1;
		(*psampledata).lmneflg[2] = 1;
		(*psampledata).lmneflg[3] = 1;
		(*psampledata).lmneflg[4] = 1;
		(*psampledata).lmneflg[5] = 1;
		(*psampledata).lmneflg[6] = 1;
		(*psampledata).lmneflg[7] = 1;
		(*psampledata).lmneflg[8] = 1;
	}
	else
	{
		//研究参数
		sprintf(studyPara[0], "%.1f", blastsp);
		sprintf(studyPara[1], "%.1f", blasts);
		sprintf(studyPara[2], "%.1f", leftp);
		sprintf(studyPara[3], "%.1f", left);
		sprintf(studyPara[4], "%.1f", nrbcp);
		sprintf(studyPara[5], "%.1f", nrbc);

		//LYMP
		sprintf((*psampledata).wbcdata.lymp, "%.1f", lymp);
		//NEUP
		sprintf((*psampledata).wbcdata.neup, "%.1f", neup);
		//MONOP
		sprintf((*psampledata).wbcdata.monop, "%.1f", monop);
		//EOSP
		sprintf((*psampledata).wbcdata.eosp, "%.1f", eosp);
		//ALYP
		sprintf((*psampledata).wbcdata.alyp, "%.1f", alyp);
		//LICP
		sprintf((*psampledata).wbcdata.licp, "%.1f", licp);

		//LYM
		sprintf((*psampledata).wbcdata.lym, "%.2f", lym);
		//NEU
		sprintf((*psampledata).wbcdata.neu, "%.2f", neu);
		//MONO
		sprintf((*psampledata).wbcdata.mono, "%.2f", mono);
		//EOS
		sprintf((*psampledata).wbcdata.eos, "%.2f", eos);
		//ALY
		sprintf((*psampledata).wbcdata.aly, "%.2f", aly);
		//LIC
		sprintf((*psampledata).wbcdata.lic, "%.2f", lic);
	}

	return retn;
}

/***********************************************************
*Function:
*Description:	对接收的数据帧的数据(rdata所指空间)进行
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:	create	wsm		2010.12.31
************************************************************/
void DataProcess::HgbAnalysis(sample_info *psampledata)
{
	unsigned short int tmp_hgb = 0;
	float hgb = 0.0;
	float a = 0, b = 1.0, c = 0;

	TRACE("\nHgbAnalysis()====================\n");
	tmp_hgb = hgbgraph[0] * 1000 + hgbgraph[1] * 100 + hgbgraph[2] * 10 + hgbgraph[3];
	if (tmp_hgb <= 8310)	//8310 是根据下位机来的数据是tmp_hgb的上限值
	{
		//hgb
		a = systemcfg.modify[systemcfg.mode].a[MOD_HGBF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_HGBF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_HGBF];
		hgb = (float)tmp_hgb / 10;		//下位机中乘10，这边要除以10
		hgb = systemcfg.calibration[systemcfg.mode][CAL_HGBF] * fabs(a*hgb*a*hgb + b*hgb + c);
	}
	TRACE("hgb=%.1f---------#\n", hgb);

	//------------------------------------------------
	//判断并进行格式转换
	if (hgb < 3.0)
	{
		hgb = 0;
		sprintf((*psampledata).rbcdata.hgb, "%.1f", hgb);

	}
	else if (hgb > 300.0)	//一般不会大于300，大于就要报灯错误，并且结果打*号。低值不需要处理
	{
		printf("HGB  is higher than 300.0----------#\n");
		//xx22  报错，参考三分类的报警机制
	}
	else
	{
		sprintf((*psampledata).rbcdata.hgb, "%.1f", hgb);
	}
}

/***********************************************************
*Function:
*Description:	对接收的数据帧的数据(rdata所指空间)进行
分析(解析判断，并存入sampledata.rbcgraph所指向的空间)
*Called by:
*Params illustration:  不要改动原始图形数据，即直方图数据
*Data Access:
*Other:
*History:	create	wsm		2010.12.31
************************************************************/
void DataProcess::RbcAnalysis(sample_info *psampledata, const uchar* pIsSuper)	//xx22 和RbcAnalysis区别在于是否用右阈值计算MCV和RBC的计算公式
{
	unsigned short int i, j;
	unsigned short int pointnum = 0;
	float dist_temp = 0.0;
	unsigned short int transbuff1[256] = { 0 };
	unsigned short int transbuff2[256] = { 0 };
	unsigned short int tempbuff[256] = { 0 };
	unsigned short int count_rbc = 0;
	unsigned short int count_rbc_amp = 0;//纵坐标放大后的计数总数	
	unsigned int count_hct = 0;
	unsigned char volume_mcv = 0;
	float hgb = 0.0;
	float rbc = 0.0;
	float hct = 0.0;
	float mcv = 0.0;
	float mch = 0.0;
	float mchc = 0.0;
	float rdwcv = 0.0;
	float rdwsd = 0.0;
	unsigned char start, end;
	unsigned char rightend = 0;
	unsigned char L1 = 0, L2 = 0;		//计算rdwcv参数，标记
	unsigned char maxnum = 0; 			//红细胞分布细胞个数最大值对应的体积
	unsigned short int maxval = 0; 		//体积最大值
	unsigned int count_temp = 0; 		//计算rdwcv的临时计数变量
	float temp1 = 0.0;
	float temp2 = 0.0;
	float cal = 1.0;
	float a = 0, b = 1.0, c = 0;

	start = systemcfg.range.thresholds[RB1];
	end = systemcfg.range.thresholds[RB2];

	for (i = 0; i < 256; i++)
	{
		transbuff1[i] = ((psampledata->rbcgraph[(i << 1) + 1]) << 8) + psampledata->rbcgraph[i << 1];
		transbuff2[i] = (rbcgraph_2[(i << 1) + 1] << 8) + rbcgraph_2[i << 1];
		tempbuff[i] = (transbuff1[i] + transbuff2[i]) / 2;
	}

	maxval = tempbuff[start];
	for (i = start + 1; i <= end; i++)
		if (tempbuff[i] > maxval)
			maxval = tempbuff[i];
	TRACE("rbc maxval=%d---------#\n", maxval);

	if (maxval > start)
	{
		if (2 * maxval - start < end)
		{
			rightend = 2 * maxval - start;
			for (i = 2 * maxval - start; i <= end; i++)
			{
				if (tempbuff[i] < 0.02*maxval)
					rightend = i;
			}
		}
		else//异常情况
			rightend = end;
	}
	else//异常情况
		rightend = end;

	//计算参数，红细胞计数及HCT计数	
	count_rbc = 0;
	count_hct = 0;
	for (i = start; i <= rightend; i++)
	{
		count_rbc += tempbuff[i];
		count_hct += tempbuff[i] * i;	//求HCT(红细胞压积)，一定容积全血中红细胞体积所占的百分比，HCT（%）=RBC*MCV/实际采样的血样本体积	
	}
	TRACE("count_rbc=%d---------#\n", count_rbc);
	TRACE("count_hct=%d---------#\n", count_hct);

	if (count_rbc <= 370370 && count_rbc > 0)	//确保测试结果<100.00，然后使用sprintf转换格式存到数据库中没有问题
	{
		//求MCV(平均红细胞体积)，根据直方图(此处先采用原始数据)来算	
		volume_mcv = count_hct / count_rbc;
		TRACE("volume_mcv=%d---------#\n", volume_mcv);

		//------------------------------------------------
		//用计数的血液样本体积为(1/VOL_RBCPLT)pl
		//AD的分辨力等于AMP_RBC(fL)

		//rbc
		a = systemcfg.modify[systemcfg.mode].a[MOD_RBCF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_RBCF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_RBCF];
		rbc = count_rbc*VOL_RBCPLT;
		rbc = systemcfg.calibration[systemcfg.mode][CAL_RBCF] * fabs(a*rbc*a*rbc + b*rbc + c);  	//体积校正,单位1E12/L	
		//MCV
		a = systemcfg.modify[systemcfg.mode].a[MOD_MCVF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_MCVF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_MCVF];
		mcv = volume_mcv*AMP_RBC;	//fL
		mcv = systemcfg.calibration[systemcfg.mode][CAL_MCVF] * fabs(a*mcv*a*mcv + b*mcv + c);

		hct = rbc*mcv / 10;
		//------------------------------------------------
		//MIC
		if (mcv < 70)		//MCV<70fl FDparam
			(*psampledata).rbcflg[0] = 2;
		//MAC
		if (mcv > 110)		//MCV>110fl FDparam
			(*psampledata).rbcflg[1] = 2;

		hgb = atof(psampledata->rbcdata.hgb);
		if (rbc < 0.00001)
			mch = 0;
		else//除数不为0
			mch = hgb / rbc;

		//求MCHC(红细胞平均血红蛋白浓度)
		//MCHC = HGB/HCT (ABX的公式)			
		if (hct < 0.00001)
			mchc = 0;
		else
			mchc = 100 * hgb / hct;

		if (mchc > 999.9)//异常,会溢出，存不下
			mchc = 0;

		//----------------------------------------
		//纵坐标放大，计算RDW-SD，RDW-CV
		if (maxval != 0)
			cal = (float)RBC_HEIGHT / maxval;
		else
			cal = 1.0;
		TRACE("rbc cal=%.2f---------#\n", cal);

		//图形调整
		for (i = start; i <= end; i++)
			tempbuff[i] *= cal;

		//加权滤波
		for (i = start + 1; i <= end - 1; i++)
			tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
		for (i = start + 3; i <= end - 3; i++)
			tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];

		//滤波时候最大值可能会变化，重新找最大值
		//寻找最大值，放大后的信号计数，放大后的信号只用于计算RDW-CV,RDW-SD	
		count_rbc_amp = tempbuff[start];
		maxval = tempbuff[start];
		maxnum = start;
		for (i = start + 1; i <= end; i++)
		{
			count_rbc_amp += tempbuff[i];
			if (tempbuff[i] > maxval)
			{
				maxval = tempbuff[i];
				maxnum = i;
			}
		}

		if (0 == count_rbc_amp)//保证除数不为0
			count_rbc_amp = 1;

		//------------------------------------------------
		//RDW-CV(%) = (L2-L1)/(L2+L1)*100%  zxg Sysmex公式
		count_temp = tempbuff[volume_mcv];
		//寻找分布宽度标记值L1,L2
		for (L1 = volume_mcv - 1, L2 = volume_mcv + 1; L1 >= start && L2 <= end; L1--, L2++)
		{
			count_temp += (tempbuff[L1] + tempbuff[L2]);
			if ((1.0*count_temp) / count_rbc_amp > 0.6826)
				break;
		}
		//选择最优边界值
		temp1 = 1.0*(count_temp - tempbuff[L1] - tempbuff[L2]) - 0.6862*count_rbc_amp;
		temp2 = 1.0*count_temp - 0.6862*count_rbc_amp;
		if (temp1 < temp2)   //边界值取L1+1，L2-1更优
		{
			L1++;
			L2--;
		}
		rdwcv = (float)(L2 - L1) / (L2 + L1) * 100;//红细胞体积分布宽度和血小板宽度

		//------------------------------------------------
		//RDW-SD			
		for (L1 = start; L1 < maxnum; L1++)
		{
			if ((1.0*tempbuff[L1] / maxval) > 0.2)
				break;
		}
		for (L2 = end; L2 > maxnum; L2--)
		{
			if ((1.0*tempbuff[L2] / maxval) > 0.2)
				break;
		}
		//选择最优标记值
		//L1
		temp1 = 1.0*(tempbuff[L1] - 0.2*maxval);
		temp2 = 1.0*(tempbuff[L1 - 1] - 0.2*maxval);
		if (temp1 > temp2)
			L1--;
		//L2
		temp1 = 1.0*(tempbuff[L2] - 0.2*maxval);
		temp2 = 1.0*(tempbuff[L2 + 1] - 0.2*maxval);
		if (temp1 > temp2)
			L2++;
		rdwsd = L2 - L1;

		a = systemcfg.modify[systemcfg.mode].a[MOD_RDWCVF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_RDWCVF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_RDWCVF];
		rdwcv = fabs(a*rdwcv*a*rdwcv + b*rdwcv + c);

		a = systemcfg.modify[systemcfg.mode].a[MOD_RDWSDF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_RDWSDF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_RDWSDF];
		rdwsd = rdwsd*AMP_RBC;
		rdwsd = fabs(a*rdwsd*a*rdwsd + b*rdwsd + c);
	}

	//RBC值小于0.05图形不显示
	if (rbc < 0.05)
	{
		for (i = 0; i < 256; i++)
			tempbuff[i] = 0;
	}

	//最终保存结果，+1对可能的0x00处理		
	for (i = 0; i < (start << 1); i++)
		psampledata->rbcgraph[i] = 1;
	for (i = start; i <= end; i++)
	{
		psampledata->rbcgraph[(i << 1)] = (tempbuff[i] & 0x00ff) + 1;
		psampledata->rbcgraph[(i << 1) + 1] = (tempbuff[i] >> 8) + 1;		//其实经过纵坐标压缩放大处理后，计数值已经小于RBC_HEIGHT<255了，所以其实rbcgraph高字节存的都是0
	}
	for (i = ((end + 1) << 1); i < 511; i++)
		psampledata->rbcgraph[i] = 1;
	psampledata->rbcgraph[511] = 0;

	//------------------------------------------------
	//如果进行开机测试则对原始数据进行保存
	if (StartupBlankTestsflag)
	{
		StartupBlankTestsrbc = rbc;
	}

	//----------------------------------------
	//判断并格式转换
	if (rbc < 0.05)	//低于0.05	
	{
		rbc = 0;
		sprintf((*psampledata).rbcdata.rbc, "%.2f", rbc);
		//其它相关参数都是初始化的值即"*"号
		(*psampledata).rbcflg[0] = 1;
		(*psampledata).rbcflg[1] = 1;
	}
	else
	{
		//RBC
		sprintf((*psampledata).rbcdata.rbc, "%.2f", rbc);
		//HCT
		sprintf((*psampledata).rbcdata.hct, "%.1f", hct);
		//MCV
		sprintf((*psampledata).rbcdata.mcv, "%.1f", mcv);
		//MCH
		sprintf((*psampledata).rbcdata.mch, "%.1f", mch);
		//MCHC
		sprintf((*psampledata).rbcdata.mchc, "%.1f", mchc);
		//RDW-CV
		sprintf((*psampledata).rbcdata.rdwcv, "%.1f", rdwcv);
		//RDW-SD
		sprintf((*psampledata).rbcdata.rdwsd, "%.1f", rdwsd);
	}

	if (*pIsSuper == 0 && (!IsBlankTest))
		IsBlocking_RBC( psampledata);
}

//PLT图形数据显示判断
bool DataProcess::PLTDisplayGraph(float plt)
{
	//PLT值小于30图形不显示
	if (plt < 30 && systemcfg.mode < 2)
		return FALSE;
	else
		return TRUE;
}
//PLT参数显示判断
bool PLTDisplayItem(float plt)
{
	//全血模式,PLT<10,不显示
	if (plt < 10 && systemcfg.mode < 2)
		return FALSE;
	else
		return TRUE;
}

/***********************************************************
*Function:
*Description:	对接收的数据帧的数据(rdata所指空间)进行
分析(解析判断，并存入sampledata.basograph所指向的空间)
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:	create	wsm		2010.12.31
************************************************************/
void DataProcess::PltAnalysis(sample_info *psampledata)	//xx21 有时间看一下，测试一下
{
	unsigned short int 	i;
	unsigned short int 	pointnum = 4;
	float 			dist_temp = 0.0;
	uchar 			tempbuff[256];
	unsigned short int 	count_plt = 0;
	unsigned short int 	count_plt2 = 0;
	unsigned int 		count_pct = 0;
	uchar 			colume_mpv = 0;
	float plt = 0.0;
	float mpv = 0.0;
	float pdw = 0.0;
	float pct = 0.0;
	float plcr = 0.0;
	uchar 	start, end;
	uchar 	maxnum = 0; 	//红细胞分布细胞个数最大值对应的体积
	unsigned short int maxval = 0;
	unsigned char L1 = 0, L2 = 0;	//计算pdw参数，标记
	float temp1 = 0.0;
	float temp2 = 0.0;
	float cal = 1.0;
	float a = 0, b = 1.0, c = 0;
	unsigned int count_temp = 0;	//计算PLCR的临时计数变量
	float  proportion = 0.3;//用于判断左阈值对应峰值比例

	TRACE("\nPltAnalysis()====================\n");
	for (i = 0; i < 256; i++)
		tempbuff[i] = (*psampledata).pltgraph[i];     //hw:20140521

	start = systemcfg.range.thresholds[PLT1];
	end = systemcfg.range.thresholds[PLT2];
	PLTRightBorderQuery = end;

	if (0 == systemcfg.PltRightThresholdMode)
	{
		TRACE("0 == PltRightThresholdMode\n");

		//求PLT(血小板总数)、PLT体积校正，求PCT(血小板压积)
		count_plt = 0;
		count_plt2 = 0;
		count_pct = 0;
		for (i = start; i <= end; i++)
		{
			count_plt += tempbuff[i];
			count_plt2 += pltgraph_2[i];
			count_pct += tempbuff[i] * i;	//一定容积全血中血小板所占的百分比 PCT = PLT*MPV/10000	
		}
		count_plt = (count_plt + count_plt2) / 2;           //取两次平均值
		TRACE("count_plt=%d---------#\n", count_plt);
		TRACE("count_pct=%d---------#\n", count_pct);

		if (count_plt <= 37037 && count_plt > 0)	//确保测试结果<10000，然后使用sprintf转换格式存到数据库中没有问题
		{
			//求MPV(平均血小板体积)
			//此放大倍数比红细胞大，值也可能比MCV大
			colume_mpv = count_pct / count_plt;
			TRACE("colume_mpv=%d---------#\n", colume_mpv);

			//求P-LCR
			count_temp = 0;
			//for(i = 120;i <= end;i++)  		//暂时认为12uL对应的点为120		///FDparam		//xx21    
			//hw_change:20140723    ori:i=120
			for (i = 60; i <= end; i++)     //200/40*12
				count_temp += tempbuff[i];
			plcr = 100.0*count_temp / count_plt;

			a = systemcfg.modify[systemcfg.mode].a[MOD_PCTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PCTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PCTF];
			pct = count_pct*VOL_RBCPLT*AMP_PLT / 10;
			pct = fabs(a*pct*a*pct + b*pct + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_PLCRF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLCRF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLCRF];
			plcr = fabs(a*plcr*a*plcr + b*plcr + c);
			//----------------------------------------
			//用计数的血液样本体积为(1/VOL_RBCPLT)pl
			//AD的分辨力等于AMP_PLT(fL)  

			//plt
			a = systemcfg.modify[systemcfg.mode].a[MOD_PLTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLTF];
			plt = count_plt*1000.0*VOL_RBCPLT;
			plt = systemcfg.calibration[systemcfg.mode][CAL_PLTF] * fabs(a*plt*a*plt + b*plt + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_MPVF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_MPVF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_MPVF];
			mpv = colume_mpv*AMP_PLT;
			mpv = fabs(a*mpv*a*mpv + b*mpv + c);
			//----------------------------------------
			//纵坐标放大，计算PDW，类似于RDW-SD

			//PLT的计数较少，相邻体积之间的计数形不成光滑曲线，只能几个点取平均值，然后再形成曲线
			//256个数据分成64*4，取64组的平均值放在本组的第二个(也可以放第三个)
			for (i = 0; i < 64; i++)
				tempbuff[1 + 4 * i] = (float)(tempbuff[4 * i] + tempbuff[1 + 4 * i] + tempbuff[2 + 4 * i] + tempbuff[3 + 4 * i]) / 4;

			//找最大值
			maxnum = 1;
			maxval = tempbuff[1];
			for (i = 1; 4 * i + 1 < end; i++)
			{
				if (tempbuff[4 * i + 1] > maxval)
				{
					maxval = tempbuff[4 * i + 1];
					maxnum = 4 * i + 1;
				}
			}
			TRACE("plt maxval=%d---------#\n", maxval);

			if (maxval != 0)
				cal = (float)PLT_HEIGHT / maxval;
			else
				cal = 1.0;
			TRACE("PLT cal=%.2f---------#\n", cal);

			for (i = start; i <= end; i++)
			{
				tempbuff[i] = tempbuff[i] * cal;	//图形纵向比例压缩
			}

			tempbuff[0] = tempbuff[1] / 2;
			pointnum = 4;
			for (i = 0; i < 63; i++)
			{
				tempbuff[2 + pointnum*i] = (float)(tempbuff[5 + pointnum*i] - tempbuff[1 + pointnum*i]) / pointnum + tempbuff[1 + pointnum*i];
				tempbuff[3 + pointnum*i] = (float)(tempbuff[5 + pointnum*i] - tempbuff[1 + pointnum*i]) * 2 / pointnum + tempbuff[1 + pointnum*i];
				tempbuff[4 + pointnum*i] = (float)(tempbuff[5 + pointnum*i] - tempbuff[1 + pointnum*i]) * 3 / pointnum + tempbuff[1 + pointnum*i];
			}
			tempbuff[254] = tempbuff[253] * 2 / 3;
			tempbuff[255] = tempbuff[253] * 1 / 3;

			//加权滤波	
			for (i = start + 1; i <= end - 1; i++)
				tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
			//加权滤波	
			for (i = start + 3; i <= end - 3; i++)
				tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];

			maxval = tempbuff[start];
			maxnum = start;
			for (i = start + 1; i <= end; i++)
				if (tempbuff[i] > maxval)
				{
					maxval = tempbuff[i];
					maxnum = i;
				}

			for (L1 = start; L1 < maxnum; L1++)
			{
				if ((1.0*tempbuff[L1] / maxval) > 0.2)
					break;
			}
			for (L2 = end; L2 > maxnum; L2--)
			{
				if ((1.0*tempbuff[L2] / maxval) > 0.2)
					break;
			}
			//选择最优标记值
			//L1
			temp1 = 1.0*(tempbuff[L1] - 0.2*maxval);
			temp2 = 1.0*(tempbuff[L1 - 1] - 0.2*maxval);
			if (temp1 > temp2)
				L1--;
			//L2
			temp1 = 1.0*(tempbuff[L2] - 0.2*maxval);
			temp2 = 1.0*(tempbuff[L2 + 1] - 0.2*maxval);
			if (temp1 > temp2)
				L2++;

			pdw = L2 - L1;
			a = systemcfg.modify[systemcfg.mode].a[MOD_PDWF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PDWF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PDWF];
			pdw = pdw*AMP_PLT;
			pdw = fabs(a*pdw*a*pdw + b*pdw + c);
		}

		//PLT值小于30图形不显示
		if (!PLTDisplayGraph(plt))
		{
			for (i = 0; i < 256; i++)
				tempbuff[i] = 0;
		}

		for (i = 0; i < start; i++)
			(*psampledata).pltgraph[i] = 1;
		for (i = start; i <= end*PLT_WIDTH / 255; i++)       //20141124_75ha_temp:有效数据不能超出右界标
			(*psampledata).pltgraph[i] = tempbuff[i] + 1;
		for (i = end*PLT_WIDTH / 255 + 1; i < 255; i++)
			(*psampledata).pltgraph[i] = 1;
		psampledata->pltgraph[255] = 0;
		if (plt>30)//20151104 zwh左界标对应PLT高于最高值proportion 警示
		{
			if (tempbuff[systemcfg.range.thresholds[PLT1]]>(float)proportion*maxval)
				(*psampledata).pltflg[2] = 2;
		}


	}
	else ///1 == systemcfg.PltRightThresholdMode
	{
		uchar		oribuff[256];
		uchar 		methodUsed;
		uchar 		minnum;
		unsigned int 	minval;
		unsigned int	transnum;
		uchar 		tempnum1;
		uchar		tempnum2;
		bool			FindMax_EN =TRUE;
		uchar		EffectiveBorder = end;
		uchar 		j;
		/******Debug********
		for(i = 0; i< 20; i++)
		tempbuff[i] = i;
		for(i = 20; i< 30; i++)
		tempbuff[i] = 40-i;
		for(i = 30; i< 80; i++)
		tempbuff[i] = 2*(i-30) + 10;
		for(i = 80; i< 100; i++)
		tempbuff[i] = 110-5*(i-80);
		for(i = 100; i < 120; i++)
		tempbuff[i] = 10+i-100;
		for(i = 120; i< 130; i++)
		tempbuff[i] = 150-i;
		for(i = 130; i< 140; i++)
		tempbuff[i] = i-100;
		******Debug********/

		for (i = 0; i < 255; i++)
			oribuff[i] = tempbuff[i];

		while (FindMax_EN)
		{
			FindMax_EN = FALSE;
			maxnum = 2;				//[2,128-1]	
			maxval = tempbuff[1] + tempbuff[2] + tempbuff[3];
			for (i = 3; i < 96; i++)
			{
				transnum = tempbuff[i - 1] + tempbuff[i] + tempbuff[i + 1];
				if (transnum >= maxval)
				{
					maxnum = i;
					maxval = transnum;
				}
			}
			maxval = (tempbuff[maxnum - 1] + tempbuff[maxnum] + tempbuff[maxnum + 1]) / 3;

			tempnum1 = tempbuff[maxnum - 3];
			tempnum2 = tempbuff[maxnum + 3];
			if (maxval - tempnum1 > 0.3 * maxval && maxval - tempnum2 > 0.3 * maxval)
			{
				tempnum2 = (tempnum2 - tempnum1) / 6;
				for (j = maxnum - 2, i = 1; j < maxnum + 3; j++, i++)
					tempbuff[j] = tempnum1 + tempnum2*i;
				FindMax_EN = TRUE;
			}
		}

		//谷底值
		minnum = maxnum;	//[maxnum,139]	
		minval = tempbuff[maxnum - 1] + tempbuff[maxnum] + tempbuff[maxnum + 1];
		//puts("---------------------------------------------------------------");
		for (i = maxnum + 1; i < 139; i++)	//FDparam 和DSP统一起来 140是DSP采集信号的上限	//xx21
			if (tempbuff[i - 1] + tempbuff[i] + tempbuff[i + 1] <= minval)
			{
				minnum = i;
				minval = tempbuff[i - 1] + tempbuff[i] + tempbuff[i + 1];
				//printf("minnum[%d]:%d minval[%d]:%d\n",i,minnum,i,minval);
			}
		minval = (tempbuff[minnum - 1] + tempbuff[minnum] + tempbuff[minnum + 1]) / 3;
		//printf("minnum:%d minval:%d\n",minnum,minval);
		//puts("---------------------------------------------------------------");

		TRACE("plt maxnum=%d---------#\n", maxnum);
		TRACE("plt maxval=%d---------#\n", maxval);
		TRACE("plt minnum=%d---------#\n", minnum);
		TRACE("plt minval=%d---------#\n", minval);

		//报警信息(18,30)fL，[115,191]取三个值的和可减小误差
		if (minnum > 191 || minnum < 115)
		{
			(*psampledata).pltflg[0] = 2;
		}
		count_temp = 0;
		for (i = 192; i < 256; i++)		//30fl之后
			count_temp += tempbuff[i];
		if (count_temp > 30000)			//FDparam 参考ABX
			(*psampledata).pltflg[0] = 2;

		count_temp = 0;
		for (i = 0; i < 20; i++)			//02~3fl
			count_temp += tempbuff[i];
		if (count_temp > 3000)			//FDparam 参考ABX
			(*psampledata).pltflg[1] = 2;

		{
			uchar compch = (tempbuff[PLTGraphEnd] + tempbuff[PLTGraphEnd + 1] + tempbuff[PLTGraphEnd + 2]) / 3;

			if (minnum <= 191 && compch <= 0.3*maxval)		//谷底在30fL以前，30fL处<=最大值的40%
			{
				methodUsed = 1;
			}
			else	 if (minnum <= 191 && compch > 0.3*maxval)		//谷底在30fL以前，30fL处>最大值的40%
			{
				methodUsed = 2;
			}
			else if (minnum > 191 && compch <= 0.3*maxval)		//谷底在30fL以后，30fL处<=最大值的40%
			{
				methodUsed = 3;
			}
			else													//谷底在30fL以后，30fL处>最大值的40%
			{
				methodUsed = 4;
			}
		}

		TRACE("methodUsed= %d\n", methodUsed);
		if (methodUsed == 1)//第一种模式下，补一块区域(正常情况下)，用第三种模式处理(异常情况下)
		{
			if (maxval > minval)
			{
				//正常情况补一块，异常情况下不补
				if (minval*(minnum - maxnum) / (maxval - minval) > 0 && 2.0*minval*(minnum - maxnum) / (maxval - minval) + minnum < 255)
				{
					tempnum1 = 2.0*minval*(minnum - maxnum) / (maxval - minval) + minnum;	//minnum一定>maxnum，2.0使得曲线平滑
					for (i = minnum; i <= tempnum1; i++)
						tempbuff[i] = minval*(tempnum1 - i) / (tempnum1 - minnum);
				}
				else//异常情况
					methodUsed = 3;
			}
			else//异常情况
				methodUsed = 3;
		}

		//将第二个峰值拉低，防止第二个峰值很大
		for (i = minnum + 1; i < 255; i++)
			if (tempbuff[i] > maxval)
			{
				tempbuff[i] = maxval;
			}
		//PLT的计数较少，相邻体积之间的计数形不成光滑曲线，只能几个点取平均值，然后再形成曲线
		//256个数据分成64*4，取64组的平均值放在本组的第二个(也可以放第三个)
		for (i = 0; i < 64; i++)
			tempbuff[1 + 4 * i] = (float)(tempbuff[4 * i] + tempbuff[1 + 4 * i] + tempbuff[2 + 4 * i] + tempbuff[3 + 4 * i]) / 4;

		//找最大值
		maxnum = 1;
		maxval = tempbuff[1];
		for (i = 1; i < 64; i++)
		{
			if (tempbuff[4 * i + 1] > maxval)
			{
				maxval = tempbuff[4 * i + 1];
				maxnum = 4 * i + 1;
			}
		}
		TRACE("plt maxval=%d---------#\n", maxval);

		if (maxval != 0)
			cal = (float)PLT_HEIGHT / maxval;
		else
			cal = 1.0;
		TRACE("PLT cal=%.2f---------#\n", cal);

		for (i = start; i <= end; i++)
		{
			tempbuff[i] = tempbuff[i] * cal;	//图形纵向比例压缩
		}

		tempbuff[0] = tempbuff[1] / 2;
		for (i = 0; i < 63; i++)
		{
			tempbuff[2 + 4 * i] = (float)(tempbuff[5 + 4 * i] - tempbuff[1 + 4 * i]) / 4 + tempbuff[1 + 4 * i];
			tempbuff[3 + 4 * i] = (float)(tempbuff[5 + 4 * i] - tempbuff[1 + 4 * i]) * 2 / 4 + tempbuff[1 + 4 * i];
			tempbuff[4 + 4 * i] = (float)(tempbuff[5 + 4 * i] - tempbuff[1 + 4 * i]) * 3 / 4 + tempbuff[1 + 4 * i];
		}
		tempbuff[254] = tempbuff[253] / 3;
		tempbuff[255] = tempbuff[253] * 2 / 3;
		//----------------------------------------

		//加权滤波	
		for (i = start + 1; i <= end - 1; i++)
			tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
		//加权滤波	
		for (i = start + 3; i <= end - 3; i++)
			tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];

		TRACE("methodUsed= %d\n", methodUsed);
		if (methodUsed == 2)
		{
			//新谷底值
			minnum = 139;
			minval = tempbuff[138] + tempbuff[139] + tempbuff[140];
			for (j = 138; j > 70; j--)	//FDparam 和DSP统一起来 140是DSP采集信号的上限	//xx21
			{
				transnum = tempbuff[j - 1] + tempbuff[j] + tempbuff[j + 1];
				if (transnum < minval)
				{
					minnum = j;
					minval = transnum;
				}
			}
			EffectiveBorder = minnum;
			PLTRightBorderQuery = minnum * 255 / PLT_WIDTH;
		}
		else if (methodUsed == 3 || methodUsed == 4)
			EffectiveBorder = systemcfg.range.thresholds[PLT2];


		//----------------------------------------		
		//求PLT(血小板总数)、PLT体积校正，求PCT(血小板压积)
		count_plt = 0;
		count_pct = 0;
		count_plt2 = 0;
		for (j = start; j <= EffectiveBorder; j++)     //
		{
			count_plt += oribuff[j];
			count_plt2 += pltgraph_2[j];
			count_pct += oribuff[j] * j;	//一定容积全血中血小板所占的百分比 PCT = PLT*MPV/10000	
		}
		count_plt = (count_plt + count_plt2) / 2;
		TRACE("count_plt=%d---------#\n", count_plt);
		TRACE("count_pct=%d---------#\n", count_pct);

		if (count_plt <= 37037 && count_plt > 0)	//确保测试结果<10000，然后使用sprintf转换格式存到数据库中没有问题
		{
			//求MPV(平均血小板体积)
			//此放大倍数比红细胞大，值也可能比MCV大
			colume_mpv = count_pct / count_plt;
			TRACE("colume_mpv=%d---------#\n", colume_mpv);

			//求P-LCR			
			count_temp = 0;
			//for(i = 120;i <= end;i++)  		//暂时认为12uL对应的点为120		///FDparam		//xx21
			for (i = 60; i <= EffectiveBorder; i++)
				count_temp += oribuff[i];
			plcr = 100.0*count_temp / count_plt;
			//---------------------------------
			a = systemcfg.modify[systemcfg.mode].a[MOD_PCTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PCTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PCTF];
			pct = count_pct*VOL_RBCPLT*AMP_PLT / 10;
			pct = fabs(a*pct*a*pct + b*pct + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_PLCRF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLCRF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLCRF];
			plcr = fabs(a*plcr*a*plcr + b*plcr + c);
			//----------------------------------------
			//用计数的血液样本体积为(1/VOL_RBCPLT)pl
			//AD的分辨力等于AMP_PLT(fL)  

			//plt
			a = systemcfg.modify[systemcfg.mode].a[MOD_PLTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLTF];
			plt = count_plt*1000.0*VOL_RBCPLT;
			plt = systemcfg.calibration[systemcfg.mode][CAL_PLTF] * fabs(a*plt*a*plt + b*plt + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_MPVF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_MPVF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_MPVF];
			mpv = colume_mpv*AMP_PLT;
			mpv = fabs(a*mpv*a*mpv + b*mpv + c);

			maxval = tempbuff[start];
			maxnum = start;
			for (i = start + 1; i <= EffectiveBorder; i++)
				if (tempbuff[i] > maxval)
				{
					maxval = tempbuff[i];
					maxnum = i;
				}

			for (L1 = start; L1 < maxnum; L1++)
			{
				if ((1.0*tempbuff[L1] / maxval) > 0.2)
					break;
			}
			for (L2 = EffectiveBorder; L2 > maxnum; L2--)      //end -> EffectiveBorder
			{
				if ((1.0*tempbuff[L2] / maxval) > 0.2)
					break;
			}
			//选择最优标记值
			//L1
			temp1 = 1.0*(tempbuff[L1] - 0.2*maxval);
			temp2 = 1.0*(tempbuff[L1 - 1] - 0.2*maxval);
			if (temp1 > temp2)
				L1--;
			//L2
			temp1 = 1.0*(tempbuff[L2] - 0.2*maxval);
			temp2 = 1.0*(tempbuff[L2 + 1] - 0.2*maxval);
			if (temp1 > temp2)
				L2++;

			pdw = L2 - L1;
			a = systemcfg.modify[systemcfg.mode].a[MOD_PDWF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PDWF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PDWF];
			pdw = pdw*AMP_PLT;
			pdw = fabs(a*pdw*a*pdw + b*pdw + c);
		}

		//PLT值小于30图形不显示
		if (!PLTDisplayGraph(plt))
		{
			for (i = 0; i < 256; i++)
				tempbuff[i] = 0;
		}

		for (i = 0; i < start; i++)
			(*psampledata).pltgraph[i] = 1;
		for (i = start; i <= end*PLT_WIDTH / 255; i++)       //20141124_75ha_temp:有效数据不能超出右界标
			(*psampledata).pltgraph[i] = tempbuff[i] + 1;
		for (i = end*PLT_WIDTH / 255 + 1; i < 255; i++)
			(*psampledata).pltgraph[i] = 1;
		psampledata->pltgraph[255] = 0;

		if (plt>30)//20151104 zwh左界标对应PLT高于最高值proportion 警示
		{
			if (tempbuff[systemcfg.range.thresholds[PLT1]]>(float)proportion*maxval)
				(*psampledata).pltflg[2] = 2;
		}

	}

	//------------------------------------------------
	//开机测试则对原始数据进行保存
	if (StartupBlankTestsflag)
	{
		StartupBlankTestsplt = plt;
	}

	//------------------------------------------------
	//判断和格式转换,可放在滤波之前

	if (plt < 0.1)    //ori:30
	{
		plt = 0;
		sprintf((*psampledata).pltdata.plt, "%.0f", plt);
		(*psampledata).pltflg[0] = 1;
		(*psampledata).pltflg[1] = 1;
	}
	else if (!PLTDisplayItem(plt))    //PLT<10,其他4项参数不显示
	{
		sprintf((*psampledata).pltdata.plt, "%.0f", plt);
		(*psampledata).pltflg[0] = 1;
		(*psampledata).pltflg[1] = 1;
	}
	else
	{
		//PLT
		sprintf((*psampledata).pltdata.plt, "%.0f", plt);
		//PCT
		sprintf((*psampledata).pltdata.pct, "%.2f", pct);
		//MPV
		sprintf((*psampledata).pltdata.mpv, "%.2f", mpv);
		//PDW
		sprintf((*psampledata).pltdata.pdw, "%.1f", pdw);
		//P_LCR
		sprintf((*psampledata).pltdata.plcr, "%.1f", plcr);
	}
}

void DataProcess::IsBlocking_RBC( sample_info* pSampleData)
{
	double rbc = atof(pSampleData->rbcdata.rbc);
	double hgb = atof(pSampleData->rbcdata.hgb);

	if (hgb > 50 && rbc < hgb / 50)
	{	
		CView* pActiveView = ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
		HWND testwnd = pActiveView->GetSafeHwnd();
		SendMessage(testwnd,WM_BLOCKER, (WPARAM)3, 0L);
	}
}