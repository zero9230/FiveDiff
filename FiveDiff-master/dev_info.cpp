
#include "stdafx.h"

#include "dev_info.h"
//------------------------------------------------------------------------------
  DevInfo::DevInfo(enu_dev id)
  {
	devID = id;
	bRunning = false;
	byRateIndex = 0;
	dwTimeout = (200<<16)+200;
	dwReadCnt = 0;
	pReadBuf = NULL;
	dwWriteCnt = 0;
	pWriteBuf = NULL;
	pMyData = NULL;
  }
//------------------------------------------------------------------------------
  DevInfo::~DevInfo()
  {
	if(pReadBuf)
	  delete pReadBuf;
	if(pWriteBuf)
	  delete pWriteBuf;
	if(pMyData)
	 delete pMyData;
  }
//------------------------------------------------------------------------------
  enu_dev DevInfo::GetDevId()
  {
	return devID;
  }
//------------------------------------------------------------------------------
  DWORD DevInfo::GetReadCnt()
  {
	return dwReadCnt;
  }
//------------------------------------------------------------------------------
  DWORD DevInfo::GetWriteCnt()
  {
	return  dwWriteCnt;
  }
//------------------------------------------------------------------------------
  BYTE* DevInfo::GetReadBuf()
  {
	return pReadBuf;
  }
//------------------------------------------------------------------------------
  BYTE* DevInfo::GetWriteBuf()
  {
    return pWriteBuf;
  }

//------------------------------------------------------------------------------
  void DevInfo::PutReadBuf(BYTE* pStr,DWORD dwLen)
  {
	BYTE* pNew = new BYTE[dwReadCnt+dwLen];
	memcpy(pNew,pReadBuf,dwReadCnt);
	memcpy(&pNew[dwReadCnt],pStr,dwLen);
	dwReadCnt = dwReadCnt+dwLen;
	delete pReadBuf;
	pReadBuf = pNew;
  }
//------------------------------------------------------------------------------
  void DevInfo::WriteBufUpdate(BYTE* pStr,DWORD dwLen)
  {
	delete pWriteBuf;
	pWriteBuf = new BYTE[dwLen];
	memcpy(pWriteBuf,pStr,dwLen);
	dwWriteCnt = dwLen;
  }
//------------------------------------------------------------------------------
  void DevInfo::ReadBufClear()
  {
   delete pReadBuf;
   pReadBuf = NULL;
   dwReadCnt = 0;
  }

  //------------------------------------------------------------------------------
  void DevInfo::WriteBufClear()
  {
   delete pWriteBuf;
   pWriteBuf = NULL;
   dwWriteCnt = 0;
  }

 void* DevInfo::GetData()
 {
   return pMyData;
 }

 void  DevInfo::SetData(void* pData)
 {
   if(pMyData)
   {
	 delete pMyData;
   }
   pMyData = pData;
 }



