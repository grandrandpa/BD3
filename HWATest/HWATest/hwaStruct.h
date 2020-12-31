#pragma once
#define VAR_LEN 1000

#define MINSNR  10
#define MAXSNR  70
struct CDemoFeature
{
	int				nID;
	CString			strName;
	CRuntimeClass*	pClass;
	CMultiDocTemplate * pTemplate;
	CView*			pView;
	CDemoFeature()
	{
		nID = 0;
		strName = "";
		pView = NULL;
		pClass = NULL;
		pTemplate = NULL;
	}
	CDemoFeature(int nID, CString strName, CMultiDocTemplate* pTemplate = NULL, CRuntimeClass*	pClass = NULL, CView* pView = NULL)
	{
		nID = nID;
		strName = strName;
		pClass = pClass;
		pTemplate = pTemplate;
		pView = pView;
	}
};

typedef struct CalDiviation 
{
	double average; //平均值
	double root; //方差
	double maxVal;  //最大值
	double minVal;  //最小值
	int length;
	CalDiviation()
	{
		average = 0;
		root = 0;
		maxVal = 0;
		minVal = 0;
		length = 0;
	}
}CalDiviation;

typedef struct CGlobalVariant 
{
	int length;
	unsigned char* buffer;
	void Clean()
	{
		length = 0;
		buffer = NULL;
	}
	CGlobalVariant()
	{
		Clean();
	}
}CGlobalVariant;
