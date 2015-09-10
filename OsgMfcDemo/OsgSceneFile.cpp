#include "stdafx.h"
#include "OsgSceneFile.h"
#include "osgDB\ReadFile"
#include <string>
#include "Common.h"
using namespace std;

COsgSceneFile::COsgSceneFile(COsgFile*osgFile):
	m_strAliasName(_T(""))
{
	m_osgFile=osgFile;
	m_osgNode=NULL;
	DoReadOsgFile();
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

osg::Node* COsgSceneFile::DoReadOsgFile()
{
	if (m_osgFile&&m_osgNode==NULL)
	{
		string str;
		ToString(m_osgFile->FilePathName(),str);
		m_osgNode=osgDB::readNodeFile(str);
	}
	return m_osgNode;
}

osg::Node* COsgSceneFile::OsgNode()
{
	if (!m_osgNode)
	{
		return DoReadOsgFile();
	}
	else
	{
		return m_osgNode;
	}
}
