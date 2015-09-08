#include "stdafx.h"
#include "OsgScene.h"


COsgScene::COsgScene(BOOL isNew)
{
	m_isNew=isNew;
	m_Name="新建场景";
	m_Name.Format(_T("新建场景%d"),NEW_COUNT++);
}

COsgScene::COsgScene( CString name,BOOL isNew )
{
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
}

int COsgScene::NEW_COUNT=1;
