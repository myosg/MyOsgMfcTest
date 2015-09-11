#include "stdafx.h"
#include "OsgScene.h"

COsgScene::COsgScene(BOOL isNew)
{
	DoInitOsgScene(_T(""), isNew);
}

COsgScene::COsgScene(CString name, BOOL isNew)
{
	DoInitOsgScene(name, isNew);
}


void COsgScene::DoInitOsgScene(CString name, BOOL isNew)
{
	static int NEW_COUNT = 1;
	m_osgSceneFileList = new list<COsgSceneFile*>();
	m_isNew = isNew;
	if(name.Trim().Compare(_T("")) == 0)
	{
		m_Name = "新建场景";
		m_Name.Format(_T("新建场景%d"), NEW_COUNT++);
	}
	m_Name = name;
	m_osgGroup=new osg::Group();
}
COsgScene::~COsgScene(void)
{
	for(list<COsgSceneFile*>::iterator it = m_osgSceneFileList->begin(); it != m_osgSceneFileList->end(); it++)
	{
		delete(*it);
	}
	delete m_osgSceneFileList;
}

void COsgScene::AddOsgSceneFile(COsgSceneFile *osgFile)
{
	m_osgSceneFileList->push_back(osgFile);

