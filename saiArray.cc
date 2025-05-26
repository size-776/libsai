
ARRAYCLASS::ARRAYCLASS()
{
	_Init();
}

ARRAYCLASS::ARRAYCLASS(const ARRAYCLASS& src)
{
	_Init();
	
	for (int i= 0; i < src.m_Num; i++)
		Add(*src.m_pData[i]);
}

ARRAYCLASS::~ARRAYCLASS()
{
	RemoveAll();
}

void ARRAYCLASS::_Init()
{
	m_pData= NULL;
	//m_pArray= NULL;
	m_Num= 0;
	m_Size= 0;
}

int ARRAYCLASS::Init(int nSize)
{
	RemoveAll();
	return Alloc(nSize);
}

int ARRAYCLASS::RemoveAll()
{
	//if (!m_pArray)
	if (!m_pData)
		return 0;

	for (int i= 0; i < m_Size; i++)
		delete m_pData[i];
	
	//delete m_pData;
	free(m_pData);
	m_pData= NULL;
	//free(m_pArray);
	//m_pArray= NULL;
	
	m_Num= 0;
	m_Size= 0;

	return 0;
}

int	ARRAYCLASS::Alloc(int nSize, bool setZero)
{
	int sai= sizeof(ARRAYITEM*);

	if (!m_pData)
		//m_pData= new ARRAYITEM*[nSize];
		m_pData= (ARRAYITEM**) malloc(sai*nSize);
	else
	{
		// devo deallocare quelli in piu'
		for (int i = nSize; i < GetSize(); ++i)
		{
			delete m_pData[i];
			m_pData[i] = NULL;
		}
		m_pData = (ARRAYITEM**)realloc(m_pData, sai*nSize);
	}

	if (m_pData)
	{
		if (setZero)
			memset(&m_pData[m_Size], 0, sai*(nSize - m_Size));

		/*if (!m_pArray)
			m_pArray= (ARRAYITEM *) malloc(sizeof(ARRAYITEM)*nSize);
		else
			m_pArray= (ARRAYITEM *) realloc(m_pArray, sizeof(ARRAYITEM)*nSize);*/
	}

	m_Size= nSize;
	return 0;
}

int ARRAYCLASS::CheckSize(int nAdd)
{
	if (m_Num+nAdd > m_Size)
	{
		if (Alloc(max(16, 4*m_Size/3)))
			return 1;
	}

	return 0;
}

int ARRAYCLASS::Add(ARRAYITEM cItem)
{
	if (CheckSize())
		return 1;

	if (m_pData[m_Num])
		delete m_pData[m_Num];

	m_pData[m_Num++]= new ARRAYITEM(cItem);
	//memcpy(&m_pArray[m_Num++], &cItem, sizeof(ARRAYITEM));
	//m_pArray[m_Num++]= cItem;

	return 0;
}

ARRAYITEM& ARRAYCLASS::operator[](int nItem)
{
	return GetAt(nItem);
}

ARRAYITEM& ARRAYCLASS::GetAt(int nItem)
{
	return *m_pData[nItem];
	//return m_pArray[nItem];
}

int ARRAYCLASS::SetAt(int nPos, ARRAYITEM Value)
{
	if (nPos >= m_Num)
		return 1;

	if (m_pData[nPos])
		delete m_pData[nPos];

	m_pData[nPos]= new ARRAYITEM(Value);
	//memcpy(&m_pArray[nPos], &Value, sizeof(ARRAYITEM));
	//m_pArray[nPos]= Value;

	return 0;
}

int ARRAYCLASS::RemoveAt(int nPos)
{
	if (nPos >= m_Num)
		return 1;

	if (m_pData[nPos])
		delete m_pData[nPos];

	int i= nPos;
	for (; i < m_Num-1; i++)
		m_pData[i]= m_pData[i+1];
	m_pData[i]= NULL;

	/*int i= nPos;
	for (; i < m_Num-1; i++)
		//memcpy(&m_pArray[i], &m_pArray[i+1], sizeof(ARRAYITEM));
		m_pArray[i]= m_pArray[i+1];
	*/
	m_Num--;
	return 0;
}

int ARRAYCLASS::GetSize()
{
	return m_Num;
}

int ARRAYCLASS::GetCount()
{
	return GetSize();
}

int ARRAYCLASS::SetSize(int nSize)
{
	int oldNum = m_Num;
	int oldSize = m_Size;

	Alloc(nSize, false);
	m_Num= max(0, min(nSize, m_Num));
	// inizializzo le nuove celle
	for (int i = oldSize; i < m_Size; ++i)
		m_pData[i] = NULL;

	return 0;
}

void ARRAYCLASS::operator=(ARRAYCLASS src)
{
	Copy(src);
}

void ARRAYCLASS::Copy(ARRAYCLASS src)
{
	for (int i= 0; i < src.GetSize(); i++)
		Add(src[i]);	
}

void ARRAYCLASS::InsertAt(int nPos, ARRAYITEM value)
{
	if (CheckSize())
		return;

	int i;
	for (i= m_Num; i > nPos; i--)
		m_pData[i]= m_pData[i-1];
	m_pData[i]= new ARRAYITEM(value);

	/*for (i= m_Num; i > nPos; i--)
		//memcpy(&m_pArray[i], &m_pArray[i-1], sizeof(ARRAYITEM));
		m_pArray[i]= m_pArray[i-1];
	m_pArray[i]= value;*/

	m_Num++;
}

ARRAYITEM** ARRAYCLASS::GetData()
{
	return m_pData;
}

/*ARRAYITEM* ARRAYCLASS::GetData()
{
	return m_pArray;
}*/

void ARRAYCLASS::Append(ARRAYCLASS arr)
{
	for (int i= 0; i < arr.GetSize(); i++)
		Add(arr[i]);
}

POSITION ARRAYCLASS::GetHeadPosition()
{
	return (POSITION) (intptr_t) 1;
}

ARRAYITEM& ARRAYCLASS::GetHead()
{
	return *m_pData[0];
}

ARRAYITEM& ARRAYCLASS::GetNext(POSITION &pos)
{
	int i= (int)pos-1;
	pos++;

	if ((int) pos > m_Num)
		pos= NULL;

	return *m_pData[i];
	//return m_pArray[i];
}

void ARRAYCLASS::AddTail(ARRAYCLASS* list)
{
	Append(*list);
}

void ARRAYCLASS::AddTail(ARRAYITEM item)
{
	Add(item);
}

bool ARRAYCLASS::IsEmpty()
{
	return !m_Num;
}

int ARRAYCLASS::QSort(int(*pfnCmp)(const void *arg1, const void *arg2))
{
	for (int i= 0; i < m_Num; i++)
	{
		for (int j= i+1; j < m_Num; j++)
		{
			int c= pfnCmp(m_pData[i], m_pData[j]);
			if (c <= 0)
				continue;

			ARRAYITEM *t= m_pData[i];
			m_pData[i]= m_pData[j];
			m_pData[j]= t;
		}
	}

	return 0;
}
