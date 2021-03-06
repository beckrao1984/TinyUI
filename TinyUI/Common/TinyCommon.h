#pragma once
#include <Windows.h>
#include <Shellapi.h>
#include <Commdlg.h>
#include <comdef.h>
#include <Mmsystem.h>
#include <new.h>
#include <WinGDI.h>
#include <GdiPlus.h>
#include <Shlwapi.h> 
#include <commctrl.inl>
#include <Psapi.h>
#include <shobjidl.h>
#include <shlobj.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <crtdbg.h>
#include <utility>
#include <Winsock2.h>
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "ws2_32.lib")
using namespace Gdiplus;
using namespace std;

namespace TinyUI
{
	//////////////////////////////////////////////////////////////////////////
#ifndef INLINE
#define INLINE		inline
#endif 
#ifndef OVERRIDE
#define OVERRIDE	override
#endif 
#ifndef FINAL
#define FINAL		final
#endif 
#ifndef DEFAULT
#define DEFAULT		default
#endif 
#ifndef NOEXCEPT
#define NOEXCEPT	throw()
#endif 
	//编译器不生成虚表
#ifndef NO_VTABLE
#define NO_VTABLE	__declspec(novtable)
#endif 
	//编译器不需要添加任何汇编代码
#ifndef NAKED
#define	NAKED		__declspec(naked)
#endif 
	//编译器移除对静态变量的重复定义
#ifndef SELECTANY
#define	SELECTANY	__declspec(selectany)
#endif 
#ifndef ASSERT
#define ASSERT(expr) _ASSERTE(expr)
#endif 
	void Trace(LPCTSTR lpszFormat, ...);
#ifndef TRACE
#define TRACE Trace
#endif
#ifndef ASSUME
#define ASSUME(expr) do { ASSERT(expr); __analysis_assume(!!(expr)); } while(0)
#endif // ASSUME
#ifndef UNUSED
#define UNUSED(x) (void)x;
#endif 
#ifndef UNIMPLEMENTED
#define UNIMPLEMENTED() TRACE("%s:%d: %s: Unimplemented code.", __FILE__, __LINE__, __FUNCSIG__)
#endif
#if __cplusplus >= 201103L
#define COMPILE_ASSERT(expr, msg) static_assert(expr, #msg)
#else
	template<bool>
	struct CompileAssert {};
#undef COMPILE_ASSERT
#define COMPILE_ASSERT(expr, msg) \
    typedef CompileAssert<(bool(expr))> msg[bool(expr)?1:-1]
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)  { if (p) { delete (p);  (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p); (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_OBJECT
#define SAFE_DELETE_OBJECT(p) { if (p) { DeleteObject(p); (p)=NULL; } }
#endif      
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)  { if (p) { (p)->Release(); (p)=NULL; } }
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(p)  { if (p) { free(p); (p)=NULL; } }
#endif
#ifndef SAFE_LOCAL_DELETE
#define SAFE_LOCAL_DELETE(p)  { if (p) { LocalFree(p); (p)=NULL; } }
#endif 
#ifndef TINY_EXPORT
#define TINY_EXPORT __declspec(dllexport)
#endif // TINY_EXPORT

#ifndef TINY_IMPORT
#define TINY_IMPORT __declspec(dllimport)
#endif // TINY_IMPORT

#ifndef TINY_NO_VTABLE
#define TINY_NO_VTABLE __declspec(novtable)
#endif

#ifndef WM_REFLECT
#define WM_REFLECT (WM_USER + 0x1C00)
#endif

#ifndef WM_COMMANDREFLECT
#define WM_COMMANDREFLECT (WM_COMMAND+WM_REFLECT)
#endif

#ifndef WM_NOTIFYREFLECT
#define WM_NOTIFYREFLECT (WM_NOTIFY+WM_REFLECT)
#endif

#ifndef WM_DRAWITEMREFLECT
#define WM_DRAWITEMREFLECT (WM_DRAWITEM + WM_REFLECT)
#endif

#ifndef WM_MEASUREITEMREFLECT
#define WM_MEASUREITEMREFLECT (WM_MEASUREITEM + WM_REFLECT)
#endif

#ifndef WM_DELETEITEMREFLECT
#define WM_DELETEITEMREFLECT (WM_DELETEITEM + WM_REFLECT)
#endif

#define WM_NCMOUSEFIRST WM_NCMOUSEMOVE
#define WM_NCMOUSELAST  WM_NCMBUTTONDBLCLK

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)    ((INT)(short)LOWORD(lParam))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)    ((INT)(short)HIWORD(lParam))
#endif

#ifndef TO_CX
#define TO_CX(rect)    abs(rect.right-rect.left)
#endif

#ifndef TO_CY
#define TO_CY(rect)    abs(rect.bottom-rect.top)
#endif

#define IS_VALID_STRING_PTR(ptr, type) \
	(!IsBadStringPtr((ptr), (UINT)-1))

#define DISALLOW_COPY(TypeName) \
private:\
	TypeName(const TypeName&) = delete;

#define DISALLOW_ASSIGN(TypeName) \
private:\
	void operator=(const TypeName&) = delete;

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
private:\
	TypeName(const TypeName&) = delete;  \
	void operator=(const TypeName&) = delete;

#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
private:\
	TypeName() = delete;   \
	DISALLOW_COPY_AND_ASSIGN(TypeName);

	template<typename T, size_t N>
	char(&ArraySizeHelper(T(&array)[N]))[N];
#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#define ARRAYSIZE_UNSAFE(a) \
	((sizeof(a) / sizeof(*(a))) / \
	static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 占位符空类型
	/// </summary>
	struct NullType;
	INLINE BOOL operator==(const NullType&, const NullType&);
	INLINE BOOL operator<(const NullType&, const NullType&);
	INLINE BOOL operator>(const NullType&, const NullType&);
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct IsVoidType
	{
		enum{ Result = 0 };
	};
	template<>
	struct IsVoidType < void >
	{
		enum{ Result = 1 };
	};
	template<typename T>
	struct IsBoolType
	{
		enum{ Result = 0 };
	};
	template<>
	struct IsBoolType < bool >
	{
		enum{ Result = 1 };
	};
	template <typename T>
	struct IsReference
	{
		enum{ Result = 0 };
	};
	template <typename T>
	struct IsReference < T& >
	{
		enum{ Result = 1 };
	};
	template <typename T>
	struct IsPointer
	{
		enum { Result = 0 };
	};
	template <class T>
	struct IsPointer < T* >
	{
		enum { Result = 1 };
	};
	template <class T>
	struct IsPointer < T*& >
	{
		enum { Result = 1 };
	};
	template <typename T>
	struct IsFunctionPointer
	{
		enum{ Result = 0 };
	};
	template <typename T>
	struct IsFunctionPointer < T(*)() >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01>
	struct IsFunctionPointer < T(*)(P01) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02>
	struct IsFunctionPointer < T(*)(P01, P02) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03>
	struct IsFunctionPointer < T(*)(P01, P02, P03) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03, typename P04>
	struct IsFunctionPointer < T(*)(P01, P02, P03, P04) >
	{
		enum { Result = 1 };
	};
	template <typename T>
	struct IsFunctionPointer < T(*)(...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01>
	struct IsFunctionPointer < T(*)(P01, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02>
	struct IsFunctionPointer < T(*)(P01, P02, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03>
	struct IsFunctionPointer < T(*)(P01, P02, P03, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename P01, typename P02, typename P03, typename P04>
	struct IsFunctionPointer < T(*)(P01, P02, P03, P04, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T>
	struct IsMemberFunctionPointer
	{
		enum{ Result = 0 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer < T(S::*)() >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer < T(S::*)(P01) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, P04) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer < T(S::*)(...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer < T(S::*)(P01, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, P04, ...) >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer < T(S::*)() const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer < T(S::*)(P01) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, P04) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S>
	struct IsMemberFunctionPointer < T(S::*)(...) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01>
	struct IsMemberFunctionPointer < T(S::*)(P01, ...) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, ...) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, ...) const >
	{
		enum { Result = 1 };
	};
	template <typename T, typename S, typename P01, typename P02, typename P03, typename P04>
	struct IsMemberFunctionPointer < T(S::*)(P01, P02, P03, P04, ...) const >
	{
		enum { Result = 1 };
	};
	template<typename T>
	struct IsArrayType
	{
		enum { Result = 0 };
	};
	template<typename T>
	struct IsArrayType < T[] >
	{
		enum { Result = 1 };
	};
	template<typename T, size_t n>
	struct IsArrayType < T[n] >
	{
		enum { Result = 1 };
	};
	template <typename T, typename U>
	struct IsSameType
	{
		enum { Result = 0 };
	};
	template <typename T>
	struct IsSameType < T, T >
	{
		enum { Result = 1 };
	};
	/// <summary>
	/// 类型列表
	/// </summary>
	template<class T1, class T2>
	class TypeList
	{
		typedef T1 T1Type;
		typedef T2 T2Type;
	};
	//////////////////////////////////////////////////////////////////////////
#define TYPE_LIST0() NullType
#define TYPE_LIST1(P1) TypeList<P1, NullType>
#define TYPE_LIST2(P1, P2) TypeList<P1, TYPE_LIST1(P2)>
#define TYPE_LIST3(P1, P2, P3) TypeList<P1, TYPE_LIST2(P2, P3)>
#define TYPE_LIST4(P1, P2, P3, P4) TypeList<P1, TYPE_LIST3(P2, P3, P4)>
	//////////////////////////////////////////////////////////////////////////
	template<class T01 = NullType, class T02 = NullType, class T03 = NullType, class T04 = NullType>
	struct Sequence
	{
		typedef typename Sequence < T02, T03, T04> ::Type Result;
	public:
		typedef TypeList<T01, Result> Type;
	};
	template<>
	struct Sequence < >
	{
		typedef NullType Type;
	};
	//////////////////////////////////////////////////////////////////////////
	template <class TList>
	struct Length;
	template <>
	struct Length < NullType >
	{
		enum { Result = 0 };
	};
	template <class T, class U>
	struct Length < TypeList<T, U> >
	{
		enum { Result = 1 + Length<U>::Result };
	};

	template <class TList, UINT index>
	struct TypeAt;
	template <class T1, class T2>
	struct TypeAt < TypeList<T1, T2>, 0 >
	{
		typedef T1 Result;
	};
	template <class T1, class T2, UINT i>
	struct TypeAt < TypeList<T1, T2>, i >
	{
		typedef typename TypeAt<T2, i - 1>::Result Result;
	};

	template <class TList, class T>
	struct IndexOf;
	template <class T>
	struct IndexOf < NullType, T >
	{
		enum { Result = -1 };
	};
	template <class T, class T2>
	struct IndexOf < TypeList<T, T2>, T >
	{
		enum { Result = 0 };
	};
	template <class T1, class T2, class T>
	struct IndexOf < TypeList<T1, T2>, T >
	{
	public:
		enum { Result = (IndexOf<T2, T>::Result == -1 ? -1 : 1 + IndexOf<T2, T>::Result) };
	};
	//////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 线程安全的引用计数基类类
	/// </summary>
	class TinyReferenceBase
	{
		DISALLOW_COPY_AND_ASSIGN(TinyReferenceBase);
	public:
		/// <summary>
		/// 获得当前的引用计数
		/// </summary>
		LONG GetReference() const;
		/// <summary>
		/// 引用+1
		/// </summary>
		void AddRef() const;
		/// <summary>
		/// 释放
		/// </summary>
		BOOL Release() const;
	protected:
		TinyReferenceBase();
		virtual ~TinyReferenceBase();
		mutable LONG	m_cRef;
	};
	template<class T>
	class DefaultTinyReferenceTraits
	{
	public:
		static void Destruct(const T* x)
		{
			TinyReference<T, DefaultTinyReferenceTraits>::Delete(x);
		}
	};
	/// <summary>
	/// 线程安全的引用计数类,可以显示提供引用析构的机会
	/// </summary>
	template<typename T, typename Traits = DefaultTinyReferenceTraits<T>>
	class TinyReference : public TinyReferenceBase
	{
		friend class DefaultTinyReferenceTraits < T > ;
		DISALLOW_COPY_AND_ASSIGN(TinyReference);
	public:
		TinyReference();
		void AddRef() const;
		void Release() const;
	protected:
		~TinyReference();
	private:
		static void Delete(const T* x);
	};
	template<class T, typename Traits>
	TinyReference<T, Traits>::TinyReference()
	{

	}
	template<class T, typename Traits>
	TinyReference<T, Traits>::~TinyReference()
	{

	}
	template<class T, typename Traits>
	void TinyReference<T, Traits>::AddRef() const
	{
		TinyReferenceBase::AddRef();
	}
	template<class T, typename Traits>
	void TinyReference<T, Traits>::Release() const
	{
		if (TinyReferenceBase::Release())
		{
			Traits::Destruct(static_cast<const T*>(this));
		}
	}
	template<class T, typename Traits>
	void TinyReference<T, Traits>::Delete(const T* x)
	{
		SAFE_DELETE(x);
	}
	/// <summary>
	/// 智能指针
	/// </summary>
	template<class T>
	class TinyAutoPtr
	{
	public:
		explicit TinyAutoPtr(T* _rP = NULL);
		explicit TinyAutoPtr(TinyAutoPtr<T>& _rP);
		~TinyAutoPtr();
		TinyAutoPtr<T>& operator = (TinyAutoPtr<T>& _rP);
		T*	Release() throw();
		void Reset(T* _ptr) throw();
		T*	Ptr() const  throw();
		operator T*() const throw();
		T&	operator*() const throw();
		T*	operator->() const throw();
	protected:
		T* _myP;
	};
	template<class T>
	TinyAutoPtr<T>::TinyAutoPtr(T* lp)
		: _myP(lp)
	{

	}
	template<class T>
	TinyAutoPtr<T>::TinyAutoPtr(TinyAutoPtr<T>& _rP)
		: _myP(_rP.Release())
	{

	}
	template<class T>
	TinyAutoPtr<T>& TinyAutoPtr<T>::operator = (TinyAutoPtr<T>& _rP)
	{
		//释放当前的指针
		Reset(_rP.Release());
		return (*this);
	}
	template<class T>
	T*	TinyAutoPtr<T>::Release() throw()
	{
		T* ps = _myP;
		_myP = NULL;
		return ps;
	}
	template<class T>
	void TinyAutoPtr<T>::Reset(T* _ptr) throw()
	{
		if (_ptr != _myP)
			delete _myP;
		_myP = _ptr;
	}
	template<class T>
	T*	TinyAutoPtr<T>::Ptr() const throw()
	{
		return (_myP);
	}
	template<class T>
	TinyAutoPtr<T>::~TinyAutoPtr()
	{
		if (_myP != NULL)
		{
			delete _myP;
			_myP = NULL;
		}
	}
	template<class T>
	T& TinyAutoPtr<T>::operator*() const throw()
	{
		return *_myP;
	}
	template<class T>
	T*	TinyAutoPtr<T>::operator->() const throw()
	{
		return _myP;
	}
	template<class T>
	TinyAutoPtr<T>::operator T*() const throw()
	{
		return _myP;
	}
	/// <summary>
	/// 智能指针但不能转让所有权
	/// </summary>
	template <class T>
	class TinyScopedPtr
	{
		DISALLOW_COPY_AND_ASSIGN(TinyScopedPtr);
	public:
		explicit TinyScopedPtr(T* ps = 0);
		~TinyScopedPtr();
		BOOL IsEmpty() const throw();
		void Reset(T* ps = 0) throw();
		operator T*() const throw();
		T& operator*() const throw();
		T* operator->() const throw();
		T* Ptr() const throw();
	public:
		T* m_myP;
	};
	template<class T>
	TinyScopedPtr<T>::TinyScopedPtr(T* ps)
		: m_myP(ps)
	{

	}
	template<class T>
	TinyScopedPtr<T>::~TinyScopedPtr()
	{
		if (m_myP != NULL)
		{
			delete m_myP;
			m_myP = NULL;
		}
	}
	template<class T>
	BOOL TinyScopedPtr<T>::IsEmpty() const throw()
	{
		return m_myP == NULL;
	}
	template<class T>
	void TinyScopedPtr<T>::Reset(T* ps) throw()
	{
		if (ps != m_myP)
			delete m_myP;
		m_myP = ps;
	}
	template<class T>
	T& TinyScopedPtr<T>::operator*() const throw()
	{
		return (*m_myP);
	}
	template<class T>
	T* TinyScopedPtr<T>::operator->() const throw()
	{
		return m_myP;
	}
	template<class T>
	T* TinyScopedPtr<T>::Ptr() const throw()
	{
		return m_myP;
	}
	template<class T>
	TinyScopedPtr<T>::operator T*() const throw()
	{
		return m_myP;
	}
	/// <summary>
	/// Scope数组
	/// </summary>
	template <class T>
	class TinyScopedArray
	{
		DISALLOW_COPY_AND_ASSIGN(TinyScopedArray);
	public:
		explicit TinyScopedArray(T* ps = 0);
		~TinyScopedArray();
		BOOL IsEmpty() const;
		void Reset(T* ps = 0) throw();
		operator T*() const throw();
		T& operator[](INT i) const;
		BOOL operator==(T* ps) const;
		BOOL operator!=(T* ps) const;
		T* Ptr() const throw();
	public:
		T* m_myP;
	};
	template<class T>
	TinyScopedArray<T>::TinyScopedArray(T* ps)
		: m_myP(ps)
	{

	}
	template<class T>
	TinyScopedArray<T>::~TinyScopedArray()
	{
		SAFE_DELETE_ARRAY(m_myP);
	}
	template<class T>
	BOOL TinyScopedArray<T>::IsEmpty() const
	{
		return m_myP == NULL;
	}
	template<class T>
	T& TinyScopedArray<T>::operator[](INT i) const
	{
		ASSERT(i >= 0);
		ASSERT(m_myP != NULL);
		return m_myP[i];
	}
	template<class T>
	BOOL TinyScopedArray<T>::operator==(T* ps) const
	{
		return m_myP == ps;
	}
	template<class T>
	BOOL TinyScopedArray<T>::operator!=(T* ps) const
	{
		return m_myP != ps;
	}
	template<class T>
	void TinyScopedArray<T>::Reset(T* ps) throw()
	{
		if (ps != m_myP)
			delete[] m_myP;
		m_myP = ps;
	}
	template<class T>
	T* TinyScopedArray<T>::Ptr() const throw()
	{
		return m_myP;
	}
	template<class T>
	TinyScopedArray<T>::operator T*() const throw()
	{
		return m_myP;
	}
	/// <summary>
	/// 引用计数智能指针,T必须显示实现AddRef,Release接口 
	/// </summary>
	template<class T>
	class TinyScopedReferencePtr
	{
	public:
		TinyScopedReferencePtr();
		TinyScopedReferencePtr(T* myP);
		TinyScopedReferencePtr(const TinyScopedReferencePtr<T>& s);
		TinyScopedReferencePtr<T>& operator=(const TinyScopedReferencePtr<T>& s);
		TinyScopedReferencePtr<T>& operator=(TinyScopedReferencePtr<T>&& s);
		~TinyScopedReferencePtr();
		T* Ptr() const;
		operator T*() const;
		T* operator->() const;
		TinyScopedReferencePtr<T>& operator=(T* ps);
		template<typename U>
		TinyScopedReferencePtr(const TinyScopedReferencePtr<U>& s) : m_myP(s.Ptr())
		{
			if (m_myP != NULL)
			{
				m_myP->AddRef();
			}
		}
		template<typename U>
		TinyScopedReferencePtr<T>& operator=(const TinyScopedReferencePtr<U>& s)
		{
			return *this = s.Ptr();
		}
		template <typename U>
		TinyScopedReferencePtr<T>& operator=(TinyScopedReferencePtr<U>&& s)
		{
			TinyScopedReferencePtr<T>(std::move(s)).swap(*this);
			return *this;
		}
		template <typename U>
		TinyScopedReferencePtr(TinyScopedReferencePtr<U>&& s)
			: m_myP(s.m_myP)
		{
			s.m_myP = NULL;
		}
	private:
		void swap(T** pp);
		void swap(TinyScopedReferencePtr<T>& s);
	protected:
		T* m_myP;
	};
	template<class T>
	TinyScopedReferencePtr<T>::TinyScopedReferencePtr()
		:m_myP(NULL)
	{

	}
	template<class T>
	TinyScopedReferencePtr<T>::TinyScopedReferencePtr(T* myP)
		: m_myP(myP)
	{
		if (m_myP)
		{
			m_myP->AddRef();
		}
	}
	template<class T>
	TinyScopedReferencePtr<T>::TinyScopedReferencePtr(const TinyScopedReferencePtr<T>& s)
		: m_myP(s.m_myP)
	{
		if (m_myP)
		{
			m_myP->AddRef();
		}
	}
	template<class T>
	TinyScopedReferencePtr<T>::~TinyScopedReferencePtr()
	{
		if (m_myP != NULL)
		{
			m_myP->Release();
		}
	}
	template<class T>
	T* TinyScopedReferencePtr<T>::Ptr() const
	{
		return m_myP;
	}
	template<class T>
	TinyScopedReferencePtr<T>::operator T*() const
	{
		return m_myP;
	}
	template<class T>
	T* TinyScopedReferencePtr<T>::operator->() const
	{
		return m_myP;
	}
	template<class T>
	TinyScopedReferencePtr<T>& TinyScopedReferencePtr<T>::operator=(T* ps)
	{
		if (ps)
			ps->AddRef();
		T* oldMyP = m_myP;
		m_myP = ps;
		if (oldMyP)
			oldMyP->Release();
		return *this;
	}
	template<class T>
	TinyScopedReferencePtr<T>& TinyScopedReferencePtr<T>::operator=(const TinyScopedReferencePtr<T>& s)
	{
		return *this = s.m_myP;
	}
	template<class T>
	TinyScopedReferencePtr<T>& TinyScopedReferencePtr<T>::operator=(TinyScopedReferencePtr<T>&& s)
	{
		TinyScopedReferencePtr<T>(std::move(s)).swap(*this);
		return *this;
	}
	template<class T>
	void TinyScopedReferencePtr<T>::swap(T** pp)
	{
		T* p = m_myP;
		m_myP = *pp;
		*pp = p;
	}
	template<class T>
	void TinyScopedReferencePtr<T>::swap(TinyScopedReferencePtr<T>& s)
	{
		swap(&s.m_myP);
	}
	/// <summary>
	/// COM智能指针
	/// </summary>
	template <class T>
	class TinyComPtr
	{
	public:
		T* m_myP;
	public:
		TinyComPtr(T* myP = NULL) throw();
		TinyComPtr(const TinyComPtr<T>& myP) throw();
		TinyComPtr(TinyComPtr<T>&& myP) throw();
		~TinyComPtr() throw();
		T* Ptr() const throw();
		void Attach(T* myP) throw();
		T* Detach() throw();
		void Release() throw();
		operator T*() const throw();
		T** operator&() throw();
		T& operator*() const;
		T* operator->();
		const T* operator->() const;
		T* operator=(T* s) throw();
		T* operator=(TinyComPtr<T>&& s) throw();
		T* operator=(const TinyComPtr<T>& s) throw();
		BOOL operator!();
		HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
		HRESULT CoCreateInstance(LPCOLESTR szProgID, LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL);
		HRESULT QueryInterface(T** myPP) const throw();
	private:
		static IUnknown* ComPtrAssign(IUnknown** pp, IUnknown* lp);
	};
	template<class T>
	TinyComPtr<T>::TinyComPtr(T* lp) throw()
	{
		if ((m_myP = lp) != NULL)
			m_myP->AddRef();
	}
	template<class T>
	TinyComPtr<T>::TinyComPtr(const TinyComPtr<T>& lp) throw()
	{
		if ((m_myP = lp._myP) != NULL)
			m_myP->AddRef();
	}
	template<class T>
	TinyComPtr<T>::TinyComPtr(TinyComPtr<T>&& lp) throw()
	{
		m_myP = lp.m_myP;
		lp.m_myP = NULL;
	}
	template<class T>
	TinyComPtr<T>::~TinyComPtr() throw()
	{
		if (m_myP)
		{
			m_myP->Release();
			m_myP = NULL;
		}
	}
	template<class T>
	void TinyComPtr<T>::Attach(T* myP) throw()
	{
		this->m_myP = myP;
	}
	template<class T>
	T* TinyComPtr<T>::Detach() throw()
	{
		T* ps = this->m_myP;
		this->m_myP = NULL;
		return ps;
	}
	template<class T>
	void TinyComPtr<T>::Release() throw()
	{
		T* ps = m_myP;
		if (ps)
		{
			m_myP = NULL;
			ps->Release();
		}
	}
	template<class T>
	T* TinyComPtr<T>::Ptr() const throw()
	{
		return (T*)m_myP;
	}
	template<class T>
	TinyComPtr<T>::operator T*() const throw()
	{
		return (T*)m_myP;
	}
	template<class T>
	T& TinyComPtr<T>::operator*() const
	{
		ASSERT(m_myP != NULL);
		return *m_myP;
	}
	template<class T>
	T** TinyComPtr<T>::operator&() throw()
	{
		return &m_myP;
	}
	template<class T>
	T* TinyComPtr<T>::operator->()
	{
		return m_myP;
	}
	template<class T>
	const T* TinyComPtr<T>::operator->() const
	{
		return m_myP;
	}
	template<class T>
	T* TinyComPtr<T>::operator=(T* lp) throw()
	{
		if (*this != lp)
		{
			return static_cast<T*>(ComPtrAssign((IUnknown**)&m_myP, lp));
		}
		return *this;
	}
	template<class T>
	T* TinyComPtr<T>::operator=(const TinyComPtr<T>& lp) throw()
	{
		if (*this != lp)
		{
			return static_cast<T*>(ComPtrAssign((IUnknown**)&m_myP, lp.p));
		}
		return *this;
	}
	template<class T>
	T* TinyComPtr<T>::operator=(TinyComPtr<T>&& lp) throw()
	{
		if (*this != lp)
		{
			if (m_myP != NULL)
				m_myP->Release();
			m_myP = lp.m_myP;
			lp.m_myP = NULL;
		}
		return *this;
	}
	template<class T>
	BOOL TinyComPtr<T>::operator!()
	{
		return (m_myP == NULL) ? TRUE : FALSE;
	}
	template<class T>
	IUnknown*  TinyComPtr<T>::ComPtrAssign(IUnknown** pp, IUnknown* lp)
	{
		if (lp != NULL)
			lp->AddRef();
		if (*pp)
			(*pp)->Release();
		*pp = lp;
		return lp;
	}
	template<class T>
	HRESULT TinyComPtr<T>::CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext) throw()
	{
		ASSERT(m_myP == NULL);
		return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof(T), (void**)&m_myP);
	}
	template<class T>
	HRESULT TinyComPtr<T>::CoCreateInstance(LPCOLESTR szProgID, LPUNKNOWN pUnkOuter, DWORD dwClsContext) throw()
	{
		CLSID clsid;
		HRESULT hRes = CLSIDFromProgID(szProgID, &clsid);
		ASSERT(m_myP == NULL);
		if (SUCCEEDED(hRes))
			hRes = ::CoCreateInstance(clsid, pUnkOuter, dwClsContext, __uuidof(T), (void**)&m_myP);
		return hRes;
	}
	template<class T>
	HRESULT TinyComPtr<T>::QueryInterface(T** myPP) const throw()
	{
		ASSERT(m_myP != NULL);
		return m_myP->QueryInterface(__uuidof(T), (void**)myPP);
	}
	/// <summary>
	/// Variant封装
	/// </summary>
	class ScopedVariant
	{
		DISALLOW_COPY_AND_ASSIGN(ScopedVariant);
	public:
		ScopedVariant();
		~ScopedVariant();
		void Reset();
		operator const VARIANT&() const throw();
		VARIANT* operator->();
		VARIANT* operator&() throw();
	protected:
		VARIANT m_var;
	};
	/// <summary>
	/// 禁止拷贝赋值类
	/// </summary>
	class noncopyable
	{
	protected:
		noncopyable() = default;//函数定义编译器自动生成 C++11特性
		~noncopyable() = default;
	private:
		noncopyable(const noncopyable& a) = delete;
		noncopyable& operator=(const noncopyable&) = delete;
	};
	/// <summary>
	/// STL的Hash算法
	/// </summary>
	template<class K>
	INLINE UINT WINAPI TinyHashKey(K key)
	{
#pragma warning(suppress: 4302) 
		ldiv_t HashVal = ldiv((long)(K)key, 127773);
		HashVal.rem = 16807 * HashVal.rem - 2836 * HashVal.quot;
		if (HashVal.rem < 0)
			HashVal.rem += 2147483647;
		return ((UINT)HashVal.rem);
	};
};
