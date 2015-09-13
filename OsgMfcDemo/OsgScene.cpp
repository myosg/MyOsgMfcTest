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
		name = "新建场景";
		name.Format(_T("新建场景%d"), NEW_COUNT++);
	}
	m_Name = name;
}
COsgScene::~COsgScene(void)
{
	if (m_osgSceneFileList)
	{
		list<COsgSceneFile*>::iterator it = m_osgSceneFileList->begin();
		while (it!=m_osgSceneFileList->end())
		{
			COsgSceneFile*t=*it;
			it = m_osgSceneFileList->erase(it);
			delete t;
		}
		delete m_osgSceneFileList;
		m_osgSceneFileList=NULL;
	}
}

void COsgScene::AddOsgSceneFile(COsgSceneFile *osgFile)
{
	m_osgSceneFileList->push_back(osgFile);

}