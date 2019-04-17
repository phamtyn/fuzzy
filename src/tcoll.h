/*
  fuzzy - The implementation of the FUZZY programming language

  File: tcoll.h

  Copyright (C) 2016-2018 Omarine <phamtyn@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __TCOLL__
#define __TCOLL__

#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

#ifndef ULONG
typedef unsigned long ULONG;
#endif
#ifndef ULONG_PTR
typedef unsigned long ULONG_PTR;
#endif

typedef long long INT64;
typedef unsigned long long UINT64;
typedef unsigned int UINT;
typedef int BOOL;
typedef int INT_PTR;

typedef long FUZRET;
#define FUZASSERT(expr) assert(expr)
#define FAILED(hr) 	(((FUZRET)(hr)) < 0)
#define S_OK 		((FUZRET)0L)
#define E_FAIL 		((FUZRET)0x80004005L)
#define E_OUTOFMEMORY 	((FUZRET)0x8007000EL)
#define E_INVALIDARG 	((FUZRET)0x80070057L)
#define TRUE		1
#define FALSE		0
#define FuzThrow(hr) throw TException(hr)
#define _FUZTRY try
#define _FUZCATCHALL() catch( ... )
#define _FUZRETHROW throw

#define _Analysis_assume_(expr)

#ifndef FUZASSUME
#define FUZASSUME(expr) do { FUZASSERT(expr); _Analysis_assume_(!!(expr)); } while (0)
#endif 

#ifndef FUZENSURE_THROW
#define FUZENSURE_THROW(expr, hr)          \
do {                                       \
	int __atl_condVal=!!(expr);            \
	FUZASSUME(__atl_condVal);              \
	if(!(__atl_condVal)) FuzThrow(hr);     \
} while (0)
#endif 

#ifndef FUZENSURE
#define FUZENSURE(expr) FUZENSURE_THROW(expr, E_FAIL)
#endif 

#define _FUZ_NEW new

class TException
{
public:
	TException() throw() :
		m_hr( E_FAIL )
	{
	}

	TException(FUZRET hr) throw() :
		m_hr( hr )
	{
	}

	operator FUZRET() const throw()
	{
		return( m_hr );
	}

public:
	FUZRET m_hr;
};

typedef struct tag__POSITION {
} __POSITION, *POSITION;

namespace FUZ
{
template<typename T>
class FuzLimits;

template<>
class FuzLimits<int>
{
public:
	static const int _Min=INT_MIN;
	static const int _Max=INT_MAX;
};

template<>
class FuzLimits<unsigned int>
{
public:
	static const unsigned int _Min=0;
	static const unsigned int _Max=UINT_MAX;
};

template<>
class FuzLimits<long>
{
public:
	static const long _Min=LONG_MIN;
	static const long _Max=LONG_MAX;
};

template<>
class FuzLimits<unsigned long>
{
public:
	static const unsigned long _Min=0;
	static const unsigned long _Max=ULONG_MAX;
};

template<>
class FuzLimits<long long>
{
public:
	static const long long _Min=LLONG_MIN;
	static const long long _Max=LLONG_MAX;
};

template<>
class FuzLimits<unsigned long long>
{
public:
	static const unsigned long long _Min=0;
	static const unsigned long long _Max=ULLONG_MAX;
};  
  

template<typename T>
inline FUZRET FuzAdd(
	T* ptResult,
	T tLeft,
	T tRight)
{
	if(::FUZ::FuzLimits<T>::_Max-tLeft < tRight)
	{
		return -1;
	}
	*ptResult= tLeft + tRight;
	return S_OK;
}  
  

template<typename T>
inline FUZRET FuzMultiply(
	T* ptResult,
	T tLeft,
	T tRight)
{
	
	if(tLeft==0)
	{
		*ptResult=0;
		return S_OK;
	}
	if(::FUZ::FuzLimits<T>::_Max/tLeft < tRight)
	{
		return -1;
	}
	*ptResult= tLeft * tRight;
	return S_OK;
}


template<>
inline FUZRET FuzMultiply(
	int *piResult,
	int iLeft,
	int iRight)
{
	INT64 i64Result=static_cast<INT64>(iLeft) * static_cast<INT64>(iRight);
	if(i64Result>INT_MAX || i64Result < INT_MIN)
	{
		return -1;
	}
	*piResult=static_cast<int>(i64Result);
	return S_OK;
}

template<>
inline FUZRET FuzMultiply(
	unsigned int *piResult,
	unsigned int iLeft,
	unsigned int iRight)
{
	UINT64 i64Result=static_cast<UINT64>(iLeft) * static_cast<UINT64>(iRight);
	if(i64Result>UINT_MAX)
	{
		return -1;
	}
	*piResult=static_cast<unsigned int>(i64Result);
	return S_OK;
}

template<>
inline FUZRET FuzMultiply(
	long *piResult,
	long iLeft,
	long iRight)
{
	INT64 i64Result=static_cast<INT64>(iLeft) * static_cast<INT64>(iRight);
	if(i64Result>LONG_MAX || i64Result < LONG_MIN)
	{
		return -1;
	}
	*piResult=static_cast<long>(i64Result);
	return S_OK;
}

template<>
inline FUZRET FuzMultiply(
	unsigned long *piResult,
	unsigned long iLeft,
	unsigned long iRight)
{
	UINT64 i64Result=static_cast<UINT64>(iLeft) * static_cast<UINT64>(iRight);
	if(i64Result>ULONG_MAX)
	{
		return -1;
	}
	*piResult=static_cast<unsigned long>(i64Result);
	return S_OK;
}
  

inline BOOL FuzIsValidAddress(
	const void* p,
	size_t nBytes,
	BOOL bReadWrite = TRUE)
{
	(bReadWrite);
	(nBytes);
	return (p != NULL);
}

template<typename T>
inline void FuzAssertValidObject(
	const T *pOb)
{
	FUZASSERT(pOb);
	FUZASSERT(FuzIsValidAddress(pOb, sizeof(T)));
	if(pOb)
		pOb->AssertValid();
}
#ifdef _DEBUG
#define FUZASSERT_VALID(x) FUZ::FuzAssertValidObject(x)
#else
#define FUZASSERT_VALID(x) ;
#endif

template<typename T>
inline T* FuzBuf(
  T* buf,
  size_t dwLen)
{
  (void)dwLen;
  return buf;
}

template <typename T>
inline T FuzAddThrow(
	T tLeft,
	T tRight)
{
	T tResult;
	FUZRET hr=FuzAdd(&tResult, tLeft, tRight);
	if(FAILED(hr))
	{
		FuzThrow(hr);
	}
	return tResult;
}
  
}

struct FuzPlex
{
	FuzPlex* pNext;

	void* data()
	{
		return this+1;
	}

	static FuzPlex* Create(
		FuzPlex*& head,
		size_t nMax,
		size_t cbElement);
			
	void FreeDataChain();       
};

inline FuzPlex* FuzPlex::Create(
	FuzPlex*& pHead,
	size_t nMax,
	size_t nElementSize)
{
	FuzPlex* pPlex;

	FUZASSERT( nMax > 0 );
	FUZASSERT( nElementSize > 0 );

	size_t nBytes=0;
	if( 	FAILED(::FUZ::FuzMultiply(&nBytes, nMax, nElementSize)) ||
		FAILED(::FUZ::FuzAdd(&nBytes, nBytes, sizeof(FuzPlex))) )
	{
		return NULL;
	}
	pPlex = static_cast< FuzPlex* >( malloc( nBytes ) );
	if( pPlex == NULL )
	{
		return( NULL );
	}

	pPlex->pNext = pHead;
	pHead = pPlex;

	return( pPlex );
}

inline void FuzPlex::FreeDataChain()
{
	FuzPlex* pPlex;

	pPlex = this;
	while( pPlex != NULL )
	{
		FuzPlex* pNextPlex;

		pNextPlex = pPlex->pNext;
		free( pPlex );
		pPlex = pNextPlex;
	}
}

template< typename T >
class FuzElementBase
{
public:
	typedef const T& INARGTYPE;
	typedef T& OUTARGTYPE;

	static void CopyElements(
		T* pDest,
		const T* pSrc,
		size_t nElements)
	{		
		for( size_t iElement = 0; iElement < nElements; iElement++ )
		{
			pDest[iElement] = pSrc[iElement];
		}
	}
	
	static void RelocateElements(
		T* pDest,
		T* pSrc,
		size_t nElements)
	{
		
		
		
	  
		memcpy( pDest, pSrc, nElements*sizeof( T ));
	}
}; 

template< typename T >
class FuzHashBase
{
public:
	static ULONG Hash(const T& element) throw()
	{
		return( ULONG( ULONG_PTR( element ) ) );
	}
};

template< typename T >
class FuzCompareBase
{
public:
	static bool CompareElements(
		const T& element1,
		const T& element2)
	{
		return( (element1 == element2) != 0 );  
		
	}

	static int CompareElementsOrdered(
		const T& element1,
		const T& element2)
	{
		if( element1 < element2 )
		{
			return( -1 );
		}
		else if( element1 == element2 )
		{
			return( 0 );
		}
		else
		{
			assert( element1 > element2 );
			return( 1 );
		}
	}
};

template< typename T >
class FuzDefaultElement :
	public FuzElementBase< T >,
	public FuzHashBase< T >,
	public FuzCompareBase< T >
{
};

template< typename T >
class FuzElement :
	public FuzDefaultElement< T >
{
};

#include <string>

template<>
class FuzElement< std::string > :
	public FuzElementBase< std::string >
{
public:
	static ULONG Hash(INARGTYPE str) throw()
	{
		ULONG nHash = 0;
		const char *pch = str.data();
		ULONG nLength = str.length();
		for( ULONG iChar = 0; iChar < nLength; iChar++ )
		{
			nHash = (nHash<<5)+nHash+pch[iChar];
		}

		return( nHash );
	}

	static bool CompareElements(
		 INARGTYPE str1,
		 INARGTYPE str2) throw()
	{
		return( str1 == str2 );
	}

	static int CompareElementsOrdered(
		 INARGTYPE str1,
		 INARGTYPE str2) throw()
	{
		return str1.compare(str2);
	}
};

template< typename E, class Favor = FuzElement< E > >
class FuzList
{
public:
	typedef typename Favor::INARGTYPE INARGTYPE;

private:
	class FuzNode :
		public __POSITION
	{
	public:
		FuzNode()
		{
		}
		FuzNode(INARGTYPE element) :
			m_element( element )
		{
		}
		~FuzNode() throw()
		{
		}

	public:
		FuzNode* m_pNext;
		FuzNode* m_pPrev;
		E m_element;

	private:
		FuzNode(const FuzNode&) throw();
	};

public:
	FuzList(UINT nBlockSize = 10) throw();

	size_t GetCount() const throw();
	bool IsEmpty() const throw();

	E& GetHead();
	const E& GetHead() const;
	E& GetTail();
	const E& GetTail() const;

	E RemoveHead();
	E RemoveTail();
	void RemoveHeadNoReturn() throw();
	void RemoveTailNoReturn() throw();

	POSITION AddHead();
	POSITION AddHead(INARGTYPE element);
	void AddHeadList(const FuzList< E, Favor >* plNew);
	POSITION AddTail();
	POSITION AddTail(INARGTYPE element);
	void AddTailList(const FuzList< E, Favor >* plNew);

	void RemoveAll() throw();

	POSITION GetHeadPosition() const throw();
	POSITION GetTailPosition() const throw();
	E& GetNext(POSITION& pos);
	const E& GetNext(POSITION& pos) const;
	E& GetPrev(POSITION& pos);
	const E& GetPrev(POSITION& pos) const throw();

	E& GetAt(POSITION pos);
	const E& GetAt(POSITION pos) const;
	void SetAt(
		POSITION pos,
		INARGTYPE element);
	void RemoveAt(POSITION pos) throw();

	POSITION InsertBefore(
		POSITION pos,
		INARGTYPE element);
	POSITION InsertAfter(
		POSITION pos,
		INARGTYPE element);

	POSITION Find(
		INARGTYPE element,
		POSITION posStartAfter = NULL) const throw();
	POSITION FindIndex(size_t iElement) const throw();

	void MoveToHead(POSITION pos);
	void MoveToTail(POSITION pos);
	void SwapElements(
		POSITION pos1,
		POSITION pos2) throw();

#ifdef _DEBUG
	void AssertValid() const;
#endif  


private:
	FuzNode* m_pHead;
	FuzNode* m_pTail;
	size_t m_nElements;
	FuzPlex* m_pBlocks;
	FuzNode* m_pFree;
	UINT m_nBlockSize;

private:
	void GetFreeNode();
	FuzNode* NewNode(
		FuzNode* pPrev,
		FuzNode* pNext);
	FuzNode* NewNode(
		INARGTYPE element,
		FuzNode* pPrev,
		FuzNode* pNext);
	void FreeNode(FuzNode* pNode) throw();

public:
	~FuzList() throw();

private:
	
	FuzList(const FuzList&) throw();
	FuzList& operator=(const FuzList&) throw();
};

template< typename E, class Favor >
inline size_t FuzList< E, Favor >::GetCount() const throw()
{
	return( m_nElements );
}

template< typename E, class Favor >
inline bool FuzList< E, Favor >::IsEmpty() const throw()
{
	return( m_nElements == 0 );
}

template< typename E, class Favor >
inline E& FuzList< E, Favor >::GetHead()
{
	FUZASSERT( m_pHead != NULL );
	return( m_pHead->m_element );
}

template< typename E, class Favor >
inline const E& FuzList< E, Favor >::GetHead() const
{
	FUZASSERT( m_pHead != NULL );
	return( m_pHead->m_element );
}

template< typename E, class Favor >
inline E& FuzList< E, Favor >::GetTail()
{
	FUZASSERT( m_pTail != NULL );
	return( m_pTail->m_element );
}

template< typename E, class Favor >
inline const E& FuzList< E, Favor >::GetTail() const
{
	FUZASSERT( m_pTail != NULL );
	return( m_pTail->m_element );
}

template< typename E, class Favor >
inline POSITION FuzList< E, Favor >::GetHeadPosition() const throw()
{
	return( POSITION( m_pHead ) );
}

template< typename E, class Favor >
inline POSITION FuzList< E, Favor >::GetTailPosition() const throw()
{
	return( POSITION( m_pTail ) );
}

template< typename E, class Favor >
inline E& FuzList< E, Favor >::GetNext(POSITION& pos)
{
	FuzNode* pNode;

	FUZASSERT( pos != NULL );
	pNode = (FuzNode*)pos;
	pos = POSITION( pNode->m_pNext );

	return( pNode->m_element );
}

template< typename E, class Favor >
inline const E& FuzList< E, Favor >::GetNext(POSITION& pos) const
{
	FuzNode* pNode;

	FUZASSERT( pos != NULL );
	pNode = (FuzNode*)pos;
	pos = POSITION( pNode->m_pNext );

	return( pNode->m_element );
}

template< typename E, class Favor >
inline E& FuzList< E, Favor >::GetPrev(POSITION& pos)
{
	FuzNode* pNode;

	FUZASSERT( pos != NULL );
	pNode = (FuzNode*)pos;
	pos = POSITION( pNode->m_pPrev );

	return( pNode->m_element );
}

template< typename E, class Favor >
inline const E& FuzList< E, Favor >::GetPrev(POSITION& pos) const throw()
{
	FuzNode* pNode;

	FUZASSERT( pos != NULL );
	pNode = (FuzNode*)pos;
	pos = POSITION( pNode->m_pPrev );

	return( pNode->m_element );
}

template< typename E, class Favor >
inline E& FuzList< E, Favor >::GetAt(POSITION pos)
{
	FUZASSERT( pos != NULL );
	FuzNode* pNode = (FuzNode*)pos;
	return( pNode->m_element );
}

template< typename E, class Favor >
inline const E& FuzList< E, Favor >::GetAt(POSITION pos) const
{
	FUZASSERT( pos != NULL );
	FuzNode* pNode = (FuzNode*)pos;
	return( pNode->m_element );
}

template< typename E, class Favor >
inline void FuzList< E, Favor >::SetAt(
	POSITION pos,
	INARGTYPE element)
{
	FUZASSERT( pos != NULL );
	FuzNode* pNode = (FuzNode*)pos;
	pNode->m_element = element;
}

template< typename E, class Favor >
FuzList< E, Favor >::FuzList(UINT nBlockSize) throw() :
	m_nElements( 0 ),
	m_pHead( NULL ),
	m_pTail( NULL ),
	m_nBlockSize( nBlockSize ),
	m_pBlocks( NULL ),
	m_pFree( NULL )
{
	FUZASSERT( nBlockSize > 0 );
}

template< typename E, class Favor >
void FuzList< E, Favor >::RemoveAll() throw()
{
	while( m_nElements > 0 )
	{
		FuzNode* pKill = m_pHead;
		FUZASSERT( pKill != NULL );

		m_pHead = m_pHead->m_pNext;
		FreeNode( pKill );
	}

	FUZASSERT( m_nElements == 0 );
	m_pHead = NULL;
	m_pTail = NULL;
	m_pFree = NULL;

	if( m_pBlocks != NULL )
	{
		m_pBlocks->FreeDataChain();
		m_pBlocks = NULL;
	}
}

template< typename E, class Favor >
FuzList< E, Favor >::~FuzList() throw()
{
	RemoveAll();
	FUZASSERT( m_nElements == 0 );
}

#pragma push_macro("new")
#undef new

template< typename E, class Favor >
void FuzList< E, Favor >::GetFreeNode()
{
	if( m_pFree == NULL )
	{
		FuzPlex* pPlex;
		FuzNode* pNode;

		pPlex = FuzPlex::Create( m_pBlocks, m_nBlockSize, sizeof( FuzNode ) );
		if( pPlex == NULL )
		{
			FuzThrow( E_OUTOFMEMORY );
		}
		pNode = (FuzNode*)pPlex->data();
		pNode += m_nBlockSize-1;
		for( int iBlock = m_nBlockSize-1; iBlock >= 0; iBlock-- )
		{
			pNode->m_pNext = m_pFree;
			m_pFree = pNode;
			pNode--;
		}
	}
	FUZASSERT( m_pFree != NULL );
}

template< typename E, class Favor >
typename FuzList< E, Favor >::FuzNode* FuzList< E, Favor >::NewNode(
	FuzNode* pPrev,
	FuzNode* pNext )
{
	GetFreeNode();

	FuzNode* pNewNode = m_pFree;
	FuzNode* pNextFree = m_pFree->m_pNext;

	::new( pNewNode ) FuzNode;

	m_pFree = pNextFree;
	pNewNode->m_pPrev = pPrev;
	pNewNode->m_pNext = pNext;
	m_nElements++;
	FUZASSERT( m_nElements > 0 );

	return( pNewNode );
}

template< typename E, class Favor >
typename FuzList< E, Favor >::FuzNode* FuzList< E, Favor >::NewNode(
	INARGTYPE element,
	FuzNode* pPrev,
	FuzNode* pNext)
{
	GetFreeNode();

	FuzNode* pNewNode = m_pFree;
	FuzNode* pNextFree = m_pFree->m_pNext;

	::new( pNewNode ) FuzNode( element );

	m_pFree = pNextFree;
	pNewNode->m_pPrev = pPrev;
	pNewNode->m_pNext = pNext;
	m_nElements++;
	FUZASSERT( m_nElements > 0 );

	return( pNewNode );
}

#pragma pop_macro("new")

template< typename E, class Favor >
void FuzList< E, Favor >::FreeNode(FuzNode* pNode) throw()
{
	pNode->~FuzNode();
	pNode->m_pNext = m_pFree;
	m_pFree = pNode;
	FUZASSERT( m_nElements > 0 );
	m_nElements--;
	if( m_nElements == 0 )
	{
		RemoveAll();
	}
}

template< typename E, class Favor >
POSITION FuzList< E, Favor >::AddHead()
{
	FuzNode* pNode = NewNode( NULL, m_pHead );
	if( m_pHead != NULL )
	{
		m_pHead->m_pPrev = pNode;
	}
	else
	{
		m_pTail = pNode;
	}
	m_pHead = pNode;

	return( POSITION( pNode ) );
}

template< typename E, class Favor >
POSITION FuzList< E, Favor >::AddHead(INARGTYPE element)
{
	FuzNode* pNode;

	pNode = NewNode( element, NULL, m_pHead );

	if( m_pHead != NULL )
	{
		m_pHead->m_pPrev = pNode;
	}
	else
	{
		m_pTail = pNode;
	}
	m_pHead = pNode;

	return( POSITION( pNode ) );
}

template< typename E, class Favor >
POSITION FuzList< E, Favor >::AddTail()
{
	FuzNode* pNode = NewNode( m_pTail, NULL );
	if( m_pTail != NULL )
	{
		m_pTail->m_pNext = pNode;
	}
	else
	{
		m_pHead = pNode;
	}
	m_pTail = pNode;

	return( POSITION( pNode ) );
}

template< typename E, class Favor >
POSITION FuzList< E, Favor >::AddTail(INARGTYPE element)
{
	FuzNode* pNode;

	pNode = NewNode( element, m_pTail, NULL );

	if( m_pTail != NULL )
	{
		m_pTail->m_pNext = pNode;
	}
	else
	{
		m_pHead = pNode;
	}
	m_pTail = pNode;

	return( POSITION( pNode ) );
}

template< typename E, class Favor >
void FuzList< E, Favor >::AddHeadList(const FuzList< E, Favor >* plNew)
{
	FUZASSERT( plNew != NULL );

	POSITION pos = plNew->GetTailPosition();
	while( pos != NULL )
	{
		INARGTYPE element = plNew->GetPrev( pos );
		AddHead( element );
	}
}

template< typename E, class Favor >
void FuzList< E, Favor >::AddTailList(const FuzList< E, Favor >* plNew)
{
	FUZASSERT( plNew != NULL );

	POSITION pos = plNew->GetHeadPosition();
	while( pos != NULL )
	{
		INARGTYPE element = plNew->GetNext( pos );
		AddTail( element );
	}
}

template< typename E, class Favor >
E FuzList< E, Favor >::RemoveHead()
{
	FUZASSERT( m_pHead != NULL );

	FuzNode* pNode = m_pHead;
	E element( pNode->m_element );

	m_pHead = pNode->m_pNext;
	if( m_pHead != NULL )
	{
		m_pHead->m_pPrev = NULL;
	}
	else
	{
		m_pTail = NULL;
	}
	FreeNode( pNode );

	return( element );
}

template< typename E, class Favor >
void FuzList< E, Favor >::RemoveHeadNoReturn() throw()
{
	FUZASSERT( m_pHead != NULL );

	FuzNode* pNode = m_pHead;

	m_pHead = pNode->m_pNext;
	if( m_pHead != NULL )
	{
		m_pHead->m_pPrev = NULL;
	}
	else
	{
		m_pTail = NULL;
	}
	FreeNode( pNode );
}

template< typename E, class Favor >
E FuzList< E, Favor >::RemoveTail()
{
	FUZASSERT( m_pTail != NULL );

	FuzNode* pNode = m_pTail;

	E element( pNode->m_element );

	m_pTail = pNode->m_pPrev;
	if( m_pTail != NULL )
	{
		m_pTail->m_pNext = NULL;
	}
	else
	{
		m_pHead = NULL;
	}
	FreeNode( pNode );

	return( element );
}

template< typename E, class Favor >
void FuzList< E, Favor >::RemoveTailNoReturn()  throw()
{
	FUZASSERT( m_pTail != NULL );

	FuzNode* pNode = m_pTail;

	m_pTail = pNode->m_pPrev;
	if( m_pTail != NULL )
	{
		m_pTail->m_pNext = NULL;
	}
	else
	{
		m_pHead = NULL;
	}
	FreeNode( pNode );
}

template< typename E, class Favor >
POSITION FuzList< E, Favor >::InsertBefore(
	POSITION pos,
	INARGTYPE element)
{
	FUZASSERT_VALID(this);

	if( pos == NULL )
		return AddHead( element ); 

	
	FuzNode* pOldNode = (FuzNode*)pos;
	FuzNode* pNewNode = NewNode( element, pOldNode->m_pPrev, pOldNode );

	if( pOldNode->m_pPrev != NULL )
	{
		FUZASSERT(FUZ::FuzIsValidAddress(pOldNode->m_pPrev, sizeof(FuzNode)));
		pOldNode->m_pPrev->m_pNext = pNewNode;
	}
	else
	{
		FUZASSERT( pOldNode == m_pHead );
		m_pHead = pNewNode;
	}
	pOldNode->m_pPrev = pNewNode;

	return( POSITION( pNewNode ) );
}

template< typename E, class Favor >
POSITION FuzList< E, Favor >::InsertAfter(
	POSITION pos,
	INARGTYPE element)
{
	FUZASSERT_VALID(this);

	if( pos == NULL )
		return AddTail( element ); 

	
	FuzNode* pOldNode = (FuzNode*)pos;
	FuzNode* pNewNode = NewNode( element, pOldNode, pOldNode->m_pNext );

	if( pOldNode->m_pNext != NULL )
	{
		FUZASSERT(FUZ::FuzIsValidAddress(pOldNode->m_pNext, sizeof(FuzNode)));
		pOldNode->m_pNext->m_pPrev = pNewNode;
	}
	else
	{
		FUZASSERT( pOldNode == m_pTail );
		m_pTail = pNewNode;
	}
	pOldNode->m_pNext = pNewNode;

	return( POSITION( pNewNode ) );
}

template< typename E, class Favor >
void FuzList< E, Favor >::RemoveAt(POSITION pos) throw()
{
	FUZASSERT_VALID(this);
	FUZASSERT( pos != NULL );

	FuzNode* pOldNode = (FuzNode*)pos;

	
	if( pOldNode == m_pHead )
	{
		m_pHead = pOldNode->m_pNext;
	}
	else
	{
		FUZASSERT( FUZ::FuzIsValidAddress( pOldNode->m_pPrev, sizeof(FuzNode) ));
		pOldNode->m_pPrev->m_pNext = pOldNode->m_pNext;
	}
	if( pOldNode == m_pTail )
	{
		m_pTail = pOldNode->m_pPrev;
	}
	else
	{
		FUZASSERT( FUZ::FuzIsValidAddress( pOldNode->m_pNext, sizeof(FuzNode) ));
		pOldNode->m_pNext->m_pPrev = pOldNode->m_pPrev;
	}
	FreeNode( pOldNode );
}

template< typename E, class Favor >
POSITION FuzList< E, Favor >::FindIndex(size_t iElement) const throw()
{
	FUZASSERT_VALID(this);

	if( iElement >= m_nElements )
		return NULL;  

	if(m_pHead == NULL)
		return NULL;

	FuzNode* pNode = m_pHead;
	for( size_t iSearch = 0; iSearch < iElement; iSearch++ )
	{
		pNode = pNode->m_pNext;
	}

	return( POSITION( pNode ) );
}

template< typename E, class Favor >
void FuzList< E, Favor >::MoveToHead(POSITION pos)
{
	FUZASSERT( pos != NULL );

	FuzNode* pNode = static_cast< FuzNode* >( pos );

	if( pNode == m_pHead )
	{
		
		return;
	}

	if( pNode->m_pNext == NULL )
	{
		FUZASSERT( pNode == m_pTail );
		m_pTail = pNode->m_pPrev;
	}
	else
	{
		pNode->m_pNext->m_pPrev = pNode->m_pPrev;
	}

	FUZASSERT( pNode->m_pPrev != NULL );
	pNode->m_pPrev->m_pNext = pNode->m_pNext;

	m_pHead->m_pPrev = pNode;
	pNode->m_pNext = m_pHead;
	pNode->m_pPrev = NULL;
	m_pHead = pNode;
}

template< typename E, class Favor >
void FuzList< E, Favor >::MoveToTail(POSITION pos)
{
	FUZASSERT( pos != NULL );
	FuzNode* pNode = static_cast< FuzNode* >( pos );

	if( pNode == m_pTail )
		return;

	if( pNode->m_pPrev == NULL )
	{
		FUZASSERT( pNode == m_pHead );
		m_pHead = pNode->m_pNext;
	}
	else
	{
		pNode->m_pPrev->m_pNext = pNode->m_pNext;
	}

	pNode->m_pNext->m_pPrev = pNode->m_pPrev;

	m_pTail->m_pNext = pNode;
	pNode->m_pPrev = m_pTail;
	pNode->m_pNext = NULL;
	m_pTail = pNode;
}

template< typename E, class Favor >
void FuzList< E, Favor >::SwapElements(
	POSITION pos1,
	POSITION pos2) throw()
{
	FUZASSERT( pos1 != NULL );
	FUZASSERT( pos2 != NULL );

	if( pos1 == pos2 )
		return;

	FuzNode* pNode1 = static_cast< FuzNode* >( pos1 );
	FuzNode* pNode2 = static_cast< FuzNode* >( pos2 );
	if( pNode2->m_pNext == pNode1 )
	{
		FuzNode* pNodeTemp = pNode1;
		pNode1 = pNode2;
		pNode2 = pNodeTemp;
	}
	if( pNode1->m_pNext == pNode2 )
	{
		pNode2->m_pPrev = pNode1->m_pPrev;
		if( pNode1->m_pPrev != NULL )
		{
			pNode1->m_pPrev->m_pNext = pNode2;
		}
		else
		{
			FUZASSERT( m_pHead == pNode1 );
			m_pHead = pNode2;
		}
		pNode1->m_pNext = pNode2->m_pNext;
		if( pNode2->m_pNext != NULL )
		{
			pNode2->m_pNext->m_pPrev = pNode1;
		}
		else
		{
			FUZASSERT( m_pTail == pNode2 );
			m_pTail = pNode1;
		}
		pNode2->m_pNext = pNode1;
		pNode1->m_pPrev = pNode2;
	}
	else
	{
		FuzNode* pNodeTemp;

		pNodeTemp = pNode1->m_pPrev;
		pNode1->m_pPrev = pNode2->m_pPrev;
		pNode2->m_pPrev = pNodeTemp;

		pNodeTemp = pNode1->m_pNext;
		pNode1->m_pNext = pNode2->m_pNext;
		pNode2->m_pNext = pNodeTemp;

		if( pNode1->m_pNext != NULL )
		{
			pNode1->m_pNext->m_pPrev = pNode1;
		}
		else
		{
			FUZASSERT( m_pTail == pNode2 );
			m_pTail = pNode1;
		}
		if( pNode1->m_pPrev != NULL )
		{
			pNode1->m_pPrev->m_pNext = pNode1;
		}
		else
		{
			FUZASSERT( m_pHead == pNode2 );
			m_pHead = pNode1;
		}
		if( pNode2->m_pNext != NULL )
		{
			pNode2->m_pNext->m_pPrev = pNode2;
		}
		else
		{
			FUZASSERT( m_pTail == pNode1 );
			m_pTail = pNode2;
		}
		if( pNode2->m_pPrev != NULL )
		{
			pNode2->m_pPrev->m_pNext = pNode2;
		}
		else
		{
			FUZASSERT( m_pHead == pNode1 );
			m_pHead = pNode2;
		}
	}
}

template< typename E, class Favor >
POSITION FuzList< E, Favor >::Find(
	INARGTYPE element,
	POSITION posStartAfter) const throw()
{
	FUZASSERT_VALID(this);

	FuzNode* pNode = (FuzNode*)posStartAfter;
	if( pNode == NULL )
	{
		pNode = m_pHead;  
	}
	else
	{
		pNode = FUZ::FuzBuf(pNode, sizeof(FuzNode));
		FUZASSERT(FUZ::FuzIsValidAddress(pNode, sizeof(FuzNode)));
		FUZASSERT(pNode != NULL);

		pNode = pNode->m_pNext;  
	}

	for( ; pNode != NULL; pNode = pNode->m_pNext )
	{
		if( Favor::CompareElements( pNode->m_element, element ) )
			return( POSITION( pNode ) );
	}

	return( NULL );
}

#ifdef _DEBUG
template< typename E, class Favor >
void FuzList< E, Favor >::AssertValid() const
{
	if( IsEmpty() )
	{
		
		FUZASSERT(m_pHead == NULL);
		FUZASSERT(m_pTail == NULL);
	}
	else
	{
		
		FUZASSERT(FUZ::FuzIsValidAddress(m_pHead, sizeof(FuzNode)));
		FUZASSERT(FUZ::FuzIsValidAddress(m_pTail, sizeof(FuzNode)));
	}
}
#endif

template< typename E, class Favor = FuzElement< E > >
class FuzArray
{
public:
	typedef typename Favor::INARGTYPE INARGTYPE;
	typedef typename Favor::OUTARGTYPE OUTARGTYPE;

public:
	FuzArray() throw();

	size_t GetCount() const throw();
	bool IsEmpty() const throw();
	bool SetCount(size_t nNewSize, int nGrowBy = -1);

	void FreeExtra() throw();
	void RemoveAll() throw();

	const E& GetAt(size_t iElement) const;
	void SetAt(
		size_t iElement,
		INARGTYPE element);
	E& GetAt(size_t iElement);

	const E* GetData() const throw();
	E* GetData() throw();

	void SetAtGrow(
		size_t iElement,
		INARGTYPE element);
	
	size_t Add();
	
	size_t Add(INARGTYPE element);
	size_t Append(const FuzArray< E, Favor >& aSrc);
	void Copy(const FuzArray< E, Favor >& aSrc);

	const E& operator[](size_t iElement) const;
	E& operator[](size_t iElement);

	void InsertAt(
		size_t iElement,
		INARGTYPE element,
		size_t nCount = 1);
	void InsertArrayAt(
		size_t iStart,
		const FuzArray< E, Favor >* paNew);
	void RemoveAt(
		size_t iElement,
		size_t nCount = 1);

#ifdef _DEBUG
	void AssertValid() const;
#endif  

private:
	bool GrowBuffer(size_t nNewSize);


private:
	E* m_pData;
	size_t m_nSize;
	size_t m_nMaxSize;
	int m_nGrowBy;

private:
	static void FuzAllConstructors(
		E* pElements,
		size_t nElements);
	static void FuzAllDestructors(
		E* pElements,
		size_t nElements) throw();

public:
	~FuzArray() throw();

private:
	
	FuzArray(const FuzArray&) throw();
	FuzArray& operator=(const FuzArray&) throw();
};

template< typename E, class Favor >
inline size_t FuzArray< E, Favor >::GetCount() const throw()
{
	return( m_nSize );
}

template< typename E, class Favor >
inline bool FuzArray< E, Favor >::IsEmpty() const throw()
{
	return( m_nSize == 0 );
}

template< typename E, class Favor >
inline void FuzArray< E, Favor >::RemoveAll() throw()
{
	SetCount( 0, -1 );
}

template< typename E, class Favor >
inline const E& FuzArray< E, Favor >::GetAt(size_t iElement) const
{
	FUZASSERT( iElement < m_nSize );
	if(iElement >= m_nSize)
		FuzThrow(E_INVALIDARG);

	return( m_pData[iElement] );
}

template< typename E, class Favor >
inline void FuzArray< E, Favor >::SetAt(
	size_t iElement,
	INARGTYPE element)
{
	FUZASSERT( iElement < m_nSize );
	if(iElement >= m_nSize)
		FuzThrow(E_INVALIDARG);

	m_pData[iElement] = element;
}

template< typename E, class Favor >
inline E& FuzArray< E, Favor >::GetAt(size_t iElement)
{
	FUZASSERT( iElement < m_nSize );
	if(iElement >= m_nSize)
		FuzThrow(E_INVALIDARG);

	return( m_pData[iElement] );
}

template< typename E, class Favor >
inline const E* FuzArray< E, Favor >::GetData() const throw()
{
	return( m_pData );
}

template< typename E, class Favor >
inline E* FuzArray< E, Favor >::GetData() throw()
{
	return( m_pData );
}

template< typename E, class Favor >
inline size_t FuzArray< E, Favor >::Add()
{
	size_t iElement;

	iElement = m_nSize;
	bool bSuccess = SetCount(FUZ::FuzAddThrow<size_t>(m_nSize, 1));
	if( !bSuccess )
	{
		FuzThrow( E_OUTOFMEMORY );
	}

	return( iElement );
}

#pragma push_macro("new")
#undef new

template< typename E, class Favor >
inline size_t FuzArray< E, Favor >::Add( INARGTYPE element)
{
	size_t iElement;

	iElement = m_nSize;
	if( iElement >= m_nMaxSize )
	{
		bool bSuccess = GrowBuffer( iElement+1 );
		if( !bSuccess )
		{
			FuzThrow( E_OUTOFMEMORY );
		}
	}
	::new( m_pData+iElement ) E( element );
	m_nSize++;

	return( iElement );
}

#pragma pop_macro("new")

template< typename E, class Favor >
inline const E& FuzArray< E, Favor >::operator[](size_t iElement) const
{
	FUZASSERT( iElement < m_nSize );
	if(iElement >= m_nSize)
		FuzThrow(E_INVALIDARG);

	return( m_pData[iElement] );
}

template< typename E, class Favor >
inline E& FuzArray< E, Favor >::operator[](size_t iElement)
{
	FUZASSERT( iElement < m_nSize );
	if(iElement >= m_nSize)
		FuzThrow(E_INVALIDARG);

	return( m_pData[iElement] );
}

template< typename E, class Favor >
FuzArray< E, Favor >::FuzArray()  throw():
	m_pData( NULL ),
	m_nSize( 0 ),
	m_nMaxSize( 0 ),
	m_nGrowBy( 0 )
{
}

template< typename E, class Favor >
FuzArray< E, Favor >::~FuzArray() throw()
{
	if( m_pData != NULL )
	{
		FuzAllDestructors( m_pData, m_nSize );
		free( m_pData );
	}
}

template< typename E, class Favor >
bool FuzArray< E, Favor >::GrowBuffer(size_t nNewSize)
{
	if( nNewSize > m_nMaxSize )
	{
		if( m_pData == NULL )
		{
			size_t nAllocSize =  size_t( m_nGrowBy ) > nNewSize ? size_t( m_nGrowBy ) : nNewSize ;
			m_pData = static_cast< E* >( calloc( nAllocSize,sizeof( E ) ) );
			if( m_pData == NULL )
			{
				return( false );
			}
			m_nMaxSize = nAllocSize;
		}
		else
		{
			
			size_t nGrowBy = m_nGrowBy;
			if( nGrowBy == 0 )
			{
				
				nGrowBy = m_nMaxSize / 2;
				
				if ((nNewSize - m_nMaxSize) > nGrowBy)
				{
					nGrowBy = nNewSize - m_nMaxSize;
				}				
			}
			size_t nNewMax;
			if( nNewSize < (m_nMaxSize+nGrowBy) )
				nNewMax = m_nMaxSize+nGrowBy;  
			else
				nNewMax = nNewSize;  

			FUZASSERT( nNewMax >= m_nMaxSize );  
#ifdef SIZE_T_MAX
			FUZASSERT( nNewMax <= SIZE_T_MAX/sizeof( E ) ); 
#endif
			E* pNewData = static_cast< E* >( calloc( nNewMax,sizeof( E ) ) );
			if( pNewData == NULL )
			{
				return false;
			}

			
			Favor::RelocateElements( pNewData, m_pData, m_nSize );

			
			free( m_pData );
			m_pData = pNewData;
			m_nMaxSize = nNewMax;
		}
	}

	return true;
}

template< typename E, class Favor >
bool FuzArray< E, Favor >::SetCount(
	size_t nNewSize,
	int nGrowBy)
{
	FUZASSERT_VALID(this);

	if( nGrowBy != -1 )
	{
		m_nGrowBy = nGrowBy;  
	}

	if( nNewSize == 0 )
	{
		
		if( m_pData != NULL )
		{
			FuzAllDestructors( m_pData, m_nSize );
			free( m_pData );
			m_pData = NULL;
		}
		m_nSize = 0;
		m_nMaxSize = 0;
	}
	else if( nNewSize <= m_nMaxSize )
	{
		
		if( nNewSize > m_nSize )
		{
			
			FuzAllConstructors( m_pData+m_nSize, nNewSize-m_nSize );
		}
		else if( m_nSize > nNewSize )
		{
			
			FuzAllDestructors( m_pData+nNewSize, m_nSize-nNewSize );
		}
		m_nSize = nNewSize;
	}
	else
	{
		bool bSuccess;

		bSuccess = GrowBuffer( nNewSize );
		if( !bSuccess )
		{
			return( false );
		}

		FUZASSERT( nNewSize > m_nSize );
		FuzAllConstructors( m_pData+m_nSize, nNewSize-m_nSize );

		m_nSize = nNewSize;
	}

	return true;
}

template< typename E, class Favor >
size_t FuzArray< E, Favor >::Append(const FuzArray< E, Favor >& aSrc)
{
	FUZASSERT_VALID(this);
	FUZASSERT( this != &aSrc );   

	size_t nOldSize = m_nSize;
	bool bSuccess = SetCount(FUZ::FuzAddThrow<size_t>(m_nSize, aSrc.m_nSize));
	if( !bSuccess )
	{
		FuzThrow( E_OUTOFMEMORY );
	}

	Favor::CopyElements( m_pData+nOldSize, aSrc.m_pData, aSrc.m_nSize );

	return( nOldSize );
}

template< typename E, class Favor >
void FuzArray< E, Favor >::Copy(const FuzArray< E, Favor >& aSrc)
{
	FUZASSERT_VALID(this);
	FUZASSERT( this != &aSrc );   

	bool bSuccess=SetCount( aSrc.m_nSize );
	if( !bSuccess )
	{
		FuzThrow( E_OUTOFMEMORY );
	}

	Favor::CopyElements( m_pData, aSrc.m_pData, aSrc.m_nSize );
}

template< typename E, class Favor >
void FuzArray< E, Favor >::FreeExtra() throw()
{
	FUZASSERT_VALID(this);

	if( m_nSize != m_nMaxSize )
	{
		
#ifdef SIZE_T_MAX
		FUZASSUME( m_nSize <= (SIZE_T_MAX/sizeof( E )) ); 
#endif
		E* pNewData = NULL;
		if( m_nSize != 0 )
		{
			pNewData = (E*)calloc( m_nSize,sizeof( E ) );
			if( pNewData == NULL )
			{
				return;
			}

			
			Favor::RelocateElements( pNewData, m_pData, m_nSize );
		}

		
		free( m_pData );
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

template< typename E, class Favor >
void FuzArray< E, Favor >::SetAtGrow(
	size_t iElement,
	INARGTYPE element)
{
	FUZASSERT_VALID(this);
	size_t nOldSize;

	nOldSize = m_nSize;
	if( iElement >= m_nSize )
	{
		bool bSuccess = SetCount(FUZ::FuzAddThrow<size_t>(iElement, 1), -1 );
		if( !bSuccess )
		{
			FuzThrow( E_OUTOFMEMORY );
		}
	}

	_FUZTRY
	{
		m_pData[iElement] = element;
	}
	_FUZCATCHALL()
	{
		if( m_nSize != nOldSize )
		{
			SetCount( nOldSize, -1 );
		}
		_FUZRETHROW;
	}
}

template< typename E, class Favor >
void FuzArray< E, Favor >::InsertAt(
	size_t iElement,
	INARGTYPE element,
	size_t nElements )
{
	FUZASSERT_VALID(this);
	FUZASSERT( nElements > 0 );     

	if( iElement >= m_nSize )
	{
		
		bool bSuccess = SetCount(FUZ::FuzAddThrow<size_t>(iElement, nElements), -1 );   
		if( !bSuccess )
		{
			FuzThrow( E_OUTOFMEMORY );
		}
	}
	else
	{
		
		size_t nOldSize = m_nSize;
		bool bSuccess = SetCount(FUZ::FuzAddThrow<size_t>(m_nSize, nElements), -1 );  
		if( !bSuccess )
		{
			FuzThrow( E_OUTOFMEMORY );
		}
		
		FuzAllDestructors( m_pData+nOldSize, nElements );
		
		Favor::RelocateElements( m_pData+(iElement+nElements), m_pData+iElement,
			nOldSize-iElement );

		_FUZTRY
		{
			
			FuzAllConstructors( m_pData+iElement, nElements );
		}
		_FUZCATCHALL()
		{
			Favor::RelocateElements( m_pData+iElement, m_pData+(iElement+nElements),
				nOldSize-iElement );
			SetCount( nOldSize, -1 );
			_FUZRETHROW;
		}
	}

	
	FUZASSERT( (iElement+nElements) <= m_nSize );
	for( size_t iNewElement = iElement; iNewElement < (iElement+nElements); iNewElement++ )
	{
		m_pData[iNewElement] = element;
	}
}

template< typename E, class Favor >
void FuzArray< E, Favor >::RemoveAt(
	size_t iElement,
	size_t nElements)
{
	FUZASSERT_VALID(this);
	FUZASSERT( (iElement+nElements) <= m_nSize );

	size_t newCount = iElement+nElements;
	if ((newCount < iElement) || (newCount < nElements) || (newCount > m_nSize))
		FuzThrow(E_INVALIDARG);

	
	size_t nMoveCount = m_nSize-(newCount);
	FuzAllDestructors( m_pData+iElement, nElements );
	if( nMoveCount > 0 )
	{
		Favor::RelocateElements( m_pData+iElement, m_pData+(newCount),
			nMoveCount );
	}
	m_nSize -= nElements;
}

template< typename E, class Favor >
void FuzArray< E, Favor >::InsertArrayAt(
	size_t iStartElement,
	const FuzArray< E, Favor >* paNew)
{
	FUZASSERT_VALID( this );
	FUZENSURE( paNew != NULL );
	FUZASSERT_VALID( paNew );

	if( paNew->GetCount() > 0 )
	{
		InsertAt( iStartElement, paNew->GetAt( 0 ), paNew->GetCount() );
		for( size_t iElement = 0; iElement < paNew->GetCount(); iElement++ )
		{
			SetAt( iStartElement+iElement, paNew->GetAt( iElement ) );
		}
	}
}

#ifdef _DEBUG
template< typename E, class Favor >
void FuzArray< E, Favor >::AssertValid() const
{
	if( m_pData == NULL )
	{
		FUZASSUME( m_nSize == 0 );
		FUZASSUME( m_nMaxSize == 0 );
	}
	else
	{
		FUZASSUME( m_nSize <= m_nMaxSize );
		FUZASSERT( FuzIsValidAddress( m_pData, m_nMaxSize * sizeof( E ) ) );
	}
}
#endif

#pragma push_macro("new")
#undef new

template< typename E, class Favor >
void FuzArray< E, Favor >::FuzAllConstructors(
	E* pElements,
	size_t nElements)
{
	size_t iElement = 0;

	_FUZTRY
	{
		for( iElement = 0; iElement < nElements; iElement++ )
		{
			::new( pElements+iElement ) E;
		}
	}
	_FUZCATCHALL()
	{
		while( iElement > 0 )
		{
			iElement--;
			pElements[iElement].~E();
		}

		_FUZRETHROW;
	}
}

#pragma pop_macro("new")

template< typename E, class Favor >
void FuzArray< E, Favor >::FuzAllDestructors(
	E* pElements,
	size_t nElements) throw()
{
	(pElements);
	
	for( size_t iElement = 0; iElement < nElements; iElement++ )
	{
		pElements[iElement].~E();
	}
}




template< typename K, typename V, class KFavor = FuzElement< K >, class VFavor = FuzElement< V > >
class FuzMap
{
public:
	typedef typename KFavor::INARGTYPE KINARGTYPE;
	typedef typename KFavor::OUTARGTYPE KOUTARGTYPE;
	typedef typename VFavor::INARGTYPE VINARGTYPE;
	typedef typename VFavor::OUTARGTYPE VOUTARGTYPE;

	class FuzPair :
		public __POSITION
	{
	protected:
		FuzPair( KINARGTYPE key) :
			m_key( key )
		{
		}

	public:
		const K m_key;
		V m_value;
	};

private:
	class FuzNode :
		public FuzPair
	{
	public:
		FuzNode(
				 KINARGTYPE key,
				UINT nHash) :
			FuzPair( key ),
			m_nHash( nHash )
		{
		}

	public:
		UINT GetHash() const throw()
		{
			return( m_nHash );
		}

	public:
		FuzNode* m_pNext;
		UINT m_nHash;
	};

public:
	FuzMap(
		 UINT nBins = 17,
		 float fOptimalLoad = 0.75f,
		 float fLoThreshold = 0.25f,
		 float fHiThreshold = 2.25f,
		 UINT nBlockSize = 10) throw();

	size_t GetCount() const throw();
	bool IsEmpty() const throw();

	bool Lookup(
		 KINARGTYPE key,
		 VOUTARGTYPE value) const;
	const FuzPair* Lookup( KINARGTYPE key) const throw();
	FuzPair* Lookup( KINARGTYPE key) throw();
	V& operator[]( KINARGTYPE key) throw();

	POSITION SetAt(
		 KINARGTYPE key,
		 VINARGTYPE value);
	void SetValueAt(
		 POSITION pos,
		 VINARGTYPE value);

	bool RemoveKey( KINARGTYPE key) throw();
	void RemoveAll();
	void RemoveAtPos( POSITION pos) throw();

	POSITION GetStartPosition() const throw();
	void GetNextAssoc(
		 POSITION& pos,
		 KOUTARGTYPE key,
		 VOUTARGTYPE value) const;
	const FuzPair* GetNext( POSITION& pos) const throw();
	FuzPair* GetNext( POSITION& pos) throw();
	const K& GetNextKey( POSITION& pos) const;
	const V& GetNextValue( POSITION& pos) const;
	V& GetNextValue( POSITION& pos);
	void GetAt(
		 POSITION pos,
		 KOUTARGTYPE key,
		 VOUTARGTYPE value) const;
	FuzPair* GetAt( POSITION pos) throw();
	const FuzPair* GetAt( POSITION pos) const throw();
	const K& GetKeyAt( POSITION pos) const;
	const V& GetValueAt( POSITION pos) const;
	V& GetValueAt( POSITION pos);

	UINT GetHashTableSize() const throw();
	bool InitHashTable(
		 UINT nBins,
		 bool bAllocNow = true);
	void EnableAutoRehash() throw();
	void DisableAutoRehash() throw();
	void Rehash( UINT nBins = 0);
	void SetOptimalLoad(
		 float fOptimalLoad,
		 float fLoThreshold,
		 float fHiThreshold,
		 bool bRehashNow = false);

#ifdef _DEBUG
	void AssertValid() const;
#endif  


private:
	FuzNode** m_ppBins;
	size_t m_nElements;
	UINT m_nBins;
	float m_fOptimalLoad;
	float m_fLoThreshold;
	float m_fHiThreshold;
	size_t m_nHiRehashThreshold;
	size_t m_nLoRehashThreshold;
	ULONG m_nLockCount;
	UINT m_nBlockSize;
	FuzPlex* m_pBlocks;
	FuzNode* m_pFree;

private:
	bool IsLocked() const throw();
	UINT PickSize( size_t nElements) const throw();
	FuzNode* NewNode(
		 KINARGTYPE key,
		 UINT iBin,
		 UINT nHash);
	void FreeNode( FuzNode* pNode);
	void FreePlexes() throw();
	 FuzNode* GetNode(
		 KINARGTYPE key,
		 UINT& iBin,
		 UINT& nHash,
		 FuzNode*& pPrev) const throw();
	FuzNode* CreateNode(
		 KINARGTYPE key,
		 UINT iBin,
		 UINT nHash) throw();
	void RemoveNode(
		 FuzNode* pNode,
		 FuzNode* pPrev) throw();
	FuzNode* FindNextNode( FuzNode* pNode) const throw();
	void UpdateRehashThresholds() throw();

public:
	~FuzMap() throw();

private:
	
	FuzMap( const FuzMap&) throw();
	FuzMap& operator=( const FuzMap&) throw();
};


template< typename K, typename V, class KFavor, class VFavor >
inline size_t FuzMap< K, V, KFavor, VFavor >::GetCount() const throw()
{
	return( m_nElements );
}

template< typename K, typename V, class KFavor, class VFavor >
inline bool FuzMap< K, V, KFavor, VFavor >::IsEmpty() const throw()
{
	return( m_nElements == 0 );
}

template< typename K, typename V, class KFavor, class VFavor >
inline V& FuzMap< K, V, KFavor, VFavor >::operator[]( KINARGTYPE key) throw()
{
	FuzNode* pNode;
	UINT iBin;
	UINT nHash;
	FuzNode* pPrev;

	pNode = GetNode( key, iBin, nHash, pPrev );
	if( pNode == NULL )
	{
		pNode = CreateNode( key, iBin, nHash );
	}

	return( pNode->m_value );
}

template< typename K, typename V, class KFavor, class VFavor >
inline UINT FuzMap< K, V, KFavor, VFavor >::GetHashTableSize() const throw()
{
	return( m_nBins );
}

template< typename K, typename V, class KFavor, class VFavor >
inline void FuzMap< K, V, KFavor, VFavor >::GetAt(
	 POSITION pos,
	 KOUTARGTYPE key,
	 VOUTARGTYPE value) const
{
	FUZENSURE( pos != NULL );

	FuzNode* pNode = static_cast< FuzNode* >( pos );

	key = pNode->m_key;
	value = pNode->m_value;
}

template< typename K, typename V, class KFavor, class VFavor >
inline typename FuzMap< K, V, KFavor, VFavor >::FuzPair* FuzMap< K, V, KFavor, VFavor >::GetAt(
	 POSITION pos) throw()
{
	FUZASSERT( pos != NULL );

	return( static_cast< FuzPair* >( pos ) );
}

template< typename K, typename V, class KFavor, class VFavor >
inline const typename FuzMap< K, V, KFavor, VFavor >::FuzPair* FuzMap< K, V, KFavor, VFavor >::GetAt(
	 POSITION pos) const throw()
{
	FUZASSERT( pos != NULL );

	return( static_cast< const FuzPair* >( pos ) );
}

template< typename K, typename V, class KFavor, class VFavor >
inline const K& FuzMap< K, V, KFavor, VFavor >::GetKeyAt( POSITION pos) const
{
	FUZENSURE( pos != NULL );

	FuzNode* pNode = (FuzNode*)pos;

	return( pNode->m_key );
}

template< typename K, typename V, class KFavor, class VFavor >
inline const V& FuzMap< K, V, KFavor, VFavor >::GetValueAt( POSITION pos) const
{
	FUZENSURE( pos != NULL );

	FuzNode* pNode = (FuzNode*)pos;

	return( pNode->m_value );
}

template< typename K, typename V, class KFavor, class VFavor >
inline V& FuzMap< K, V, KFavor, VFavor >::GetValueAt( POSITION pos)
{
	FUZENSURE( pos != NULL );

	FuzNode* pNode = (FuzNode*)pos;

	return( pNode->m_value );
}

template< typename K, typename V, class KFavor, class VFavor >
inline void FuzMap< K, V, KFavor, VFavor >::DisableAutoRehash() throw()
{
	m_nLockCount++;
}

template< typename K, typename V, class KFavor, class VFavor >
inline void FuzMap< K, V, KFavor, VFavor >::EnableAutoRehash() throw()
{
	FUZASSUME( m_nLockCount > 0 );
	m_nLockCount--;
}

template< typename K, typename V, class KFavor, class VFavor >
inline bool FuzMap< K, V, KFavor, VFavor >::IsLocked() const throw()
{
	return( m_nLockCount != 0 );
}


const UINT s_anPrimes[] =
{
	17, 23, 29, 37, 41, 53, 67, 83, 103, 131, 163, 211, 257, 331, 409, 521, 647, 821,
	1031, 1291, 1627, 2053, 2591, 3251, 4099, 5167, 6521, 8209, 10331,
	13007, 16411, 20663, 26017, 32771, 41299, 52021, 65537, 82571, 104033,
	131101, 165161, 208067, 262147, 330287, 416147, 524309, 660563,
	832291, 1048583, 1321139, 1664543, 2097169, 2642257, 3329023, 4194319,
	5284493, 6658049, 8388617, 10568993, 13316089, UINT_MAX
};

template< typename K, typename V, class KFavor, class VFavor >
UINT FuzMap< K, V, KFavor, VFavor >::PickSize( size_t nElements) const throw()
{
	size_t nBins = (size_t)(nElements/m_fOptimalLoad);
	UINT nBinsCal = UINT(  UINT_MAX < nBins ? UINT_MAX : nBins );

	
	int iPrime = 0;
	while( nBinsCal > s_anPrimes[iPrime] )
	{
		iPrime++;
	}

	if( s_anPrimes[iPrime] == UINT_MAX )
	{
		return( nBinsCal );
	}
	else
	{
		return( s_anPrimes[iPrime] );
	}
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzMap< K, V, KFavor, VFavor >::FuzNode* FuzMap< K, V, KFavor, VFavor >::CreateNode(
	 KINARGTYPE key,
	 UINT iBin,
	 UINT nHash) throw()
{
	FuzNode* pNode;

	if( m_ppBins == NULL )
	{
		bool bSuccess;

		bSuccess = InitHashTable( m_nBins );
		if( !bSuccess )
		{
			FuzThrow( E_OUTOFMEMORY );
		}
	}

	pNode = NewNode( key, iBin, nHash );

	return( pNode );
}

template< typename K, typename V, class KFavor, class VFavor >
POSITION FuzMap< K, V, KFavor, VFavor >::GetStartPosition() const throw()
{
	if( IsEmpty() )
	{
		return( NULL );
	}

	for( UINT iBin = 0; iBin < m_nBins; iBin++ )
	{
		if( m_ppBins[iBin] != NULL )
		{
			return( POSITION( m_ppBins[iBin] ) );
		}
	}
	FUZASSERT( false );

	return( NULL );
}

template< typename K, typename V, class KFavor, class VFavor >
POSITION FuzMap< K, V, KFavor, VFavor >::SetAt(
	 KINARGTYPE key,
	 VINARGTYPE value)
{
	FuzNode* pNode;
	UINT iBin;
	UINT nHash;
	FuzNode* pPrev;

	pNode = GetNode( key, iBin, nHash, pPrev );
	if( pNode == NULL )
	{
		pNode = CreateNode( key, iBin, nHash );
		_FUZTRY
		{
			pNode->m_value = value;
		}
		_FUZCATCHALL()
		{
			RemoveAtPos( POSITION( pNode ) );
			_FUZRETHROW;
		}
	}
	else
	{
		pNode->m_value = value;
	}

	return( POSITION( pNode ) );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::SetValueAt(
	 POSITION pos,
	 VINARGTYPE value)
{
	FUZASSUME( pos != NULL );

	FuzNode* pNode = static_cast< FuzNode* >( pos );

	pNode->m_value = value;
}

template< typename K, typename V, class KFavor, class VFavor >
FuzMap< K, V, KFavor, VFavor >::FuzMap(
		 UINT nBins,
		 float fOptimalLoad,
		 float fLoThreshold,
		 float fHiThreshold,
		 UINT nBlockSize) throw() :
	m_ppBins( NULL ),
	m_nBins( nBins ),
	m_nElements( 0 ),
	m_nLockCount( 0 ),  
	m_fOptimalLoad( fOptimalLoad ),
	m_fLoThreshold( fLoThreshold ),
	m_fHiThreshold( fHiThreshold ),
	m_nHiRehashThreshold( UINT_MAX ),
	m_nLoRehashThreshold( 0 ),
	m_pBlocks( NULL ),
	m_pFree( NULL ),
	m_nBlockSize( nBlockSize )
{
	FUZASSERT( nBins > 0 );
	FUZASSERT( nBlockSize > 0 );

	SetOptimalLoad( fOptimalLoad, fLoThreshold, fHiThreshold, false );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::SetOptimalLoad(
	 float fOptimalLoad,
	 float fLoThreshold,
	 float fHiThreshold,
	 bool bRehashNow)
{
	FUZASSERT( fOptimalLoad > 0 );
	FUZASSERT( (fLoThreshold >= 0) && (fLoThreshold < fOptimalLoad) );
	FUZASSERT( fHiThreshold > fOptimalLoad );

	m_fOptimalLoad = fOptimalLoad;
	m_fLoThreshold = fLoThreshold;
	m_fHiThreshold = fHiThreshold;

	UpdateRehashThresholds();

	if( bRehashNow && ((m_nElements > m_nHiRehashThreshold) ||
		(m_nElements < m_nLoRehashThreshold)) )
	{
		Rehash( PickSize( m_nElements ) );
	}
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::UpdateRehashThresholds() throw()
{
	m_nHiRehashThreshold = size_t( m_fHiThreshold*m_nBins );
	m_nLoRehashThreshold = size_t( m_fLoThreshold*m_nBins );
	if( m_nLoRehashThreshold < 17 )
	{
		m_nLoRehashThreshold = 0;
	}
}

template< typename K, typename V, class KFavor, class VFavor >
bool FuzMap< K, V, KFavor, VFavor >::InitHashTable( UINT nBins,  bool bAllocNow)
{
	FUZASSUME( m_nElements == 0 );
	FUZASSERT( nBins > 0 );

	if( m_ppBins != NULL )
	{
		delete[] m_ppBins;
		m_ppBins = NULL;
	}

	if( bAllocNow )
	{
		m_ppBins = _FUZ_NEW FuzNode*[nBins];
		if( m_ppBins == NULL )
		{
			return false;
		}

		FUZENSURE( UINT_MAX / sizeof( FuzNode* ) >= nBins );
		memset( m_ppBins, 0, sizeof( FuzNode* )*nBins );
	}
	m_nBins = nBins;

	UpdateRehashThresholds();

	return true;
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::RemoveAll()
{
	DisableAutoRehash();
	if( m_ppBins != NULL )
	{
		for( UINT iBin = 0; iBin < m_nBins; iBin++ )
		{
			FuzNode* pNext;

			pNext = m_ppBins[iBin];
			while( pNext != NULL )
			{
				FuzNode* pKill;

				pKill = pNext;
				pNext = pNext->m_pNext;
				FreeNode( pKill );
			}
		}
	}

	delete[] m_ppBins;
	m_ppBins = NULL;
	m_nElements = 0;

	if( !IsLocked() )
	{
		InitHashTable( PickSize( m_nElements ), false );
	}

	FreePlexes();
	EnableAutoRehash();
}

template< typename K, typename V, class KFavor, class VFavor >
FuzMap< K, V, KFavor, VFavor >::~FuzMap() throw()
{
	_FUZTRY
	{
		RemoveAll();
	}
	_FUZCATCHALL()
	{
		FUZASSERT(false);
	}
}

#pragma push_macro("new")
#undef new

template< typename K, typename V, class KFavor, class VFavor >
typename FuzMap< K, V, KFavor, VFavor >::FuzNode* FuzMap< K, V, KFavor, VFavor >::NewNode(
	 KINARGTYPE key,
	 UINT iBin,
	 UINT nHash)
{
	FuzNode* pNewNode;

	if( m_pFree == NULL )
	{
		FuzPlex* pPlex;
		FuzNode* pNode;

		pPlex = FuzPlex::Create( m_pBlocks, m_nBlockSize, sizeof( FuzNode ) );
		if( pPlex == NULL )
		{
			FuzThrow( E_OUTOFMEMORY );
		}
		pNode = (FuzNode*)pPlex->data();
		pNode += m_nBlockSize-1;
		for( int iBlock = m_nBlockSize-1; iBlock >= 0; iBlock-- )
		{
			pNode->m_pNext = m_pFree;
			m_pFree = pNode;
			pNode--;
		}
	}
	FUZENSURE(m_pFree != NULL );
	pNewNode = m_pFree;
	m_pFree = pNewNode->m_pNext;

	_FUZTRY
	{
		::new( pNewNode ) FuzNode( key, nHash );
	}
	_FUZCATCHALL()
	{
		pNewNode->m_pNext = m_pFree;
		m_pFree = pNewNode;

		_FUZRETHROW;
	}
	m_nElements++;

	pNewNode->m_pNext = m_ppBins[iBin];




	
	m_ppBins[iBin] = pNewNode;

	if( (m_nElements > m_nHiRehashThreshold) && !IsLocked() )
	{
		Rehash( PickSize( m_nElements ) );
	}

	return( pNewNode );
}

#pragma pop_macro("new")

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::FreeNode( FuzNode* pNode)
{
	FUZENSURE( pNode != NULL );

	pNode->~FuzNode();
	pNode->m_pNext = m_pFree;
	m_pFree = pNode;

	FUZASSUME( m_nElements > 0 );
	m_nElements--;

	if( (m_nElements < m_nLoRehashThreshold) && !IsLocked() )
	{
		Rehash( PickSize( m_nElements ) );
	}

	if( m_nElements == 0 )
	{
		FreePlexes();
	}
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::FreePlexes() throw()
{
	m_pFree = NULL;
	if( m_pBlocks != NULL )
	{
		m_pBlocks->FreeDataChain();
		m_pBlocks = NULL;
	}
}

template< typename K, typename V, class KFavor, class VFavor >
 typename FuzMap< K, V, KFavor, VFavor >::FuzNode* FuzMap< K, V, KFavor, VFavor >::GetNode(
	 KINARGTYPE key,
	 UINT& iBin,
	 UINT& nHash,
	 FuzNode*& pPrev) const throw()
{
	FuzNode* pFollow;

	nHash = KFavor::Hash( key );
	iBin = nHash%m_nBins;
	pPrev = NULL;

	if( m_ppBins == NULL )
	{
		return( NULL );
	}

	pFollow = NULL;
	for( FuzNode* pNode = m_ppBins[iBin]; pNode != NULL; pNode = pNode->m_pNext )
	{
		if( (pNode->GetHash() == nHash) && KFavor::CompareElements( pNode->m_key, key ) )
		{
			pPrev = pFollow;
			return( pNode );
		}
		pFollow = pNode;
	}

	return( NULL );
}

template< typename K, typename V, class KFavor, class VFavor >
bool FuzMap< K, V, KFavor, VFavor >::Lookup(
	 KINARGTYPE key,
	 VOUTARGTYPE value) const
{
	UINT iBin;
	UINT nHash;
	FuzNode* pNode;
	FuzNode* pPrev;

	pNode = GetNode( key, iBin, nHash, pPrev );
	if( pNode == NULL )
	{
		return( false );
	}

	value = pNode->m_value;

	return( true );
}

template< typename K, typename V, class KFavor, class VFavor >
const typename FuzMap< K, V, KFavor, VFavor >::FuzPair* FuzMap< K, V, KFavor, VFavor >::Lookup(
	 KINARGTYPE key) const throw()
{
	UINT iBin;
	UINT nHash;
	FuzNode* pNode;
	FuzNode* pPrev;

	pNode = GetNode( key, iBin, nHash, pPrev );

	return( pNode );
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzMap< K, V, KFavor, VFavor >::FuzPair* FuzMap< K, V, KFavor, VFavor >::Lookup(
	 KINARGTYPE key) throw()
{
	UINT iBin;
	UINT nHash;
	FuzNode* pNode;
	FuzNode* pPrev;

	pNode = GetNode( key, iBin, nHash, pPrev );

	return( pNode );
}

template< typename K, typename V, class KFavor, class VFavor >
bool FuzMap< K, V, KFavor, VFavor >::RemoveKey( KINARGTYPE key) throw()
{
	FuzNode* pNode;
	UINT iBin;
	UINT nHash;
	FuzNode* pPrev;

	pPrev = NULL;
	pNode = GetNode( key, iBin, nHash, pPrev );
	if( pNode == NULL )
	{
		return( false );
	}

	RemoveNode( pNode, pPrev );

	return( true );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::RemoveNode(
	 FuzNode* pNode,
	 FuzNode* pPrev) throw () 
{
	FUZENSURE( pNode != NULL );

	UINT iBin = pNode->GetHash() % m_nBins;

	if( pPrev == NULL )
	{
		FUZASSUME( m_ppBins[iBin] == pNode );
		m_ppBins[iBin] = pNode->m_pNext;
	}
	else
	{
		FUZASSERT( pPrev->m_pNext == pNode );
		pPrev->m_pNext = pNode->m_pNext;
	}
	FreeNode( pNode );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::RemoveAtPos( POSITION pos) throw ()
{
	FUZENSURE( pos != NULL );

	FuzNode* pNode = static_cast< FuzNode* >( pos );
	FuzNode* pPrev = NULL;
	UINT iBin = pNode->GetHash() % m_nBins;

	FUZASSUME( m_ppBins[iBin] != NULL );
	if( pNode == m_ppBins[iBin] )
	{
		pPrev = NULL;
	}
	else
	{
		pPrev = m_ppBins[iBin];
		while( pPrev->m_pNext != pNode )
		{
			pPrev = pPrev->m_pNext;
			FUZASSERT( pPrev != NULL );
		}
	}
	RemoveNode( pNode, pPrev );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::Rehash( UINT nBins)
{
	if( nBins == 0 )
	{
		nBins = PickSize( m_nElements );
	}

	if( nBins == m_nBins )
	{
		return;
	}

	

	if( m_ppBins == NULL )
	{
		
		InitHashTable( nBins, false );
		return;
	}

	FuzNode** ppBins = _FUZ_NEW FuzNode*[nBins];
	if (ppBins == NULL)
	{
		FuzThrow( E_OUTOFMEMORY );
	}

	FUZENSURE( UINT_MAX / sizeof( FuzNode* ) >= nBins );
	memset( ppBins, 0, nBins*sizeof( FuzNode* ) );
	
	for( UINT iSrcBin = 0; iSrcBin < m_nBins; iSrcBin++ )
	{
		FuzNode* pNode;

		pNode = m_ppBins[iSrcBin];
		while( pNode != NULL )
		{
			FuzNode* pNext;
			UINT iDestBin;

			pNext = pNode->m_pNext;  
			iDestBin = pNode->GetHash()%nBins;
			pNode->m_pNext = ppBins[iDestBin];
			ppBins[iDestBin] = pNode;

			pNode = pNext;
		}
	}

	delete[] m_ppBins;
	m_ppBins = ppBins;
	m_nBins = nBins;

	UpdateRehashThresholds();
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::GetNextAssoc(
	 POSITION& pos,
	 KOUTARGTYPE key,
	 VOUTARGTYPE value) const
{
	FuzNode* pNode;
	FuzNode* pNext;

	FUZASSUME( m_ppBins != NULL );
	FUZENSURE( pos != NULL );

	pNode = (FuzNode*)pos;
	pNext = FindNextNode( pNode );

	pos = POSITION( pNext );
	key = pNode->m_key;
	value = pNode->m_value;
}

template< typename K, typename V, class KFavor, class VFavor >
const typename FuzMap< K, V, KFavor, VFavor >::FuzPair* FuzMap< K, V, KFavor, VFavor >::GetNext(
	 POSITION& pos) const throw()
{
	FuzNode* pNode;
	FuzNode* pNext;

	FUZASSUME( m_ppBins != NULL );
	FUZASSERT( pos != NULL );

	pNode = (FuzNode*)pos;
	pNext = FindNextNode( pNode );

	pos = POSITION( pNext );

	return( pNode );
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzMap< K, V, KFavor, VFavor >::FuzPair* FuzMap< K, V, KFavor, VFavor >::GetNext(
	 POSITION& pos) throw()
{
	FUZASSUME( m_ppBins != NULL );
	FUZASSERT( pos != NULL );

	FuzNode* pNode = static_cast< FuzNode* >( pos );
	FuzNode* pNext = FindNextNode( pNode );

	pos = POSITION( pNext );

	return( pNode );
}

template< typename K, typename V, class KFavor, class VFavor >
const K& FuzMap< K, V, KFavor, VFavor >::GetNextKey(
	 POSITION& pos) const
{
	FuzNode* pNode;
	FuzNode* pNext;

	FUZASSUME( m_ppBins != NULL );
	FUZENSURE( pos != NULL );

	pNode = (FuzNode*)pos;
	pNext = FindNextNode( pNode );

	pos = POSITION( pNext );

	return( pNode->m_key );
}

template< typename K, typename V, class KFavor, class VFavor >
const V& FuzMap< K, V, KFavor, VFavor >::GetNextValue(
	 POSITION& pos) const
{
	FuzNode* pNode;
	FuzNode* pNext;

	FUZASSUME( m_ppBins != NULL );
	FUZENSURE( pos != NULL );

	pNode = (FuzNode*)pos;
	pNext = FindNextNode( pNode );

	pos = POSITION( pNext );

	return( pNode->m_value );
}

template< typename K, typename V, class KFavor, class VFavor >
V& FuzMap< K, V, KFavor, VFavor >::GetNextValue(
	 POSITION& pos)
{
	FuzNode* pNode;
	FuzNode* pNext;

	FUZASSUME( m_ppBins != NULL );
	FUZENSURE( pos != NULL );

	pNode = (FuzNode*)pos;
	pNext = FindNextNode( pNode );

	pos = POSITION( pNext );

	return( pNode->m_value );
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzMap< K, V, KFavor, VFavor >::FuzNode* FuzMap< K, V, KFavor, VFavor >::FindNextNode(
	 FuzNode* pNode) const throw()
{
	FuzNode* pNext;

	if(pNode == NULL)
	{
		FUZASSERT(FALSE);
		return NULL;
	}

	if( pNode->m_pNext != NULL )
	{
		pNext = pNode->m_pNext;
	}
	else
	{
		UINT iBin;

		pNext = NULL;
		iBin = (pNode->GetHash()%m_nBins)+1;
		while( (pNext == NULL) && (iBin < m_nBins) )
		{
			if( m_ppBins[iBin] != NULL )
			{
				pNext = m_ppBins[iBin];
			}

			iBin++;
		}
	}

	return( pNext );
}

#ifdef _DEBUG
template< typename K, typename V, class KFavor, class VFavor >
void FuzMap< K, V, KFavor, VFavor >::AssertValid() const
{
	FUZASSUME( m_nBins > 0 );
	
	FUZASSERT( IsEmpty() || (m_ppBins != NULL) );
}
#endif

template< typename K, typename V, class KFavor = FuzElement< K >, class VFavor = FuzElement< V > >
class FuzTree
{
public:
	typedef typename KFavor::INARGTYPE KINARGTYPE;
	typedef typename KFavor::OUTARGTYPE KOUTARGTYPE;
	typedef typename VFavor::INARGTYPE VINARGTYPE;
	typedef typename VFavor::OUTARGTYPE VOUTARGTYPE;

public:
	class FuzPair :
		public __POSITION
	{
	protected:

		FuzPair(
				 KINARGTYPE key,
				 VINARGTYPE value) :
			m_key( key ),
			m_value( value )
		{
		}
		~FuzPair() throw()
		{
		}

	public:
		const K m_key;
		V m_value;
	};

private:

	class FuzNode :
		public FuzPair
	{
	public:
		enum FUZ_COLOR
		{
			FUZ_RED,
			FUZ_BLACK
		};

	public:
		FUZ_COLOR m_eColor;
		FuzNode* m_pLeft;
		FuzNode* m_pRight;
		FuzNode* m_pParent;

		FuzNode(
				 KINARGTYPE key,
				 VINARGTYPE value) :
			FuzPair( key, value ),
			m_pParent( NULL ),
			m_eColor( FUZ_BLACK )
		{
		}
		~FuzNode() throw()
		{
		}
	};

private:
	FuzNode* m_pRoot;
	size_t m_nCount;
	FuzNode* m_pFree;
	FuzPlex* m_pBlocks;
	size_t m_nBlockSize;

	
	FuzNode *m_pNil;

	
	bool IsNil( FuzNode *p) const throw();
	void SetNil( FuzNode **p) throw();

	FuzNode* NewNode(
		 KINARGTYPE key,
		 VINARGTYPE value) throw();
	void FreeNode( FuzNode* pNode) throw();
	void RemovePostOrder( FuzNode* pNode) throw();
	FuzNode* LeftRotate( FuzNode* pNode) throw();
	FuzNode* RightRotate( FuzNode* pNode) throw();
	void SwapNode(
		 FuzNode* pDest,
		 FuzNode* pSrc) throw();
	FuzNode* InsertImpl(
		 KINARGTYPE key,
		 VINARGTYPE value) throw();
	void FUZDeleteFixup( FuzNode* pNode) throw();
	bool FUZDelete( FuzNode* pZ) throw();

#ifdef _DEBUG

private:
	void VerifyIntegrity(
		 const FuzNode *pNode,
		 int nCurrBlackDepth,
		 int &nBlackDepth) const throw();

public:
	void VerifyIntegrity() const throw();

#endif 

protected:
	FuzNode* Minimum( FuzNode* pNode) const throw();
	FuzNode* Maximum( FuzNode* pNode) const throw();
	FuzNode* Predecessor( FuzNode* pNode) const throw();
	FuzNode* Successor( FuzNode* pNode) const throw();
	FuzNode* FUZInsert(
		 KINARGTYPE key,
		 VINARGTYPE value) throw();
	FuzNode* Find( KINARGTYPE key) const throw();
	FuzNode* FindPrefix( KINARGTYPE key) const throw();

protected:
	explicit FuzTree( size_t nBlockSize = 10) throw();  

public:
	~FuzTree() throw();

	void RemoveAll() throw();
	void RemoveAt( POSITION pos) throw();

	size_t GetCount() const throw();
	bool IsEmpty() const throw();

	POSITION FindFirstKeyAfter( KINARGTYPE key) const throw();

	POSITION GetHeadPosition() const throw();
	POSITION GetTailPosition() const throw();
	void GetNextAssoc(
		 POSITION& pos,
		 KOUTARGTYPE key,
		 VOUTARGTYPE value) const;
	const FuzPair* GetNext( POSITION& pos) const throw();
	FuzPair* GetNext( POSITION& pos) throw();
	const FuzPair* GetPrev( POSITION& pos) const throw();
	FuzPair* GetPrev( POSITION& pos) throw();
	const K& GetNextKey( POSITION& pos) const throw();
	const V& GetNextValue( POSITION& pos) const throw();
	V& GetNextValue( POSITION& pos) throw();

	FuzPair* GetAt( POSITION pos) throw();
	const FuzPair* GetAt( POSITION pos) const throw();
	void GetAt(
		 POSITION pos,
		 KOUTARGTYPE key,
		 VOUTARGTYPE value) const;
	const K& GetKeyAt( POSITION pos) const;
	const V& GetValueAt( POSITION pos) const;
	V& GetValueAt( POSITION pos);
	void SetValueAt(
		 POSITION pos,
		 VINARGTYPE value);

private:
	
	FuzTree( const FuzTree&) throw();
	FuzTree& operator=( const FuzTree&) throw();
};

template< typename K, typename V, class KFavor, class VFavor >
inline bool FuzTree< K, V, KFavor, VFavor >::IsNil( FuzNode *p) const throw()
{
	return ( p == m_pNil );
}

template< typename K, typename V, class KFavor, class VFavor >
inline void FuzTree< K, V, KFavor, VFavor >::SetNil( FuzNode **p) throw () 
{
	FUZENSURE( p != NULL );
	*p = m_pNil;
}

template< typename K, typename V, class KFavor, class VFavor >
FuzTree< K, V, KFavor, VFavor >::FuzTree( size_t nBlockSize) throw() :
	m_pRoot( NULL ),
	m_nCount( 0 ),
	m_nBlockSize( nBlockSize ),
	m_pFree( NULL ),
	m_pBlocks( NULL ),
	m_pNil( NULL )
{
	FUZASSERT( nBlockSize > 0 );
}

template< typename K, typename V, class KFavor, class VFavor >
FuzTree< K, V, KFavor, VFavor >::~FuzTree() throw()
{
	RemoveAll();
	if (m_pNil != NULL)
	{
		free(m_pNil);
	}
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::RemoveAll() throw()
{
	if (!IsNil(m_pRoot))
		RemovePostOrder(m_pRoot);
	m_nCount = 0;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
	m_pFree = NULL;
	m_pRoot = m_pNil;
}

template< typename K, typename V, class KFavor, class VFavor >
size_t FuzTree< K, V, KFavor, VFavor >::GetCount() const throw()
{
	return m_nCount;
}

template< typename K, typename V, class KFavor, class VFavor >
bool FuzTree< K, V, KFavor, VFavor >::IsEmpty() const throw()
{
	return( m_nCount == 0 );
}

template< typename K, typename V, class KFavor, class VFavor >
POSITION FuzTree< K, V, KFavor, VFavor >::FindFirstKeyAfter( KINARGTYPE key) const throw()
{
	return( FindPrefix( key ) );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::RemoveAt( POSITION pos) throw()
{
	FUZASSERT(pos != NULL);
	FUZDelete(static_cast<FuzNode*>(pos));
}

template< typename K, typename V, class KFavor, class VFavor >
POSITION FuzTree< K, V, KFavor, VFavor >::GetHeadPosition() const throw()
{
	return( Minimum( m_pRoot ) );
}

template< typename K, typename V, class KFavor, class VFavor >
POSITION FuzTree< K, V, KFavor, VFavor >::GetTailPosition() const throw()
{
	return( Maximum( m_pRoot ) );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::GetNextAssoc(
	 POSITION& pos,
	 KOUTARGTYPE key,
	 VOUTARGTYPE value) const
{
	FUZASSERT(pos != NULL);
	FuzNode* pNode = static_cast< FuzNode* >(pos);

	key = pNode->m_key;
	value = pNode->m_value;

	pos = Successor(pNode);
}

template< typename K, typename V, class KFavor, class VFavor >
const typename FuzTree< K, V, KFavor, VFavor >::FuzPair* FuzTree< K, V, KFavor, VFavor >::GetNext(
	 POSITION& pos) const throw()
{
	FUZASSERT(pos != NULL);
	FuzNode* pNode = static_cast< FuzNode* >(pos);
	pos = Successor(pNode);
	return pNode;
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzPair* FuzTree< K, V, KFavor, VFavor >::GetNext(
	 POSITION& pos) throw()
{
	FUZASSERT(pos != NULL);
	FuzNode* pNode = static_cast< FuzNode* >(pos);
	pos = Successor(pNode);
	return pNode;
}

template< typename K, typename V, class KFavor, class VFavor >
const typename FuzTree< K, V, KFavor, VFavor >::FuzPair* FuzTree< K, V, KFavor, VFavor >::GetPrev(
	 POSITION& pos) const throw()
{
	FUZASSERT(pos != NULL);
	FuzNode* pNode = static_cast< FuzNode* >(pos);
	pos = Predecessor(pNode);

	return pNode;
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzPair* FuzTree< K, V, KFavor, VFavor >::GetPrev(
	 POSITION& pos) throw()
{
	FUZASSERT(pos != NULL);
	FuzNode* pNode = static_cast< FuzNode* >(pos);
	pos = Predecessor(pNode);

	return pNode;
}

template< typename K, typename V, class KFavor, class VFavor >
const K& FuzTree< K, V, KFavor, VFavor >::GetNextKey(
	 POSITION& pos) const throw()
{
	FUZASSERT(pos != NULL);
	FuzNode* pNode = static_cast<FuzNode*>(pos);
	pos = Successor(pNode);

	return pNode->m_key;
}

template< typename K, typename V, class KFavor, class VFavor >
const V& FuzTree< K, V, KFavor, VFavor >::GetNextValue(
	 POSITION& pos) const throw()
{
	FUZASSERT(pos != NULL);
	FuzNode* pNode = static_cast<FuzNode*>(pos);
	pos = Successor(pNode);

	return pNode->m_value;
}

template< typename K, typename V, class KFavor, class VFavor >
V& FuzTree< K, V, KFavor, VFavor >::GetNextValue(
	 POSITION& pos) throw()
{
	FUZASSERT(pos != NULL);
	FuzNode* pNode = static_cast<FuzNode*>(pos);
	pos = Successor(pNode);

	return pNode->m_value;
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzPair* FuzTree< K, V, KFavor, VFavor >::GetAt(
	 POSITION pos) throw()
{
	FUZASSERT( pos != NULL );

	return( static_cast< FuzPair* >( pos ) );
}

template< typename K, typename V, class KFavor, class VFavor >
const typename FuzTree< K, V, KFavor, VFavor >::FuzPair* FuzTree< K, V, KFavor, VFavor >::GetAt(
	 POSITION pos) const throw()
{
	FUZASSERT( pos != NULL );

	return( static_cast< const FuzPair* >( pos ) );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::GetAt(
	 POSITION pos,
	 KOUTARGTYPE key,
	 VOUTARGTYPE value) const
{
	FUZENSURE( pos != NULL );
	key = static_cast<FuzNode*>(pos)->m_key;
	value = static_cast<FuzNode*>(pos)->m_value;
}

template< typename K, typename V, class KFavor, class VFavor >
const K& FuzTree< K, V, KFavor, VFavor >::GetKeyAt( POSITION pos) const
{
	FUZENSURE( pos != NULL );
	return static_cast<FuzNode*>(pos)->m_key;
}

template< typename K, typename V, class KFavor, class VFavor >
const V& FuzTree< K, V, KFavor, VFavor >::GetValueAt( POSITION pos) const
{
	FUZENSURE( pos != NULL );
	return static_cast<FuzNode*>(pos)->m_value;
}

template< typename K, typename V, class KFavor, class VFavor >
V& FuzTree< K, V, KFavor, VFavor >::GetValueAt( POSITION pos)
{
	FUZENSURE( pos != NULL );
	return static_cast<FuzNode*>(pos)->m_value;
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::SetValueAt(
	 POSITION pos,
	 VINARGTYPE value)
{
	FUZENSURE( pos != NULL );
	static_cast<FuzNode*>(pos)->m_value = value;
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::NewNode(
	 KINARGTYPE key,
	 VINARGTYPE value) throw()
{
	if( m_pFree == NULL )
	{
		if (m_pNil == NULL)
		{
			m_pNil = reinterpret_cast<FuzNode *>(malloc(sizeof( FuzNode )));
			if (m_pNil == NULL)
			{
				FuzThrow( E_OUTOFMEMORY );
			}
			memset(m_pNil, 0x00, sizeof(FuzNode));
			m_pNil->m_eColor = FuzNode::FUZ_BLACK;
			m_pNil->m_pParent = m_pNil->m_pLeft = m_pNil->m_pRight = m_pNil;
			m_pRoot = m_pNil;
		}

		FuzPlex* pPlex = FuzPlex::Create( m_pBlocks, m_nBlockSize, sizeof( FuzNode ) );
		if( pPlex == NULL )
		{
			FuzThrow( E_OUTOFMEMORY );
		}
		FuzNode* pNode = static_cast< FuzNode* >( pPlex->data() );
		pNode += m_nBlockSize-1;
		for( INT_PTR iBlock = m_nBlockSize-1; iBlock >= 0; iBlock-- )
		{
			pNode->m_pLeft = m_pFree;
			m_pFree = pNode;
			pNode--;
		}
	}
	FUZASSUME( m_pFree != NULL );

	FuzNode* pNewNode = m_pFree;
	::new( pNewNode ) FuzNode( key, value );

	m_pFree = m_pFree->m_pLeft;
	pNewNode->m_eColor = FuzNode::FUZ_RED;
	SetNil(&pNewNode->m_pLeft);
	SetNil(&pNewNode->m_pRight);
	SetNil(&pNewNode->m_pParent);

	m_nCount++;
	FUZASSUME( m_nCount > 0 );

	return( pNewNode );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::FreeNode( FuzNode* pNode) throw ()
{
	FUZENSURE( pNode != NULL );
	pNode->~FuzNode();
	pNode->m_pLeft = m_pFree;
	m_pFree = pNode;
	FUZASSUME( m_nCount > 0 );
	m_nCount--;
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::RemovePostOrder( FuzNode* pNode) throw()
{
	if (IsNil(pNode))
		return;
	RemovePostOrder(pNode->m_pLeft);
	RemovePostOrder(pNode->m_pRight);
	FreeNode( pNode );
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::LeftRotate(
	 FuzNode* pNode) throw()
{
	FUZASSERT(pNode != NULL);
	if(pNode == NULL)
		return NULL;

	FuzNode* pRight = pNode->m_pRight;
	pNode->m_pRight = pRight->m_pLeft;
	if (!IsNil(pRight->m_pLeft))
		pRight->m_pLeft->m_pParent = pNode;

	pRight->m_pParent = pNode->m_pParent;
	if (IsNil(pNode->m_pParent))
		m_pRoot = pRight;
	else if (pNode == pNode->m_pParent->m_pLeft)
		pNode->m_pParent->m_pLeft = pRight;
	else
		pNode->m_pParent->m_pRight = pRight;

	pRight->m_pLeft = pNode;
	pNode->m_pParent = pRight;
	return pNode;

}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::RightRotate(
	 FuzNode* pNode) throw()
{
	FUZASSERT(pNode != NULL);
	if(pNode == NULL)
		return NULL;

	FuzNode* pLeft = pNode->m_pLeft;
	pNode->m_pLeft = pLeft->m_pRight;
	if (!IsNil(pLeft->m_pRight))
		pLeft->m_pRight->m_pParent = pNode;

	pLeft->m_pParent = pNode->m_pParent;
	if (IsNil(pNode->m_pParent))
		m_pRoot = pLeft;
	else if (pNode == pNode->m_pParent->m_pRight)
		pNode->m_pParent->m_pRight = pLeft;
	else
		pNode->m_pParent->m_pLeft = pLeft;

	pLeft->m_pRight = pNode;
	pNode->m_pParent = pLeft;
	return pNode;
}


template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::Find(
	 KINARGTYPE key) const throw()
{
	FuzNode* pKey = NULL;
	FuzNode* pNode = m_pRoot;
	while( !IsNil(pNode) && (pKey == NULL) )
	{
		int nCompare = KFavor::CompareElementsOrdered( key, pNode->m_key );
		if( nCompare == 0 )
		{
			pKey = pNode;
		}
		else
		{
			if( nCompare < 0 )
			{
				pNode = pNode->m_pLeft;
			}
			else
			{
				pNode = pNode->m_pRight;
			}
		}
	}

	if( pKey == NULL )
	{
		return( NULL );
	}

	while( true )
	{
		FuzNode* pPrev = Predecessor( pKey );
		if( (pPrev != NULL) && KFavor::CompareElements( key, pPrev->m_key ) )
		{
			pKey = pPrev;
		}
		else
		{
			return( pKey );
		}
	}

}


template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::FindPrefix(
	 KINARGTYPE key) const throw()
{
	
	FuzNode* pParent = NULL;
	FuzNode* pKey = NULL;
	FuzNode* pNode = m_pRoot;
	while( !IsNil(pNode) && (pKey == NULL) )
	{
		pParent = pNode;
		int nCompare = KFavor::CompareElementsOrdered( key, pNode->m_key );
		if( nCompare == 0 )
		{
			pKey = pNode;
		}
		else if( nCompare < 0 )
		{
			pNode = pNode->m_pLeft;
		}
		else
		{
			pNode = pNode->m_pRight;
		}
	}

	if( pKey != NULL )
	{
		while( true )
		{
			FuzNode* pNext = Successor( pKey );
			if ((pNext != NULL) && KFavor::CompareElements( key, pNext->m_key ))
			{
				pKey = pNext;
			}
			else
			{
				return pNext;
			}
		}
	}
	else if (pParent != NULL)
	{
		int nCompare = KFavor::CompareElementsOrdered( key, pParent->m_key );
		if( nCompare < 0 )
		{
			pKey = pParent;
		}
		else
		{
			FUZASSERT( nCompare > 0 );
			pKey = Successor( pParent );
		}
	}

	return( pKey );
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::SwapNode( FuzNode* pDest,  FuzNode* pSrc) throw ()
{
	FUZENSURE( pDest != NULL );
	FUZENSURE( pSrc != NULL );

	pDest->m_pParent = pSrc->m_pParent;
	if (pSrc->m_pParent->m_pLeft == pSrc)
	{
		pSrc->m_pParent->m_pLeft = pDest;
	}
	else
	{
		pSrc->m_pParent->m_pRight = pDest;
	}

	pDest->m_pRight = pSrc->m_pRight;
	pDest->m_pLeft = pSrc->m_pLeft;
	pDest->m_eColor = pSrc->m_eColor;
	pDest->m_pRight->m_pParent = pDest;
	pDest->m_pLeft->m_pParent = pDest;

	if (m_pRoot == pSrc)
	{
		m_pRoot = pDest;
	}
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::InsertImpl(
	 KINARGTYPE key,
	 VINARGTYPE value) throw()
{
	FuzNode* pNew = NewNode( key, value );

	FuzNode* pY = NULL;
	FuzNode* pX = m_pRoot;

	while (!IsNil(pX))
	{
		pY = pX;
		if( KFavor::CompareElementsOrdered( key, pX->m_key ) <= 0 )
			pX = pX->m_pLeft;
		else
			pX = pX->m_pRight;
	}

	pNew->m_pParent = pY;
	if (pY == NULL)
	{
		m_pRoot = pNew;
	}
	else if( KFavor::CompareElementsOrdered( key, pY->m_key ) <= 0 )
		pY->m_pLeft = pNew;
	else
		pY->m_pRight = pNew;

	return pNew;
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::FUZDeleteFixup( FuzNode* pNode) throw ()
{
	FUZENSURE( pNode != NULL );

	FuzNode* pX = pNode;
	FuzNode* pW = NULL;

	while (( pX != m_pRoot ) && ( pX->m_eColor == FuzNode::FUZ_BLACK ))
	{
		if (pX == pX->m_pParent->m_pLeft)
		{
			pW = pX->m_pParent->m_pRight;
			if (pW->m_eColor == FuzNode::FUZ_RED)
			{
				pW->m_eColor = FuzNode::FUZ_BLACK;
				pW->m_pParent->m_eColor = FuzNode::FUZ_RED;
				LeftRotate(pX->m_pParent);
				pW = pX->m_pParent->m_pRight;
			}
			if (pW->m_pLeft->m_eColor == FuzNode::FUZ_BLACK && pW->m_pRight->m_eColor == FuzNode::FUZ_BLACK)
			{
				pW->m_eColor = FuzNode::FUZ_RED;
				pX = pX->m_pParent;
			}
			else
			{
				if (pW->m_pRight->m_eColor == FuzNode::FUZ_BLACK)
				{
					pW->m_pLeft->m_eColor = FuzNode::FUZ_BLACK;
					pW->m_eColor = FuzNode::FUZ_RED;
					RightRotate(pW);
					pW = pX->m_pParent->m_pRight;
				}
				pW->m_eColor = pX->m_pParent->m_eColor;
				pX->m_pParent->m_eColor = FuzNode::FUZ_BLACK;
				pW->m_pRight->m_eColor = FuzNode::FUZ_BLACK;
				LeftRotate(pX->m_pParent);
				pX = m_pRoot;
			}
		}
		else
		{
			pW = pX->m_pParent->m_pLeft;
			if (pW->m_eColor == FuzNode::FUZ_RED)
			{
				pW->m_eColor = FuzNode::FUZ_BLACK;
				pW->m_pParent->m_eColor = FuzNode::FUZ_RED;
				RightRotate(pX->m_pParent);
				pW = pX->m_pParent->m_pLeft;
			}
			if (pW->m_pRight->m_eColor == FuzNode::FUZ_BLACK && pW->m_pLeft->m_eColor == FuzNode::FUZ_BLACK)
			{
				pW->m_eColor = FuzNode::FUZ_RED;
				pX = pX->m_pParent;
			}
			else
			{
				if (pW->m_pLeft->m_eColor == FuzNode::FUZ_BLACK)
				{
					pW->m_pRight->m_eColor = FuzNode::FUZ_BLACK;
					pW->m_eColor = FuzNode::FUZ_RED;
					LeftRotate(pW);
					pW = pX->m_pParent->m_pLeft;
				}
				pW->m_eColor = pX->m_pParent->m_eColor;
				pX->m_pParent->m_eColor = FuzNode::FUZ_BLACK;
				pW->m_pLeft->m_eColor = FuzNode::FUZ_BLACK;
				RightRotate(pX->m_pParent);
				pX = m_pRoot;
			}
		}
	}

	pX->m_eColor = FuzNode::FUZ_BLACK;
}

template< typename K, typename V, class KFavor, class VFavor >
bool FuzTree< K, V, KFavor, VFavor >::FUZDelete( FuzNode* pZ) throw()
{
	if (pZ == NULL)
		return false;

	FuzNode* pY = NULL;
	FuzNode* pX = NULL;
	if (IsNil(pZ->m_pLeft) || IsNil(pZ->m_pRight))
		pY = pZ;
	else
		pY = Successor(pZ);

	if (!IsNil(pY->m_pLeft))
		pX = pY->m_pLeft;
	else
		pX = pY->m_pRight;

	pX->m_pParent = pY->m_pParent;

	if (IsNil(pY->m_pParent))
		m_pRoot = pX;
	else if (pY == pY->m_pParent->m_pLeft)
		pY->m_pParent->m_pLeft = pX;
	else
		pY->m_pParent->m_pRight = pX;

	if (pY->m_eColor == FuzNode::FUZ_BLACK)
		FUZDeleteFixup(pX);

	if (pY != pZ)
		SwapNode(pY, pZ);

	if (m_pRoot != NULL)
		SetNil(&m_pRoot->m_pParent);

	FreeNode( pZ );

	return true;
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::Minimum(
	 FuzNode* pNode) const throw()
{
	if (pNode == NULL || IsNil(pNode))
	{
		return NULL;
	}

	FuzNode* pMin = pNode;
	while (!IsNil(pMin->m_pLeft))
	{
		pMin = pMin->m_pLeft;
	}

	return pMin;
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::Maximum(
	 FuzNode* pNode) const throw()
{
	if (pNode == NULL || IsNil(pNode))
	{
		return NULL;
	}

	FuzNode* pMax = pNode;
	while (!IsNil(pMax->m_pRight))
	{
		pMax = pMax->m_pRight;
	}

	return pMax;
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::Predecessor(
	 FuzNode* pNode ) const throw()
{
	if( pNode == NULL )
	{
		return( NULL );
	}
	if( !IsNil(pNode->m_pLeft) )
	{
		return( Maximum( pNode->m_pLeft ) );
	}

	FuzNode* pParent = pNode->m_pParent;
	FuzNode* pLeft = pNode;
	while( !IsNil(pParent) && (pLeft == pParent->m_pLeft) )
	{
		pLeft = pParent;
		pParent = pParent->m_pParent;
	}

	if (IsNil(pParent))
	{
		pParent = NULL;
	}
	return( pParent );
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::Successor(
	 FuzNode* pNode) const throw()
{
	if ( pNode == NULL )
	{
		return NULL;
	}
	if ( !IsNil(pNode->m_pRight) )
	{
		return Minimum(pNode->m_pRight);
	}

	FuzNode* pParent = pNode->m_pParent;
	FuzNode* pRight = pNode;
	while ( !IsNil(pParent) && (pRight == pParent->m_pRight) )
	{
		pRight = pParent;
		pParent = pParent->m_pParent;
	}

	if (IsNil(pParent))
	{
		pParent = NULL;
	}
	return pParent;
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzNode* FuzTree< K, V, KFavor, VFavor >::FUZInsert(
	 KINARGTYPE key,
	 VINARGTYPE value) throw()
{
	FuzNode* pNewNode = InsertImpl( key, value );

	FuzNode* pX = pNewNode;
	pX->m_eColor = FuzNode::FUZ_RED;
	FuzNode* pY = NULL;
	while (pX != m_pRoot && pX->m_pParent->m_eColor == FuzNode::FUZ_RED)
	{
		if (pX->m_pParent == pX->m_pParent->m_pParent->m_pLeft)
		{
			pY = pX->m_pParent->m_pParent->m_pRight;
			if (pY != NULL && pY->m_eColor == FuzNode::FUZ_RED)
			{
				pX->m_pParent->m_eColor = FuzNode::FUZ_BLACK;
				pY->m_eColor = FuzNode::FUZ_BLACK;
				pX->m_pParent->m_pParent->m_eColor = FuzNode::FUZ_RED;
				pX = pX->m_pParent->m_pParent;
			}
			else
			{
				if (pX == pX->m_pParent->m_pRight)
				{
					pX = pX->m_pParent;
					LeftRotate(pX);
				}
				pX->m_pParent->m_eColor = FuzNode::FUZ_BLACK;
				pX->m_pParent->m_pParent->m_eColor = FuzNode::FUZ_RED;
				RightRotate(pX->m_pParent->m_pParent);
			}
		}
		else
		{
			pY = pX->m_pParent->m_pParent->m_pLeft;
			if (pY != NULL && pY->m_eColor == FuzNode::FUZ_RED)
			{
				pX->m_pParent->m_eColor = FuzNode::FUZ_BLACK;
				pY->m_eColor = FuzNode::FUZ_BLACK;
				pX->m_pParent->m_pParent->m_eColor = FuzNode::FUZ_RED;
				pX = pX->m_pParent->m_pParent;
			}
			else
			{
				if (pX == pX->m_pParent->m_pLeft)
				{
					pX = pX->m_pParent;
					RightRotate(pX);
				}
				pX->m_pParent->m_eColor = FuzNode::FUZ_BLACK;
				pX->m_pParent->m_pParent->m_eColor = FuzNode::FUZ_RED;
				LeftRotate(pX->m_pParent->m_pParent);
			}
		}
	}

	m_pRoot->m_eColor = FuzNode::FUZ_BLACK;
	SetNil(&m_pRoot->m_pParent);

	return( pNewNode );
}

#ifdef _DEBUG

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::VerifyIntegrity(
	 const FuzNode *pNode,
	 int nCurrBlackDepth,
	 int &nBlackDepth) const throw()
{
	bool bCheckForBlack = false;
	bool bLeaf = true;

	if (pNode->m_eColor == FuzNode::FUZ_RED)
		bCheckForBlack = true;
	else
		nCurrBlackDepth++;

	FUZASSERT(pNode->m_pLeft != NULL);
	if (!IsNil(pNode->m_pLeft))
	{
		bLeaf = false;
		if (bCheckForBlack)
		{
			FUZASSERT(pNode->m_pLeft->m_eColor == FuzNode::FUZ_BLACK);
		}

		VerifyIntegrity(pNode->m_pLeft, nCurrBlackDepth, nBlackDepth);
	}

	FUZASSERT(pNode->m_pRight != NULL);
	if (!IsNil(pNode->m_pRight))
	{
		bLeaf = false;
		if (bCheckForBlack)
		{
			FUZASSERT(pNode->m_pRight->m_eColor == FuzNode::FUZ_BLACK);
		}

		VerifyIntegrity(pNode->m_pRight, nCurrBlackDepth, nBlackDepth);
	}

	FUZASSERT( pNode->m_pParent != NULL );
	FUZASSERT( ( IsNil(pNode->m_pParent) ) ||
			( pNode->m_pParent->m_pLeft == pNode ) ||
			( pNode->m_pParent->m_pRight == pNode ) );

	if (bLeaf)
	{
		if (nBlackDepth == 0)
		{
			nBlackDepth = nCurrBlackDepth;
		}
		else
		{
			FUZASSERT(nBlackDepth == nCurrBlackDepth);
		}
	}
}

template< typename K, typename V, class KFavor, class VFavor >
void FuzTree< K, V, KFavor, VFavor >::VerifyIntegrity() const throw()
{
	if ((m_pRoot == NULL) || (IsNil(m_pRoot)))
		return;

	FUZASSUME(m_pRoot->m_eColor == FuzNode::FUZ_BLACK);
	int nBlackDepth = 0;
	VerifyIntegrity(m_pRoot, 0, nBlackDepth);
}

#endif 

template< typename K, typename V, class KFavor = FuzElement< K >, class VFavor = FuzElement< V > >
class FuzRBMap : public FuzTree< K, V, KFavor, VFavor >
{
public:
	typedef typename KFavor::INARGTYPE KINARGTYPE;
	typedef typename KFavor::OUTARGTYPE KOUTARGTYPE;
	typedef typename VFavor::INARGTYPE VINARGTYPE;
	typedef typename VFavor::OUTARGTYPE VOUTARGTYPE;
	
	explicit FuzRBMap( size_t nBlockSize = 10) throw();
	~FuzRBMap() throw();

	 bool Lookup(
		 KINARGTYPE key,
		 VOUTARGTYPE value) const throw();
	typename FuzTree<K, V, KFavor, VFavor>::FuzPair const * Lookup( KINARGTYPE key) const throw();
	typename FuzTree<K, V, KFavor, VFavor>::FuzPair* Lookup( KINARGTYPE key) throw();
	POSITION SetAt(
		 KINARGTYPE key,
		 VINARGTYPE value) throw();
	bool RemoveKey( KINARGTYPE key) throw();
};

template< typename K, typename V, class KFavor, class VFavor >
FuzRBMap< K, V, KFavor, VFavor >::FuzRBMap( size_t nBlockSize) throw() :
	FuzTree< K, V, KFavor, VFavor >( nBlockSize )
{
}

template< typename K, typename V, class KFavor, class VFavor >
FuzRBMap< K, V, KFavor, VFavor >::~FuzRBMap() throw()
{
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree<K, V, KFavor, VFavor>::FuzPair const * FuzRBMap< K, V, KFavor, VFavor >::Lookup(
	 KINARGTYPE key) const throw()
{
	return FuzTree<K, V, KFavor, VFavor>::Find(key);
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree< K, V, KFavor, VFavor >::FuzPair* FuzRBMap< K, V, KFavor, VFavor >::Lookup(
	 KINARGTYPE key) throw()
{
	return FuzTree<K, V, KFavor, VFavor>::Find(key);
}

template< typename K, typename V, class KFavor, class VFavor >
bool FuzRBMap< K, V, KFavor, VFavor >::Lookup(
	 KINARGTYPE key,
	 VOUTARGTYPE value) const throw()
{
	const typename FuzTree<K, V, KFavor, VFavor>::FuzPair* pLookup = FuzTree<K, V, KFavor, VFavor>::Find( key );
	if( pLookup == NULL )
		return false;

	value = pLookup->m_value;
	return true;
}

template< typename K, typename V, class KFavor, class VFavor >
POSITION FuzRBMap< K, V, KFavor, VFavor >::SetAt(
	 KINARGTYPE key,
	 VINARGTYPE value) throw()
{
	typename FuzTree<K, V, KFavor, VFavor>::FuzPair* pNode = FuzTree<K, V, KFavor, VFavor>::Find( key );
	if( pNode == NULL )
	{
		return( FuzTree<K, V, KFavor, VFavor>::FUZInsert( key, value ) );
	}
	else
	{
		pNode->m_value = value;

		return( pNode );
	}
}

template< typename K, typename V, class KFavor, class VFavor >
bool FuzRBMap< K, V, KFavor, VFavor >::RemoveKey( KINARGTYPE key) throw()
{
	POSITION pos = Lookup( key );
	if( pos != NULL )
	{
		FuzTree<K, V, KFavor, VFavor>::RemoveAt( pos );

		return( true );
	}
	else
	{
		return( false );
	}
}

template< typename K, typename V, class KFavor = FuzElement< K >, class VFavor = FuzElement< V > >
class FuzMultiMap : public FuzTree< K, V, KFavor, VFavor >
{
public:
	typedef typename KFavor::INARGTYPE KINARGTYPE;
	typedef typename KFavor::OUTARGTYPE KOUTARGTYPE;
	typedef typename VFavor::INARGTYPE VINARGTYPE;
	typedef typename VFavor::OUTARGTYPE VOUTARGTYPE;
  
	explicit FuzMultiMap( size_t nBlockSize = 10) throw();
	~FuzMultiMap() throw();

	POSITION Insert(
		 KINARGTYPE key,
		 VINARGTYPE value) throw();
	size_t RemoveKey( KINARGTYPE key) throw();

	POSITION FindFirstWithKey( KINARGTYPE key) const throw();
	const typename FuzTree<K, V, KFavor, VFavor>::FuzPair* GetNextWithKey(
		 POSITION& pos,
		 KINARGTYPE key) const throw();
	typename FuzTree<K, V, KFavor, VFavor>::FuzPair* GetNextWithKey(
		 POSITION& pos,
		 KINARGTYPE key) throw();
	const V& GetNextValueWithKey(
		 POSITION& pos,
		 KINARGTYPE key) const throw();
	V& GetNextValueWithKey(
		 POSITION& pos,
		 KINARGTYPE key) throw();
};

template< typename K, typename V, class KFavor, class VFavor >
FuzMultiMap< K, V, KFavor, VFavor >::FuzMultiMap( size_t nBlockSize) throw() :
	FuzTree< K, V, KFavor, VFavor >( nBlockSize )
{
}

template< typename K, typename V, class KFavor, class VFavor >
FuzMultiMap< K, V, KFavor, VFavor >::~FuzMultiMap() throw()
{
}

template< typename K, typename V, class KFavor, class VFavor >
POSITION FuzMultiMap< K, V, KFavor, VFavor >::Insert(
	 KINARGTYPE key,
	 VINARGTYPE value) throw()
{
	return( FuzTree<K, V, KFavor, VFavor>::FUZInsert( key, value ) );
}

template< typename K, typename V, class KFavor, class VFavor >
size_t FuzMultiMap< K, V, KFavor, VFavor >::RemoveKey(
	 KINARGTYPE key) throw()
{
	size_t nElementsDeleted = 0;

	POSITION pos = FindFirstWithKey( key );
	while( pos != NULL )
	{
		POSITION posDelete = pos;
		GetNextWithKey( pos, key );
		FuzTree<K, V, KFavor, VFavor>::RemoveAt( posDelete );
		nElementsDeleted++;
	}

	return( nElementsDeleted );
}

template< typename K, typename V, class KFavor, class VFavor >
POSITION FuzMultiMap< K, V, KFavor, VFavor >::FindFirstWithKey(
	 KINARGTYPE key) const throw()
{
	return( FuzTree<K, V, KFavor, VFavor>::Find( key ) );
}

template< typename K, typename V, class KFavor, class VFavor >
const typename FuzTree<K, V, KFavor, VFavor>::FuzPair* FuzMultiMap< K, V, KFavor, VFavor >::GetNextWithKey(
	 POSITION& pos,
	 KINARGTYPE key) const throw()
{
	FUZASSERT( pos != NULL );
	const typename FuzTree<K, V, KFavor, VFavor>::FuzPair* pNode = FuzTree<K, V, KFavor, VFavor>::GetNext( pos );
	if( (pos == NULL) || !KFavor::CompareElements( static_cast< typename FuzTree<K, V, KFavor, VFavor>::FuzPair* >( pos )->m_key, key ) )
	{
		pos = NULL;
	}

	return( pNode );
}

template< typename K, typename V, class KFavor, class VFavor >
typename FuzTree<K, V, KFavor, VFavor>::FuzPair* FuzMultiMap< K, V, KFavor, VFavor >::GetNextWithKey(
	 POSITION& pos,
	 KINARGTYPE key) throw()
{
	FUZASSERT( pos != NULL );
	typename FuzTree<K, V, KFavor, VFavor>::FuzPair* pNode = FuzTree<K, V, KFavor, VFavor>::GetNext( pos );
	if( (pos == NULL) || !KFavor::CompareElements( static_cast< typename FuzTree<K, V, KFavor, VFavor>::FuzPair* >( pos )->m_key, key ) )
	{
		pos = NULL;
	}

	return( pNode );
}

template< typename K, typename V, class KFavor, class VFavor >
const V& FuzMultiMap< K, V, KFavor, VFavor >::GetNextValueWithKey(
	 POSITION& pos,
	 KINARGTYPE key) const throw()
{
	const typename FuzTree<K, V, KFavor, VFavor>::FuzPair* pPair = GetNextWithKey( pos, key );

	return( pPair->m_value );
}

template< typename K, typename V, class KFavor, class VFavor >
V& FuzMultiMap< K, V, KFavor, VFavor >::GetNextValueWithKey(
	 POSITION& pos,
	 KINARGTYPE key) throw()
{
	typename FuzTree<K, V, KFavor, VFavor>::FuzPair* pPair = GetNextWithKey( pos, key );

	return( pPair->m_value );
}

#endif	// end __TCOLL__
