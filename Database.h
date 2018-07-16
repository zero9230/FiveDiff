#ifndef __DATABASE_H__
#define __DATABASE_H__ 
CString ChartsToCString(char * chart, int len);
int OpenDataBase(CString filename, _ConnectionPtr  &m_pDB, _RecordsetPtr &m_pRs);
int CloseDataBase(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs);
int loadnum(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, unsigned int *param);
int IS_NO_exist(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, int *param);
//int loadpatient(void *param, int n_column, char **column_value, char **column_name);
int loadpatient(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, patient_info &param);
int loaddoctor(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, doctor_info &param);
int loadresult(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, sample_info &param);
int ExeSql(_ConnectionPtr  &m_pDB, _RecordsetPtr   &m_pRs, CString sql);
int AddSampleRecord(sample_info *psampledata);
int AddPatientRecord(patient_info *ppatientdata);
int QcLjXXrEditFileAdd(qc_edit_data_info *pqcLjXXrEditData);
int QcLjXXrEditFileAdd2(qc_edit_data_info *pqcLjXXrEditData);
int AddQcLjXXrResult(qcresult_info *qcresultdata);
int QcLjXXrEditFileExistReset(qc_edit_data_info *pqcLjXXrEditData);
int DelQcLjXXrResult(unsigned int qctypeparam, unsigned int filenumparam, unsigned int rowparam);
int EmptyXB_ListRecord(void);
void GetRowNo( int &row,  int &number);
int strcopy_ex(void* dest, void* src);
int AddWorkSheet(int &row, int &number);
#endif
