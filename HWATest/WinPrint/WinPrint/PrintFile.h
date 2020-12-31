#pragma once

#define __SAVE_SAT_POS_ 1
class CPrintFile
{
public:
	CPrintFile(void);
	~CPrintFile(void);
private:
	int		m_nStart;
	CString m_strPath;
	CString m_strConfigPath;
	CString m_strDatabase;
public:
	void LoadConfig(CString strDatabase, CString strConfigPath);
	void SaveCODFile(BD2_COD* data);
	void SaveEPHFile(BD2_EPH* data);
	void SaveIONFile(BD2_ION* data);
	void SaveALMFile(BD2_ALM* data);
	void SaveJALFile(BD2_JAL* data);
	void SaveCOMFile(SETCOM* data);
	void SaveMODFile(SETMOD* data);
	void SavePOSFile(BD2_POS* data);
	void SaveRANFile(BD2_RAN* data);
	void SaveREFFile(SETREF* data);
	void SaveGSVFile(BD2_GSV* data);
	void SaveSTAFile(BD2_STA* data);
	void SaveTIMFile(BD2_TIME* data);
	void SaveGBSFile(BD2_GBS* data);
	void SaveXPVFile(BD2_POS* data);
	void SaveTESTFile(BD2_PAORDER* data);
	void SaveCHDFile(BD2_CHD* data);
	

    void SaveAllGSVFile(NmeaAllData* data);
};
