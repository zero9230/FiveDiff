#pragma once
class DataProcess
{
public:
	DataProcess();
	~DataProcess();
	void	BasoLmneRbcPlt_2Analyse(sample_info *psampledata);
	void	WbcBasoAnalysis(sample_info *psampledata, uchar* pIsSuper);
	void	LmneCoeCalculate(sample_info *psampledata);
	void	LmneAmpRes(sample_info *psampledata);
	void	Init_B_LMNE(float	coefficient, B_LMNE* p_blmne);
	int		LmneAnalysis(sample_info *psampledata, uchar* pIsSuper);
	void	HgbAnalysis(sample_info *psampledata);
	void	PltAnalysis(sample_info *psampledata);
	void	RbcAnalysis(sample_info *psampledata, const uchar* pIsSuper);
	

	bool	PLTDisplayGraph(float plt);

	void	IsBlocking_RBC(sample_info* pSampleData);

	/*void TwoGroupPaint(HDC hdc);
	void FramePaint(HDC hdc);
	void SampleIDPaint(HWND hDlg, HDC hdc, patient_info *ppatientdata);
	void PatientPaint(HDC hdc, patient_info *ppatientdata);
	void WbcBasoGraphPaint(HDC hdc, sample_info *psampledata, const unsigned char rangetype);
	void LmneGraphPaint(HDC hdc, sample_info *psampledata, const unsigned char rangetype);
	void RbcGraphPaint(HDC hdc, sample_info *psampledata, const unsigned char rangetype);
	void PltGraphPaint(HDC hdc, sample_info *psampledata, const unsigned char rangetype);
	void Threshold_LMNE(HDC hdc, sample_info* psampledata);
	void ThresholdsPaint(HDC hdc, sample_info* psampledata, uchar pltmode);*/

public:

	static double		WbcForCompare ;    //用于比较wbc/baso通道与LMNE通道wbc总数，从而判断堵?
};

