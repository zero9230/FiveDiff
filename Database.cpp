/*************************************************
Copyright (C), SINNOWA. Co., Ltd.
File name: 	Database.c
Author:
Description: 	数据库操作函数
Others:       	病人信息表的编号是主关键字，唯一
血液样本的编号是主关键字，唯一
Function List:
1. int OpenDataBase(const char *filename, sqlite3 **ppDb);
数据库打开函数
2.	 int ExeSql(sqlite3 *db, const char *zSql, sqlite3_callback xCallBack);
数据库执行语句
3. int CloseDataBase(sqlite3 *db);
数据库关闭函数
History:
mod	
*************************************************/
#include "stdafx.h"
#include "Includes_app.h"


CString ChartsToCString(char * chart,int len)
{
	CString string;
	int i = 0;
	
	//while (i<len){
	while ((i < len) && (chart[i] != 0)){
		if ((chart[i] >= 0) && (chart[i] <= 9))
			chart[i] += 48;
		/*if (chart[i] == '\x1')
		{
			char temp = 0;
			string += temp;
			break;
		}
		else*/
		{
			string += chart[i];
			i++;
		}
	}
	char a = 0;
	string += a;
	string.Replace('\0', ' ');
	return string;
}

CString ChartsToCStringdata(unsigned char * chart, int len)
{
	CString string;
	int i = 0;

	//while (i<len){
	while ((i < len) && (chart[i]!=0))
	{
		CString final_test1;
		if (chart[i] < 16)
		{
			int a = 0;
			CString temp;
			temp.Format(_T("%d"),a);
			string += temp;
		}
		final_test1.Format(_T("%x"), chart[i]);
		string += final_test1;
		i++;
	}
	char a = 0;
	string += a;
	string.Replace('\0', ' ');
	return string;

}

//------------------------------------------------
//打开数据库

int OpenDataBase(CString filename, _ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs)
{
	CString filename_1;
	filename_1.Format(_T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=%s"), filename);
	try
	{
		CoInitialize(NULL);
		m_pDB = _ConnectionPtr(__uuidof(Connection));
		m_pDB->CursorLocation = adUseClient;
		m_pRs=m_pDB->Open((_bstr_t)filename_1, "", "", adModeUnknown);
		TRACE("连接数据库成功  \n");
	}
	catch (_com_error& e)
	{
		TRACE("连接数据库失败  \n");
		AfxMessageBox(e.Description());
		return -1;
	}
	return 0;

}

//------------------------------------------------
//关闭数据库
int CloseDataBase(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs)
{
	if (m_pRs->State)
	{
		m_pRs->Close();
		m_pRs.Release();
		m_pRs = NULL;
	}
	if (m_pDB->State)
		m_pDB->Close();
	//m_pDB.Release();
	m_pDB = NULL;
	CoUninitialize();
	TRACE("关闭数据库成功  \n");
	return 0;

}
//-------------------------------------------------
//回调函数，获得数据编号
int loadnum(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, unsigned int *param)
{
	int *number;
	number = (int*)param;
	_variant_t var;
	CString strName;
	strName = "";
	try
	{
		if (!m_pRs->BOF){
			//m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空\n");
			return TRUE;
		}
		int num = 0;
		while ((!m_pRs->adoEOF) && (num == 0))
		{
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			num++;
		}
		TRACE(strName);
		*number = _ttoi(strName);
	}
	catch (_com_error &e)
	{
		TRACE("loadnum函数程序异常\n");
	}
	return 0;
}

int loadnum1(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, unsigned int &param)
{
	int var;
	CString strName;
	strName = "";
	try
	{
		if (!m_pRs->BOF)
		{
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空");
			return TRUE;
		}
		unsigned int num = 0;
		while ((!m_pRs->adoEOF))
		{
			//var = m_pRs->GetCollect("NUMBER");
			//if (var != VT_NULL)
			//strName = (LPCSTR)_bstr_t(var);
			num++;
			m_pRs->MoveNext();
		}
		TRACE(strName);
		param = num;
	}
	catch (_com_error &e)
	{
		TRACE("loadnum1函数程序异常");
	}
	return 0;
}
int loadnum_maxnum(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, unsigned int &param)
{
	int var;
	CString strName;
	strName = "";
	try
	{
		if (!m_pRs->BOF)
		{
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空");
			return TRUE;
		}
		unsigned int num = 0;
		while ((!m_pRs->adoEOF))
		{
			var = m_pRs->GetCollect("maxnum");
			if (var != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			num++;
			m_pRs->MoveNext();
		}
		TRACE(strName);
		param = var;
	}
	catch (_com_error &e)
	{
		TRACE("loadnum_maxnum函数程序异常");
	}
	return 0;
}
//------------------------------------------------
//回调函数，判断该编号病人是否存在，回调函数每次只能处理一个记录
int IS_NO_exist(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs,int *param)
{
	
	int *number_exist;
	number_exist = (int*)param;
	//*number_exist = atoi(column_value[0]);
	_variant_t var;
	CString strName;
	strName = "";
	try
	{
		if (!m_pRs->BOF){
			//m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空\n");
			return TRUE;
		}
		int num = 0;
		while ((!m_pRs->adoEOF) && (num == 0))
		{
			var = m_pRs->GetCollect("NUMBER");
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			num++;
		}
		TRACE(strName);
		*number_exist = _ttoi(strName);
	}
	catch (_com_error &e)
	{
		TRACE("IS_NO_exist函数程序异常\n");
	}
	return 0;
}

int loaddoctor(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, doctor_info &param)
{
	TRACE("loadpatient()====================\n");
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空\n");
			return TRUE;
		}
		if ((!m_pRs->adoEOF))
		{
			_variant_t var;
			char *temp;
			USES_CONVERSION;
			//var = m_pRs->GetCollect("doct_id");
			//if (var.vt != VT_NULL)
			//{
			//	long id = (long)m_pRs->GetCollect("doct_id");
			//	(param).id = id;
			//}

			var = m_pRs->GetCollect("name");
			if (var.vt != VT_NULL)
			{
				CString name = m_pRs->GetCollect("name");
				temp = W2A(name);
				strncpy(param.name, temp, sizeof(param.name) / sizeof(char));
				//CString name_test;//
				//name_test = param.name;//关于带有中文的   注意 注意  注意  此处是个测试
			}
			var = m_pRs->GetCollect("doct_memo");
			if (var.vt != VT_NULL)
			{
				char memo = m_pRs->GetCollect("doct_memo");
				//(param).sex = sex;
				strncpy(param.memo, temp, sizeof(param.memo) / sizeof(char));
			}
		}
	}
	catch (_com_error &e)
	{
		TRACE("loadpatient函数程序异常\n");
	}
	TRACE("End:::loadpatient()====================\n");
	return 0;
}

//------------------------------------------------
//回调函数，读取保存的数据测试用
int loadpatient(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, patient_info &param)
{
	TRACE("loadpatient()====================\n");
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空\n");
			return TRUE;
		}
		if ((!m_pRs->adoEOF))
		{
			_variant_t var;
			char *temp;
			USES_CONVERSION;
			var = m_pRs->GetCollect("row");
			if (var.vt != VT_NULL)
			{
				int row = m_pRs->GetCollect("row");
				(param).row = row;
			}
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
			{
				int number = m_pRs->GetCollect("number");
				(param).number = number;
			}
			var = m_pRs->GetCollect("name");
			if (var.vt != VT_NULL)
			{
				CString name = m_pRs->GetCollect("name");
				temp = W2A(name);
				strncpy(param.name, temp, sizeof(param.name) / sizeof(char));
				//CString name_test;//
				//name_test = param.name;//关于带有中文的   注意 注意  注意  此处是个测试
			}
			var = m_pRs->GetCollect("sex");
			if (var.vt != VT_NULL)
			{
				char sex = m_pRs->GetCollect("sex");
				(param).sex = sex;
			}
			var = m_pRs->GetCollect("rangetype");
			if (var.vt != VT_NULL)
			{
				char rangetype = m_pRs->GetCollect("rangetype");
				(param).rangetype = rangetype;
			}
			var = m_pRs->GetCollect("age");
			if (var.vt != VT_NULL)
			{
				CString age = m_pRs->GetCollect("age");
				temp = W2A(age);
				strncpy(param.age, temp, sizeof(param.age) / sizeof(char));
			}
			var = m_pRs->GetCollect("code");
			if (var.vt != VT_NULL)
			{
				CString code = m_pRs->GetCollect("code");
				temp = W2A(code);
				strncpy(param.code, temp, sizeof(param.code) / sizeof(char));
			}
			var = m_pRs->GetCollect("technician");
			if (var.vt != VT_NULL)
			{
				CString technician = m_pRs->GetCollect("technician");
				temp = W2A(technician);
				strncpy(param.technician, temp, sizeof(param.technician) / sizeof(char));
			}
			var = m_pRs->GetCollect("doctor");
			if (var.vt != VT_NULL)
			{
				CString doctor = m_pRs->GetCollect("doctor");
				temp = W2A(doctor);
				strncpy(param.doctor, temp, sizeof(param.doctor) / sizeof(char));
			}
		}
	}
	catch (_com_error &e)
	{
		TRACE("loadpatient函数程序异常\n");
	}
	TRACE("End:::loadpatient()====================\n");
	return 0;
}
//int loadpatient(void *param, int n_column, char **column_value, char **column_name)
//{
//	patient_info *ppatientdata;
//	ppatientdata = (patient_info*)param;
//	TRACE("loadpatient()====================\n");
//	(*ppatientdata).row = atoi(column_value[0]);
//	(*ppatientdata).number = atoi(column_value[1]);
//	strcopy_ex((*ppatientdata).name, column_value[2]);
//	(*ppatientdata).sex = atoi(column_value[3]);
//	(*ppatientdata).rangetype = atoi(column_value[4]);
//	strcopy_ex((*ppatientdata).age, column_value[5]);
//	strcopy_ex((*ppatientdata).code, column_value[6]);
//	strcopy_ex((*ppatientdata).technician, column_value[7]);
//	return 0;
//}
//------------------------------------------------
//回调函数，读取保存的数据测试用
int loadresult(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, sample_info &param)
{
	sample_info *psampledata;
	TRACE("loadresult()====================\n");
	try
	{
		if (!m_pRs->BOF)
		{
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空\n");
			return TRUE;
		}
		if ((!m_pRs->adoEOF))
		{
			_variant_t var;
			char *temp;
			USES_CONVERSION;
			var = m_pRs->GetCollect("row");
			if (var.vt != VT_NULL)
			{
				int row = m_pRs->GetCollect("row");
				(param).row = row;
			}
			var = m_pRs->GetCollect("WBC");
			if (var.vt != VT_NULL)
			{
				CString wbc = m_pRs->GetCollect("WBC");
				temp = W2A(wbc);
				strncpy(param.wbcdata.wbc, temp, sizeof(param.wbcdata.wbc) / sizeof(char));
			}
			var = m_pRs->GetCollect("lymp");
			if (var.vt != VT_NULL)
			{
				CString lymp = m_pRs->GetCollect("lymp");
				temp = W2A(lymp);
				strncpy(param.wbcdata.lymp, temp, sizeof(param.wbcdata.lymp) / sizeof(char));
			}
			var = m_pRs->GetCollect("neup");
			if (var.vt != VT_NULL)
			{
				CString neup = m_pRs->GetCollect("neup");
				temp = W2A(neup);
				strncpy(param.wbcdata.neup, temp, sizeof(param.wbcdata.neup) / sizeof(char));
			}
			var = m_pRs->GetCollect("monop");
			if (var.vt != VT_NULL)
			{
				CString monop = m_pRs->GetCollect("monop");
				temp = W2A(monop);
				strncpy(param.wbcdata.monop, temp, sizeof(param.wbcdata.monop) / sizeof(char));
			}
			var = m_pRs->GetCollect("eosp");
			if (var.vt != VT_NULL)
			{
				CString eosp = m_pRs->GetCollect("eosp");
				temp = W2A(eosp);
				strncpy(param.wbcdata.eosp, temp, sizeof(param.wbcdata.eosp) / sizeof(char));
			}
			var = m_pRs->GetCollect("basop");
			if (var.vt != VT_NULL)
			{
				CString basp = m_pRs->GetCollect("basop");
				temp = W2A(basp);
				strncpy(param.wbcdata.basp, temp, sizeof(param.wbcdata.basp) / sizeof(char));
			}
			var = m_pRs->GetCollect("alyp");
			if (var.vt != VT_NULL)
			{
				CString alyp = m_pRs->GetCollect("alyp");
				temp = W2A(alyp);
				strncpy(param.wbcdata.alyp, temp, sizeof(param.wbcdata.alyp) / sizeof(char));
			}
			var = m_pRs->GetCollect("licp");
			if (var.vt != VT_NULL)
			{
				CString licp = m_pRs->GetCollect("licp");
				temp = W2A(licp);
				strncpy(param.wbcdata.licp, temp, sizeof(param.wbcdata.licp) / sizeof(char));
			}
			var = m_pRs->GetCollect("lym");
			if (var.vt != VT_NULL)
			{
				CString lym = m_pRs->GetCollect("lym");
				temp = W2A(lym);
				strncpy(param.wbcdata.lym, temp, sizeof(param.wbcdata.lym) / sizeof(char));
			}
			var = m_pRs->GetCollect("neu");
			if (var.vt != VT_NULL)
			{
				CString neu = m_pRs->GetCollect("neu");
				temp = W2A(neu);
				strncpy(param.wbcdata.neu, temp, sizeof(param.wbcdata.neu) / sizeof(char));
			}
			var = m_pRs->GetCollect("mono");
			if (var.vt != VT_NULL)
			{
				CString mono = m_pRs->GetCollect("mono");
				temp = W2A(mono);
				strncpy(param.wbcdata.mono, temp, sizeof(param.wbcdata.mono) / sizeof(char));
			}
			var = m_pRs->GetCollect("eos");
			if (var.vt != VT_NULL)
			{
				CString eos = m_pRs->GetCollect("eos");
				temp = W2A(eos);
				strncpy(param.wbcdata.eos, temp, sizeof(param.wbcdata.eos) / sizeof(char));
			}
			var = m_pRs->GetCollect("baso");
			if (var.vt != VT_NULL)
			{
				CString bas = m_pRs->GetCollect("baso");
				temp = W2A(bas);
				strncpy(param.wbcdata.bas, temp, sizeof(param.wbcdata.bas) / sizeof(char));
			}
			var = m_pRs->GetCollect("aly");
			if (var.vt != VT_NULL)
			{
				CString aly = m_pRs->GetCollect("aly");
				temp = W2A(aly);
				strncpy(param.wbcdata.aly, temp, sizeof(param.wbcdata.aly) / sizeof(char));
			}
			var = m_pRs->GetCollect("lic");
			if (var.vt != VT_NULL)
			{
				CString lic = m_pRs->GetCollect("lic");
				temp = W2A(lic);
				strncpy(param.wbcdata.lic, temp, sizeof(param.wbcdata.lic) / sizeof(char));
			}
			var = m_pRs->GetCollect("rbc");
			if (var.vt != VT_NULL)
			{
				CString rbc = m_pRs->GetCollect("rbc");
				temp = W2A(rbc);
				strncpy(param.rbcdata.rbc, temp, sizeof(param.rbcdata.rbc) / sizeof(char));
			}
			var = m_pRs->GetCollect("hgb");
			if (var.vt != VT_NULL)
			{
				CString hgb = m_pRs->GetCollect("hgb");
				temp = W2A(hgb);
				strncpy(param.rbcdata.hgb, temp, sizeof(param.rbcdata.hgb) / sizeof(char));
			}
			var = m_pRs->GetCollect("hct");
			if (var.vt != VT_NULL)
			{
				CString hct = m_pRs->GetCollect("hct");
				temp = W2A(hct);
				strncpy(param.rbcdata.hct, temp, sizeof(param.rbcdata.hct) / sizeof(char));
			}
			var = m_pRs->GetCollect("mcv");
			if (var.vt != VT_NULL)
			{
				CString mcv = m_pRs->GetCollect("mcv");
				temp = W2A(mcv);
				strncpy(param.rbcdata.mcv, temp, sizeof(param.rbcdata.mcv) / sizeof(char));
			}
			var = m_pRs->GetCollect("mcv");
			if (var.vt != VT_NULL)
			{
				CString mch = m_pRs->GetCollect("mch");
				temp = W2A(mch);
				strncpy(param.rbcdata.mch, temp, sizeof(param.rbcdata.mch) / sizeof(char));
			}
			var = m_pRs->GetCollect("mchc");
			if (var.vt != VT_NULL)
			{
				CString mchc = m_pRs->GetCollect("mchc");
				temp = W2A(mchc);
				strncpy(param.rbcdata.mchc, temp, sizeof(param.rbcdata.mchc) / sizeof(char));
			}
			var = m_pRs->GetCollect("rdwcv");
			if (var.vt != VT_NULL)
			{
				CString rdwcv = m_pRs->GetCollect("rdwcv");
				temp = W2A(rdwcv);
				strncpy(param.rbcdata.rdwcv, temp, sizeof(param.rbcdata.rdwcv) / sizeof(char));
			}
			var = m_pRs->GetCollect("rdwsd");
			if (var.vt != VT_NULL)
			{
				CString rdwsd = m_pRs->GetCollect("rdwsd");
				temp = W2A(rdwsd);
				strncpy(param.rbcdata.rdwsd, temp, sizeof(param.rbcdata.rdwsd) / sizeof(char));
			}
			var = m_pRs->GetCollect("plt");
			if (var.vt != VT_NULL)
			{
				CString plt = m_pRs->GetCollect("plt");
				temp = W2A(plt);
				strncpy(param.pltdata.plt, temp, sizeof(param.pltdata.plt) / sizeof(char));
			}
			var = m_pRs->GetCollect("mpv");
			if (var.vt != VT_NULL)
			{
				CString mpv = m_pRs->GetCollect("mpv");
				temp = W2A(mpv);
				strncpy(param.pltdata.mpv, temp, sizeof(param.pltdata.mpv) / sizeof(char));
			}
			var = m_pRs->GetCollect("pdw");
			if (var.vt != VT_NULL)
			{
				CString pdw = m_pRs->GetCollect("pdw");
				temp = W2A(pdw);
				strncpy(param.pltdata.pdw, temp, sizeof(param.pltdata.pdw) / sizeof(char));
			}
			var = m_pRs->GetCollect("pct");
			if (var.vt != VT_NULL)
			{
				CString pct = m_pRs->GetCollect("pct");
				temp = W2A(pct);
				strncpy(param.pltdata.pct, temp, sizeof(param.pltdata.pct) / sizeof(char));
			}
			var = m_pRs->GetCollect("plcr");
			if (var.vt != VT_NULL)
			{
				CString plcr = m_pRs->GetCollect("plcr");
				temp = W2A(plcr);
				strncpy(param.pltdata.plcr, temp, sizeof(param.pltdata.plcr) / sizeof(char));
			}
			var = m_pRs->GetCollect("lmne");
			if (var.vt != VT_NULL)
			{
				CString lmnegraph = m_pRs->GetCollect("lmne");
				temp = W2A(lmnegraph);
				INT_PTR iLen = (lmnegraph.GetLength()) / 2;
				BYTE *pByte = new BYTE[iLen];
				int iPos = 0, iStart = 0;
				while (iPos<iLen)
				{
					CString strToken;
					strToken = lmnegraph[iPos * 2];
					strToken += lmnegraph[iPos * 2 + 1];
					if (strToken.IsEmpty())
						break;
					pByte[iPos] = (BYTE)_tcstol(strToken, NULL, 16);
					param.lmnegraph[iPos] = pByte[iPos];
					iPos++;
				}
				delete[]pByte;
//				strncpy(param.lmnegraph, temp, sizeof(param.lmnegraph) / sizeof(char));
			}
			var = m_pRs->GetCollect("basograph");
			if (var.vt != VT_NULL)
			{
				CString basograph = m_pRs->GetCollect("basograph");
				temp = W2A(basograph);
				INT_PTR iLen = (basograph.GetLength()) / 2;
				BYTE *pByte = new BYTE[iLen];
				int iPos = 0, iStart = 0;
				while (iPos<iLen)
				{
					CString strToken;
					strToken = basograph[iPos * 2];
					strToken += basograph[iPos * 2 + 1];
					if (strToken.IsEmpty())
						break;
					pByte[iPos] = (BYTE)_tcstol(strToken, NULL, 16);
					param.basograph[iPos] = pByte[iPos];
					iPos++;
				}
				delete[]pByte;
//				strncpy(param.basograph, temp, sizeof(param.basograph) / sizeof(char));
			}
			var = m_pRs->GetCollect("rbcgraph");
			if (var.vt != VT_NULL)
			{
				CString rbcgraph = m_pRs->GetCollect("rbcgraph");
				temp = W2A(rbcgraph);
				INT_PTR iLen = (rbcgraph.GetLength()) / 2;
				BYTE *pByte = new BYTE[iLen];
				int iPos = 0, iStart = 0;
				while (iPos<iLen)
				{
					CString strToken;
					strToken = rbcgraph[iPos * 2];
					strToken += rbcgraph[iPos * 2 + 1];
					if (strToken.IsEmpty())
						break;
					pByte[iPos] = (BYTE)_tcstol(strToken, NULL, 16);
					param.rbcgraph[iPos] = pByte[iPos];
					iPos++;
				}
				delete[]pByte;
//				strncpy(param.rbcgraph, temp, sizeof(param.rbcgraph) / sizeof(char));
			}
			var = m_pRs->GetCollect("pltgraph");
			if (var.vt != VT_NULL)
			{
				CString pltgraph = m_pRs->GetCollect("pltgraph");
				temp = W2A(pltgraph);
				INT_PTR iLen = (pltgraph.GetLength()) / 2;
				BYTE *pByte = new BYTE[iLen];
				int iPos = 0, iStart = 0;
				while (iPos<iLen)
				{
					CString strToken;
					strToken = pltgraph[iPos * 2];
					strToken += pltgraph[iPos * 2 + 1];
					if (strToken.IsEmpty())
						break;
					pByte[iPos] = (BYTE)_tcstol(strToken, NULL, 16);
					param.pltgraph[iPos] = pByte[iPos];
					iPos++;
				}
				delete[]pByte;
//				strncpy(param.pltgraph, temp, sizeof(param.pltgraph) / sizeof(char));
			}
			var = m_pRs->GetCollect("lmneflg");
			if (var.vt != VT_NULL)
			{
				CString lmneflg = m_pRs->GetCollect("lmneflg");
				temp = W2A(lmneflg);
				strncpy(param.lmneflg, temp, sizeof(param.lmneflg) / sizeof(char));
			}
			var = m_pRs->GetCollect("basoflg");
			if (var.vt != VT_NULL)
			{
				CString basoflg = m_pRs->GetCollect("basoflg");
				temp = W2A(basoflg);
				strncpy(param.basoflg, temp, sizeof(param.basoflg) / sizeof(char));
			}
			var = m_pRs->GetCollect("rbcflg");
			if (var.vt != VT_NULL)
			{
				CString rbcflg = m_pRs->GetCollect("rbcflg");
				temp = W2A(rbcflg);
				strncpy(param.rbcflg, temp, sizeof(param.rbcflg) / sizeof(char));
			}
			var = m_pRs->GetCollect("pltflg");
			if (var.vt != VT_NULL)
			{
				CString pltflg = m_pRs->GetCollect("pltflg");
				temp = W2A(pltflg);
				strncpy(param.pltflg, temp, sizeof(param.pltflg) / sizeof(char));
			}
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
			{
				int number = m_pRs->GetCollect("number");
				(param).number = number;
			}
			var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
			{
				int time = m_pRs->GetCollect("time");
				(param).time = time;
			}
			var = m_pRs->GetCollect("mode");
			if (var.vt != VT_NULL)
			{
				char mode = m_pRs->GetCollect("mode");
				(param).mode = mode;
			}
			var = m_pRs->GetCollect("flag_wrp");
			if (var.vt != VT_NULL)
			{
				CString flag_wrp = m_pRs->GetCollect("flag_wrp");
				temp = W2A(flag_wrp);
				strncpy(param.flag_wrp, temp, sizeof(param.flag_wrp) / sizeof(char));
			}
			var = m_pRs->GetCollect("coeoflmne");
			if (var.vt != VT_NULL)
			{
				float coeoflmne = m_pRs->GetCollect("coeoflmne");
				(param).coeoflmne = coeoflmne;
			}
			
		}
	}
	catch (_com_error &e)
	{
		TRACE("loadresult()函数程序异常\n");
	}
	TRACE("End:::loadresult()====================\n");
	return 0;
}

//------------------------------------------------
//执行数据库语句

int ExeSql(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, CString sql)
{

	try{
		m_pDB->CursorLocation = adUseClient;
		m_pRs = m_pDB->Execute(_bstr_t(sql), 0, adCmdText);
		TRACE("操作成功\n");
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.Description());
		return -1;
	}
	return 0;
}

/*************************************************
*Function:
*Description: 	将patientdata指向的空间的数据库中插入病人信息表
或者用patientdata指向的空间的数据更存在编号的新病人信息
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/
int AddPatientRecord(patient_info *ppatientdata)
{
	USES_CONVERSION;
	int number_exsit = 0;
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;

	CString number;
	number.Format(_T("%d"), ppatientdata->number);
	CString name;
	name = A2W(ppatientdata->name);
	CString doctor;
	doctor = A2W(ppatientdata->doctor);
	CString sex;
	char sex_1 = ppatientdata->sex;
	if (sex_1<10)
		sex_1 = ppatientdata->sex + 48;
	sex = sex_1;
	CString rangetype;
	char rangetype_1 = ppatientdata->rangetype;
	if (rangetype_1 < 10)
		rangetype_1 = ppatientdata->rangetype + 48;

	rangetype = rangetype_1;
	CString age;
	age = ChartsToCString(ppatientdata->age, sizeof(ppatientdata->age) / sizeof(char));
	CString code;
	code = ChartsToCString(ppatientdata->code, sizeof(ppatientdata->code) / sizeof(char));
	CString technician;
	technician = ChartsToCString(ppatientdata->technician, sizeof(ppatientdata->technician) / sizeof(char));
	/********数据库更新*********/
	CString  row;
	row.Format(_T("%d"), ppatientdata->row);



	CString doc_check = _T("select * from doctordata where doct_name ='") + doctor + "'";
	ExeSql(m_pDB, m_pRs, doc_check);
	CString doct_id;
	_variant_t var;
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空");

		}
		while (!m_pRs->adoEOF)
		{

			var = m_pRs->GetCollect("doct_id");
			if (var.vt != VT_NULL)
				doct_id = (LPCSTR)_bstr_t(var);
			m_pRs->MoveNext();
		}

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}


	CString select = _T("select * from patientdata where number ='") + number + "'";
	ExeSql(m_pDB, m_pRs, select);
	IS_NO_exist(m_pDB, m_pRs, &number_exsit);
	if (number_exsit){
		//更新的时候，行号row不用更新
		CString updatepatient = _T("update patientdata set name='") + name + "' , sex = '" + sex + "', code = '" + code + "', age = '" + age + "', doctor = " + doct_id + ", technician = '" + technician + "', rangetype = '" + rangetype + "' where number ='" + number + "'";// + "', technician = '" + technician + 
		
		ExeSql(m_pDB, m_pRs, updatepatient);
	}
	else{
		CString insertpatient = _T("INSERT INTO [patientdata] ([row],[number],[name],[sex],[rangetype],[age],[code],[technician],[doctor]) VALUES('") + row + "' ,'" + number + "' ,'" + name + "' ,'" + sex + "' ,'" + rangetype + "' ,'" + age + "','" + code + "','" + technician + "' ,'" + doct_id + "');";
		ExeSql(m_pDB, m_pRs, insertpatient);
	}
	CloseDataBase(m_pDB, m_pRs);
	TRACE("AddPatientRecord---------------- #\n");
	return 0;
}

/*************************************************
*Function:
*Description:	保存X-B质控中用于绘制质控列表和质控图的数据
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/
int AddXB_ListRecord()
{
	//存到数据中的数据
	char date_temp[11];		//日期
	unsigned int time_temp;	//时间
	char mcv_temp[6];
	char mch_temp[6];
	char mchc_temp[6];
	float sum;
	float XBdata[3][2000];
	float mean[3];
	char databuff[6] = { 0 };
	unsigned int nColumn, nRow, i, j;
	CString dbResult[3][2000];
	time(&systime);
	caltime = localtime(&systime);
	sprintf(date_temp, "%04d-%02d-%02d", caltime->tm_year + 1900, caltime->tm_mon + 1, caltime->tm_mday);
	time_temp = (caltime->tm_hour) * 10000 + (caltime->tm_min) * 100 + caltime->tm_sec;
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	CString select = _T("select MCV,MCH,MCHC from XB_QCdata;");
	ExeSql(m_pDB, m_pRs, select);
	nRow = int(m_pRs->GetRecordCount());//select函数获取的记录条数
	nColumn = int(m_pRs->Fields->Count);//select函数获取的一条记录中的字段数
	if (nRow > 200)//肯定不能超出200
	{
		TRACE("XB_QCdata nRow > 200\n");
		return -1;
	}
	else{
		i = 0;
		_variant_t var;
		char strName;
		try
		{
			if (!m_pRs->BOF){
				m_pRs->MoveFirst();
			}
			else
			{
				TRACE("表内数据为空\n");
				return -1;
			}
			while ((!m_pRs->adoEOF))
			{
				var = m_pRs->GetCollect("MCV");
				if (var.vt != VT_NULL){
					dbResult[0][i] = var;
				}
				var = m_pRs->GetCollect("MCH");
				if (var.vt != VT_NULL)
				{
					dbResult[1][i] = var;
				}
				var = m_pRs->GetCollect("MCHC");
				if (var.vt != VT_NULL)
				{
					dbResult[2][i] = var;
				}
				i++;
				m_pRs->MoveNext();
			}
		}
		catch (_com_error &e)
		{
			TRACE("AddXB_ListRecord函数程序异常\n");
		}
		for (i = 0; i< nColumn; i++)
			for (j = 0; j < nRow; j++)
			{
				memcpy(databuff, dbResult[i][j], 6);
				XBdata[i][j] = atof(databuff);

			}
	}
	for (i = 0; i < 3; i++)
	{
		sum = 0;
		for (j = 0; j < nRow; j++)
		{
			sum = sum + XBdata[i][j];
		}
		mean[i] = sum / nRow;	//不会出现0
	}
	sprintf(mcv_temp, "%.1f", mean[0]);//mcv_temp很难溢出，存值范围很大
	sprintf(mch_temp, "%.1f", mean[1]);
	sprintf(mchc_temp, "%.1f", mean[2]);
	CloseDataBase(m_pDB, m_pRs);
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	CString date_temp1;
	date_temp1 = ChartsToCString(date_temp, sizeof(date_temp) / sizeof(char));
	CString time_temp1;
	time_temp1.Format(_T("%d"), time_temp);
	CString mcv_temp1;
	mcv_temp1 = ChartsToCString(mcv_temp, sizeof(mcv_temp) / sizeof(char));
	CString mch_temp1;
	mch_temp1 = ChartsToCString(mch_temp, sizeof(mch_temp) / sizeof(char));
	CString mchc_temp1;
	mchc_temp1 = ChartsToCString(mchc_temp, sizeof(mchc_temp) / sizeof(char));
	CString insert = _T("insert into [XB_Listdata]([data],[time],[mcv],[mch],[mchc]) values('") + date_temp1 + "' ,'" + time_temp1 + "' ,'" + mcv_temp1 + "' ,'" + mch_temp1 + "' ,'" + mchc_temp1 + "');";
	ExeSql(m_pDB, m_pRs, insert);
	CString DEL = _T("delete from XB_QCdata;");
	CloseDataBase(m_pDB, m_pRs);
	return 0;
}

/*************************************************
*Function:
*Description:	将sampledata指向的空间的数据库中插入样本数据表
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/
int AddSampleRecord(sample_info *psampledata)
{
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	int number_exsit = 0;
	unsigned int row_XB_QC = 0;
	char border[4] = { 0 };
	unsigned int minnumber = 0;
	unsigned int minnumber_row = 0;
	unsigned int nRow = 0, nColumn = 0;
	static char **dbResult;
	char *zErrMsg = NULL;
	time(&systime);
	caltime = localtime(&systime);
	TRACE("\nStart:AddSampleRecord::psampledata = (*sample_info)0x%x---------#\n", psampledata);
	psampledata->time = (caltime->tm_hour) * 10000 + (caltime->tm_min) * 100 + caltime->tm_sec;
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	TRACE( "row : %d ************************************\n", psampledata->row);
	if (psampledata->row > 1000)    //1000
	{
		//查询编号number最小的那个
		CString select_minnumber = _T("select min(number) from sampledata");
		ExeSql(m_pDB, m_pRs, select_minnumber);
		nRow = int(m_pRs->GetRecordCount());//select函数获取的记录条数
		nColumn = int(m_pRs->Fields->Count);//select函数获取的一条记录中的字段数
		_variant_t var;
		char strName;
		int i = 0;
		try
		{
			if (!m_pRs->BOF){
				m_pRs->MoveFirst();
			}
			else
			{
				TRACE("表内数据为空\n");
				return -1;
			}
			while ((!m_pRs->adoEOF)&&(i==0))
			{
				var = m_pRs->GetCollect("NUMBER");
				if (var.vt != VT_NULL){
					strName = (char)(var);
					dbResult[0][i] = strName;
				}
				i++;
			}
		}
		catch (_com_error &e)
		{
			TRACE("AddSampleRecord函数程序异常\n");
		}
		minnumber = dbResult[0][0];
		//查询编号number最小对应的row
		CString minnumber1;
		minnumber1.Format(minnumber);
		CString select_minnumber_row = _T("select row from sampledata where number='") + minnumber1+_T("'");
		ExeSql(m_pDB, m_pRs, select_minnumber_row);
		nRow = int(m_pRs->GetRecordCount());//select函数获取的记录条数
		nColumn = int(m_pRs->Fields->Count);//select函数获取的一条记录中的字段数
		i = 0;
		try
		{
			if (!m_pRs->BOF){
				m_pRs->MoveFirst();
			}
			else
			{
				TRACE("表内数据为空\n");
				return -1;
			}
			while ((!m_pRs->adoEOF) && (i == 0))
			{
				var = m_pRs->GetCollect("ROW");
				if (var.vt != VT_NULL){
					strName = (char)(var);
					dbResult[0][i] = strName;
				}
				i++;
				m_pRs->MoveNext();
			}
		}
		catch (_com_error &e)
		{
			TRACE("AddSampleRecord函数程序异常\n");
		}
		minnumber_row = dbResult[0][0];
		//删除编号number最小对应的row
		CString minnumber_row1;
		minnumber_row1.Format(minnumber_row);
		CString DEL_minnumber_row = _T("delete from sampledata where row ='") + minnumber_row1 + _T("'");
		ExeSql(m_pDB, m_pRs, DEL_minnumber_row);
		//删除病人信息表中编号number最小对应的row
		CString DEL_minnumber_row_patientdata = _T("delete from patientdata where row = '") + minnumber_row1 + _T("'");
		ExeSql(m_pDB, m_pRs, DEL_minnumber_row_patientdata);
		psampledata->row = minnumber_row;
	}
	CString number1;
	number1.Format(_T("%d"), psampledata->number);
	CString selectsample = _T("select * from sampledata where number = '") + number1+_T("'");
	ExeSql(m_pDB, m_pRs, selectsample);
	IS_NO_exist(m_pDB, m_pRs, &number_exsit);//number_exsit存的是表中row元素 
	//printf("number_exist:%d------------\n",number_exsit);
	TRACE("=============AddSampleRecord===================\n");
	TRACE("====%d\n", number_exsit);
	sprintf(border, "%d", PLTRightBorderQuery);
	number_exsit = 0;
	if (number_exsit){
		CString row;
		row.Format(_T("%d"), psampledata->row);
		CString wbcdata_wbc;
		wbcdata_wbc = ChartsToCString(psampledata->wbcdata.wbc, sizeof(psampledata->wbcdata.wbc) / sizeof(char));
		CString wbcdata_lymp;
		wbcdata_lymp = ChartsToCString(psampledata->wbcdata.lymp, sizeof(psampledata->wbcdata.lymp) / sizeof(char));
		CString wbcdata_neup;
		wbcdata_neup = ChartsToCString(psampledata->wbcdata.neup, sizeof(psampledata->wbcdata.neup) / sizeof(char));
		CString wbcdata_monop;
		wbcdata_monop = ChartsToCString(psampledata->wbcdata.monop, sizeof(psampledata->wbcdata.monop) / sizeof(char));
		CString wbcdata_eosp;
		wbcdata_eosp = ChartsToCString(psampledata->wbcdata.eosp, sizeof(psampledata->wbcdata.eosp) / sizeof(char));
		CString wbcdata_basp;
		wbcdata_basp = ChartsToCString(psampledata->wbcdata.basp, sizeof(psampledata->wbcdata.basp) / sizeof(char));
		CString wbcdata_alyp;
		wbcdata_alyp = ChartsToCString(psampledata->wbcdata.alyp, sizeof(psampledata->wbcdata.alyp) / sizeof(char));
		CString wbcdata_licp;
		wbcdata_licp = ChartsToCString(psampledata->wbcdata.licp, sizeof(psampledata->wbcdata.licp) / sizeof(char));
		CString wbcdata_lym;
		wbcdata_lym = ChartsToCString(psampledata->wbcdata.lym, sizeof(psampledata->wbcdata.lym) / sizeof(char));
		CString wbcdata_neu;
		wbcdata_neu = ChartsToCString(psampledata->wbcdata.neu, sizeof(psampledata->wbcdata.neu) / sizeof(char));
		CString wbcdata_mono;
		wbcdata_mono = ChartsToCString(psampledata->wbcdata.mono, sizeof(psampledata->wbcdata.mono) / sizeof(char));
		CString wbcdata_eos;
		wbcdata_eos = ChartsToCString(psampledata->wbcdata.eos, sizeof(psampledata->wbcdata.eos) / sizeof(char));
		CString wbcdata_bas;
		wbcdata_bas = ChartsToCString(psampledata->wbcdata.bas, sizeof(psampledata->wbcdata.bas) / sizeof(char));
		CString wbcdata_aly;
		wbcdata_aly = ChartsToCString(psampledata->wbcdata.aly, sizeof(psampledata->wbcdata.aly) / sizeof(char));
		CString wbcdata_lic;
		wbcdata_lic = ChartsToCString(psampledata->wbcdata.lic, sizeof(psampledata->wbcdata.lic) / sizeof(char));
		CString rbcdata_rbc;
		rbcdata_rbc = ChartsToCString(psampledata->rbcdata.rbc, sizeof(psampledata->rbcdata.rbc) / sizeof(char));
		CString rbcdata_hgb;
		rbcdata_hgb = ChartsToCString(psampledata->rbcdata.hgb, sizeof(psampledata->rbcdata.hgb) / sizeof(char));
		CString rbcdata_hct;
		rbcdata_hct = ChartsToCString(psampledata->rbcdata.hct, sizeof(psampledata->rbcdata.hct) / sizeof(char));
		CString rbcdata_mcv;
		rbcdata_mcv = ChartsToCString(psampledata->rbcdata.mcv, sizeof(psampledata->rbcdata.mcv) / sizeof(char));
		CString rbcdata_mch;
		rbcdata_mch = ChartsToCString(psampledata->rbcdata.mch, sizeof(psampledata->rbcdata.mch) / sizeof(char));
		CString rbcdata_mchc;
		rbcdata_mchc = ChartsToCString(psampledata->rbcdata.mchc, sizeof(psampledata->rbcdata.mchc) / sizeof(char));
		CString rbcdata_rdwcv;
		rbcdata_rdwcv = ChartsToCString(psampledata->rbcdata.rdwcv, sizeof(psampledata->rbcdata.rdwcv) / sizeof(char));
		CString rbcdata_rdwsd;
		rbcdata_rdwsd = ChartsToCString(psampledata->rbcdata.rdwsd, sizeof(psampledata->rbcdata.rdwsd) / sizeof(char));
		CString pltdata_plt;
		pltdata_plt = ChartsToCString(psampledata->pltdata.plt, sizeof(psampledata->pltdata.plt) / sizeof(char));
		CString pltdata_mpv;
		pltdata_mpv = ChartsToCString(psampledata->pltdata.mpv, sizeof(psampledata->pltdata.mpv) / sizeof(char));
		CString pltdata_pdw;
		pltdata_pdw = ChartsToCString(psampledata->pltdata.pdw, sizeof(psampledata->pltdata.pdw) / sizeof(char));
		CString pltdata_pct;
		pltdata_pct = ChartsToCString(psampledata->pltdata.pct, sizeof(psampledata->pltdata.pct) / sizeof(char));
		CString pltdata_plcr;
		pltdata_plcr = ChartsToCString(psampledata->pltdata.plcr, sizeof(psampledata->pltdata.plcr) / sizeof(char));
		CString lmnegraph;
		lmnegraph = ChartsToCStringdata(psampledata->lmnegraph, sizeof(psampledata->lmnegraph) / sizeof(char));
		CString basograph;
		basograph = ChartsToCStringdata(psampledata->basograph, sizeof(psampledata->basograph) / sizeof(char));
		CString rbcgraph;
		rbcgraph = ChartsToCStringdata(psampledata->rbcgraph, sizeof(psampledata->rbcgraph) / sizeof(char));
		CString pltgraph;
		pltgraph = ChartsToCStringdata(psampledata->pltgraph, sizeof(psampledata->pltgraph) / sizeof(char));
		CString lmneflg;
		lmneflg = ChartsToCString(psampledata->lmneflg, sizeof(psampledata->lmneflg) / sizeof(char));
		CString basoflg;
		basoflg = ChartsToCString(psampledata->basoflg, sizeof(psampledata->basoflg) / sizeof(char));
		CString rbcflg;
		rbcflg = ChartsToCString(psampledata->rbcflg, sizeof(psampledata->rbcflg) / sizeof(char));
		CString pltflg;
		pltflg = ChartsToCString(psampledata->pltflg, sizeof(psampledata->pltflg) / sizeof(char));
		CString number;
		number.Format(_T("%d"), psampledata->number);
		CString time;
		time.Format(_T("%d"), psampledata->time);
		if (psampledata->time < 100000){
			time = "0" + time;
		}
		CString mode;
		mode.Format(_T("%d"), psampledata->mode);
		CString border1;
		border1 = border;
		CString flag_wrp;
		//flag_wrp = psampledata->flag_wrp;
		flag_wrp = ChartsToCString(psampledata->flag_wrp,sizeof(psampledata->flag_wrp)/sizeof(char));
		CString coeoflmne;
		coeoflmne.Format(_T("%f"), psampledata->coeoflmne);
		TRACE("===========updatesample=============\n");
		CString updatesample = _T("update sampledata set [row]='") + row + _T("',[WBC]='") + wbcdata_wbc + _T("',[LYMP]='") + wbcdata_lymp + _T("',[NEUP]='") + wbcdata_neup
			+ _T("',[MONOP]='") + wbcdata_monop + _T("',[EOSP] ='") + wbcdata_eosp + _T("',[BASOP] ='") + wbcdata_basp + _T("',[ALYP] = '") + wbcdata_alyp + _T("',[LICP] ='") + wbcdata_licp
			+ _T("',[LYM] ='") + wbcdata_lym + _T("',[NEU] ='") + wbcdata_neu + _T("',[MONO] ='") + wbcdata_mono + _T("',[EOS] ='") + wbcdata_eos + _T("',[BASO] ='") + wbcdata_bas
			+ _T("',[ALY]='") + wbcdata_aly + _T("',[LIC]='") + wbcdata_lic + _T("',[RBC] ='") + rbcdata_rbc + _T("',[HGB] ='") + rbcdata_hgb + _T("',[HCT] ='") + rbcdata_hct + _T("',[MCV] = '") + rbcdata_mcv
			+ _T("',[MCH] ='") + rbcdata_mch + _T("',[MCHC] = '") + rbcdata_mchc + _T("',[RDWCV] = '") + rbcdata_rdwcv + _T("',[RDWSD] = '") + rbcdata_rdwsd + _T("',[PLT] ='") + pltdata_plt
			+ _T("',[MPV] ='") + pltdata_mpv + _T("',[PDW] = '") + pltdata_pdw + _T("',[PCT] ='") + pltdata_pct + _T("',[PLCR] ='") + pltdata_plcr + _T("',[lmne] = '") + lmnegraph + _T("',[basograph] = '") + basograph
			+ _T("',[rbcgraph]='") + rbcgraph + _T("',[pltgraph] ='") + pltgraph + _T("',[lmneflg] ='") + lmneflg + _T("',[basoflg] ='") + basoflg + _T("',[rbcflg] ='") + rbcflg + _T("',[pltflg] ='") + pltflg
			+ _T("',[number] ='") + number + _T("',[time] ='") + time + _T("',[mode] ='") + mode + _T("',[pltrightborder] ='") + border1 + _T("',[flag_wrp] ='") + flag_wrp + _T("',[coeoflmne] ='") + coeoflmne
			+ _T("'where [number] ='") + number + _T("'");
		TRACE("updatesample=%s\n", updatesample);
		ExeSql(m_pDB, m_pRs, updatesample);
	}
	else{
		CString row;
		row.Format(_T("%d"), psampledata->row);
		CString wbcdata_wbc;
		wbcdata_wbc = ChartsToCString(psampledata->wbcdata.wbc, sizeof(psampledata->wbcdata.wbc) / sizeof(char));
		CString wbcdata_lymp;
		wbcdata_lymp = ChartsToCString(psampledata->wbcdata.lymp, sizeof(psampledata->wbcdata.lymp) / sizeof(char));
		CString wbcdata_neup;
		wbcdata_neup = ChartsToCString(psampledata->wbcdata.neup, sizeof(psampledata->wbcdata.neup) / sizeof(char));
		CString wbcdata_monop;
		wbcdata_monop = ChartsToCString(psampledata->wbcdata.monop, sizeof(psampledata->wbcdata.monop) / sizeof(char));
		CString wbcdata_eosp;
		wbcdata_eosp = ChartsToCString(psampledata->wbcdata.eosp, sizeof(psampledata->wbcdata.eosp) / sizeof(char));
		CString wbcdata_basp;
		wbcdata_basp = ChartsToCString(psampledata->wbcdata.basp, sizeof(psampledata->wbcdata.basp) / sizeof(char));
		CString wbcdata_alyp;
		wbcdata_alyp = ChartsToCString(psampledata->wbcdata.alyp, sizeof(psampledata->wbcdata.alyp) / sizeof(char));
		CString wbcdata_licp;
		wbcdata_licp = ChartsToCString(psampledata->wbcdata.licp, sizeof(psampledata->wbcdata.licp) / sizeof(char));
		CString wbcdata_lym;
		wbcdata_lym = ChartsToCString(psampledata->wbcdata.lym, sizeof(psampledata->wbcdata.lym) / sizeof(char));
		CString wbcdata_neu;
		wbcdata_neu = ChartsToCString(psampledata->wbcdata.neu, sizeof(psampledata->wbcdata.neu) / sizeof(char));
		CString wbcdata_mono;
		wbcdata_mono = ChartsToCString(psampledata->wbcdata.mono, sizeof(psampledata->wbcdata.mono) / sizeof(char));
		CString wbcdata_eos;
		wbcdata_eos = ChartsToCString(psampledata->wbcdata.eos, sizeof(psampledata->wbcdata.eos) / sizeof(char));
		CString wbcdata_bas;
		wbcdata_bas = ChartsToCString(psampledata->wbcdata.bas, sizeof(psampledata->wbcdata.bas) / sizeof(char));
		CString wbcdata_aly;
		wbcdata_aly = ChartsToCString(psampledata->wbcdata.aly, sizeof(psampledata->wbcdata.aly) / sizeof(char));
		CString wbcdata_lic;
		wbcdata_lic = ChartsToCString(psampledata->wbcdata.lic, sizeof(psampledata->wbcdata.lic) / sizeof(char));
		CString rbcdata_rbc;
		rbcdata_rbc = ChartsToCString(psampledata->rbcdata.rbc, sizeof(psampledata->rbcdata.rbc) / sizeof(char));
		CString rbcdata_hgb;
		rbcdata_hgb = ChartsToCString(psampledata->rbcdata.hgb, sizeof(psampledata->rbcdata.hgb) / sizeof(char));
		CString rbcdata_hct;
		rbcdata_hct = ChartsToCString(psampledata->rbcdata.hct, sizeof(psampledata->rbcdata.hct) / sizeof(char));
		CString rbcdata_mcv;
		rbcdata_mcv = ChartsToCString(psampledata->rbcdata.mcv, sizeof(psampledata->rbcdata.mcv) / sizeof(char));
		CString rbcdata_mch;
		rbcdata_mch = ChartsToCString(psampledata->rbcdata.mch, sizeof(psampledata->rbcdata.mch) / sizeof(char));
		CString rbcdata_mchc;
		rbcdata_mchc = ChartsToCString(psampledata->rbcdata.mchc, sizeof(psampledata->rbcdata.mchc) / sizeof(char));
		CString rbcdata_rdwcv;
		rbcdata_rdwcv = ChartsToCString(psampledata->rbcdata.rdwcv, sizeof(psampledata->rbcdata.rdwcv) / sizeof(char));
		CString rbcdata_rdwsd;
		rbcdata_rdwsd = ChartsToCString(psampledata->rbcdata.rdwsd, sizeof(psampledata->rbcdata.rdwsd) / sizeof(char));
		CString pltdata_plt;
		pltdata_plt = ChartsToCString(psampledata->pltdata.plt, sizeof(psampledata->pltdata.plt) / sizeof(char));
		CString pltdata_mpv;
		pltdata_mpv = ChartsToCString(psampledata->pltdata.mpv, sizeof(psampledata->pltdata.mpv) / sizeof(char));
		CString pltdata_pdw;
		pltdata_pdw = ChartsToCString(psampledata->pltdata.pdw, sizeof(psampledata->pltdata.pdw) / sizeof(char));
		CString pltdata_pct;
		pltdata_pct = ChartsToCString(psampledata->pltdata.pct, sizeof(psampledata->pltdata.pct) / sizeof(char));
		CString pltdata_plcr;
		pltdata_plcr = ChartsToCString(psampledata->pltdata.plcr, sizeof(psampledata->pltdata.plcr) / sizeof(char));
		CString lmnegraph;
		lmnegraph = ChartsToCStringdata(psampledata->lmnegraph, sizeof(psampledata->lmnegraph) / sizeof(char));
		TRACE(_T("----lmnegraph:%s-------\n"), lmnegraph);
		CString basograph;
		basograph = ChartsToCStringdata(psampledata->basograph, sizeof(psampledata->basograph) / sizeof(char));
		TRACE(_T("----basograph:%s-------\n"), basograph);
		CString rbcgraph;
		rbcgraph = ChartsToCStringdata(psampledata->rbcgraph, sizeof(psampledata->rbcgraph) / sizeof(char));
		TRACE(_T("----rbcgraph:%s-------\n"), rbcgraph);
		CString pltgraph;
		pltgraph = ChartsToCStringdata(psampledata->pltgraph, sizeof(psampledata->pltgraph) / sizeof(char));
		TRACE(_T("----pltgraph:%s-------\n"), pltgraph);
		CString lmneflg;
		lmneflg = ChartsToCString(psampledata->lmneflg, sizeof(psampledata->lmneflg) / sizeof(char));
		TRACE(_T("----lmneflg:%s-------\n"), lmneflg);
		CString basoflg;
		basoflg = ChartsToCString(psampledata->basoflg, sizeof(psampledata->basoflg) / sizeof(char));
		TRACE(_T("----basoflg:%s-------\n"), basoflg);
		CString rbcflg;
		rbcflg = ChartsToCString(psampledata->rbcflg, sizeof(psampledata->rbcflg) / sizeof(char));
		TRACE(_T("----rbcflg:%s-------\n"), rbcflg);
		CString pltflg;
		pltflg = ChartsToCString(psampledata->pltflg, sizeof(psampledata->pltflg) / sizeof(char));
		TRACE(_T("----pltflg:%s-------\n"), pltflg);
		CString number;
		number.Format(_T("%d"), psampledata->number);
		CString time;
		time.Format(_T("%d"), psampledata->time);
		if (psampledata->time < 100000){
			time = "0" + time;
		}
		CString mode;
		mode.Format(_T("%d"), psampledata->mode);
		CString border1;
		border1 = border;
		CString flag_wrp;
		flag_wrp = ChartsToCString(psampledata->flag_wrp, sizeof(psampledata->flag_wrp) / sizeof(char));
		CString coeoflmne;
		coeoflmne.Format(_T("%f"), psampledata->coeoflmne);
		TRACE("===========insertsample=============\n");
		CString insertsample = _T("insert into [sampledata]([row],[WBC],[LYMP],[NEUP],[MONOP],[EOSP],[BASOP],[ALYP],[LICP],[LYM],[NEU],[MONO],[EOS],[BASO],[ALY],[LIC],[RBC],[HGB],[HCT],[MCV],[MCH],[MCHC],[RDWCV],[RDWSD],[PLT],[MPV],[PDW],[PCT],[PLCR],[lmne],[basograph],[rbcgraph],[pltgraph],[lmneflg],[basoflg],[rbcflg],[pltflg],[number],[time],[mode],[pltrightborder],[flag_wrp],[coeoflmne]) values('") 
			+ row + "' ,'" + wbcdata_wbc + "' ,'" + wbcdata_lymp + "' ,'"+ wbcdata_neup + "' ,'"
			+ wbcdata_monop +"' ,'" + wbcdata_eosp + "' ,'" + wbcdata_basp + "' ,'" + wbcdata_alyp + "' ,'" + wbcdata_licp + "' ,'" + wbcdata_lym +"' ,'" 
			+ wbcdata_neu + "' ,'" + wbcdata_mono + "' ,'" + wbcdata_eos + "' ,'" + wbcdata_bas +"' ,'" + wbcdata_aly + "' ,'" + wbcdata_lic+ "' ,'"
			+ rbcdata_rbc + "' ,'" + rbcdata_hgb + "' ,'" + rbcdata_hct + "' ,'" + rbcdata_mcv +"' ,'" + rbcdata_mch + "' ,'" + rbcdata_mchc +"' ,'"
			+ rbcdata_rdwcv + "' ,'" + rbcdata_rdwsd +"' ,'" + pltdata_plt + "' ,'" + pltdata_mpv + "' ,'" + pltdata_pdw +"' ,'" + pltdata_pct + "' ,'"
			+ pltdata_plcr + "' ,'" + lmnegraph + "' ,'" + basograph + "' ,'" + rbcgraph +"' ,'" + pltgraph + "' ,'" + lmneflg + "' ,'" + basoflg + "' ,'"
			+ rbcflg + "' ,'" + pltflg +"' ,'" + number + "' ,'" + time +"' ,'" + mode + "' ,'" + border1 + "' ,'" + flag_wrp + "' ,'" + coeoflmne + "');";
		TRACE(_T("insertsample=%S\n"), insertsample);
			ExeSql(m_pDB, m_pRs, insertsample);
	}
	TRACE("End:  AddSampleRecord::psampledata = (*sample_info)0x%x---------#\n", psampledata);
	//判断X-B质控开关打开的情况下实现存入数据计数	
	if (systemcfg.qualitycontrol.XB_on == 1)
	{
		if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
			return -1;
		if (number_exsit){
			CString mcv;
			mcv = ChartsToCString(psampledata->rbcdata.mcv, sizeof(psampledata->rbcdata.mcv) / sizeof(uchar));
			CString mch;
			mch = ChartsToCString(psampledata->rbcdata.mch, sizeof(psampledata->rbcdata.mch) / sizeof(uchar));
			CString mchc;
			mchc = ChartsToCString(psampledata->rbcdata.mchc, sizeof(psampledata->rbcdata.mchc) / sizeof(uchar));
			CString updateXB_QC = _T("update XB_QCdata set [MCV]='") + mcv + "',[MCH]='" + mch + "',[MCHC]='" + mchc + "'";
			ExeSql(m_pDB, m_pRs, updateXB_QC);
		}
		else{
			CString mcv;
			mcv = ChartsToCString(psampledata->rbcdata.mcv, sizeof(psampledata->rbcdata.mcv) / sizeof(uchar));
			CString mch;
			mch = ChartsToCString(psampledata->rbcdata.mch, sizeof(psampledata->rbcdata.mch) / sizeof(uchar));
			CString mchc;
			mchc = ChartsToCString(psampledata->rbcdata.mchc, sizeof(psampledata->rbcdata.mchc) / sizeof(uchar));
			CString insertXB_QC = _T("insert into [XB_QCdata]([MCV],[MCH],[MCHC]) values('") + mcv + "' ,'" + mch + "' ,'" + mchc + "');";
			ExeSql(m_pDB, m_pRs, insertXB_QC);
		}
		//查询总记录数
		CString select_row = _T("select * from XB_QCdata;");
		ExeSql(m_pDB, m_pRs, select_row);
		loadnum1(m_pDB, m_pRs, row_XB_QC);
		CloseDataBase(m_pDB, m_pRs);
		if (row_XB_QC >= systemcfg.qualitycontrol.XB_group_num)
			AddXB_ListRecord();
	}
	return 0;
}

/*************************************************
*Function:
*Description:	将新编写的用于质控的靶值和偏差值保存到数据表当中	。应用于L-J及X质控
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/
int QcLjXXrEditFileAdd(qc_edit_data_info *pqcLjXXrEditData)
{
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	CString qctype;
	//qctype.Format((*pqcLjXXrEditData).qctype);
	qctype = (*pqcLjXXrEditData).qctype;
	//TRACE("***###\nqctype=%s\n",qctype);
	CString filenum;
	//filenum.Format((*pqcLjXXrEditData).filenum);
	filenum = (*pqcLjXXrEditData).filenum;
	CString Number;
	Number = ChartsToCString((*pqcLjXXrEditData).Number, sizeof((*pqcLjXXrEditData).Number)/sizeof(char));
	CString Deadline;
	Deadline = ChartsToCString((*pqcLjXXrEditData).Deadline, sizeof((*pqcLjXXrEditData).Deadline)/sizeof(char));
	CString wbctarget_wbc;
	wbctarget_wbc = ChartsToCString((*pqcLjXXrEditData).wbctarget.wbc, sizeof((*pqcLjXXrEditData).wbctarget.wbc) / sizeof(char));
	CString wbctarget_lymp;
	wbctarget_lymp = ChartsToCString((*pqcLjXXrEditData).wbctarget.lymp, sizeof((*pqcLjXXrEditData).wbctarget.lymp) / sizeof(char));
	CString wbctarget_neup;
	wbctarget_neup = ChartsToCString((*pqcLjXXrEditData).wbctarget.neup, sizeof((*pqcLjXXrEditData).wbctarget.neup) / sizeof(char));
	CString wbctarget_monop;
	wbctarget_monop = ChartsToCString((*pqcLjXXrEditData).wbctarget.monop, sizeof((*pqcLjXXrEditData).wbctarget.monop) / sizeof(char));
	CString wbctarget_eosp;
	wbctarget_eosp = ChartsToCString((*pqcLjXXrEditData).wbctarget.eosp, sizeof((*pqcLjXXrEditData).wbctarget.eosp) / sizeof(char));
	CString wbctarget_basp;
	wbctarget_basp = ChartsToCString((*pqcLjXXrEditData).wbctarget.basp, sizeof((*pqcLjXXrEditData).wbctarget.basp) / sizeof(char));
	CString wbctarget_alyp;
	wbctarget_alyp = ChartsToCString((*pqcLjXXrEditData).wbctarget.alyp, sizeof((*pqcLjXXrEditData).wbctarget.alyp) / sizeof(char));
	CString wbctarget_licp;
	wbctarget_licp = ChartsToCString((*pqcLjXXrEditData).wbctarget.licp, sizeof((*pqcLjXXrEditData).wbctarget.licp) / sizeof(char));
	CString wbctarget_lym;
	wbctarget_lym = ChartsToCString((*pqcLjXXrEditData).wbctarget.lym, sizeof((*pqcLjXXrEditData).wbctarget.lym) / sizeof(char));
	CString wbctarget_neu;
	wbctarget_neu = ChartsToCString((*pqcLjXXrEditData).wbctarget.neu, sizeof((*pqcLjXXrEditData).wbctarget.neu) / sizeof(char));
	CString wbctarget_mono;
	wbctarget_mono = ChartsToCString((*pqcLjXXrEditData).wbctarget.mono, sizeof((*pqcLjXXrEditData).wbctarget.mono) / sizeof(char));
	CString wbctarget_eos;
	wbctarget_eos = ChartsToCString((*pqcLjXXrEditData).wbctarget.eos, sizeof((*pqcLjXXrEditData).wbctarget.eos) / sizeof(char));
	CString wbctarget_bas;
	wbctarget_bas = ChartsToCString((*pqcLjXXrEditData).wbctarget.bas, sizeof((*pqcLjXXrEditData).wbctarget.bas) / sizeof(char));
	CString wbctarget_aly;
	wbctarget_aly = ChartsToCString((*pqcLjXXrEditData).wbctarget.aly, sizeof((*pqcLjXXrEditData).wbctarget.aly) / sizeof(char));
	CString wbctarget_lic;
	wbctarget_lic = ChartsToCString((*pqcLjXXrEditData).wbctarget.lic, sizeof((*pqcLjXXrEditData).wbctarget.lic) / sizeof(char));
	CString rbctarget_rbc;
	rbctarget_rbc = ChartsToCString((*pqcLjXXrEditData).rbctarget.rbc, sizeof((*pqcLjXXrEditData).rbctarget.rbc) / sizeof(char));
	CString rbctarget_hgb;
	rbctarget_hgb = ChartsToCString((*pqcLjXXrEditData).rbctarget.hgb, sizeof((*pqcLjXXrEditData).rbctarget.hgb) / sizeof(char));
	CString rbctarget_hct;
	rbctarget_hct = ChartsToCString((*pqcLjXXrEditData).rbctarget.hct, sizeof((*pqcLjXXrEditData).rbctarget.hct) / sizeof(char));
	CString rbctarget_mcv;
	rbctarget_mcv = ChartsToCString((*pqcLjXXrEditData).rbctarget.mcv, sizeof((*pqcLjXXrEditData).rbctarget.mcv) / sizeof(char));
	CString rbctarget_mch;
	rbctarget_mch = ChartsToCString((*pqcLjXXrEditData).rbctarget.mch, sizeof((*pqcLjXXrEditData).rbctarget.mch) / sizeof(char));
	CString rbctarget_mchc;
	rbctarget_mchc = ChartsToCString((*pqcLjXXrEditData).rbctarget.mchc, sizeof((*pqcLjXXrEditData).rbctarget.mchc) / sizeof(char));
	CString rbctarget_rdw;
	rbctarget_rdw = ChartsToCString((*pqcLjXXrEditData).rbctarget.rdw, sizeof((*pqcLjXXrEditData).rbctarget.rdw) / sizeof(char));
	CString plttarget_plt;
	plttarget_plt = ChartsToCString((*pqcLjXXrEditData).plttarget.plt, sizeof((*pqcLjXXrEditData).plttarget.plt) / sizeof(char));
	CString plttarget_mpv;
	plttarget_mpv = ChartsToCString((*pqcLjXXrEditData).plttarget.mpv, sizeof((*pqcLjXXrEditData).plttarget.mpv) / sizeof(char));
	CString plttarget_pdw;
	plttarget_pdw = ChartsToCString((*pqcLjXXrEditData).plttarget.pdw, sizeof((*pqcLjXXrEditData).plttarget.pdw) / sizeof(char));
	CString plttarget_pct;
	plttarget_pct = ChartsToCString((*pqcLjXXrEditData).plttarget.pct, sizeof((*pqcLjXXrEditData).plttarget.pct) / sizeof(char));
	CString wbcsd_wbc;
	wbcsd_wbc = ChartsToCString((*pqcLjXXrEditData).wbcsd.wbc, sizeof((*pqcLjXXrEditData).wbcsd.wbc) / sizeof(char));
	CString wbcsd_lymp;
	wbcsd_lymp = ChartsToCString((*pqcLjXXrEditData).wbcsd.lymp, sizeof((*pqcLjXXrEditData).wbcsd.lymp) / sizeof(char));
	CString wbcsd_neup;
	wbcsd_neup = ChartsToCString((*pqcLjXXrEditData).wbcsd.neup, sizeof((*pqcLjXXrEditData).wbcsd.neup) / sizeof(char));
	CString wbcsd_monop;
	wbcsd_monop = ChartsToCString((*pqcLjXXrEditData).wbcsd.monop, sizeof((*pqcLjXXrEditData).wbcsd.monop) / sizeof(char));
	CString wbcsd_eosp;
	wbcsd_eosp = ChartsToCString((*pqcLjXXrEditData).wbcsd.eosp, sizeof((*pqcLjXXrEditData).wbcsd.eosp) / sizeof(char));
	CString wbcsd_basp;
	wbcsd_basp = ChartsToCString((*pqcLjXXrEditData).wbcsd.basp, sizeof((*pqcLjXXrEditData).wbcsd.basp) / sizeof(char));
	CString wbcsd_alyp;
	wbcsd_alyp = ChartsToCString((*pqcLjXXrEditData).wbcsd.alyp, sizeof((*pqcLjXXrEditData).wbcsd.alyp) / sizeof(char));
	CString wbcsd_licp;
	wbcsd_licp = ChartsToCString((*pqcLjXXrEditData).wbcsd.licp, sizeof((*pqcLjXXrEditData).wbcsd.licp) / sizeof(char));
	CString wbcsd_lym;
	wbcsd_lym = ChartsToCString((*pqcLjXXrEditData).wbcsd.lym, sizeof((*pqcLjXXrEditData).wbcsd.lym) / sizeof(char));
	CString wbcsd_neu;
	wbcsd_neu = ChartsToCString((*pqcLjXXrEditData).wbcsd.neu, sizeof((*pqcLjXXrEditData).wbcsd.neu) / sizeof(char));
	CString wbcsd_mono;
	wbcsd_mono = ChartsToCString((*pqcLjXXrEditData).wbcsd.mono, sizeof((*pqcLjXXrEditData).wbcsd.mono) / sizeof(char));
	CString wbcsd_eos;
	wbcsd_eos = ChartsToCString((*pqcLjXXrEditData).wbcsd.eos, sizeof((*pqcLjXXrEditData).wbcsd.eos) / sizeof(char));
	CString wbcsd_bas;
	wbcsd_bas = ChartsToCString((*pqcLjXXrEditData).wbcsd.bas, sizeof((*pqcLjXXrEditData).wbcsd.bas) / sizeof(char));
	CString wbcsd_aly;
	wbcsd_aly = ChartsToCString((*pqcLjXXrEditData).wbcsd.aly, sizeof((*pqcLjXXrEditData).wbcsd.aly) / sizeof(char));
	CString wbcsd_lic;
	wbcsd_lic = ChartsToCString((*pqcLjXXrEditData).wbcsd.lic, sizeof((*pqcLjXXrEditData).wbcsd.lic) / sizeof(char));
	CString rbcsd_rbc;
	rbcsd_rbc = ChartsToCString((*pqcLjXXrEditData).rbcsd.rbc, sizeof((*pqcLjXXrEditData).rbcsd.rbc) / sizeof(char));
	CString rbcsd_hgb;
	rbcsd_hgb = ChartsToCString((*pqcLjXXrEditData).rbcsd.hgb, sizeof((*pqcLjXXrEditData).rbcsd.hgb) / sizeof(char));
	CString rbcsd_hct;
	rbcsd_hct = ChartsToCString((*pqcLjXXrEditData).rbcsd.hct, sizeof((*pqcLjXXrEditData).rbcsd.hct) / sizeof(char));
	CString rbcsd_mcv;
	rbcsd_mcv = ChartsToCString((*pqcLjXXrEditData).rbcsd.mcv, sizeof((*pqcLjXXrEditData).rbcsd.mcv) / sizeof(char));
	CString rbcsd_mch;
	rbcsd_mch = ChartsToCString((*pqcLjXXrEditData).rbcsd.mch, sizeof((*pqcLjXXrEditData).rbcsd.mch) / sizeof(char));
	CString rbcsd_mchc;
	rbcsd_mchc = ChartsToCString((*pqcLjXXrEditData).rbcsd.mchc, sizeof((*pqcLjXXrEditData).rbcsd.mchc) / sizeof(char));
	CString rbcsd_rdw;
	rbcsd_rdw = ChartsToCString((*pqcLjXXrEditData).rbcsd.rdw, sizeof((*pqcLjXXrEditData).rbcsd.rdw) / sizeof(char));
	CString pltsd_plt;
	pltsd_plt = ChartsToCString((*pqcLjXXrEditData).pltsd.plt, sizeof((*pqcLjXXrEditData).pltsd.plt) / sizeof(char));
	CString pltsd_mpv;
	pltsd_mpv = ChartsToCString((*pqcLjXXrEditData).pltsd.mpv, sizeof((*pqcLjXXrEditData).pltsd.mpv) / sizeof(char));
	CString pltsd_pdw;
	pltsd_pdw = ChartsToCString((*pqcLjXXrEditData).pltsd.pdw, sizeof((*pqcLjXXrEditData).pltsd.pdw) / sizeof(char));
	CString pltsd_pct;
	pltsd_pct = ChartsToCString((*pqcLjXXrEditData).pltsd.pct, sizeof((*pqcLjXXrEditData).pltsd.pct) / sizeof(char));
	CString insertqceditdata = _T("insert into [qceditdata]([qctype],[filenum],[number],[deadline],[WBC],[LYMP],[NEUP],[MONOP],[EOSP],[BASOP],[ALYP],[LICP],[LYM],[NEU],[MONO],[EOS],[BASO],[ALY],[LIC],[RBC],[HGB],[HCT],[MCV],[MCH],[MCHC],[RDW],[PLT],[MPV],[PDW],[PCT],[WBC_SD],[LYMP_SD],[NEUP_SD],[MONOP_SD],[EOSP_SD],[BASOP_SD],[ALYP_SD],[LICP_SD],[LYM_SD],[NEU_SD],[MONO_SD],[EOS_SD],[BASO_SD],[ALY_SD],[LIC_SD],[RBC_SD],[HGB_SD],[HCT_SD],[MCV_SD],[MCH_SD],[MCHC_SD],[RDW_SD],[PLT_SD],[MPV_SD],[PDW_SD],[PCT_SD]) values('") + 
		qctype.Trim() + "' ,'" + filenum.Trim() + "' ,'" + Number.Trim() + "' ,'" + Deadline.Trim() + "' ,'" +
		wbctarget_wbc.Trim() + "' ,'" + wbctarget_lymp.Trim() + "' ,'" + wbctarget_neup.Trim() + "' ,'" + wbctarget_monop.Trim() + "' ,'" + wbctarget_eosp.Trim() + "' ,'" +
		wbctarget_basp.Trim() + "' ,'" + wbctarget_alyp.Trim() + "' ,'" + wbctarget_licp.Trim() + "' ,'" + wbctarget_lym.Trim() + "' ,'" + wbctarget_neu.Trim() + "' ,'" +
		wbctarget_mono.Trim() + "' ,'" + wbctarget_eos.Trim() + "' ,'" + wbctarget_bas.Trim() + "' ,'" + wbctarget_aly.Trim() + "' ,'" + wbctarget_lic.Trim() + "' ,'" +
		rbctarget_rbc.Trim() + "' ,'" + rbctarget_hgb.Trim() + "' ,'" + rbctarget_hct.Trim() + "' ,'" + rbctarget_mcv.Trim() + "' ,'" + rbctarget_mch.Trim() + "' ,'" +
		rbctarget_mchc.Trim() + "' ,'" + rbctarget_rdw.Trim() + "' ,'" + plttarget_plt.Trim() + "' ,'" + plttarget_mpv.Trim() + "' ,'" + plttarget_pdw.Trim() + "' ,'" +
		plttarget_pct.Trim() + "' ,'" + wbcsd_wbc.Trim() + "' ,'" + wbcsd_lymp.Trim() + "' ,'" + wbcsd_neup.Trim() + "' ,'" + wbcsd_monop.Trim() + "' ,'" + wbcsd_eosp.Trim() + "' ,'" +
		wbcsd_basp.Trim() + "' ,'" + wbcsd_alyp.Trim() + "' ,'" + wbcsd_licp.Trim() + "' ,'" + wbcsd_lym.Trim() + "' ,'" + wbcsd_neu.Trim() + "' ,'" + wbcsd_mono.Trim() + "' ,'" + wbcsd_eos.Trim() + "' ,'" +
		wbcsd_bas.Trim() + "' ,'" + wbcsd_aly.Trim() + "' ,'" + wbcsd_lic.Trim() + "' ,'" + rbcsd_rbc.Trim() + "' ,'" + rbcsd_hgb.Trim() + "' ,'" + rbcsd_hct.Trim() + "' ,'" + rbcsd_mcv.Trim() + "' ,'" +
		rbcsd_mch.Trim() + "' ,'" + rbcsd_mchc.Trim() + "' ,'" + rbcsd_rdw.Trim() + "' ,'" + pltsd_plt.Trim() + "' ,'" + pltsd_mpv.Trim() + "' ,'" + pltsd_pdw.Trim() + "' ,'" + pltsd_pct.Trim() + "');";
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, insertqceditdata);
	CloseDataBase(m_pDB, m_pRs);
	return 0;
}

/*************************************************
*Function:
*Description:	重置质控靶值和偏差限	，并删除对应的测试结果。应用于L-J及X质控
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/
int QcLjXXrEditFileExistReset(qc_edit_data_info *pqcLjXXrEditData)
{
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	char *zStatement = NULL;
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	CString qctype;
	qctype = (*pqcLjXXrEditData).qctype;
	//qctype.Format((*pqcLjXXrEditData).qctype);//张文浩
	CString filenum;
	filenum = (*pqcLjXXrEditData).filenum;
	CString Number;
	Number = ChartsToCString((*pqcLjXXrEditData).Number, sizeof((*pqcLjXXrEditData).Number)/sizeof(char));
	CString Deadline;
	Deadline = ChartsToCString((*pqcLjXXrEditData).Deadline, sizeof((*pqcLjXXrEditData).Deadline) / sizeof(char));
	CString wbctarget_wbc;
	wbctarget_wbc = ChartsToCString((*pqcLjXXrEditData).wbctarget.wbc, sizeof((*pqcLjXXrEditData).wbctarget.wbc) / sizeof(char));
	CString wbctarget_lymp;
	wbctarget_lymp = ChartsToCString((*pqcLjXXrEditData).wbctarget.lymp, sizeof((*pqcLjXXrEditData).wbctarget.lymp) / sizeof(char));
	CString wbctarget_neup;
	wbctarget_neup = ChartsToCString((*pqcLjXXrEditData).wbctarget.neup, sizeof((*pqcLjXXrEditData).wbctarget.neup) / sizeof(char));
	CString wbctarget_monop;
	wbctarget_monop = ChartsToCString((*pqcLjXXrEditData).wbctarget.monop, sizeof((*pqcLjXXrEditData).wbctarget.monop) / sizeof(char));
	CString wbctarget_eosp;
	wbctarget_eosp = ChartsToCString((*pqcLjXXrEditData).wbctarget.eosp, sizeof((*pqcLjXXrEditData).wbctarget.eosp) / sizeof(char));
	CString wbctarget_basp;
	wbctarget_basp = ChartsToCString((*pqcLjXXrEditData).wbctarget.basp, sizeof((*pqcLjXXrEditData).wbctarget.basp) / sizeof(char));
	CString wbctarget_alyp;
	wbctarget_alyp = ChartsToCString((*pqcLjXXrEditData).wbctarget.alyp, sizeof((*pqcLjXXrEditData).wbctarget.alyp) / sizeof(char));
	CString wbctarget_licp;
	wbctarget_licp = ChartsToCString((*pqcLjXXrEditData).wbctarget.licp, sizeof((*pqcLjXXrEditData).wbctarget.licp) / sizeof(char));
	CString wbctarget_lym;
	wbctarget_lym = ChartsToCString((*pqcLjXXrEditData).wbctarget.lym, sizeof((*pqcLjXXrEditData).wbctarget.lym) / sizeof(char));
	CString wbctarget_neu;
	wbctarget_neu = ChartsToCString((*pqcLjXXrEditData).wbctarget.neu, sizeof((*pqcLjXXrEditData).wbctarget.neu) / sizeof(char));
	CString wbctarget_mono;
	wbctarget_mono = ChartsToCString((*pqcLjXXrEditData).wbctarget.mono, sizeof((*pqcLjXXrEditData).wbctarget.mono) / sizeof(char));
	CString wbctarget_eos;
	wbctarget_eos = ChartsToCString((*pqcLjXXrEditData).wbctarget.eos, sizeof((*pqcLjXXrEditData).wbctarget.eos) / sizeof(char));
	CString wbctarget_bas;
	wbctarget_bas = ChartsToCString((*pqcLjXXrEditData).wbctarget.bas, sizeof((*pqcLjXXrEditData).wbctarget.bas) / sizeof(char));
	CString wbctarget_aly;
	wbctarget_aly = ChartsToCString((*pqcLjXXrEditData).wbctarget.aly, sizeof((*pqcLjXXrEditData).wbctarget.aly) / sizeof(char));
	CString wbctarget_lic;
	wbctarget_lic = ChartsToCString((*pqcLjXXrEditData).wbctarget.lic, sizeof((*pqcLjXXrEditData).wbctarget.lic) / sizeof(char));
	CString rbctarget_rbc;
	rbctarget_rbc = ChartsToCString((*pqcLjXXrEditData).rbctarget.rbc, sizeof((*pqcLjXXrEditData).rbctarget.rbc) / sizeof(char));
	CString rbctarget_hgb;
	rbctarget_hgb = ChartsToCString((*pqcLjXXrEditData).rbctarget.hgb, sizeof((*pqcLjXXrEditData).rbctarget.hgb) / sizeof(char));
	CString rbctarget_hct;
	rbctarget_hct = ChartsToCString((*pqcLjXXrEditData).rbctarget.hct, sizeof((*pqcLjXXrEditData).rbctarget.hct) / sizeof(char));
	CString rbctarget_mcv;
	rbctarget_mcv = ChartsToCString((*pqcLjXXrEditData).rbctarget.mcv, sizeof((*pqcLjXXrEditData).rbctarget.mcv) / sizeof(char));
	CString plttarget_mpv;
	plttarget_mpv = ChartsToCString((*pqcLjXXrEditData).plttarget.mpv, sizeof((*pqcLjXXrEditData).plttarget.mpv) / sizeof(char));
	CString plttarget_pdw;
	plttarget_pdw = ChartsToCString((*pqcLjXXrEditData).plttarget.pdw, sizeof((*pqcLjXXrEditData).plttarget.pdw) / sizeof(char));
	CString plttarget_pct;
	plttarget_pct = ChartsToCString((*pqcLjXXrEditData).plttarget.pct, sizeof((*pqcLjXXrEditData).plttarget.pct) / sizeof(char));
	CString wbcsd_wbc;
	wbcsd_wbc = ChartsToCString((*pqcLjXXrEditData).wbcsd.wbc, sizeof((*pqcLjXXrEditData).wbcsd.wbc) / sizeof(char));
	CString wbcsd_lymp;
	wbcsd_lymp = ChartsToCString((*pqcLjXXrEditData).wbcsd.lymp, sizeof((*pqcLjXXrEditData).wbcsd.lymp) / sizeof(char));
	CString wbcsd_neup;
	wbcsd_neup = ChartsToCString((*pqcLjXXrEditData).wbcsd.neup, sizeof((*pqcLjXXrEditData).wbcsd.neup) / sizeof(char));
	CString wbcsd_monop;
	wbcsd_monop = ChartsToCString((*pqcLjXXrEditData).wbcsd.monop, sizeof((*pqcLjXXrEditData).wbcsd.monop) / sizeof(char));
	CString wbcsd_eosp;
	wbcsd_eosp = ChartsToCString((*pqcLjXXrEditData).wbcsd.eosp, sizeof((*pqcLjXXrEditData).wbcsd.eosp) / sizeof(char));
	CString wbcsd_basp;
	wbcsd_basp = ChartsToCString((*pqcLjXXrEditData).wbcsd.basp, sizeof((*pqcLjXXrEditData).wbcsd.basp) / sizeof(char));
	CString wbcsd_alyp;
	wbcsd_alyp = ChartsToCString((*pqcLjXXrEditData).wbcsd.alyp, sizeof((*pqcLjXXrEditData).wbcsd.alyp) / sizeof(char));
	CString wbcsd_licp;
	wbcsd_licp = ChartsToCString((*pqcLjXXrEditData).wbcsd.licp, sizeof((*pqcLjXXrEditData).wbcsd.licp) / sizeof(char));
	CString wbcsd_lym;
	wbcsd_lym = ChartsToCString((*pqcLjXXrEditData).wbcsd.lym, sizeof((*pqcLjXXrEditData).wbcsd.lym) / sizeof(char));
	CString wbcsd_neu;
	wbcsd_neu = ChartsToCString((*pqcLjXXrEditData).wbcsd.neu, sizeof((*pqcLjXXrEditData).wbcsd.neu) / sizeof(char));
	CString wbcsd_mono;
	wbcsd_mono = ChartsToCString((*pqcLjXXrEditData).wbcsd.mono, sizeof((*pqcLjXXrEditData).wbcsd.mono) / sizeof(char));
	CString wbcsd_eos;
	wbcsd_eos = ChartsToCString((*pqcLjXXrEditData).wbcsd.eos, sizeof((*pqcLjXXrEditData).wbcsd.eos) / sizeof(char));
	CString wbcsd_bas;
	wbcsd_bas = ChartsToCString((*pqcLjXXrEditData).wbcsd.bas, sizeof((*pqcLjXXrEditData).wbcsd.bas) / sizeof(char));
	CString wbcsd_aly;
	wbcsd_aly = ChartsToCString((*pqcLjXXrEditData).wbctarget.aly, sizeof((*pqcLjXXrEditData).wbctarget.aly) / sizeof(char));
	CString rbctarget_mch;
	rbctarget_mch = ChartsToCString((*pqcLjXXrEditData).rbctarget.mch, sizeof((*pqcLjXXrEditData).rbctarget.mch) / sizeof(char));
	CString rbctarget_mchc;
	rbctarget_mchc = ChartsToCString((*pqcLjXXrEditData).rbctarget.mchc, sizeof((*pqcLjXXrEditData).rbctarget.mchc) / sizeof(char));
	CString rbctarget_rdw;
	rbctarget_rdw = ChartsToCString((*pqcLjXXrEditData).rbctarget.rdw, sizeof((*pqcLjXXrEditData).rbctarget.rdw) / sizeof(char));
	CString plttarget_plt;
	plttarget_plt = ChartsToCString((*pqcLjXXrEditData).plttarget.plt, sizeof((*pqcLjXXrEditData).plttarget.plt) / sizeof(char));
	CString wbcsd_lic;
	wbcsd_lic = ChartsToCString((*pqcLjXXrEditData).wbcsd.lic, sizeof((*pqcLjXXrEditData).wbcsd.lic) / sizeof(char));
	CString rbcsd_rbc;
	rbcsd_rbc = ChartsToCString((*pqcLjXXrEditData).rbcsd.rbc, sizeof((*pqcLjXXrEditData).rbcsd.rbc) / sizeof(char));
	CString rbcsd_hgb;
	rbcsd_hgb = ChartsToCString((*pqcLjXXrEditData).rbcsd.hgb, sizeof((*pqcLjXXrEditData).rbcsd.hgb) / sizeof(char));
	CString rbcsd_hct;
	rbcsd_hct = ChartsToCString((*pqcLjXXrEditData).rbcsd.hct, sizeof((*pqcLjXXrEditData).rbcsd.hct) / sizeof(char));
	CString rbcsd_mcv;
	rbcsd_mcv = ChartsToCString((*pqcLjXXrEditData).rbcsd.mcv, sizeof((*pqcLjXXrEditData).rbcsd.mcv) / sizeof(char));
	CString rbcsd_mch;
	rbcsd_mch = ChartsToCString((*pqcLjXXrEditData).rbcsd.mch, sizeof((*pqcLjXXrEditData).rbcsd.mch) / sizeof(char));
	CString rbcsd_mchc;
	rbcsd_mchc = ChartsToCString((*pqcLjXXrEditData).rbcsd.mchc, sizeof((*pqcLjXXrEditData).rbcsd.mchc) / sizeof(char));
	CString rbcsd_rdw;
	rbcsd_rdw = ChartsToCString((*pqcLjXXrEditData).rbcsd.rdw, sizeof((*pqcLjXXrEditData).rbcsd.rdw) / sizeof(char));
	CString pltsd_plt;
	plttarget_plt = ChartsToCString((*pqcLjXXrEditData).plttarget.plt, sizeof((*pqcLjXXrEditData).plttarget.plt) / sizeof(char));
	pltsd_plt = (*pqcLjXXrEditData).pltsd.plt;
	CString pltsd_mpv;
	pltsd_mpv = ChartsToCString((*pqcLjXXrEditData).pltsd.mpv, sizeof((*pqcLjXXrEditData).pltsd.mpv) / sizeof(char));
	CString pltsd_pdw;
	pltsd_pdw = ChartsToCString((*pqcLjXXrEditData).pltsd.pdw, sizeof((*pqcLjXXrEditData).pltsd.pdw) / sizeof(char));
	CString pltsd_pct;
	pltsd_pct = ChartsToCString((*pqcLjXXrEditData).pltsd.pct, sizeof((*pqcLjXXrEditData).pltsd.pct) / sizeof(char));
	CString DELedit = _T("delete from qceditdata where qctype ='") + qctype + "' and filenum ='" + filenum+ "'";
	ExeSql(m_pDB, m_pRs, DELedit);
	CString DELresult = _T("delete from qcresultdata where qctype ='") + qctype + "' and filenum ='" + filenum + "'";
	ExeSql(m_pDB, m_pRs, DELresult);
	CString insertqceditdata = _T("insert into [qceditdata]([qctype],[filenum],[number],[deadline],[WBC],[LYMP],[NEUP],[MONOP],[EOSP],[BASOP],[ALYP],[LICP],[LYM],[NEU],[MONO],[EOS],[BASO],[ALY],[LIC],[RBC],[HGB],[HCT],[MCV],[MCH],[MCHC],[RDW],[PLT],[MPV],[PDW],[PCT],[WBC_SD],[LYMP_SD],[NEUP_SD],[MONOP_SD],[EOSP_SD],[BASOP_SD],[ALYP_SD],[LICP_SD],[LYM_SD],[NEU_SD],[MONO_SD],[EOS_SD],[BASO_SD],[ALY_SD],[LIC_SD],[RBC_SD],[HGB_SD],[HCT_SD],[MCV_SD],[MCH_SD],[MCHC_SD],[RDW_SD],[PLT_SD],[MPV_SD],[PDW_SD],[PCT_SD]) values('") + qctype.Trim() + "' ,'" + filenum.Trim() + "' ,'" + Number.Trim() + "' ,'" + Deadline.Trim() + "' ,'" +
		wbctarget_wbc.Trim() + "' ,'" + wbctarget_lymp.Trim() + "' ,'" + wbctarget_neup.Trim() + "' ,'" + wbctarget_monop.Trim() + "' ,'" + wbctarget_eosp.Trim() + "' ,'" +
		wbctarget_basp.Trim() + "' ,'" + wbctarget_alyp.Trim() + "' ,'" + wbctarget_licp.Trim() + "' ,'" + wbctarget_lym.Trim() + "' ,'" + wbctarget_neu.Trim() + "' ,'" +
		wbctarget_mono.Trim() + "' ,'" + wbctarget_eos.Trim() + "' ,'" + wbctarget_bas.Trim() + "' ,'" + wbctarget_aly.Trim() + "' ,'" + wbctarget_lic.Trim() + "' ,'" +
		rbctarget_rbc.Trim() + "' ,'" + rbctarget_hgb.Trim() + "' ,'" + rbctarget_hct.Trim() + "' ,'" + rbctarget_mcv.Trim() + "' ,'" + rbctarget_mch.Trim() + "' ,'" +
		rbctarget_mchc.Trim() + "' ,'" + rbctarget_rdw.Trim() + "' ,'" + plttarget_plt.Trim() + "' ,'" + plttarget_mpv.Trim() + "' ,'" + plttarget_pdw.Trim() + "' ,'" +
		plttarget_pct.Trim() + "' ,'" + wbcsd_wbc.Trim() + "' ,'" + wbcsd_lymp.Trim() + "' ,'" + wbcsd_neup.Trim() + "' ,'" + wbcsd_monop.Trim() + "' ,'" + wbcsd_eosp.Trim() + "' ,'" +
		wbcsd_basp.Trim() + "' ,'" + wbcsd_alyp.Trim() + "' ,'" + wbcsd_licp.Trim() + "' ,'" + wbcsd_lym.Trim() + "' ,'" + wbcsd_neu.Trim() + "' ,'" + wbcsd_mono.Trim() + "' ,'" + wbcsd_eos.Trim() + "' ,'" +
		wbcsd_bas.Trim() + "' ,'" + wbcsd_aly.Trim() + "' ,'" + wbcsd_lic.Trim() + "' ,'" + rbcsd_rbc.Trim() + "' ,'" + rbcsd_hgb.Trim() + "' ,'" + rbcsd_hct.Trim() + "' ,'" + rbcsd_mcv.Trim() + "' ,'" +
		rbcsd_mch.Trim() + "' ,'" + rbcsd_mchc.Trim() + "' ,'" + rbcsd_rdw.Trim() + "' ,'" + pltsd_plt.Trim() + "' ,'" + pltsd_mpv.Trim() + "' ,'" + pltsd_pdw.Trim() + "' ,'" + pltsd_pct.Trim() + "');";
	rbcsd_mch.Trim() + "' ,'" + rbcsd_mchc.Trim() + "' ,'" + rbcsd_rdw.Trim() + "' ,'" + pltsd_plt.Trim() + "' ,'" + pltsd_mpv.Trim() + "' ,'" + pltsd_pdw.Trim() + "' ,'" + pltsd_pct.Trim() + "');";
	ExeSql(m_pDB, m_pRs, insertqceditdata);
	CloseDataBase(m_pDB, m_pRs);
	return 0;
}

/*************************************************
*Function:
*Description:	保存L-J及X及X-R质控运行所获得的样本数据
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/

int AddQcLjXXrResult(qcresult_info *qcresultdata)
{
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	CString row;
	row.Format(_T("%d"), qcresultdata->row);
	CString wbcdata_wbc;
	wbcdata_wbc = ChartsToCString(qcresultdata->wbcdata.wbc, sizeof(qcresultdata->wbcdata.wbc)/sizeof(char));
	CString wbcdata_lymp;
	wbcdata_lymp = ChartsToCString(qcresultdata->wbcdata.lymp, sizeof(qcresultdata->wbcdata.lymp) / sizeof(char));
	CString wbcdata_neup;
	wbcdata_neup = ChartsToCString(qcresultdata->wbcdata.neup, sizeof(qcresultdata->wbcdata.neup) / sizeof(char));
	CString wbcdata_monop;
	wbcdata_monop = ChartsToCString(qcresultdata->wbcdata.monop, sizeof(qcresultdata->wbcdata.monop) / sizeof(char));
	CString wbcdata_eosp;
	wbcdata_eosp = ChartsToCString(qcresultdata->wbcdata.eosp, sizeof(qcresultdata->wbcdata.eosp) / sizeof(char));
	CString wbcdata_basp;
	wbcdata_basp = ChartsToCString(qcresultdata->wbcdata.basp, sizeof(qcresultdata->wbcdata.basp) / sizeof(char));
	CString wbcdata_alyp;
	wbcdata_alyp = ChartsToCString(qcresultdata->wbcdata.alyp, sizeof(qcresultdata->wbcdata.alyp) / sizeof(char));
	CString wbcdata_licp;
	wbcdata_licp = ChartsToCString(qcresultdata->wbcdata.licp, sizeof(qcresultdata->wbcdata.licp) / sizeof(char));
	CString wbcdata_lym;
	wbcdata_lym = ChartsToCString(qcresultdata->wbcdata.lym, sizeof(qcresultdata->wbcdata.lym) / sizeof(char));
	CString wbcdata_neu;
	wbcdata_neu = ChartsToCString(qcresultdata->wbcdata.neu, sizeof(qcresultdata->wbcdata.neu) / sizeof(char));
	CString wbcdata_mono;
	wbcdata_mono = ChartsToCString(qcresultdata->wbcdata.mono, sizeof(qcresultdata->wbcdata.mono) / sizeof(char));
	CString wbcdata_eos;
	wbcdata_eos = ChartsToCString(qcresultdata->wbcdata.eos, sizeof(qcresultdata->wbcdata.eos) / sizeof(char));
	CString wbcdata_bas;
	wbcdata_bas = ChartsToCString(qcresultdata->wbcdata.bas, sizeof(qcresultdata->wbcdata.bas) / sizeof(char));
	CString wbcdata_aly;
	wbcdata_aly = ChartsToCString(qcresultdata->wbcdata.aly, sizeof(qcresultdata->wbcdata.aly) / sizeof(char));
	CString wbcdata_lic;
	wbcdata_lic = ChartsToCString(qcresultdata->wbcdata.lic, sizeof(qcresultdata->wbcdata.lic) / sizeof(char));
	CString rbcdata_rbc;
	rbcdata_rbc = ChartsToCString(qcresultdata->rbcdata.rbc, sizeof(qcresultdata->rbcdata.rbc) / sizeof(char));
	CString rbcdata_hgb;
	rbcdata_hgb = ChartsToCString(qcresultdata->rbcdata.hgb, sizeof(qcresultdata->rbcdata.hgb) / sizeof(char));
	CString rbcdata_hct;
	rbcdata_hct = ChartsToCString(qcresultdata->rbcdata.hct, sizeof(qcresultdata->rbcdata.hct) / sizeof(char));
	CString rbcdata_mcv;
	rbcdata_mcv = ChartsToCString(qcresultdata->rbcdata.mcv, sizeof(qcresultdata->rbcdata.mcv) / sizeof(char));
	CString rbcdata_mch;
	rbcdata_mch = ChartsToCString(qcresultdata->rbcdata.mch, sizeof(qcresultdata->rbcdata.mch) / sizeof(char));
	CString rbcdata_mchc;
	rbcdata_mchc = ChartsToCString(qcresultdata->rbcdata.mchc, sizeof(qcresultdata->rbcdata.mchc) / sizeof(char));
	CString rbcdata_rdw;
	rbcdata_rdw = ChartsToCString(qcresultdata->rbcdata.rdw, sizeof(qcresultdata->rbcdata.rdw) / sizeof(char));
	CString pltdata_plt;
	pltdata_plt = ChartsToCString(qcresultdata->pltdata.plt, sizeof(qcresultdata->pltdata.plt) / sizeof(char));
	CString pltdata_mpv;
	pltdata_mpv = ChartsToCString(qcresultdata->pltdata.mpv, sizeof(qcresultdata->pltdata.mpv) / sizeof(char));
	CString pltdata_pdw;
	pltdata_pdw = ChartsToCString(qcresultdata->pltdata.pdw, sizeof(qcresultdata->pltdata.pdw) / sizeof(char));
	CString pltdata_pct;
	pltdata_pct = ChartsToCString(qcresultdata->pltdata.pct, sizeof(qcresultdata->pltdata.pct) / sizeof(char));
	CString lmnegraph;
	lmnegraph = ChartsToCStringdata(qcresultdata->lmnegraph, sizeof(qcresultdata->lmnegraph) / sizeof(char));
	CString basograph;
	basograph = ChartsToCStringdata(qcresultdata->basograph, sizeof(qcresultdata->basograph) / sizeof(char));
	CString rbcgraph;
	rbcgraph = ChartsToCStringdata(qcresultdata->rbcgraph, sizeof(qcresultdata->rbcgraph) / sizeof(char));
	CString pltgraph;
	pltgraph = ChartsToCStringdata(qcresultdata->pltgraph, sizeof(qcresultdata->pltgraph) / sizeof(char));
	CString lmneflg;
	lmneflg = ChartsToCString(qcresultdata->lmneflg, sizeof(qcresultdata->lmneflg) / sizeof(char));
	CString basoflg;
	basoflg = ChartsToCString(qcresultdata->basoflg, sizeof(qcresultdata->basoflg) / sizeof(char));
	CString rbcflg;
	rbcflg = ChartsToCString(qcresultdata->rbcflg, sizeof(qcresultdata->rbcflg) / sizeof(char));
	CString pltflg;
	pltflg = ChartsToCString(qcresultdata->pltflg, sizeof(qcresultdata->pltflg) / sizeof(char));
	CString qctype;
	qctype=(qcresultdata->qctype);
	CString filenum;
	filenum = qcresultdata->filenum;
	CString time1;
	
	//date = ChartsToCString(qcresultdata->date, sizeof(qcresultdata->date) / sizeof(char));
	time(&systime);
	caltime = localtime(&systime);
	qcresultdata->time = (caltime->tm_hour) * 10000 + (caltime->tm_min) * 100 + caltime->tm_sec;
	
	sprintf(qcresultdata->date, "%04d-%02d-%02d", caltime->tm_year + 1900, caltime->tm_mon + 1, caltime->tm_mday);//mny,20171219
	
	time1.Format(_T("%d"), qcresultdata->time);
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	CString insertqcresult = _T("insert into [qcresultdata]([row],[WBC],[LYMP],[NEUP],[MONOP],[EOSP],[BASOP],[ALYP],[LICP],[LYM],[NEU],[MONO],[EOS],[BASO],[ALY],[LIC],[RBC],[HGB],[HCT],[MCV],[MCH],[MCHC],[RDW],[PLT],[MPV],[PDW],[PCT],[lmne],[basograph],[rbcgraph],[pltgraph],[lmneflg],[basoflg],[rbcflg],[pltflg],[qctype],[filenum],[time],[date]) values(") + row + " ,'" + wbcdata_wbc + "' ,'" + wbcdata_lymp + "' ,'" + wbcdata_neup + "' ,'" +
		wbcdata_monop + "' ,'" + wbcdata_eosp + "' ,'" + wbcdata_basp + "' ,'" + wbcdata_alyp + "' ,'" + wbcdata_licp + "' ,'" + wbcdata_lym + "' ,'" +
		wbcdata_neu + "' ,'" + wbcdata_mono + "' ,'" + wbcdata_eos + "' ,'" + wbcdata_bas + "' ,'" + wbcdata_aly + "' ,'" + wbcdata_lic + "' ,'" +
		rbcdata_rbc + "' ,'" + rbcdata_hgb + "' ,'" + rbcdata_hct + "' ,'" + rbcdata_mcv + "' ,'" + rbcdata_mch + "' ,'" + rbcdata_mchc + "' ,'" +
		rbcdata_rdw + "' ,'" + pltdata_plt + "' ,'" + pltdata_mpv + "' ,'" + pltdata_pdw + "' ,'" + pltdata_pct + "' ,'" + lmnegraph + "' ,'" + 
		basograph + "' ,'" + rbcgraph + "' ,'" + pltgraph + "' ,'" + lmneflg + "' ,'" + basoflg + "' ,'" + rbcflg + "' ,'" + pltflg + "' ,'" 
		+ qctype + "' ,'" + filenum + "' ,'" + time1 + "' ,'" + qcresultdata->date + "');";
	
	//[lmne],[basograph],,[pltgraph]
	//+ lmnegraph + "' ,'" + basograph + "' ,'" +  + "' ,'"+pltgraph
	CString testtesttest = _T("insert into [qcresultdata]([rbcgraph]) values('")  + rbcgraph + "');";
	//ExeSql(m_pDB, m_pRs, insertqcresult);
	ExeSql(m_pDB, m_pRs, insertqcresult);
	CloseDataBase(m_pDB, m_pRs);
	return 0;
}

/*************************************************
*Function:
*Description:	删除L-J及X及X-R质控运行所获得的样本数据
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/
int DelQcLjXXrResult(unsigned int qctypeparam, unsigned int filenumparam, unsigned int rowparam)
{
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	CString qctypeparam1;
	qctypeparam1.Format(L"%d",qctypeparam);
	CString filenumparam1;
	filenumparam1.Format(L"%d",filenumparam);
	CString rowparam1;
	rowparam1.Format(L"%d",rowparam);
	CString DEL_QcRow = _T("delete from qcresultdata where qctype ='") + qctypeparam1 + "'and filenum ='" + filenumparam1 + "' and row =" + rowparam1 + "";
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, DEL_QcRow);
	CloseDataBase(m_pDB, m_pRs);
	return 0;
}

/*************************************************
*Function:
*Description:	清空所有的X-B质控列表中的数据
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/

int EmptyXB_ListRecord()
{
	//char *zStatement = NULL;
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	//char DELXB_List[] = "delete from XB_Listdata";
	CString DELXB_List = _T("delete from XB_Listdata");
	//char DEL[] = "delete from XB_QCdata;";
	CString DEL = _T("delete from XB_QCdata;");
	if (OpenDataBase(filename,m_pDB,m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, DELXB_List);
	ExeSql(m_pDB, m_pRs, DEL);
	CloseDataBase(m_pDB, m_pRs);
	return 0;
}

/*************************************************
*Function:
*Description:	获得最后记录数和当前日期的最后编号数
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/
void GetRowNo( int &row,  int &number)
{
	static unsigned int date;
	static unsigned int today_count;		//num的前面的部分
	unsigned int today_num;
	unsigned int today_start_num;
	static unsigned int today_end_num;
	time(&systime);
	caltime = localtime(&systime);
	date = (caltime->tm_year + 1900) * 10000 + (caltime->tm_mon + 1) * 100 + caltime->tm_mday;
	//由于位数原因，编号在存入数据库的日期的高两位截取掉
	today_start_num = (date % 1000000) * 10000;
	today_end_num = today_start_num + 9999;
	CString select_row = _T("select * from sampledata;");
	//以时间开的头，用SQL语句的LIKE来操作
	CString today_start_num_1;
	today_start_num_1.Format(_T("%d"), today_start_num);
	CString today_end_num_1;
	today_end_num_1.Format(_T("%d"), today_end_num);
	CString select_number = _T("select * from sampledata where number >='") + today_start_num_1 + "'and number <='" + today_end_num_1 + "';";
	CString select_max = _T("SELECT MAX(number) AS maxnum FROM sampledata WHERE number >='") + today_start_num_1 + "' and number <='" + today_end_num_1 + "';";
	//hw_debug	
	TRACE("=========In GetRowNo=============\n");
	TRACE("date: %d-------------------------------\n", date);
	TRACE("today_start_num: %d-------------------------------\n", today_start_num);
	today_count = 0;
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	if (OpenDataBase(filename, m_pDB, m_pRs) != -1)
	{
		//查询总记录数
		ExeSql(m_pDB, m_pRs, select_row);
		row = int(m_pRs->GetRecordCount());
		//查询当天已做数量
		ExeSql(m_pDB, m_pRs, select_number);
		today_count = int(m_pRs->GetRecordCount());
		//hw_debug
		TRACE("today_count: %d-------------------------------\n", today_count);
		if (today_count != 0)
		{
			ExeSql(m_pDB, m_pRs, select_max);
			loadnum_maxnum(m_pDB, m_pRs, today_num);
		}
		CloseDataBase(m_pDB, m_pRs);
		(row)++;
		if (today_count != 0)
			number = today_num + 1;
		else
			number = today_start_num + 1;

		TRACE("number : %d------------------------------------\n", number);
		TRACE("=========GetRowNo  End=============\n");
	}
}



/*************************************************
*Function:
*Description:	添加工作表记录
*Called by:
*Params illustration:
*Data Access:
*History:
*************************************************/
int AddWorkSheet(task_info* ptaskdata)
{
	CString filename;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	CString tasknum, number, mode, status, name, sex, age, doctor, time, remark;
	//tasknum.Format(L"%d", ptaskdata->tasknum);
	number.Format(L"%d", ptaskdata->number);
	mode.Format(L"%d", ptaskdata->mode);
	sex.Format(L"%d",ptaskdata->sex);

	status = ChartsToCString(ptaskdata->status, sizeof(ptaskdata->status) / sizeof(char));
	name = ChartsToCString(ptaskdata->name, sizeof(ptaskdata->name) / sizeof(char));
	

	CString updateWorkSheet = "update ";
	CString insertWorkSheet = "";
	static char **dbResult;
	return 0;
}

int strcopy_ex(void* dest, void* src)
{
	if (dest == NULL || src == NULL)
		return -1;
	unsigned char* to = (unsigned char*)dest;
	unsigned char* from = (unsigned char*)src;
	while (*to++ = *from++);
	return 0;
}