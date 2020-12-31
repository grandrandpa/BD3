// username.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
using namespace std;

void OutHelp()
{
	cout<<"*******************************************************"<<endl;
	cout<<" *** Build at: "<<__DATE__<<" "<<__TIME__<<endl;
	cout<<" *** username.exe username.h"<<endl;
	cout<<"*******************************************************"<<endl;
}  

int Exit(int exit)
{
	if(exit)
	{
		cout<<" *** Please press Enter to exit!"<<endl;
		getchar();
	}
	return exit;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CString strName, str;
	CString usName = "#define __USERNAME__ ";
	CString vsName = "#define __VERSION__ ";
	strName = getenv("username");

	OutHelp();
	if(argc == 2)
	{
		FILE *pFile;
		if((pFile=fopen(argv[1], "w+t")) == NULL) //ÎÄ±¾
		{
			cout<<" *** Open File "<<argv[1]<<" Failure"<<endl;
			return Exit(1);
		}
		str.Format("%s \"%s\"", usName, strName);
		fwrite(str,sizeof(char), str.GetLength(), pFile);

		cout<<" *** UserName is "<<strName<<endl;
		fclose(pFile);
		cout<<" *** GetUserName Successful "<<endl;
	}
	else
	{
		return Exit(1);
	}
	return 0;
}

