#pragma once
#include <list>
using namespace std;
template <class T>
class ICollection
{
private:
	typedef void (*EventHandle)(T*item);
	typedef void (*SwapEventHandle)(T*item1,T*item2);
	typedef void (*ClearEventHandle)(void);
protected:
	BOOL m_onDestoryItems;
	list<T*> m_List;
public:
	ICollection(void);
	~ICollection(void);
public:
	void virtual Add(T*item);//添加对象
	void virtual Remove(T*item);//移除对象
	BOOL virtual Contains(T*item);//是否包含对象
	BOOL virtual Swap(T*item1,T*item2);//交换对象顺序
	void virtual Clear();//清空集合
	void virtual Delete(T*item);//移除集合对象，并回收（使用delete）
	void virtual DeleteAll();//移除所有对象，并回收（使用delete）
	list<T*> Collection() const;//获取集合对象
	int Count() const;//集合个数
	T*Get(int index=0);//取得指定位置对象
	T*operator[](int index) const;
	BOOL OnDestoryItems() const;//获取是否析构时删除对象
	void OnDestoryItems(BOOL val);//设置是否删除时删除对象
public:
	EventHandle Added;
	EventHandle Removed;
	ClearEventHandle Cleared; 
	SwapEventHandle Swaped;
};

template <class T>
BOOL ICollection<T>::Contains( T*item )
{
	list<T*>::iterator it=m_List.begin();
	while (it!=m_List.end())
	{
		T*t=*it;
		if (t==item)
		{
			return TRUE;
		}
		it++;
	}
	return FALSE;
}

template <class T>
int ICollection<T>::Count() const
{
	return m_List.size();
}

template <class T>
T* ICollection<T>::operator[]( const int index ) const
{
	return Get(index);
}

template <class T>
T* ICollection<T>::Get( int index/*=0*/ )
{
	std::list<T*>::iterator it=m_List.begin();
	int i=0;
	while (it!=m_List.end())
	{
		if (i==index)
		{
			T* t=*it;
			return t;
		}
		it++;
		i++;
	}
	return NULL;
}

template <class T>
ICollection<T>::ICollection( void )
{
	m_List.clear();
	Added=NULL;
	Removed=NULL;
	Cleared=NULL;
	Swaped=NULL;
}

template <class T>
ICollection<T>::~ICollection( void )
{
	if (m_onDestoryItems)
	{
		DeleteAll();
	}
	else
	{
		Clear();
	}
}

template <class T>
void ICollection<T>::Add( T*item )
{
	m_List.push_back(item);
	if (Added!=NULL)
	{
		Added(item);
	}
}

template <class T>
void ICollection<T>::Remove( T*item )
{
	m_List.remove(item);
	if (Removed!=NULL)
	{
		Removed(item);
	}
}

template <class T>
BOOL ICollection<T>::Swap( T*item1,T*item2 )
{
	if(item1==item2)
	{
		return FALSE;
	}
	int i = -1;
	int i1 = -1;
	int i2 = -1;
	for(std::list<T*>::iterator it = m_List.begin(); it != m_List.end(); it++)
	{
		i++;
		if(i1 == -1 && *it==item1)
		{
			i1 = i;
			if(i1 != -1 && i2 != -1)
			{
				break;
			}
		}
		else if(i2 == -1 && *it==item2)
		{
			i2 = i;
			if(i1 != -1 && i2 != -1)
			{
				break;
			}
		}
	}
	if(i1 == -1 || i2 == -1)
	{
		return FALSE;
	}
	i = -1;
	//交换
	for(std::list<T*>::iterator it = m_List.begin(); it != m_List.end();)
	{
		i++;
		if (i1<i2)
		{
			if (i==i1)
			{
				it = m_List.insert(it,1,item2);//在item1前插入item2
				it++;
				it = m_List.erase(it);
				i++;
				if (i!=i2)
				{
					continue;
				}
			}
			if(i==i2)
			{
				it = m_List.insert(it,1,item1);//在item2前插入item1
				it++;
				m_List.erase(it);
				break;
			}
		}
		else if(i1>i2)
		{
			if (i==i2)
			{
				it = m_List.insert(it,1,item1);//在item2前插入item1
				it++;
				it = m_List.erase(it);
				i++;
				if (i!=i1)
				{
					continue;
				}
			}
			else if(i==i1)
			{
				it = m_List.insert(it,1,item2);//在item1前插入item2
				it++;
				m_List.erase(it);
				break;
			}
		}
		it++;
	}
	if (Swaped!=NULL)
	{
		Swaped(item1,item2);
	}
	return TRUE;
}

template <class T>
void ICollection<T>::Clear()
{
	m_List.clear();
	if (Cleared!=NULL)
	{
		Cleared();
	}
}

template <class T>
list<T*> ICollection<T>::Collection() const
{
	return m_List;
}

template <class T>
void ICollection<T>::Delete( T*item )
{
	if (item!=NULL)
	{
		Remove(item);
		delete item;
	}
}

template <class T>
void ICollection<T>::DeleteAll()
{
	list<T*>::iterator it=m_List.begin();
	while (it!=m_List.end())
	{
		T*t=*it;
		it=m_List.erase(it);
		delete t;
	}
	if (Cleared!=NULL)
	{
		Cleared();
	}
}
template <class T>
BOOL ICollection<T>::OnDestoryItems() const
{
	return m_onDestoryItems;
}

template <class T>
void ICollection<T>::OnDestoryItems( BOOL val )
{
	m_onDestoryItems = val;
}

