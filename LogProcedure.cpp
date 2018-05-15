#include "StdAfx.h"
#include "LogProcedure.h"
//#include "locale.h"
//#include "Includes_app.h"
CLogProcedure::CLogProcedure()
{


}

CLogProcedure::~CLogProcedure()
{

}


void CLogProcedure::WriteRecord(CString inputstring)
{

	CStdioFile myfile;
	CTime time;
	time = CTime::GetCurrentTime();

	if (!myfile.Open(_T("./Log/test.log"), CFile::modeCreate | CFile::modeWrite | CFile::modeRead| CFile::modeNoTruncate))
	{
		AfxMessageBox(_T("创建初始化文件失败！"));
		return ;
	}
	
	CString strTemp;
	int num;
	strTemp.Format(_T("%s---%s---\n"), time.Format("%Y-%m-%d %H:%M:%S"),inputstring);
	num= myfile.GetLength();
	myfile.SeekToEnd();
	myfile.WriteString(strTemp);
	myfile.Close();
	return ;

}

void CLogProcedure::ReadRecord()
{
	CString tmp, str;
	CStdioFile file;
	try{
		int i = file.Open(_T("test.log"), CFile::modeRead);
		if (i == 0)
			return;
	}
	catch (CFileException *e)
	{
		TCHAR szBuf[256];
		e->GetErrorMessage(szBuf, 256, NULL);
		//MessageBox(szBuf, _T("Warning"));
		e->Delete();
	}
	while (1)
	{
		DWORD i = file.ReadString(str);
		if (i == 0)goto end;
		tmp += str;
		tmp += "\r\n";
	}
	end:
	m_edlog.SetWindowText(tmp);
}
