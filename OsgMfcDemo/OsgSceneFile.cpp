#include "stdafx.h"
#include "OsgSceneFile.h"


COsgSceneFile::COsgSceneFile(COsgFile*osgFile):
	m_strAliasName(_T(""))
{
	m_osgFile=osgFile;
}


COsgSceneFile::~COsgSceneFile(void)
{
}

CString COsgSceneFile::AliasName()
{
	if(m_strAliasName.IsEmpty())
	{
		return m_osgFile->FileName();
	}
	else
	{
		 return m_strAliasName;
	}
}
