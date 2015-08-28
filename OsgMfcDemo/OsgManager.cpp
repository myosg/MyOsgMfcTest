#include "stdafx.h"
#include "OsgManager.h"


COsgManager::COsgManager(void)
{
	m_osgFileList.clear();
}

COsgManager::~COsgManager(void)
{
	ClearOsgFileList();
}

void COsgManager::AddOsgFile(COsgFile* osgfile)
{
	m_osgFileList.push_back(osgfile);
}

std::list<COsgFile*> COsgManager::OsgFileList() const
{
	return m_osgFileList;
}

void COsgManager::RemoveOsgFile(COsgFile * const osgfile)
{
	m_osgFileList.remove(osgfile);
}

BOOL COsgManager::SwapOsgFile( COsgFile*const osgFile1,  COsgFile*const osgFile2)
{
	if(osgFile1==osgFile2)
	{
		return FALSE;
	}
	int i = -1;
	int i1 = -1;
	int i2 = -1;
	for(std::list<COsgFile*>::iterator it = m_osgFileList.begin(); it != m_osgFileList.end(); it++)
	{
		i++;
		if(i1 == -1 && *it==osgFile1)
		{
			i1 = i;
			if(i1 != -1 && i2 != -1)
			{
				break;
			}
		}
		else if(i2 == -1 && *it==osgFile2)
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
	for(std::list<COsgFile*>::iterator it = m_osgFileList.begin(); it != m_osgFileList.end();)
	{
		i++;
		if (i1<i2)
		{
			if (i==i1)
			{
				it = m_osgFileList.insert(it,1,osgFile2);//在osgFile1前插入osgFile2
				it++;
				it = m_osgFileList.erase(it);
				i++;
				if (i!=i2)
				{
					continue;
				}
			}
			if(i==i2)
			{
				it = m_osgFileList.insert(it,1,osgFile1);//在osgFile1前插入osgFile1
				it++;
				m_osgFileList.erase(it);
				break;
			}
		}
		else if(i1>i2)
		{
			if (i==i2)
			{
				it = m_osgFileList.insert(it,1,osgFile1);//在osgFile1前插入osgFile1
				it++;
				it = m_osgFileList.erase(it);
				i++;
				if (i!=i1)
				{
					continue;
				}
			}
			else if(i==i1)
			{
				it = m_osgFileList.insert(it,1,osgFile2);//在osgFile1前插入osgFile2
				it++;
				m_osgFileList.erase(it);
				break;
			}
		}
		it++;
	}
	return TRUE;
}

void COsgManager::ClearOsgFileList()
{
	std::list<COsgFile*>::iterator it = m_osgFileList.begin();
	while (it!=m_osgFileList.end())
	{
		delete *it;
		it = m_osgFileList.erase(it);
	}
}

void COsgManager::DeleteOsgFile( COsgFile * const osgfile )
{
	RemoveOsgFile(osgfile);
	delete osgfile;
}
