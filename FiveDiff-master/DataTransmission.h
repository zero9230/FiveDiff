#pragma once
class DataTransmission
{
public:
	DataTransmission();
	~DataTransmission();
	void  GetNormalData_BASO(sample_info*);
	void  GetNormalData_LMNE(sample_info*);
	void  GetNormalData_HGB();
	void  GetNormalData_RBC(sample_info*);
	void  GetNormalData_PLT(sample_info*);
	void  GetNormalTestData(uchar, sample_info*);

	CSpi m_spidev;
private:
	void doGetNormalData(int	loop_times, uchar CMD, uchar DataType, uchar* target, const char* strFlag);
};

