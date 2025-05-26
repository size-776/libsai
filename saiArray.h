//#pragma once // rimosso per smartlib
#ifndef _EASYARRAY_H
#define _EASYARRAY_H

#define ARRAYCLASS CsaiIntArray
#define ARRAYITEM int
#include "saiArray.hh"
#undef ARRAYCLASS
#undef ARRAYITEM

//#define ARRAYCLASS CsaiStrArray
//#define ARRAYITEM CString
//#include "saiArray.hh"
//#undef ARRAYCLASS
//#undef ARRAYITEM

#define ARRAYCLASS CsaiDoubleArray
#define ARRAYITEM double
#include "saiArray.hh"
#undef ARRAYCLASS
#undef ARRAYITEM

#define ARRAYCLASS CsaiBoolArray
#define ARRAYITEM bool
#include "saiArray.hh"
#undef ARRAYCLASS
#undef ARRAYITEM

#define ARRAYCLASS CsaiVoidPtrArray
#define ARRAYITEM void*
#include "saiArray.hh"
#undef ARRAYCLASS
#undef ARRAYITEM

//#define ARRAYCLASS CsaiStringList
//#define ARRAYITEM CString
//#include "saiArray.hh"
//#undef ARRAYCLASS
//#undef ARRAYITEM

#include "saiVTypeArray.h"

#ifdef _LIBSAI
#define IntArray CsaiVTypeArray<int>
#else
#define IntArray CIntArray
#endif

template <typename T>
class CsaiArray
{
public:

	CsaiArray();
	~CsaiArray();

	int Init		(int nSize= 256);
	int RemoveAll	();
	T& operator[](int nItem);
	int	Alloc		(int nSize);
	int Add			(T cItem);
	int	GetSize		();
	int GetCount	();
	int SetSize		(int nSize);
	int SetAt		(int nPos, T Value);
	int RemoveAt	(int nPos);
	void Copy		(CsaiArray src);
	T**		GetData();
	T&		GetAt(int nItem);
	void InsertAt	(int nPos, T value);
	//T* GetData();
	void Append		(CsaiArray arr);
	void AddTail	(T cItem);
	void AddTail	(CsaiArray* list);
	POSITION GetHeadPosition();
	T& GetNext(POSITION &pos);	

protected:
	int CheckSize	(int nAdd= 1);

	//T*	*m_Array;
	T**	m_pData;
	int			m_Num;
	int			m_Size;		
};

template <typename T>
CsaiArray<T>::CsaiArray()
{
	m_pData= NULL;
	m_Num= 0;
	m_Size= 0;
}

template <typename T>
CsaiArray<T>::~CsaiArray()
{
	RemoveAll();
}

template <typename T>
int CsaiArray<T>::Init(int nSize)
{
	RemoveAll();
	return Alloc(nSize);
}

template <typename T>
int CsaiArray<T>::RemoveAll()
{
	if (!m_pData)
		return 0;

	for (int i= 0; i < m_Num; i++)
		delete m_pData[i];

	//delete m_pData;
	free(m_pData);
	m_pData= NULL;
	m_Num= 0;
	m_Size= 0;

	return 0;
}

template <typename T>
int	CsaiArray<T>::Alloc(int nSize)
{
	if (!m_pData)
		//m_pData= new T*[nSize];
		m_pData= (T**) malloc(sizeof(T*)*nSize);
	else
		m_pData= (T**) realloc(m_pData, sizeof(T*)*nSize);

	if (!m_pData)
		return 1;

	m_Size= nSize;
	return 0;
}

template <typename T>
int CsaiArray<T>::CheckSize(int nAdd)
{
	if (m_Num+nAdd > m_Size)
	{
		if (Alloc(max(16, 4*m_Size/3)))
			return 1;
	}

	return 0;
}

template <typename T>
int CsaiArray<T>::Add(T cItem)
{
	if (CheckSize())
		return 1;

	m_pData[m_Num++]= new T(cItem);
	return 0;
}

template <typename T>
T& CsaiArray<T>::operator[](int nItem)
{
	return GetAt(nItem);
}

template <typename T>
T** CsaiArray<T>::GetData()
{
	return m_pData;
}

template <typename T>
T& CsaiArray<T>::GetAt(int nItem)
{
	return *m_pData[nItem];
}

template <typename T>
int CsaiArray<T>::SetAt(int nPos, T Value)
{
	if (nPos >= m_Num)
		return 1;

	if (m_pData[nPos])
		delete m_pData[nPos];

	m_pData[nPos]= new T(Value);
	return 0;
}

template <typename T>
int CsaiArray<T>::RemoveAt(int nPos)
{
	if (nPos >= m_Num)
		return 1;

	if (m_pData[nPos])
		delete m_pData[nPos];

	int i= nPos;
	for (; i < m_Num-1; i++)
		m_pData[i]= m_pData[i+1];
	m_pData[i]= NULL;

	m_Num--;
	return 0;
}

template <typename T>
int CsaiArray<T>::GetSize()
{
	return m_Num;
}

template <typename T>
int CsaiArray<T>::GetCount()
{
	return GetSize();
}

template <typename T>
int CsaiArray<T>::SetSize(int nSize)
{
	int oldNum = m_Num;
	m_Num= max(0, min(nSize, m_Num));
	for (int i=m_Num; i < oldNum; i++)
	{
		delete m_pData[i];
		m_pData[i] = NULL;
	}

	return 0;
}

template <typename T>
void CsaiArray<T>::Copy(CsaiArray src)
{
	int i;
	for (i= 0; i < src.GetSize(); i++)
	{
		Add(src[i]);
	}
}

template <typename T>
void CsaiArray<T>::InsertAt(int nPos, T value)
{
	if (CheckSize())
		return;

	int i;
	for (i= m_Num; i > nPos; i--)
		m_pData[i]= m_pData[i-1];
	m_pData[i]= new T(value);
	m_Num++;
}

/*T* CsaiArray<T>::GetData()
{
	return m_pData;
}*/

template <typename T>
void CsaiArray<T>::Append(CsaiArray arr)
{
	for (int i= 0; i < arr.GetSize(); i++)
		Add(arr[i]);
}

template <typename T>
POSITION CsaiArray<T>::GetHeadPosition()
{
	return (POSITION) (intptr_t) 1;
}

template <typename T>
T& CsaiArray<T>::GetNext(POSITION &pos)
{
	int i= (int)pos-1;
	pos++;

	if ((int) pos > m_Num)
		pos= NULL;

	return *m_pData[i];
}

template <typename T>
void CsaiArray<T>::AddTail(CsaiArray* list)
{
	Append(*list);
}

template <typename T>
void CsaiArray<T>::AddTail(T item)
{
	Add(item);
}

#ifndef _LIBSAI
#define QSORTARRAY(a, t, c) qsort(a.GetData(), a.GetCount(), sizeof(t), c);
#else
#define QSORTARRAY(a, t, c) a.QSort(c)
#endif

#endif // _EASYARRAY_H
