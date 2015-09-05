#pragma once
#include <list>
#include "OsgSceneCollection.h"
#include "OsgWindowCollection.h"
#include "OsgFileSource.h"
using namespace std;
class COsgManager
{
private:
	COsgFileSource * m_fileSource;//文件列表
	COsgSceneCollection* m_sceneCollection;//场景集合
	COsgWindowCollection*m_windowCollection;//窗口集合
public:
	COsgManager(void);
	~COsgManager(void);
public:
	COsgFileSource * FileSource() const;
	COsgSceneCollection* SceneCollection()const;
	COsgWindowCollection* WindowCollection() const;
};

