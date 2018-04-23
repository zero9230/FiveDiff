#include "StructDefine.h"

#pragma once
class QcDataProcess
{
public:
	QcDataProcess();
	~QcDataProcess();

	void QcWbcBasoAnalysis(qcresult_info *psampledata);
	void QcLmneAnalysis(qcresult_info *psampledata);
	void QcHgbAnalysis(qcresult_info *psampledata);
	void QcRbcAnalysis(qcresult_info *psampledata);
	void QcPltAnalysis(qcresult_info *psampledata);

	void QcFramePaint(HDC hdc);
	void QcWbcBasoGraphPaint(HDC hdc, qcresult_info *psampledata);
	void QcLmneGraphPaint(HDC hdc, qcresult_info *psampledata);
	void QcRbcGraphPaint(HDC hdc, qcresult_info *psampledata);
	void QcPltGraphPaint(HDC hdc, qcresult_info *psampledata);
	void QcThresholdsPaint(HDC hdc);

};

