#pragma once
//#include "afx.h"
#include "Includes_app.h"
class CLogProcedure
{
public:
	CLogProcedure(void);
	~CLogProcedure(void);
	void WriteRecord(CString inputstring);
	void ReadRecord(void);

	CEdit m_edlog;

private:
	static CStdioFile m_plogFile;
};