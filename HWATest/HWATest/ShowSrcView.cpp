// ShowSrcView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowSrcView.h"


// CShowSrcView

IMPLEMENT_DYNCREATE(CShowSrcView, CHWATestView)

CShowSrcView::CShowSrcView()
: m_bHex(false)
{
	m_bLock = false;
	m_bRecvDataPro = false;
	m_RecvList.clear();//接收数据队列
	m_hRecvListMtx = CreateMutex(NULL,FALSE,NULL);
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowSrcView::~CShowSrcView()
{
	m_hRecvListMtx = NULL;
	m_bLock = false;
	m_RecvList.clear();//接收数据队列
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowSrcView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_SRC_CLEAR, &CShowSrcView::OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_SRC_CLEAR, &CShowSrcView::OnUpdateClearView)
	ON_COMMAND(IDR_SRC_LOCK, &CShowSrcView::OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_SRC_LOCK, &CShowSrcView::OnUpdateLockView)
	ON_COMMAND(IDR_SRC_HEX, &CShowSrcView::OnClickHex)
	ON_UPDATE_COMMAND_UI(IDR_SRC_HEX, &CShowSrcView::OnUpdateClickHex)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CShowSrcView drawing

void CShowSrcView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowSrcView diagnostics

#ifdef _DEBUG
void CShowSrcView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowSrcView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowSrcView message handlers

int CShowSrcView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here 
	CRect rect;
	rect.SetRectEmpty();
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)
	}
	m_wndToolBar.LoadToolBar(IDR_SRC_TOOLBAR);

	dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL|LVS_REPORT;
	CRect chartRect(rect.left,rect.top+30,rect.Width (),rect.Height()-30);
	m_listCtrl.m_bVisualManagerStyle = true;
	if (!m_listCtrl.Create(dwStyle, chartRect, this, 1))
	{
		TRACE0("未能创建列表窗口\n");
		return -1;      // 未能创建
	}
	/*m_listCtrl.SetBkColor(RGB(227,239,255));
	m_listCtrl.SetTextBkColor(RGB(227,239,255));
	m_listCtrl.SetTextColor(RGB(0,0,255));*/
	dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER;// | LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.SetExtendedStyle(dwStyle);
	m_listCtrl.InsertColumn(0, "帧头", LVCFMT_CENTER, 60, -1);
	m_listCtrl.InsertColumn(1, "数据包", LVCFMT_LEFT, 1000, -1);
	//AfxBeginThread(DisposeData, this);

	return 0;
}

void CShowSrcView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-40,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}
void CShowSrcView::Clear()
{
	OnClearView();
}
void CShowSrcView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowSrcView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowSrcView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("文本控制台");
}

void CShowSrcView::RefreshView(char* pBuff, int len)
{
	unsigned int id = 0, i = 0;
	CString str,strText;
	if (m_listCtrl.GetItemCount() > 1000)
		m_listCtrl.DeleteAllItems();

	if (theApp.m_nProtocol == 2)
	{
		id = (pBuff[4] & 0xFF) | ((pBuff[5] << 8) & 0xFF00);
		str.Format("%d", id);
		m_listCtrl.InsertItem(0, str);
		str.Empty();
		strText.Empty();
		for (i=0; i<len; i++)
		{
			str.Format("%02X ", pBuff[i] & 0xFF);
			strText += str;
		}
		m_listCtrl.SetItemText(0, 1, strText);
	} 
	else
	{
		CString strText = CString(pBuff);
		strText.ReleaseBuffer(len-2);
		m_listCtrl.InsertItem(0, strText.Left(6));
		m_listCtrl.SetItemText(0, 1, strText);
	}
}

void CShowSrcView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_SRC* src = new BD2_SRC;
	memcpy(src, data->buffer, sizeof(BD2_SRC));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(src->Buffer, src->length);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete src;
}

void CShowSrcView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowSrcView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}
void CShowSrcView::OnClickHex()
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bHex = !m_bHex;
	LeaveCriticalSection(&m_BufferCriticalSection);
}
void CShowSrcView::OnUpdateClickHex(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}
UINT CShowSrcView::DisposeData(LPVOID lparm)
{
	CShowSrcView* obj = (CShowSrcView*)lparm;
	return obj->_DisposeData();
}
UINT CShowSrcView::_DisposeData()
{
	unsigned int id = 0;
	int len = 0, i = 0;
	CString str,strText;
	m_bRecvDataPro = true;
	while(true)
	{
		WaitForSingleObject(m_hRecvListMtx,INFINITE);
		len = m_RecvList.size();
		if (len > 0)
		{
			try
			{
				ComPackageData* pData = m_RecvList.front();
				m_RecvList.pop_front();
				if (pData)
				{
				//处理数据
					if (theApp.m_nProtocol == 2)
					{
						id = (pData->pBuffer[4] & 0xFF) | ((pData->pBuffer[5] << 8) & 0xFF00);
						str.Format("%d", id);
						m_listCtrl.InsertItem(0, str);
						str.Empty();
						strText.Empty();
						for (i=0; i<pData->nLength; i++)
						{
							str.Format("%02X ", pData->pBuffer[i] & 0xFF);
							strText += str;
						}
						m_listCtrl.SetItemText(0, 1, strText);
					} 
					else
					{
						CString strText = CString(pData->pBuffer);
						strText.ReleaseBuffer(pData->nLength-2);
						m_listCtrl.InsertItem(0, strText.Left(6));
						m_listCtrl.SetItemText(0, 1, strText);
					}
					free(pData->pBuffer);
					delete pData;
				}
			}
			catch (...)
			{
			}
		}
		else if(!m_bRecvDataPro)
				break;
		ReleaseMutex(m_hRecvListMtx);
		Sleep(15);
	}
	return 0;
}

void CShowSrcView::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_bRecvDataPro = false;
	Sleep(25);
	m_listCtrl.DeleteAllItems();
	if(m_RecvList.size() > 0)
		m_RecvList.clear();

	CHWATestView::OnClose();
}
