#include "stdafx.h"
#include "OsgManager.h"


COsgManager::COsgManager(void)
{
	m_fileSource=new COsgFileSource();
	m_sceneCollection=new COsgSceneCollection(); 
}

COsgManager::~COsgManager( void )
{
	m_sceneCollection->DeleteAll();
	delete m_sceneCollection;
	m_fileSource->DeleteAll();
	delete m_fileSource;
}

COsgFileSource * COsgManager::FileSource() const
{
	return m_fileSource;
}

COsgSceneCollection* COsgManager::SceneCollection() const
{
	return m_sceneCollection;
}


