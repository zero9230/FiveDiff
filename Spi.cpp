/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Spi.c
Author:	xubinbin	Version:	1.0	Date: 2016-02-25
Description:	Spi总线通讯接口函数
Others:    	// 其它内容的说明
Function List:
History:
*************************************************/
#include "stdafx.h"
#include "Includes_app.h"
#include "Spi.h"

CSpi::CSpi()
{
}

CSpi::~CSpi()
{
}


/*****************************************************
*Function:	check_frame
*Description:	计算帧校验和
*Called by:
*Other:		去除帧同步、帧头、帧尾
*History:	create	wsm		2010.9.9
******************************************************/
unsigned char CSpi::check_frame(unsigned char *pdata, unsigned int len)
{
	unsigned short i;
	unsigned char ret = 0;
	for (i = 0; i < len; i++)
		ret += pdata[i];
	return ret;
}

/*****************************************************
*Function:	open_spi
*Description:	打开SPI总线
*Called by:
*Other:      
*History:	create	wsm		2010.9.9
******************************************************/
int CSpi::open_spi(void)
{
	char serial[15];
	int spi_fd;
	byDevIndex = 0xFF;
	SPI_dev = new DevInfo(DEV_SPI);
	SPI_dev->byRateIndex = 0x04;
	SPI_dev->dwTimeout = 0x00C8000C8;
	
	byDevIndex = USBIO_OpenDevice();//取得设备号
	if (byDevIndex == 0xFF)
	{
		TRACE("打开设备失败!    \n");
		return -1;
	}
	else
	{	
		SetSpiConfig();
		USBIO_GetSerialNo(byDevIndex, serial);
		//SetWindowText(serial);

		USBIO_SPIGetConfig(byDevIndex, &SPI_dev->byRateIndex, &SPI_dev->dwTimeout);
		spi_fd = 0;
	}
	//UpdateController();



	//gpio_cmd(EN_SPI);	//Enable spi communication	
	return (spi_fd);
}
/*****************************************************
*Function:	SetSpiConfig
*Description:	设置制定设备spi接口
*Called by:
*Other: 		
*History:	create	wsm		2010.9.9
******************************************************/
void CSpi::SetSpiConfig()
{
	BYTE byRate;
	DWORD dwTimeout;
	byRate = 0 + (1 << 4);//0表示波特率为200K，1<<4表示模式1
	dwTimeout = 200 + (200 << 16);
	if (USBIO_SPISetConfig(byDevIndex, byRate, dwTimeout))
	{
		SPI_dev->byRateIndex = byRate;
		SPI_dev->dwTimeout = dwTimeout;
	}
	//UpdateController();
}
/*****************************************************
*Function:	close_spi
*Description:	关闭SPI总线
*Called by:
*Other: 		gpio_cmd(DISABLE_SPI)即SPI从设备(DSP)使能无效
*History:	create	wsm		2010.9.9
******************************************************/
int CSpi::close_spi(int spi_fd)
{
	char serial[15] = { 0 };
	if (spi_fd < 0)
	{
		return -1;
	}
	else
	{
		if (byDevIndex != 0xFF)
		{
			if (USBIO_CloseDevice(byDevIndex) == false)
			{
				TRACE("关闭设备失败!    \n");
				return -1;
			}
			byDevIndex = 0xFF;
		}
	}
	return 0;
}

/***********************************************************
*Function:	make_frame
*Description:	制作帧
*Called by:	send_frame
*Params illustration:  sdata[] :制作帧的原始数据
frametype:	制作帧的数据类型
pp_MyFrame:制作后的帧(为什么用指针的指针，暂时不改它
*Other:
*History:	create	wsm		2010.9.9
************************************************************/
void CSpi::make_frame(unsigned char sdata[], unsigned char frametype, unsigned char *psendframe)
{
	int i;
	unsigned char *pmyframe = NULL;
	pmyframe = psendframe;
	*pmyframe++ = SPI_FM_SYNC;
	*pmyframe++ = SPI_FM_HEADER;
	*pmyframe++ = frametype;
	for (i = 0; i < framelen[frametype]; i++)
		*pmyframe++ = sdata[i];
	*pmyframe++ = check_frame(sdata, framelen[frametype]);
	*pmyframe = SPI_FM_END;
}

/***********************************************************
*Function:	send_frame
*Description:	发送帧
*Called by:
*Params illustration:	sdata[] :发送帧的原始数据
frametype:	发送帧的类型
*Other:	发送各种类型的帧DSP
*History:	create	wsm		2010.9.9
************************************************************/
/*int CSpi::send_frame(unsigned char *sdata, unsigned char frametype)
{
	int spi_fd;
	unsigned char *psendframe = NULL;
	BYTE Temp[128];
	BYTE comLen;
	AfxMessageBox(_T("发送成功1"));

	if ((spi_fd = open_spi()) < 0)
		return -1;
	//帧长度要加上这五帧sync, head,type, cs, end   
	AfxMessageBox(_T("发送成功1"));
	if ((psendframe = (unsigned char *)malloc(framelen[frametype] + 5)) == NULL)
	{
		TRACE("malloc failed during send_frame---------!\n");
		exit(1);
	}
	make_frame(sdata, frametype, psendframe);	//send frame length is normally 5  
	comLen = sizeof(psendframe) / 2;
	//if (comLen)
		//StrToVal(Temp, psendframe);
	AfxMessageBox(_T("发送成功2"));
	if (USBIO_SPIWrite(byDevIndex, psendframe, framelen[frametype] + 5, (void*)SPI_dev->GetWriteBuf(), SPI_dev->GetWriteCnt()) == 0)//通过指定的设备的 SPI 接口写数据
	{
		TRACE("write to spi_fd failed---------!\n");
		return -1;
	}

	free(psendframe);
	psendframe = NULL;
	close_spi(spi_fd);
	AfxMessageBox(_T("发送成功3"));
	return 0;
}*/

int CSpi::send_frame(unsigned char *sdata, unsigned char frametype)
{
	int spi_fd;
	unsigned char *psendframe = NULL;
	unsigned char *psendframe2 = NULL;
	BYTE Temp[128];
	BYTE comLen;
	if ((spi_fd = open_spi()) < 0)
		return -1;
	//帧长度要加上这五帧sync, head,type, cs, end   
	if ((psendframe = (unsigned char *)malloc(framelen[frametype] + 5)) == NULL)
	{
		TRACE("malloc failed during send_frame---------!\n");
		exit(1);
	}
	make_frame(sdata, frametype, psendframe);	//send frame length is normally 5  
	comLen = sizeof(psendframe) / 2;
	//if (comLen)
	//StrToVal(Temp, psendframe);
	int len = framelen[frametype] + 5;
	psendframe2 = psendframe;
	while (len > 0)
	{
		if (USBIO_SPIWrite(byDevIndex, psendframe2, 1, (void*)SPI_dev->GetWriteBuf(), SPI_dev->GetWriteCnt()) == 0)//通过指定的设备的 SPI 接口写数据
		{
			TRACE("write to spi_fd failed---------!\n");
			return -1;
		}
		//AfxMessageBox(*psendframe);
		psendframe2++;
		len--;
	}
	free(psendframe);
	psendframe2 = NULL;
	psendframe = NULL;
	close_spi(spi_fd);
	return 0;
}
/***********************************************************
*Function:	receive_frame
*Description:	接受帧,将接受的状态实时通知到主界面
*Called by:
*Params illustration:
*Other:	接受模式，通过向DSP发送伪码0xFF
从而接受DSP上传的数据帧
*History:	create	wsm		2010.9.9
************************************************************/
int CSpi::receive_frame(unsigned char *rdata, unsigned char frametype)
{
	int spi_fd, i;
	int retu;
	int tout = SPI_TIMEOUT;
	unsigned char *receivebuff = NULL;
	unsigned char *temp = NULL;
	temp = (unsigned char *)malloc(1);
	if ((spi_fd = open_spi()) < 0)
		return -1;
	//实际帧长要加上这五帧sync, head,type, cs, end   	
	if ((receivebuff = (unsigned char *)malloc(framelen[frametype] + 5)) == NULL)//申请的内存在函数返回前要释放
	{
		TRACE("malloc failed during receive_frame---------!\n");
		exit(1);
	}

	do
	{
		//if (USBIO_SPIRead(byDevIndex, receivebuff, 1, (void*)SPI_dev->GetWriteBuf(), SPI_dev->GetWriteCnt())==0)
		if (USBIO_SPIRead(byDevIndex, 0, 0, receivebuff, 1) == 0)//USBIO_SPIRead(byDevIndex, receivebuff, 1, receivebuff, 1)
		{
			TRACE("read spi_fd failed---------!\n");
			return -1;
		}
		TRACE("receivebuff:%X---------#\n", receivebuff[0]);
		tout--;
	} while ((*receivebuff) != 0x02 && tout);//
	if (!tout)
	{
		//向所需窗口发送接受超时错误消息，接受数据错误
		TRACE("SPI_TIMEOUT---------!\n");
		//return -1;//超时错误
		retu = -1;
	}
	else
	{
		TRACE("sync:%X---------#\n", receivebuff[0]);
		//USBIO_SPIRead(byDevIndex, receivebuff, framelen[frametype] + 4, (void*)SPI_dev->GetWriteBuf(), SPI_dev->GetWriteCnt());
		int len = framelen[frametype] + 4;
		int index = 0;
		while (len > 0)
		{
			USBIO_SPIRead(byDevIndex, 0, 0, temp, 1);
			receivebuff[index] = *temp;
			index++;
			len--;
		}
		//USBIO_SPIRead(byDevIndex, receivebuff, framelen[frametype] + 4, receivebuff, framelen[frametype] + 4);
		if (receivebuff[0] == 0x68 && receivebuff[framelen[frametype] + 3] == 0x16)
		{
			TRACE("head:%X---------#\n", receivebuff[0]);
			if (receivebuff[1] == frametype)
			{
				TRACE("frametype:%X---------#\n", receivebuff[1]);
				if (receivebuff[framelen[frametype] + 2] == check_frame(receivebuff + 2, framelen[frametype]))
				{
					for (i = 0; i < framelen[frametype]; i++)
					{
						rdata[i] = receivebuff[i + 2];
						TRACE("i:%d----------#\n",i);
						TRACE("rxdata:%X---------#\n", rdata[i]);
					}
					TRACE("cs:%X---------#\n", receivebuff[framelen[frametype] + 2]);
					TRACE("tail:%X---------#\n", receivebuff[framelen[frametype] + 3]);
					//return 0;	
					retu = 0;
				}
				else
				{
					TRACE("**********frame check error*********************\n");
					//向所需窗口放送接受数据错误消息
					//return -4;//帧校验错误
					retu = -4;
				}
			}
			else
			{
				TRACE("frametype:%X---------#\n", receivebuff[1]);
				TRACE("**********frame type error****************\n");
				//向所需窗口发送接受数据错误消息
				//return -3;//帧类型错误	
				retu = -3;
			}
		}
		else
		{
			TRACE("head:%X---------#\n", receivebuff[0]);
			TRACE("tail:%X---------#\n", receivebuff[framelen[frametype] + 3]);
			TRACE("**********frame structure error**************\n");
			//向所需窗口发送接受数据错误消息
			//return -2;	//帧结构错误
			retu = -2;
		}
	}
	//TRACE("rxdata:%X---------#\n", rdata[0]);
	free(receivebuff);
	free(temp);
	receivebuff = NULL;
	temp = NULL;
	close_spi(spi_fd);
	return retu;
	//向所需窗口发送成功接受数据消息
}
//=============================//


