#pragma once

typedef struct FilePackData 
{
	char* pBuffer;
	int nLength;
	FilePackData()
	{
		nLength = 0;
		pBuffer = NULL;
	}
}FilePackData;

class CFileStore
{
public:
	CFileStore(void);
	~CFileStore(void);
private:
	CStdioFile m_file;
	BOOL m_bOpen;
	BOOL m_bStartWrite;
	CWinThread* m_pWriteThread;
	list<FilePackData*> m_storeData;
	CRITICAL_SECTION	m_Lock;//ÁÙ½çÇø
public:
	bool Open(CString strName, UINT flag);
	void Write(char* pBuff, int len);
	void Close();
private:
	static UINT WriteDataPro(LPVOID lparm);
	UINT _WriteDataPro();
};

