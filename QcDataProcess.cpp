/*************************************************	//参考来源于嵌入式五分类QcDatabaseProcess.c
Copyright (C), SINNOWA. Co., Ltd.
File name: 	QcDataProcess.cpp
Author:			Version:		Date:
Description: 	质控运行数据处理
Others:      	// 其它内容的说明
Function List:
History:
*************************************************/

#include "stdafx.h"
#include "QcDataProcess.h"
#include "Includes_app.h"
#include "DataProcess.h"
//#include <math.h>

//分析计算参数宏定义
#define   VOLAMP_WBCBASO 	0.0015 	//WBCBASO体积和放大相关倍数
#define 	VOL_RBCPLT			0.00027	//采样体积相关系数
#define  	AMP_RBC			0.97		//RBC放大倍数相关
#define	AMP_PLT			0.125	//PLT放大倍数相关

//画图相关宏定义
#define LMNE_LEFT		340
#define LMNE_BOTTOM 	365
#define LMNE_WIDTH		200
#define LMNE_HEIGHT		200

#define BASO_LEFT		570
#define BASO_BOTTOM	305
#define BASO_WIDTH		204
#define BASO_HEIGHT		105

#define RBC_LEFT			340
#define RBC_BOTTOM		525
#define RBC_WIDTH		204
#define RBC_HEIGHT		105

#define PLT_LEFT			570
#define PLT_BOTTOM		525
#define PLT_WIDTH		204
#define PLT_HEIGHT		105


//extern const int  PLTGraphEnd;
extern int PLTGraphEnd ;


int	plt_threshold = 193;

//质控26个参数，而不是28项参数
static const char *static_param_qc[26] =
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
	"PLT",
	"MPV",
	"PDW",
	"PCT"
};

//质控的单位
static const char *static_unit_standard_qc[26] =
{
	"10^9/L",
	"%",
	"%",
	"%",
	"%",
	"%",
	"%",
	"%",
	"10^9/L",
	"10^9/L",
	"10^9/L",
	"10^9/L",
	"10^9/L",
	"10^9/L",
	"10^9/L",
	"10^12/L",
	"g/L",
	"%",
	"fL",
	"pg",
	"g/L",
	"%",
	"10^9/L",
	"fL",
	"fL",
	"%"
};

QcDataProcess::QcDataProcess()
{
}


QcDataProcess::~QcDataProcess()
{
}


void QcDataProcess::QcWbcBasoAnalysis(qcresult_info *psampledata)
{
	unsigned short int i;
	unsigned char tempbuff[256] = { 0 };
	unsigned char start, mid, end;
	unsigned short int maxval = 0;
	unsigned char threshold = 0;
	unsigned short int count_baso = 0;
	unsigned short int count_wbc = 0;
	float cal = 1.0;
	float wbc = 0;
	float baso = 0;
	float basop = 0;
	float		a = 0, b = 1.0, c = 0;
	TRACE("\nBasoAnalysis()====================\n");

	for (i = 0; i < 256; i++)	//BASO数据，共256通道
		tempbuff[i] = (*psampledata).basograph[i];

	//取有效数据段(幅值滤波)
	start = systemcfg.range.thresholds_qc[QCBA1];
	mid = systemcfg.range.thresholds_qc[QCBA2];
	end = systemcfg.range.thresholds_qc[QCBA3];

	//求BASO总数，BASO的数据太少，先计数再滤波，先滤波在计数BASO显著减少	
	count_baso = 0;
	for (i = mid; i <= end; i++)
		count_baso += tempbuff[i];//BASO总数		
	TRACE("count_baso=%d---------#\n", count_baso);

	//求WBC总数
	count_wbc = count_baso;
	for (i = start; i < mid; i++)
		count_wbc += tempbuff[i];
	TRACE("count_wbc=%d---------#\n", count_wbc);

	if (count_wbc <= 66666 && count_wbc > 0)	//确保测试结果<100.00，然后使用sprintf转换格式存到数据库中没有问题
	{
		//baso
		basop = (100.0*count_baso) / count_wbc;
		//baso#
		baso = count_baso*VOLAMP_WBCBASO;
		//wbc
		//75ha_add:20141111
		a = systemcfg.modify[systemcfg.mode].a[MOD_WBCF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_WBCF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_WBCF];
		wbc = count_wbc*VOLAMP_WBCBASO;
		wbc = systemcfg.calibration[systemcfg.mode][CAL_WBCF] * fabs(a*wbc*a*wbc + b*wbc + c);
	}

	maxval = tempbuff[start];
	for (i = start + 1; i <= end; i++)
		if (tempbuff[i] > maxval)
			maxval = tempbuff[i];
	TRACE("BASO->maxval=%d---------#\n", maxval);

	//threshold = (int)(maxval*(BASO_HEIGHT)/(BASO_HEIGHT+55.0));
	threshold = (int)((float)maxval*(BASO_HEIGHT) / (BASO_HEIGHT + 58.33));
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

	//加权滤波
	for (i = start + 1; i <= end - 1; i++)
		tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
	for (i = start + 3; i <= end - 3; i++)
		tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];

	//加1处理，消除0x00截止符,否则以TEXT格式存入数据库会有问题
	for (i = 0; i < start; i++)
		(*psampledata).basograph[i] = 1;
	for (i = start; i <= end; i++)
		(*psampledata).basograph[i] = tempbuff[i] + 1;
	for (i = end + 1; i < 255; i++)
		(*psampledata).basograph[i] = 1;
	psampledata->basograph[255] = 0;

	//------------------------------------------------
	//判断并格式转换
	sprintf((*psampledata).wbcdata.wbc, "%.2f", wbc);
	sprintf((*psampledata).wbcdata.basp, "%.1f", basop);
	sprintf((*psampledata).wbcdata.bas, "%.2f", baso);
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
*History:
************************************************************/
void QcDataProcess::QcLmneAnalysis(qcresult_info *psampledata)
{
	unsigned int i;
	unsigned char res = 0;		//电阻抗信号
	unsigned char scatter = 0;	//光散射信号

	unsigned short int count_eos = 0;
	unsigned short int count_neu = 0;
	unsigned short int count_lneu = 0;
	unsigned short int count_rneu = 0;
	unsigned short int count_lym = 0;
	unsigned short int count_llym = 0;
	unsigned short int count_rlym = 0;
	unsigned short int count_mono = 0;
	unsigned short int count_rmono = 0;

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

	TRACE("\nLmneAnalysis()====================\n");

	for (i = 0; i < MATRIX_DATA_MAX; i++)
		if (255 == (*psampledata).lmnegraph[i])
			(*psampledata).lmnegraph[i] = 254;

	for (i = 0; i < MATRIX_POINT_MAX; i++)
	{
		res = (*psampledata).lmnegraph[(i << 1)];
		scatter = (*psampledata).lmnegraph[(i << 1) + 1];
		if (scatter >= systemcfg.range.thresholds[NE])
		{
			if (res < systemcfg.range.thresholds[NoE])
				count_noise++;
			else
				count_eos++;
		}
		else if (scatter >= systemcfg.range.thresholds[RMN])
		{
			if (res < systemcfg.range.thresholds[NoN])
				count_noise++;
			else if (res < systemcfg.range.thresholds[LN])
				count_lneu++;
			else if (res < systemcfg.range.thresholds[RN])
				count_neu++;
			else
				count_rneu++;
		}
		else if (scatter >= systemcfg.range.thresholds[NL])
		{
			if (res < systemcfg.range.thresholds[NoN])
				count_noise++;
			else if (res < systemcfg.range.thresholds[LN])
				count_lneu++;
			else if (res < systemcfg.range.thresholds[LMN])
				count_neu++;
			else if (res < systemcfg.range.thresholds[MN])
			{
				if ((res - systemcfg.range.thresholds[LMN])*(systemcfg.range.thresholds[RMN] - systemcfg.range.thresholds[NL]) <
					(systemcfg.range.thresholds[MN] - systemcfg.range.thresholds[LMN])*(scatter - systemcfg.range.thresholds[NL]))
					count_neu++;
				else
					count_mono++;
			}
			else if (res < systemcfg.range.thresholds[RM])
				count_mono++;
			else
				count_rmono++;
		}
		else
		{
			if (res < systemcfg.range.thresholds[NoL])
				count_noise++;
			else if (res < systemcfg.range.thresholds[LL])
				count_llym++;
			else if (res < systemcfg.range.thresholds[AL])
				count_lym++;
			else if (res < systemcfg.range.thresholds[LMU])
				count_rlym++;
			else if (res < systemcfg.range.thresholds[LMD])
			{
				if ((systemcfg.range.thresholds[LMD] - res)*systemcfg.range.thresholds[NL] >
					(systemcfg.range.thresholds[LMD] - systemcfg.range.thresholds[LMU])*scatter)
					count_rlym++;
				else
					count_mono++;
			}
			else if (res < systemcfg.range.thresholds[RM])
				count_mono++;
			else
				count_rmono++;
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
	//noise	
	TRACE("count_noise=%d---------#\n", count_noise);

	//加1处理，消除0x00截止符,否则以TEXT格式存入数据库会有问题
	for (i = 0; i < MATRIX_DATA_MAX - 1; i++)
		(*psampledata).lmnegraph[i] += 1;
	(*psampledata).lmnegraph[MATRIX_DATA_MAX - 1] = 0;

	if (count_blood > 0)	//如果count_bloos为0，除法运算会出现异常
	{
		wbc = atof(psampledata->wbcdata.wbc);
		coefficient = (100 - atof(psampledata->wbcdata.basp)) / count_blood;

		lymp = coefficient*(count_llym + count_rlym + count_lym);
		neup = coefficient*(count_lneu + count_rneu + count_neu);
		monop = coefficient*(count_rmono + count_mono);
		eosp = coefficient*count_eos;

		alyp = coefficient*count_aly;
		licp = coefficient*count_lic;

		lym = wbc*lymp / 100;
		neu = wbc*neup / 100;
		mono = wbc*monop / 100;
		eos = wbc*eosp / 100;

		aly = wbc*alyp / 100;
		lic = wbc*licp / 100;
	}

	//判断并格式转换
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


/***********************************************************
*Function:
*Description:	对接收的数据帧的数据(rdata所指空间)进行
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:
************************************************************/
void QcDataProcess::QcHgbAnalysis(qcresult_info *psampledata)
{
	unsigned int tmp_hgb = 0;
	double hgb = 0.0;
	float a = 0, b = 1.0, c = 0;

	TRACE("\nHgbAnalysis()====================\n");
	tmp_hgb = hgbgraph[0] * 1000 + hgbgraph[1] * 100 + hgbgraph[2] * 10 + hgbgraph[3];
	if (tmp_hgb <= 8310)	//8310 是根据下位机来的数据是tmp_hgb的上限值
	{
		//hgb
		//75ha_add
		a = systemcfg.modify[systemcfg.mode].a[MOD_HGBF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_HGBF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_HGBF];
		hgb = (double)tmp_hgb / 10;		//下位机中乘10，这边要除以10
		hgb = systemcfg.calibration[systemcfg.mode][CAL_HGBF] * fabs(a*hgb*a*hgb + b*hgb + c);
	}
	TRACE("hgb=%.1f---------#\n", hgb);

	//判断并进行格式转换
	sprintf((*psampledata).rbcdata.hgb, "%.1f", hgb);
}


void QcDataProcess::QcRbcAnalysis(qcresult_info *psampledata)
{
	unsigned short int i;
	unsigned short int  tempbuff[256] = { 0 };//分析数据
	unsigned short int count_rbc = 0;
	unsigned int count_hct = 0;
	unsigned int count_mcv = 0;
	//unsigned short int hgb;
	float hgb = 0.0;
	float rbc = 0.0;
	float hct = 0.0;
	float mcv = 0.0;
	double mch = 0.0;
	float mchc = 0.0;
	float rdwcv = 0.0;
	unsigned char start, end;
	unsigned short int maxval = 0;
	unsigned short int count_rbc_amp = 0;	//纵坐标放大后的计数总数	
	unsigned short int maxvol = 0; 		//红细胞分布细胞个数最大值对应的体积
	unsigned short int L1 = 0, L2 = 0;		//计算rdwcv参数，标记
	unsigned int count_temp = 0; 		//计算rdwcv的临时计数变量
	float temp1 = 0.0;
	float temp2 = 0.0;
	float cal = 1.0;
	float		a = 0, b = 1.0, c = 0;
	TRACE("\nRbcAnalysis()====================\n");

	start = systemcfg.range.thresholds[RB1];
	end = systemcfg.range.thresholds[RB2];

	for (i = 0; i < 256; i++)
		tempbuff[i] = ((psampledata->rbcgraph[(i << 1) + 1]) << 8) + psampledata->rbcgraph[i << 1];

	//计算参数，红细胞计数及HCT计数	
	count_rbc = 0;
	count_hct = 0;
	for (i = start; i <= end; i++)
	{
		count_rbc += tempbuff[i];
		count_hct += tempbuff[i] * i;
	}
	TRACE("count_rbc=%d---------#\n", count_rbc);
	TRACE("count_hct=%d---------#\n", count_hct);

	if (count_rbc <= 370370 && count_rbc > 0)
	{
		count_mcv = count_hct / count_rbc;
		TRACE("count_mcv=%d---------#\n", count_mcv);
		//75ha_add
		//hct = count_hct*VOL_RBCPLT*AMP_RBC/10;
		a = systemcfg.modify[systemcfg.mode].a[MOD_RBCF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_RBCF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_RBCF];
		rbc = count_rbc*VOL_RBCPLT;
		rbc = systemcfg.calibration[systemcfg.mode][CAL_RBCF] * fabs(a*rbc*a*rbc + b*rbc + c);  	//体积校正,单位1E12/L	
		//MCV
		a = systemcfg.modify[systemcfg.mode].a[MOD_MCVF];
		b = systemcfg.modify[systemcfg.mode].b[MOD_MCVF];
		c = systemcfg.modify[systemcfg.mode].c[MOD_MCVF];
		mcv = count_mcv*AMP_RBC;	//fL
		mcv = systemcfg.calibration[systemcfg.mode][CAL_MCVF] * fabs(a*mcv*a*mcv + b*mcv + c);

		hct = rbc*mcv / 10;

		hgb = atof((*psampledata).rbcdata.hgb);
		if (rbc < 0.00001)
			mch = 0;
		else
			mch = hgb / rbc;

		if (hct < 0.00001)
			mchc = 0.0;
		else
			mchc = 100 * hgb / hct;

		if (mchc > 999.9 || mchc <0)//异常,会溢出，存不下
			mchc = 0;

		maxval = tempbuff[start];
		for (i = start + 1; i <= end; i++)
			if (tempbuff[i] > maxval)
				maxval = tempbuff[i];
		TRACE("rbc maxval=%d---------#\n", maxval);

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

		count_rbc_amp = tempbuff[start];
		maxval = tempbuff[start];
		maxvol = start;
		for (i = start + 1; i <= end; i++)
		{
			count_rbc_amp += tempbuff[i];
			if (tempbuff[i] > maxval)
			{
				maxval = tempbuff[i];
				maxvol = i;
			}
		}

		if (0 == count_rbc_amp)//保证除数不为0
			count_rbc_amp = 1;

		//RDW-CV
		count_temp = tempbuff[count_mcv];
		//寻找分布宽度标记值L1,L2
		for (L1 = count_mcv - 1, L2 = count_mcv + 1; L1 >= start && L2 <= end; L1--, L2++)
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
		rdwcv = (float)(L2 - L1) / (L2 + L1) * 100;
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

	//判断并格式转换
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
	sprintf((*psampledata).rbcdata.rdw, "%.1f", rdwcv);
}


/***********************************************************
*Function:
*Description:	对接收的数据帧的数据(rdata所指空间)进行
分析(解析判断，并存入sampledata.basograph所指向的空间)
*Called by:
*Params illustration:
*Data Access:
*Other:
*History:
************************************************************/
void QcDataProcess::QcPltAnalysis(qcresult_info *psampledata)
{
	unsigned short int i;
	unsigned char tempbuff[256] = { 0 };
	unsigned short int count_plt = 0;
	unsigned short int count_mpv = 0;
	unsigned int count_pct = 0;
	float plt = 0.0;
	float pct = 0.0;
	float mpv = 0.0;
	float pdw = 0.0;
	unsigned char start, end;
	unsigned short int maxval = 0;
	unsigned short int maxvol = 0; 	//红细胞分布细胞个数最大值对应的体积
	unsigned short int L1 = 0, L2 = 0;	//计算pdw参数，标记
	float temp1 = 0.0;
	float temp2 = 0.0;
	float cal = 1.0;
	float a = 0, b = 1.0, c = 0;
	TRACE("\nPltAnalysis()====================\n");

	for (i = 0; i < 256; i++)	//PLT数据，共256通道
		tempbuff[i] = (*psampledata).pltgraph[i];

	start = systemcfg.range.thresholds[PLT1];
	end = systemcfg.range.thresholds[PLT2];
	plt_threshold = end;

	if (0 == systemcfg.PltRightThresholdMode)
	{
		//求PLT(血小板总数)、PLT体积校正，求PCT(血小板压积)
		count_plt = 0;
		count_pct = 0;
		for (i = start; i <= end; i++)
		{
			count_plt += tempbuff[i];
			count_pct += tempbuff[i] * i;	//一定容积全血中血小板所占的百分比 PCT = PLT*MPV/10000	
		}

		if (count_plt <= 37037 && count_plt > 0)	//确保测试结果<10000，然后使用sprintf转换格式存到数据库中没有问题
		{
			//求MPV(平均血小板体积)
			//此放大倍数比红细胞大，值也可能比MCV大
			count_mpv = count_pct / count_plt;

			a = systemcfg.modify[systemcfg.mode].a[MOD_PCTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PCTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PCTF];
			pct = count_pct*VOL_RBCPLT*AMP_PLT / 10;
			pct = fabs(a*pct*a*pct + b*pct + c);

			//plt
			a = systemcfg.modify[systemcfg.mode].a[MOD_PLTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLTF];
			plt = count_plt*1000.0*VOL_RBCPLT;
			plt = systemcfg.calibration[systemcfg.mode][CAL_PLTF] * fabs(a*plt*a*plt + b*plt + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_MPVF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_MPVF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_MPVF];
			mpv = count_mpv*AMP_PLT;
			mpv = fabs(a*mpv*a*mpv + b*mpv + c);
			//----------------------------------------

			//PLT的计数较少，相邻体积之间的计数形不成光滑曲线，只能几个点取平均值，然后再形成曲线
			//256个数据分成64*4，取64组的平均值放在本组的第二个(也可以放第三个)
			for (i = 0; i < 64; i++)
				tempbuff[1 + 4 * i] = (float)(tempbuff[4 * i] + tempbuff[1 + 4 * i] + tempbuff[2 + 4 * i] + tempbuff[3 + 4 * i]) / 4;

			//找最大值
			maxvol = 1;
			maxval = tempbuff[1];
			for (i = 1; 4 * i + 1 < end; i++)
			{
				if (tempbuff[4 * i + 1] > maxval)
				{
					maxval = tempbuff[4 * i + 1];
					maxvol = 4 * i + 1;
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
			{
				int pointnum = 4;

				for (i = 0; i < 63; i++)
				{
					tempbuff[2 + pointnum*i] = (float)(tempbuff[5 + pointnum*i] - tempbuff[1 + pointnum*i]) / pointnum + tempbuff[1 + pointnum*i];
					tempbuff[3 + pointnum*i] = (float)(tempbuff[5 + pointnum*i] - tempbuff[1 + pointnum*i]) * 2 / pointnum + tempbuff[1 + pointnum*i];
					tempbuff[4 + pointnum*i] = (float)(tempbuff[5 + pointnum*i] - tempbuff[1 + pointnum*i]) * 3 / pointnum + tempbuff[1 + pointnum*i];
				}
				tempbuff[254] = tempbuff[253] * 2 / 3;
				tempbuff[255] = tempbuff[253] * 1 / 3;
			}

			//加权滤波	
			for (i = start + 1; i <= end - 1; i++)
				tempbuff[i] = 0.4*tempbuff[i - 1] + 0.4*tempbuff[i] + 0.2*tempbuff[i + 1];
			//加权滤波	
			for (i = start + 3; i <= end - 3; i++)
				tempbuff[i] = 0.3*tempbuff[i - 2] + 0.3*tempbuff[i - 1] + 0.2*tempbuff[i] + 0.1*tempbuff[i + 1] + 0.1*tempbuff[i + 1];

			maxval = tempbuff[start];
			maxvol = start;
			for (i = start + 1; i <= end; i++)
				if (tempbuff[i] > maxval)
				{
					maxval = tempbuff[i];
					maxvol = i;
				}

			for (L1 = start; L1 < maxvol; L1++)
			{
				if ((1.0*tempbuff[L1] / maxval) > 0.2)
					break;
			}
			for (L2 = end; L2 > maxvol; L2--)
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

		for (i = 0; i < start; i++)
			(*psampledata).pltgraph[i] = 1;
		for (i = start; i <= end*PLT_WIDTH / 255; i++)       //20141124_75ha_temp:有效数据不能超出右界标
			(*psampledata).pltgraph[i] = tempbuff[i] + 1;
		for (i = end*PLT_WIDTH / 255 + 1; i < 255; i++)
			(*psampledata).pltgraph[i] = 1;
		psampledata->pltgraph[255] = 0;
	}

	else// 1 == systemcfg.PltRightThresholdMode
	{
		uchar			oribuff[256] = { 0 };
		bool				FindMax_EN = true;
		uchar 			maxnum = 0;
		uchar			minnum = 0;
		unsigned int 		minval = 0;
		unsigned int 		transnum = 0;
		uchar 			tempnum1 = 0;
		uchar 			tempnum2 = 0;
		int				j;
		uchar			methodUsed = 4;
		uchar			EffectiveBorder = end;

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
			FindMax_EN = false;
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
				FindMax_EN = true;
			}
		}
		//谷底值
		minnum = maxnum;	//[maxnum,139]	
		minval = tempbuff[maxnum - 1] + tempbuff[maxnum] + tempbuff[maxnum + 1];

		for (i = maxnum + 1; i < 139; i++)	//FDparam 和DSP统一起来 140是DSP采集信号的上限	//xx21
			if (tempbuff[i - 1] + tempbuff[i] + tempbuff[i + 1] <= minval)
			{
				minnum = i;
				minval = tempbuff[i - 1] + tempbuff[i] + tempbuff[i + 1];
			}
		minval = (tempbuff[minnum - 1] + tempbuff[minnum] + tempbuff[minnum + 1]) / 3;
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

		if (maxval != 0)
			cal = (float)PLT_HEIGHT / maxval;
		else
			cal = 1.0;

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
			plt_threshold = minnum * 255 / PLT_WIDTH;
		}
		else if (methodUsed == 3 || methodUsed == 4)
			EffectiveBorder = systemcfg.range.thresholds[PLT2];
		//----------------------------------------		
		//求PLT(血小板总数)、PLT体积校正，求PCT(血小板压积)
		count_plt = 0;
		count_pct = 0;
		for (j = start; j <= EffectiveBorder; j++)     //
		{
			count_plt += oribuff[j];
			count_pct += oribuff[j] * j;	//一定容积全血中血小板所占的百分比 PCT = PLT*MPV/10000	
		}
		if (count_plt <= 37037 && count_plt > 0)	//确保测试结果<10000，然后使用sprintf转换格式存到数据库中没有问题
		{
			//求MPV(平均血小板体积)
			//此放大倍数比红细胞大，值也可能比MCV大
			count_mpv = count_pct / count_plt;
			//---------------------------------
			a = systemcfg.modify[systemcfg.mode].a[MOD_PCTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PCTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PCTF];
			pct = count_pct*VOL_RBCPLT*AMP_PLT / 10;
			pct = fabs(a*pct*a*pct + b*pct + c);

			//plt
			a = systemcfg.modify[systemcfg.mode].a[MOD_PLTF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_PLTF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_PLTF];
			plt = count_plt*1000.0*VOL_RBCPLT;
			plt = systemcfg.calibration[systemcfg.mode][CAL_PLTF] * fabs(a*plt*a*plt + b*plt + c);

			a = systemcfg.modify[systemcfg.mode].a[MOD_MPVF];
			b = systemcfg.modify[systemcfg.mode].b[MOD_MPVF];
			c = systemcfg.modify[systemcfg.mode].c[MOD_MPVF];
			mpv = count_mpv*AMP_PLT;
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

		for (i = 0; i < start; i++)
			(*psampledata).pltgraph[i] = 1;
		for (i = start; i <= end*PLT_WIDTH / 255; i++)       //75ha:有效数据不能超出右界标
			(*psampledata).pltgraph[i] = tempbuff[i] + 1;
		for (i = end*PLT_WIDTH / 255 + 1; i < 255; i++)
			(*psampledata).pltgraph[i] = 1;
		psampledata->pltgraph[255] = 0;
	}

	//判断和格式转换,可放在滤波之前
	//PLT
	sprintf((*psampledata).pltdata.plt, "%.0f", plt);
	//PCT
	sprintf((*psampledata).pltdata.pct, "%.2f", pct);
	//MPV
	sprintf((*psampledata).pltdata.mpv, "%.2f", mpv);
	//PDW
	sprintf((*psampledata).pltdata.pdw, "%.1f", pdw);
}


