class ARRAYCLASS
{
public:

	ARRAYCLASS();
	ARRAYCLASS(const ARRAYCLASS &src);
	~ARRAYCLASS();

	void _Init		();
	int Init		(int nSize= 256);
	int RemoveAll	();
	ARRAYITEM& operator[](int nItem);
	int	Alloc		(int nSize, bool setZero = true);
	int Add			(ARRAYITEM cItem);
	int	GetSize		();
	int GetCount	();
	int SetSize		(int nSize);
	int SetAt		(int nPos, ARRAYITEM Value);
	int RemoveAt	(int nPos);
	void Copy		(ARRAYCLASS src);
	void operator=	(ARRAYCLASS src);	
	ARRAYITEM**		GetData();
	//ARRAYITEM*		GetData();
	ARRAYITEM&		GetAt(int nItem);
	void InsertAt	(int nPos, ARRAYITEM value);
	void Append		(ARRAYCLASS arr);
	void AddTail	(ARRAYITEM cItem);
	void AddTail	(ARRAYCLASS* list);
	POSITION GetHeadPosition();
	ARRAYITEM&		GetHead();
	ARRAYITEM& GetNext(POSITION &pos);
	bool IsEmpty();
	int QSort(int (*pfnCmp)(const void *arg1, const void *arg2));
#ifdef _WINDOWS
#ifdef _EASYPOINTARRAY
	ARRAYCLASS Filter(RECT r);
	ARRAYCLASS FilterLines(RECT r, bool bExclude= true);
#endif
#endif
protected:
	int CheckSize	(int nAdd= 1);

	//ARRAYITEM	*m_pArray;
	ARRAYITEM*	*m_pData;
	int			m_Num;
	int			m_Size;		
};
