#pragma once
#include <atlcoll.h>

template <typename T >
class CompListener 
{
protected:
	CAtlArray<T*>	m_iListeners;
	CAtlArray<HWND>	m_hListeners;

//operations
public:
	bool Add ( T *pListener )
	{
		if ( NULL == pListener )
		{
			ATLASSERT ( false );
			return false;
		}

		for ( int i = 0; i < (int)m_iListeners.GetCount(); ++i )
		{
			if ( pListener == m_iListeners[i] )
			{
				return false;
			}
		}
		m_iListeners.Add( pListener );
		return true;
	}

	bool Add ( HWND hWnd )
	{
		if ( NULL == hWnd )
		{
			ATLASSERT ( false );
			return false;
		}

		for ( int i = 0; i < (int)m_hListeners.GetCount(); ++i )
		{
			if ( hWnd == m_hListeners[i] )
			{
				return false;
			}
		}
		m_hListeners.Add( hWnd );
		return true;
	}

	bool Remove( T *pListener )
	{
		if ( NULL == pListener )
		{
			ATLASSERT( false );
			return false;
		}

		int count = m_iListeners.GetCount();
		if(count <= 0)
			return false;

		for ( int i = 0; i < count; ++i )
		{
			if ( pListener == m_iListeners[i] )
			{
				m_iListeners.RemoveAt(i);
				return true;
			}
		}
		return false;
	}

	bool Remove( HWND hWnd )
	{
		int count = m_hListeners.GetCount();
		if(count <= 0)
			return false;

		if ( NULL == hWnd )
		{
			ATLASSERT( false );
			return false;
		}

		for ( int i = 0; i < count; ++i )
		{
			if ( hWnd == m_hListeners[i] )
			{
				m_hListeners.RemoveAt(i);
				return true;
			}
		}
		return false;
	}
	void clear()
	{
		m_hListeners.RemoveAll();
		m_iListeners.RemoveAll();
	}
};

class IMsUnknown
{
public:
	IMsUnknown() : m_cRef(1) {}
	virtual ~IMsUnknown() {}

public:
	virtual ULONG AddRef()
	{
		LONG lRef = InterlockedIncrement(&m_cRef);
		ASSERT(lRef > 0);
		return ((ULONG)m_cRef > 1ul ? m_cRef : 1ul);
	}
	virtual ULONG Release()
	{
		LONG lRef = InterlockedDecrement(&m_cRef);
		if (0 == lRef)
		{
			delete this;
			return (ULONG)0;
		}
		return ((ULONG)m_cRef > 1ul ? m_cRef : 1ul);
	}

protected:
	LONG m_cRef;
};

//事件观察者接口，此处不满足要求，可能会有很多的事件要处理
class IEventObserver : public IMsUnknown
{
public:
	virtual void OnEventDispose(void* data,unsigned short eventType = 0) = 0;
};
