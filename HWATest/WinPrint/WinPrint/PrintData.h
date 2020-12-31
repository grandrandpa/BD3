#pragma once

extern CString strFREQ[13];
class CPrintData
{
public:
	CPrintData(void);
	~CPrintData(void);
private:
	CString m_strPath;
	CString m_strSaveData;
	CString m_strConfigPath;
private:
	unsigned char  m_nLeap;
	unsigned int m_globalWeek;
	double		 m_globalTow;
	double		 m_nRanTime;
	BD2_RAN	m_packRAN[15];
	BD2_RAN	m_cacheRAN[15];
	BD2_EPH m_cacheEPH[13][64];
	BD2_ION m_cacheION[13][64];
	//flag
	bool m_bBDEPHFlag;
	bool m_bBSEPHFlag;
	bool m_bBDIONFlag;
	bool m_bBSIONFlag;
	bool m_bBDALMFlag;
	bool m_bBSALMFlag;
	bool m_bBSJALFlag;
	bool m_bBDRANFlag;
	void Reset();
	bool CompareEPH(BD2_EPH* eph0, BD2_EPH* eph1);
	bool CompareION(BD2_ION* ion0, BD2_ION* ion1);
public:
	void LoadConfig(CString strSaveData, CString strConfigPath);
	void SaveCODFile(BD2_COD* data);
	void SaveEPHFile(BD2_EPH* data);
	void SaveIONFile(BD2_ION* data);
	void SaveALMFile(BD2_ALM* data);
	void SaveJALFile(BD2_JAL* data);
	void SavePOSFile(BD2_POS* data);
	void SaveXPVFile(BD2_POS* data);
	void SaveRANFile(BD2_RAN* data);
	void SaveGSVFile(BD2_GSV* data);
	void SaveSTAFile(BD2_STA* data);
	void SaveTIMFile(BD2_TIME* data);
	void SaveGBSFile(BD2_GBS* data);
	void SaveREFFile(SETREF* data);
	void SaveCOMFile(SETCOM* data);
	void SaveMODFile(SETMOD* data);
	void SaveTESTFile(BD2_PAORDER* data);
	void SaveCHDFile(BD2_CHD* data);


	
};
