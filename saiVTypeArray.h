#pragma once

#include <stdlib.h>
//#include <cstring> // 20231006 SIZE: in bits_config++ fa l'undef di min/max

template <typename T>
class CsaiVTypeArray
{
public:

	CsaiVTypeArray();
	~CsaiVTypeArray();

	CsaiVTypeArray(const CsaiVTypeArray<T>& other);
	T& operator=(const CsaiVTypeArray<T>& other);

	int Init		(int nSize= 256);
	int RemoveAll	();
	T& operator[](int nItem);
	int	Alloc		(int nSize);
	int Add			(T cItem);
	int	GetSize		();
	int GetCount	();
	void SetSize	(int nSize, int nGrowBy = -1);
	void SetAt		(int nPos, T Value);
	void RemoveAt	(int nPos, int count=1);
	void InsertAt	(int nPos, T value);
	void Copy		(CsaiVTypeArray src);
	T* GetData();
	T&		GetAt(int nItem);
	void Append		(CsaiVTypeArray arr);
	void AddTail	(T cItem);
	void AddTail	(CsaiVTypeArray* list);

protected:
	int CheckSize	(int nAdd= 1);

	T*	m_pData;
	int			m_Num;
	int			m_Size;
};

#ifndef IntArray
#ifdef __AFX_H__
#define IntArray CIntArray
#else
#define IntArray CsaiVTypeArray<int>
#endif
#endif // IntArray

template <typename T>
CsaiVTypeArray<T>::CsaiVTypeArray()
{
	m_pData= NULL;
	m_Num= 0;
	m_Size= 0;
}

template <typename T>
CsaiVTypeArray<T>::CsaiVTypeArray(const CsaiVTypeArray<T>& other)
{
	m_pData = NULL;
	m_Num = 0;
	m_Size = 0;

	if (other.m_Num)
	{
		Alloc(other.m_Num);
		m_Num = other.m_Num;
		memcpy((void *) m_pData, (void *) other.m_pData, sizeof(T) * other.m_Num);
	}
}

template <typename T>
T& CsaiVTypeArray<T>::operator=(const CsaiVTypeArray<T>& other)
{
	if (m_pData && m_pData != other.m_pData)
	{
		if (other.m_Num)
		{
			Alloc(other.m_Num);
			m_Num = other.m_Num;
			memcpy((void *) m_pData, (void *) other.m_pData, sizeof(T) * m_Num);
		}
		else
			RemoveAll();
	}
	else
	{
		// self assignment
		int FBP = 0;
	}

	return *this;
}

template <typename T>
CsaiVTypeArray<T>::~CsaiVTypeArray()
{
	RemoveAll();
}

template <typename T>
int CsaiVTypeArray<T>::Init(int nSize)
{
	RemoveAll();
	return Alloc(nSize);
}

template <typename T>
int CsaiVTypeArray<T>::RemoveAll()
{
	if (!m_pData)
		return 0;

	free(m_pData);
	m_pData= NULL;
	m_Num= 0;
	m_Size= 0;

	return 0;
}

template <typename T>
int	CsaiVTypeArray<T>::Alloc(int nSize)
{
	if (!m_pData)
		m_pData= (T*) malloc(sizeof(T) * nSize);
	else
		m_pData= (T*) realloc(m_pData, sizeof(T) * nSize);

	if (!m_pData)
		return 1;

	// Grezzata per inizializzare la virtual table!!
	{
		T tmp;
		for (int i=m_Size; i < nSize; ++i)
			memcpy((void *) &m_pData[i], (void *) &tmp, sizeof(tmp));
	}

	m_Size= nSize;
	return 0;
}

template <typename T>
int CsaiVTypeArray<T>::CheckSize(int nAdd)
{
	if (m_Num+nAdd > m_Size)
	{
		if (Alloc(max(16, 4*m_Size/3)))
			return 1;
	}

	return 0;
}

template <typename T>
int CsaiVTypeArray<T>::Add(T cItem)
{
	if (CheckSize())
		return -1;

	int pos = m_Num++;
	m_pData[pos]= cItem;

	return pos;
}

template <typename T>
T& CsaiVTypeArray<T>::operator[](int nItem)
{
	return GetAt(nItem);
}

template <typename T>
T* CsaiVTypeArray<T>::GetData()
{
	return m_pData;
}

template <typename T>
T& CsaiVTypeArray<T>::GetAt(int nItem)
{
	return m_pData[nItem];
}

template <typename T>
void CsaiVTypeArray<T>::SetAt(int nPos, T Value)
{
	if (nPos >= m_Num)
		return;

	m_pData[nPos]= Value;
}

template <typename T>
void CsaiVTypeArray<T>::RemoveAt(int nPos, int count)
{
	if (nPos + count > m_Num)
		return;

	if (m_Num - nPos-count)
		memmove((void *) &m_pData[nPos], (void *) &m_pData[nPos+count], (m_Num - nPos-count) * sizeof(T));
	m_Num -= count;
}

template <typename T>
int CsaiVTypeArray<T>::GetSize()
{
	// 20210127 GetSize e GetCount devono essere equivalenti!!!
	return m_Num;//m_Size;
}

template <typename T>
int CsaiVTypeArray<T>::GetCount()
{
	return m_Num;//GetSize();
}

template <typename T>
void CsaiVTypeArray<T>::SetSize(int nSize, int nGrowBy)
{
	Alloc(nSize);
	m_Num= max(0, min(nSize, m_Num));
}

template <typename T>
void CsaiVTypeArray<T>::Copy(CsaiVTypeArray src)
{
	int i;
	for (i= 0; i < src.GetCount(); i++)
	{
		Add(src[i]);
	}
}

template <typename T>
void CsaiVTypeArray<T>::InsertAt(int nPos, T value)
{
	if (CheckSize(1))
		return;

	memmove((void *) &m_pData[nPos+1], (void *) &m_pData[nPos], (m_Num - nPos) * sizeof(m_pData[0]));
	m_pData[nPos]= value;
	m_Num++;
}

/*T* CsaiVTypeArray<T>::GetData()
{
	return m_pData;
}*/

template <typename T>
void CsaiVTypeArray<T>::Append(CsaiVTypeArray arr)
{
	for (int i= 0; i < arr.GetCount(); i++)
		Add(arr[i]);
}

template <typename T>
void CsaiVTypeArray<T>::AddTail(CsaiVTypeArray* list)
{
	Append(*list);
}

template <typename T>
void CsaiVTypeArray<T>::AddTail(T item)
{
	Add(item);
}

template <typename T>
class CEasyVTypeList : public CsaiVTypeArray<T>
{
public:
	POSITION GetHeadPosition();
	POSITION GetTailPosition();
	T& GetNext(POSITION &pos);

	POSITION InsertAfter(POSITION position, T newElement);
	POSITION InsertBefore(POSITION position, T newElement);
};


template <typename T>
POSITION CEasyVTypeList<T>::GetHeadPosition()
{
	return (POSITION) (intptr_t) 1;
}


template <typename T>
POSITION CEasyVTypeList<T>::GetTailPosition()
{
	return (POSITION) (intptr_t) this->GetCount();
}

template <typename T>
T& CEasyVTypeList<T>::GetNext(POSITION &pos)
{
	int i= (int)pos-1;
	pos++;

	if ((int) pos > this->m_Num)
		pos= NULL;

	return this->m_pData[i];
}

template <typename T>
POSITION CEasyVTypeList<T>::InsertAfter(POSITION position, T newElement)
{
	CEasyVTypeList<T>::InsertAt(position, newElement);
	return (POSITION) (intptr_t) (position+1);
}

template <typename T>
POSITION CEasyVTypeList<T>::InsertBefore(POSITION position, T newElement)
{
	CEasyVTypeList<T>::InsertAt(position-1, newElement);
	return (POSITION) (intptr_t) (position);
}
