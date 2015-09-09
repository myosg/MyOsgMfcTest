#include "stdafx.h"
#include "OsgScene.h"


COsgScene::COsgScene(BOOL isNew)
{
	m_osgSceneFileList=new list<COsgSceneFile*>();
	m_isNew=isNew;
	m_Name="新建场景";
	m_Name.Format(_T("新建场景%d"),NEW_COUNT++);
}

COsgScene::COsgScene( CString name,BOOL isNew )
{
	m_osgSceneFileList=new list<COsgSceneFile*>();
	m_isNew=isNew;
	if (name.Trim().Compare(_T(""))==0)
	{
		m_Name="新建场景";
		m_Name.Format(_T("新建场景%d"),NEW_COUNT++);
	}
	m_Name=name;
}


COsgScene::~COsgScene(void)
{
	for (list<COsgSceneFile*>::iterator it = m_osgSceneFileList->begin(); it!=m_osgSceneFileList->end(); it++)
	{
		delete (*it);
	}
	delete m_osgSceneFileList;
}

void COsgScene::AddOsgSceneFile( COsgSceneFile *osgFile )
{
	m_osgSceneFileList->push_back(osgFile);
}

int COsgScene::NEW_COUNT=1;
