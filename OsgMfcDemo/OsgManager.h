#pragma once
#include "OsgFile.h"
#include <list>
class COsgManager
{
private:
	std::list<COsgFile*> m_osgFileList;//打开文件管理器
public:
	COsgManager(void);
	~COsgManager(void);
public:
	void AddOsgFile(COsgFile* osgfile);//添加模型文件
	void RemoveOsgFile(COsgFile * const osgfile);//移除指定模型文件
	void DeleteOsgFile(COsgFile * const osgfile);//删除指定模型文件
	BOOL SwapOsgFile(COsgFile*const osgFile1,COsgFile*const osgFile2);//交换模型文件
	std::list<COsgFile*> OsgFileList() const;
	void ClearOsgFileList();
};

