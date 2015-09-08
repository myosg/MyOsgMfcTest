#include "stdafx.h"
#include "OsgFileSource.h"


COsgFileSource::COsgFileSource(void)
{
}


COsgFileSource::~COsgFileSource(void)
{

}

BOOL COsgFileSource::Contains( CString fileName )
{
	list<COsgFile*>::iterator it=m_List.begin();
	while (it!=m_List.end())
	{
		if((*it)->FilePathName().CompareNoCase(fileName)==0)
		{
			return TRUE;
		}
		it++;
	}
	return FALSE;
}


