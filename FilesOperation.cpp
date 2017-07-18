#include"StdAfx.h"
#include "Includes_app.h"

void ReadSystemcfgFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	ReadFile(hFile, &systemcfg, sizeof(systemcfg), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteSystemcfgFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	WriteFile(hFile, &systemcfg, sizeof(systemcfg), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;

}

void ReadSystemcfg2File()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg2.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	ReadFile(hFile, &systemcfg2, sizeof(systemcfg2), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteSystemcfg2File()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg2.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	WriteFile(hFile, &systemcfg2, sizeof(systemcfg2), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;

}


void ReadSystemcfg3File()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg3.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	ReadFile(hFile, &systemcfg3, sizeof(systemcfg3), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteSystemcfg3File()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//systemcfg3.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	WriteFile(hFile, &systemcfg3, sizeof(systemcfg3), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;

}

void ReadLogFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//logfile.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	ReadFile(hFile, &logfile, sizeof(logfile), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteLogFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//logfile.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	WriteFile(hFile, &logfile, sizeof(logfile), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;

}

void ReadMaintainFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//maintain.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	ReadFile(hFile, &m_sMaintain, sizeof(m_sMaintain), &dwWritenSize, NULL);
	CloseHandle;
}

void WriteMaintainFile()
{
	DWORD dwWritenSize;
	HANDLE hFile = ::CreateFile(_T(".//Config//maintain.dat"),     //创建文件的名称。
		GENERIC_WRITE | GENERIC_READ,          // 写和读文件。
		FILE_SHARE_READ | FILE_SHARE_WRITE,                      // 共享读写。
		NULL,                   // 缺省安全属性。
		OPEN_ALWAYS,          // 如果文件存在，直接打开。
		FILE_ATTRIBUTE_NORMAL, // 一般的文件。      
		NULL);                 // 模板文件为空。
	WriteFile(hFile, &m_sMaintain, sizeof(m_sMaintain), &dwWritenSize, NULL);
	FlushFileBuffers(hFile);
	CloseHandle;
}