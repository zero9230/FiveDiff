//****************************************
//**  Copyright  (C)  USBIO  2011-2031  **

//****************************************
//**  DLL for USB interface chip USB2uis**
//**                            **
//****************************************
//
// USB转UART,I2C,SPI 应用层接口库 V1.0
// 作者: USB2uis  antony.wang
// USB2uis.DLL  V1.0
// 运行环境: Windows XP vista window7

/***************history*******************
v1.0:
 1>  created        2011.12.07   by antony
*****************end*********************/

#ifndef		USBIO_H
#define		USBIO_H
#define DllExport extern "C"__declspec(dllimport)
#define FM_TIRGER_FUNCTION
//#ifdef __cplusplus
//extern "C" {
//#endif



// 设备事件通知回调程序
// 设备事件和当前状态(在下行定义): 0=设备拔出, 0x80=设备插入
//typedef	 VOID (CALLBACK* USB_MONITOR_CALLBACK )(BYTE iDevStatus);
//typedef  VOID (CALLBACK* USB_TRIG_CALLBACK )(DWORD iTrigInfo);
 typedef	 VOID (CALLBACK* USB_DLL_CALLBACK )(BYTE iDevIndex, DWORD iDevStatus);
//iTrigInfo定义 

//bit0~7定义触发类型 bit8~15 附加信息,高16位保留
   
#define EXT_IO_TRIG          0xAA    //外部IO中断触发 
#define SPI_READ_TRIG        0xB0    //SPI预读请求,bit7~bit15   读请求长度 0~255分别代表1~256字节
#define SPI_WRITE_TRIG       0xB1    //SPI写请求,  bit7~bit15   写请求长度 0~255分别代表1~256字节
#define SPI_INIT_READ_TRIG   0xB2    //SPI指示回到读起始位置(实际上是重新读,只针对读写长度大于256的数据段)
#define SPI_INIT_WRITE_TRIG  0xB3    //SPI指示回到写起始位置(实际上是重新写,只针对读写长度大于256的数据段)
#define I2C_READ_TRIG        0xC0    //I2C预读请求,bit7~bit15   读请求长度 0~255分别代表1~256字节
#define I2C_WRITE_TRIG       0xC1    //I2C写请求,  bit7~bit15   写请求长度 0~255分别代表1~256字节

//取得设备软件版本号
DllExport bool                    //TRUE：成功
		  USBIO_GetVersion(
							BYTE byIndex ,        // 设备号,
							BYTE byType,         //0->DLL版本信息;1->驱动程序版本信息;2->固件版本信息
							LPVOID lpBuffer      //用来保存版本信息的缓存
							);

 //取得可以同时打开的设备数最大值
DllExport BYTE                     //返回设备数
					   USBIO_GetMaxNumofDev(
											void
											);

//取得指定设备号的序列号
DllExport BYTE      //返回当前设备状态   0->当前设备不存在; 1->未使用;  2->使用中

						USBIO_GetSerialNo
										   (
											 BYTE byIndex,     // 设备号,
											 char* lpBuff
										   );

//取得指定设备号的设备路径
DllExport char*      //返回设备路径指针,如果是NULL,指定设备不存在
						USBIO_GetDevicePath
										   (
											 BYTE byIndex     // 设备号,
										   );
//得到当前工作模式
/*
   *lpMode == 0x02 -->正常模式;
			  0x01 -->升级模式;
*/
DllExport bool                  //TRUE：获取成功
						USBIO_GetWorkMode
							(
                               BYTE byIndex,         //设备号
							   BYTE* lpMode          //存取模式值的指针
							);
//复位设备
 /*
#define DEV_UART     0x80             //unused
#define DEV_I2C      0x81
#define DEV_SPI      0x82
#define DEV_HDQ      0x83
#define DEV_CAN      0x84             //unused
#define DEV_GPIO     0x85
#define DEV_ADC      0x86
#define DEV_PWM      0x87
#define DEV_PARALLEL 0x88             //unused
#define DEV_CE       0x8D             //unused
#define DEV_TRIG     0x8E             //unused
#define DEV_ALL      0x8F
*/
DllExport bool                    //TRUE：复位成功
		  USBIO_ResetDevice(
							BYTE byIndex,         // 设备号
							BYTE byDevId          //设备类型
		 );

//设置回调函数，用来处理USB插拔事件

DllExport void   USBIO_SetUSBNotify(
                           bool bLog,
						   USB_DLL_CALLBACK pUSB_CallBack      //USB回调函数指针
						   );

//设置回调函数，用来处理IO触发事件
DllExport void
		 USBIO_SetTrigNotify(
							 BYTE byIndex,          //设备号
							 USB_DLL_CALLBACK pTrig_CallBack   //触发回调函数指针
							 );

// 按指定序列号打开一个USB2uis设备,一般从0开始,如果是返回0xFF,打开不成功
DllExport BYTE
		 USBIO_OpenDeviceByNumber(
							 char* pSerialString     //设备序列号
							 );

DllExport  BYTE               // 随机打开一个USB2uis设备,一般从0开始,如果是返回0xFF,打开不成功
		 USBIO_OpenDevice   (
								void
							  );


DllExport bool
          USBIO_CloseDevice  (                       // 关闭一个USB2uis设备
							   BYTE byIndex          //设备号
							  );

DllExport bool
 USBIO_I2cSetConfig          (                        //配置I2c接口
                               BYTE byIndex,          //设备号
							   BYTE byDevAddr,        //设备地址
							   BYTE byRate,           //I2c时钟频率,0~3 单位100k~400k
							   DWORD dwMilliseconds   //I2c读写超时,单位:毫秒 ;低16bit为读超时,高16bit为写超时
                               );
DllExport bool
 USBIO_I2cGetConfig          (                        //取得I2c接口配置
                               BYTE byIndex,           //设备号
							   BYTE* pbyDevAddr,        //设备地址
							   BYTE* byRate,           //I2c时钟频率,0~3 单位100k~400k
							   DWORD* pdwMilliseconds   //I2c读写超时,单位:毫秒 ;低16bit为读超时,高16bit为写超时
                               );

DllExport bool                                //实际读入的字节数
 USBIO_I2cRead               (                       //从I2c接口读数据
							   BYTE byIndex,         //设备号
							   BYTE byDevAddr,       //i2c设备地址
							   LPVOID lpParaBuffer,  //用来保存在读I2c数据之前要写入的命令或地址
							   BYTE  byParaSize,     //要写入的数据缓存长度,如果不需要写入,设为0
							   LPVOID lpReadBuffer,   //读入数据缓存
							   WORD wReadSize         //请求读入数据长度
							   );
DllExport bool                                       //实际写入的字节数
 USBIO_I2cWrite              (                       //写数据到I2c接口
							   BYTE byIndex,         //设备号
							   BYTE byDevAddr,       //i2c设备地址
							   LPVOID lpParaBuffer,  //用来保存在写I2c数据之前要写入的命令或地址
							   BYTE  byParaSize,     //要写入的命令或地址长度,如果不需要写入,设为0
							   LPVOID lpWriteBuffer,  //写入数据缓存
							   WORD dWriteSize      //请求写入的数据长度
							   );
 DllExport bool                              //实际读入的字节数
   USBIO_I2cReadEEProm       (                       //读数据到I2c接口
							   BYTE byIndex,         //设备号
							   BYTE byDevAddr,       //i2c设备地址
							   BYTE byTypeIndex,     //EEProm 型号 0~12 对应24C01~24C4096
							   DWORD dwOffset,       //EEProm 起始地址
							   BYTE* lpReadBuffer,   //读入数据缓存
							   WORD wReadSize        //请求读入数据长度
							   );
 DllExport bool                               //实际写入的字节数
   USBIO_I2cWriteEEProm      (                        //写数据到I2c接口
							   BYTE byIndex,          //设备号
							   BYTE byDevAddr,        //i2c设备地址
							   BYTE byTypeIndex,      //EEProm 型号 0~12 对应24C01~24C4096
							   DWORD dwOffset,         //EEProm 起始地址
							   BYTE* lpWriteBuffer,    //写入数据缓存
							   WORD dWriteSize          //请求写入的数据长度
							   );

 DllExport bool
 USBIO_SPISetConfig          (
							  BYTE byIndex,          //设备号
							  BYTE byRate,           //低四位是波特率 0~8 对应200k,400k,600k,800k,1000k,2000k,4000k,6000k,12000K
													  //bit4~bit5是SPI工作模式0~3  00=>(POL=0,PHA=0); 01=>(POL=0,PHA=1);10=>(POL=1,PHA=0);11=>(POL=1,PHA=1)
													  //bit6 未用
													  //bit7 SPI设备类型  0=>主设备; 1=>从设备
							  DWORD dwMilliseconds    //SPI读写超时,单位:毫秒 ;低16bit为读超时,高16bit为写超时
							  );
 DllExport bool
 USBIO_SPIGetConfig  	     (
							  BYTE byIndex,           //设备号
							  BYTE* pbyRate,          //低四位是波特率 0~8  对应200k,400k,600k,800k,1000k,2000k,4000k,6000k,12000K
													  //bit4~bit5是SPI工作模式0~3  00=>(POL=0,PHA=0); 01=>(POL=0,PHA=1);10=>(POL=1,PHA=0);11=>(POL=1,PHA=1)
													  //bit6 未用
													  //bit7 SPI设备类型  0=>主设备; 1=>从设备
							  DWORD* pdwMilliseconds  //SPI读写超时,单位:毫秒;低16bit为读超时,高16bit为写超时
							  );
 DllExport bool
 USBIO_SPIRead              (
							  BYTE byIndex,           //设备号
							  LPVOID lpComBuffer,     //用来保存在读SPI数据之前要写入的命令
							  BYTE  byComSize,        //要写入的命令长度,如果不需要写入,设为0
							  LPVOID lpBuffer,        //读入数据缓存
							  WORD wBuffSize          //请求读入数据长度
							  );
 DllExport bool
 USBIO_SPIWrite              (
							  BYTE byIndex,            //设备号
							  LPVOID lpComBuffer,      //用来保存在读SPI数据之前要写入的命令
							  BYTE  byComSize,         //要写入的命令长度,如果不需要写入,设为0
							  LPVOID lpBuffer,         //写入数据缓存
							  WORD wBuffSize            //请求写入数据长度
							  );
 DllExport bool
  USBIO_HDQSetConfig         (
							  BYTE byIndex,            //设备号
							  DWORD dwMilliseconds,    //HDQ读写超时
							  BYTE* lpParaBuffer,      //HDQ时序参数  一个指向struct { 	WORD tCYCH,tHW1,tHW0,tBreak,tBR,tCYCD_min,tCYCD_max,tDW1_min,tDW1_max,tDW0_min,tDW0_max,tTO}的指针;}
							  BYTE byParaSize          //HDQ时序参数长度 ，固定为24
							  );
 DllExport bool
 USBIO_HDQGetConfig          (
							  BYTE byIndex,        //设备号
							  DWORD* pdwMilliseconds,    //HDQ读写超时
							  BYTE* lpParaBuff,      //HDQ时序参数  一个指向struct { 	WORD tCYCH,tHW1,tHW0,tBreak,tBR,tCYCD_min,tCYCD_max,tDW1_min,tDW1_max,tDW0_min,tDW0_max,tTO}的指针;
							  BYTE byParaSize       //HDQ时序参数长度 ，固定为24
							  );
 DllExport bool
 USBIO_HDQWrite              (
							  BYTE byIndex,         //设备号
							  BYTE addr,             //HDQ设备地址,必须在0~0x7F之间
							  LPVOID lpBuffer,      //写入缓存
							  BYTE wBuffSize        //写入数据长度，BYTE mode为1，WORD mode 为2
							  );
 DllExport bool
 USBIO_HDQRead               (
							  BYTE byIndex,       //设备号
							  BYTE addr,          //HDQ设备地址,必须在0~0x7F之间
							  LPVOID lpBuffer,    //读入缓存
							  WORD wBuffSize      //读入数据长度，BYTE mode为1，WORD mode 为2
							  );
 DllExport bool
 USBIO_SetCE                  //           设置HDQ引脚电平
							 (
							  BYTE byIndex,      //设备号
							  bool bHigh         //true 为高电平, false 为低电平
							 );
 DllExport bool
 USBIO_GetCE                (
							  BYTE byIndex,      //设备号
							  BYTE* pbyLevel     //指向CE pin电平的指针 1为高电平, 0为低电平
							  ) ;

 DllExport bool
 USBIO_GetGPIOConfig         (                   //获取GPIO方向配置 1为输入,0为输出
							  BYTE byIndex,      //设备号
							  BYTE* pbyValue      //读入缓存指针   b0~b7分别对应J7-10~J7~3
							  );

DllExport bool
USBIO_SetGPIOConfig          (                   //设置GPIO方向 1为输入,0为输出
							  BYTE byIndex,      //设备号
							  BYTE byValue      //写入缓存   b0~b7分别对应J7-10~J7~3
							  );
 DllExport bool
 USBIO_GPIOWrite             (                   //设置GPIO电平 1为高电平,0为低电平
							  BYTE byIndex,      //设备号
							  BYTE byValue,     //读入缓存   b0~b7分别对应J7-10~J7~3
							  BYTE byMask        //屏蔽设置,   b0~b7位设为1时，该位的值不改变
							  );

DllExport bool
USBIO_GPIORead               (                   //读取GPIO电平 1为高电平,0为输出
							  BYTE byIndex,      //设备号
							  BYTE* pbyValue     //读入缓存指针   b0~b7分别对应J7-10~J7~3
							  );
DllExport bool
USBIO_TrigGetConfig          (
							   BYTE byIndex,    //设备号
							   BYTE* pbySelect  //触发类型指针
							   );

DllExport bool
USBIO_TrigSetConfig          (
							   BYTE byIndex,    //设备号
							   BYTE bySelect    //触发类型  0:上升缘 1:下降缘 2:高电平 3:低电平
							  );

DllExport bool         //进入触发等待状态
USBIO_WaitForTrig               (
							  BYTE byIndex      //设备号
							  );

DllExport bool         //退出触发等待状态
USBIO_ExitTrig               (
							  BYTE byIndex       //设备号
							  );

DllExport bool
USBIO_GetPWMConfig           (
							  BYTE byIndex,      //设备号
							  BYTE* pbyRate,     //PWM波特率 0~10分别对应1k,2k,4k,6k,8k,10k,20k,40k,60k,80k,100k
							  BYTE* pbyNum,      //PWM通道数,低四位表示,第七位指示PWM是否在运行 ,1指示PWM在运行
							  WORD* pwDuty      //大小为4个字的缓存，用来接收四个通道的占空比 ,每个通道的占空比用两个bytes表示
							  );

DllExport bool
USBIO_SetPWMConfig           (
							  BYTE byIndex,     //设备号
							  BYTE byRate,      //PWM波特率 0~10分别对应1k,2k,4k,6k,8k,10k,20k,40k,60k,80k,100k
							  BYTE byNum,       //PWM通道数,低四位表示
							  WORD* pwDuty     //大小为4个字的缓存，存有四个通道的占空比，每个通道的占空比用两个bytes表示
							  );

DllExport bool
USBIO_StartPWM               (
							  BYTE byIndex     //设备号
							 );

DllExport bool
USBIO_StopPWM               (
							  BYTE byIndex     //设备号
							 );

DllExport bool
USBIO_GetADCConfig			(
							 BYTE byIndex,     //设备号
							 BYTE* pbyMask,    //指向ADC通道的开关的指针;Bit0~3分别为通道1~4,如果为1,指示该通道打开
							 BYTE* pbyIOSelect //指向4个byte的指针,每个BYTE对应一个通道的IO选择;低半字节采样通道负极输入选择,高半字节采样通道正极输入选择;
											   //对于正极通道值0~9分别对应J7-03~J7-10,内部温度传感器和VDD
											   //对于负极通道值0~9分别对应J7-03~J7-10,内部参考电压和GND
							 );

DllExport bool
USBIO_SetADCConfig           (
							   BYTE byIndex,    //设备号
							   BYTE byMask,     //指定ADC通道的开关;Bit0~3分别为通道1~4,如果为1,指示该通道打开
							   BYTE* pbyIOSelect //指向4个byte的指针,每个BYTE对应一个通道的IO选择;低半字节采样通道负极输入选择,高半字节采样通道正极输入选择;
												 //对于正极通道值0~9分别对应J7-03~J7-10,内部温度传感器和VDD
											     //对于负极通道值0~9分别对应J7-03~J7-10,内部参考电压和GND
							  );

DllExport bool
USBIO_ADCRead               (
							  BYTE byIndex,         //设备号
							  WORD* lpReadBuffer,   //用来存取ADC采用的数据指针
							  WORD wBuffSize        //指定ADC lpReadBuffer的大小,必须为通道数的倍数  wBuffSize = chan x 采样次数
							 );

DllExport bool
 USBIO_UpdateSector          (                       //更新扇区内容
                               BYTE byIndex,         //设备号
                               WORD wIndex,             //扇区索引
                               LPVOID lpBuffer,   //写入数据缓存，512 bytes
                               BYTE* lpResult       //0x00 -->成功; 0x01 -->命令错 ;0x02-->crc错;0x04-->擦除错
                              );

//#ifdef __cplusplus
//}
//#endif

#endif		// _mUSBIO_PACKET_LENGTH_DLL_H
