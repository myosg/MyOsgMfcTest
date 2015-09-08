#pragma once
#include <list>
#include "OsgFile.h"
using namespace std;
class COsgScene
{
private:
	list<COsgFile*>m_osgFileList;//文件列表
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
};

