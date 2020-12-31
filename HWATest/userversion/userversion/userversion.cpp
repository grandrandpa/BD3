// userversion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "userversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;


void OutHelp()
{
	cout<<"*******************************************************"<<endl;
	cout<<" *** Build at: "<<__DATE__<<" "<<__TIME__<<" By wu.xp"<<endl;
	cout<<" *** userversion.exe config.ini "<<endl;
	cout<<"*******************************************************"<<endl;
	cout<<"     Please enter the valid filename"<<endl;
}  

int Exit(int exit)
{
	if(exit)
	{
		cout<<"Please press Enter to exit!"<<endl;
		getchar();
	}
	return exit;
}
// The one and only application object
CWinApp theApp;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	CString strText,strPath;
	int nRetCode = 0;
	char buf[MAX_PATH];
	int version[4]={0};
	CString strUser = getenv("username");
	CTime tt = CTime::GetCurrentTime();
	GetCurrentDirectory(MAX_PATH, buf);
	strText = CString(buf);
	strPath = strText + "\\" + argv[1];
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
		OutHelp();
		Exit(argc);
	}
	else
	{
		// TODO: code your application's behavior here.
		cout<<"write parameter to "<<argv[1]<<endl;
		WritePrivateProfileString("Product", "Author", strUser, strPath);
		cout<<"Author="<<strUser<<endl;
		GetPrivateProfileString("Product", "Version", "V3.0.0.0", buf, MAX_PATH, strPath);
		sscanf(buf, "V%d.%d.%d.%d", &version[0], &version[1], &version[2], &version[3]);
		version[3]++;
		if (version[3] > 20)
		{
			version[2]++;
			version[3] = 0;
			if (version[2] > 12)
			{
				version[1]++;
				version[2] = 0;
				if (version[1] > 9)
				{
					version[0]++;
					version[1] = 0;
					if (version[0] > 9)
					{
						version[0] = 0;
					}
				}
			}
		}
		strText.Format("V%d.%d.%d.%d", version[0], version[1], version[2], version[3]);
		WritePrivateProfileString("Product", "Version", strText, strPath);
		cout<<"Version="<<strText<<endl;
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", tt.GetYear(), tt.GetMonth(), tt.GetDay(), tt.GetHour(), tt.GetMinute(), tt.GetSecond());
		WritePrivateProfileString("Product", "Date", strText, strPath);
		cout<<"Date="<<strText<<endl;
	}

	return nRetCode;
}
