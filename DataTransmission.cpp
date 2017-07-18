#include "stdafx.h"
#include "Includes_app.h"


DataTransmission::DataTransmission()
{
}


DataTransmission::~DataTransmission()
{
}


void DataTransmission::doGetNormalData(int	loop_times, uchar CMD, uchar DataType, uchar* target, const char* strFlag)
{
	unsigned int		i;

	for (i = 0; i < loop_times; i++)	//循环三次，防止数据传输异常
	{
		sdata_cmd[0] = CMD;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (0 == PC_RECEIVE_FRAME(target, DataType))
			break;
	}
	if (i == loop_times)
		fprintf(stderr, "Error: \"Get data of normal test \" --%s\n", strFlag);
}

void DataTransmission::GetNormalData_BASO(sample_info* psampledata)
{
	doGetNormalData(3, SPI_CMD_REQBASO, SPI_TYPE_BASORES, (uchar*)psampledata->basograph, "BASO");
	doGetNormalData(3, SPI_CMD_REQBASO_2, SPI_TYPE_BASORES, basograph_2, "BASO_2");
}

void DataTransmission::GetNormalData_LMNE(sample_info* psampledata)
{
	doGetNormalData(6, SPI_CMD_REQLMNE, SPI_TYPE_LMNERES, (uchar*)psampledata->lmnegraph, "LMNE");
}

void DataTransmission::GetNormalData_HGB()
{
	doGetNormalData(3, SPI_CMD_REQHGB, SPI_TYPE_HGBRES, hgbgraph, "HGB");
}

void DataTransmission::GetNormalData_RBC(sample_info* psampledata)
{
	doGetNormalData(3, SPI_CMD_REQRBC, SPI_TYPE_RBCRES, (uchar*)psampledata->rbcgraph, "RBC");
	doGetNormalData(3, SPI_CMD_REQRBC_2, SPI_TYPE_RBCRES, rbcgraph_2, "RBC_2");
}

void DataTransmission::GetNormalData_PLT(sample_info* psampledata)
{
	doGetNormalData(3, SPI_CMD_REQPLT, SPI_TYPE_PLTRES, (uchar*)psampledata->pltgraph, "PLT");
	doGetNormalData(3, SPI_CMD_REQPLT_2, SPI_TYPE_PLTRES, pltgraph_2, "PLT_2");
}

/***********************************************************
*Function:	GetNormalTestData
*Description:	SPI通信接收测试数据
*Called by:
*Params illustration:
*Other:
*History:
************************************************************/
void DataTransmission::GetNormalTestData(uchar TestMode, sample_info* psampledata)
{
	GetNormalData_BASO(psampledata);
	if (WHOLEDIFF == TestMode || DILUENTDIFF == TestMode)		//CBC模式不需要接收Lmne信号
	{
		GetNormalData_LMNE(psampledata);
	}
	GetNormalData_HGB();
	GetNormalData_RBC(psampledata);
	GetNormalData_PLT(psampledata);
}
