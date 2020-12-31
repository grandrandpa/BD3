#pragma once 

#include <malloc.h>
#include <math.h>
#include <tchar.h>
//#include <gdiplustypes.h>
#include <afxtempl.h>

#define CMsList		CList
#define CMsArray	CArray	
#define CMsMap		CMap
#define MSAPI		__stdcall

// some utility macros definition
#define MsSafeAddRef(_p)\
	if (NULL != (_p))	\
	{	(_p)->AddRef();	}	\

#define MsSafeRelease(_p)\
	if (NULL != (_p))	\
	{ (_p)->Release();	(_p) = NULL;}	\

#define MsSafeDeleteWnd(_p)\
	if(NULL != (_p))\
	{(_p)->DestroyWindow();delete (_p);(_p) = NULL;}\

#define MsSafeDeleteArray(_p)\
	if (NULL != (_p))\
	{ delete[] (_p); (_p) = NULL;}\

#define MsSafeDeleteObject(_p)\
	if (NULL != (_p))\
	{delete (_p);(_p) = NULL;}\

#define MsSafeCloseHandle(_h)\
	if (NULL != (_h))\
	{CloseHandle((_h));(_h) = NULL;}\

#define MS_FALSE_BREAK(_b)\
	if (FALSE == (_b))\
	{	ASSERT(FALSE); break;}\

#define MS_FALSE_RETURN(_b)\
	if (FALSE == (_b))\
	{	ASSERT(FALSE); return;}\

#define MS_FALSE_RETURN_VALUE(_b, _result)\
	if (FALSE == (_b))\
	{	ASSERT(FALSE); return (_result);}\

#define MS_FALSE_RETURN_CLEAN(_b, _clean_func)\
	if (FALSE == (_b))\
	{(_clean_func);	return FALSE;}\

#define MS_FAILED_RETURN(_hr, _result)	\
	if (FAILED((_hr)))\
	{ASSERT(FALSE);	return _result;}\

#define MS_FAILED_BREAK(_hr)	\
	if (FAILED((_hr)))\
	{ASSERT(FALSE);break;}\


#define MS_DEL_BUFFER(_pbuffer)	\
	if(_pbuffer)\
	{delete[] _pbuffer; _pbuffer = NULL;}\

#define MS_DELETE_EXCEPTION(e) do { e->Delete(); } while (0)

//////////////////////////////////////////////////////////////////////////
//
// Clone\Copy等函数实现宏
//
#define MS_DECLARE_CLONE_PURE(base_class_name)  \
public:\
	virtual base_class_name* Clone() = 0;   

#define MS_DECLARE_CLONE(base_class_name)  \
public:\
	virtual base_class_name* Clone();   

#define MS_IMPLEMENT_CLONE(class_name, base_class_name) \
	base_class_name* class_name::Clone()\
	{\
	class_name* pNew = NULL;\
	pNew = new class_name;\
	*pNew = *this;\
	return pNew;\
	}


#define MS_DECLARE_COPY_PURE(baseclass_name)\
public: \
	virtual void Copy(baseclass_name* p) = 0; 

#define MS_DECLARE_COPY(baseclass_name)\
public: \
	virtual void Copy(baseclass_name* p); 

#define MS_IMPLEMENT_COPY(class_name, baseclass_name) \
	void class_name::Copy(baseclass_name* p)	\
	{ *((class_name*)this) = *((class_name*)p);	}	


#define MS_DECLARE_CLONE_COPY_PURE(base_class_name)\
	MS_DECLARE_CLONE_PURE(base_class_name)\
	MS_DECLARE_COPY_PURE(base_class_name)

#define MS_DECLARE_CLONE_COPY(base_class_name)\
	MS_DECLARE_CLONE(base_class_name)\
	MS_DECLARE_COPY(base_class_name)

#define MS_IMPLEMENT_CLONE_COPY(class_name, base_class_name) \
	MS_IMPLEMENT_CLONE(class_name, base_class_name) \
	MS_IMPLEMENT_COPY(class_name, base_class_name)

//
// Generic test for success on any status value (non-negative numbers
// indicate success).
//
#define MSSUCCEEDED(hr) ((HRESULT)(hr) >= 0)

//
// and the inverse
//
#define MSFAILED(hr) ((HRESULT)(hr) < 0)

// Aligned memory allocated/free
#define MsAlignedAlloc(_dwSize, _align)		_aligned_malloc((_dwSize), (_align))

#define MsAlignedFree(_pointer)\
	if (NULL != (_pointer))\
	{_aligned_free((void*)(_pointer));(_pointer) = NULL;}\

// math 
#define MS_DB2INT(a) \
	(INT)(((a)>0.0 ? ((a)+0.5) : ((a)-0.5)))

// For platform vs.2003 or vs.2005
// we should use these macs to do math
// fabs & sqrt()
#define MS_FABS_F(_f)		fabs((FLOAT)(_f))
#define MS_FABS_D(_d)		fabs((DOUBLE)(_d))
#define MS_SQRT_F(_f)		sqrt((FLOAT)(_f))
#define MS_SQRT_D(_d)		sqrt((DOUBLE)(_d))

#define MS_DBEQUAL_F(_a, _b, _less)\
	((MS_FABS_F((_a)-(_b))-0.0)<=_less)

#define MS_DBEQUAL_D(_a, _b, _less)\
	((MS_FABS_D((_a)-(_b))-0.0)<=_less)

#define MS_CLIP_ANGLE(_fAngle)\
	if ((_fAngle) > 360.f)\
	{(_fAngle) -= 360.f;}\
	else if ((_fAngle) < 0.f)\
	{(_fAngle) += 360.f;}

// Effect position & frame index converting
#define MS_POS2FRAME(_dPos, _in, _out)		((_in) + VX_DB2INT((_dPos) * ((_out) - (_in) - 1)))
#define MS_FRAME2POS(_frame, _in, _out)		((DOUBLE)(_frame - _in) / (DOUBLE)((_out) - (_in) - 1))
#define MS_POS2FRAME_DUR(_dPos, _dur)		(VX_DB2INT((_dPos) * ((_dur) - 1)))

///* String conversion functions */
#define MS_T2I(_in)			_ttoi(_in)




//MoveWindow


// color
#define MS_R(_color)	(((_color) & 0x00FF0000) >> 16)
#define MS_G(_color)	(((_color) & 0x0000FF00) >> 8)
#define MS_B(_color)	(((_color) & 0x000000FF))
#define MS_A(_color)	(((_color) & 0xFF000000) >> 24)
#define MS_MAKE_ARGB(_a, _r, _g, _b)	(((_a) << 24) | ((_r) << 16) | ((_g) << 8) | (_b))
#define MS_AxBDiv255(_a, _b)			(((_a) * (_b) + 255) >> 8)

template <class T>
inline void MsSafeAddRefTplList(CMsList<T, T>& lst)
{
	POSITION pos = lst.GetHeadPosition();
	while (pos)
	{
		T temp = lst.GetNext(pos);
		MsSafeAddRef(temp);
	}
}

template <class T>
inline void MsSafeAddRefTplArray(CMsArray<T, T>& ary)
{
	for (int i = 0; i < ary.GetSize(); i++)
	{
		T temp = ary.GetAt(i);
		MsSafeAddRef(temp);
	}
}

template <class T>
inline void MsSafeReleaseTplList(CMsList<T, T>& lst)
{
	while (lst.GetCount() > 0)
	{
		T temp = lst.GetHead();
		lst.RemoveHead();
		MsSafeRelease(temp);
	}
}



template <class T>
inline void MsSafeReleaseTplListWnd(CMsList<T, T>& lst)
{
	while (lst.GetCount() > 0)
	{
		T temp = lst.GetHead();
		lst.RemoveHead();
		MsSafeDeleteWnd(temp);
	}
}

//template <class KEY, class T>
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline void MsSafeReleaseTplMap(CMsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>& mapUnknown)
{
	POSITION pos = mapUnknown.GetStartPosition();
	KEY guidApp;
	while (pos != NULL)
	{
		VALUE pIData = NULL;
		mapUnknown.GetNextAssoc(pos, guidApp, pIData);
		mapUnknown.RemoveKey(guidApp);

		MsSafeRelease(pIData);
	}

	mapUnknown.RemoveAll();
}

//template <class KEY, class T>
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline void MsSafeDeleteTplMap(CMsMap<KEY, ARG_KEY, VALUE, ARG_VALUE>& mapUnknown)
{
	POSITION pos = mapUnknown.GetStartPosition();
	KEY guidApp;
	while (pos != NULL)
	{
		VALUE pIData = NULL;
		mapUnknown.GetNextAssoc(pos, guidApp, pIData);
		mapUnknown.RemoveKey(guidApp);

		MsSafeDeleteObject(pIData);
	}

	mapUnknown.RemoveAll();
}

template <class T>
inline void MsSafeReleaseTplArray(CMsArray<T, T>& ary)
{
	while (ary.GetSize() > 0)
	{
		T temp = ary.GetAt(0);
		ary.RemoveAt(0);
		MsSafeRelease(temp);
	}
}

template <class T>
inline void MsSafeDeleteTplList(CMsList<T, T>& lst)
{
	while (lst.GetCount() > 0)
	{
		T temp = lst.GetHead();
		lst.RemoveHead();
		MsSafeDeleteObject(temp);
	}
}

template <class T>
inline void MsSafeDeleteTplArray(CMsArray<T, T>& ary)
{
	while (ary.GetSize() > 0)
	{
		T temp = ary.GetAt(0);
		ary.RemoveAt(0);
		MsSafeDeleteObject(temp);
	}
}

// Hot key helper
#define MsIsKeyPressed(_nVirtKey)		((GetKeyState(_nVirtKey) & 0x8000) ? TRUE : FALSE)

// Color helper
#define MsMakeColor32(_a, _r, _g, _b)			MAKELONG(MAKEWORD((_b), (_g)), MAKEWORD((_r), (_a)))
#define MsMakeUYVY422_8bit(_u0, _y0, _v0, _y1)	MAKELONG(MAKEWORD((_u0), (_y0)), MAKEWORD((_v0), (_y1)))
#define GetAValue(rgba)							(LOBYTE((rgba)>>24))

