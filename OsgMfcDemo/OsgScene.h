#pragma once
#include <list>
#include "OsgSceneFile.h"
using namespace std;
class COsgScene
{
private:
	list<COsgSceneFile*>* m_osgSceneFileList;//文件列表
	BOOL m_isNew;//是否是新建（未命名）
	BOOL m_isSaved;//是否已保存
	CString m_Name;//场景名称
	static int NEW_COUNT;
public:
	COsgScene(BOOL isNew);
	COsgScene(CString name,BOOL isNew);
	~COsgScene(void);
public:
	CString Name() const { return m_Name; }
	void Name(CString val) { m_Name = val; }
	list<COsgSceneFile*>* OsgSceneFileList() const { return m_osgSceneFileList; }
	void AddOsgSceneFile(COsgSceneFile *osgFile);
};

