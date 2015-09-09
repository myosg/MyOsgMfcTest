#pragma once
#include "OsgFile.h"
class COsgSceneFile
{
private:
	COsgFile*m_osgFile;
	CString m_strAliasName;
public:
	COsgSceneFile(COsgFile*osgFile);
	~COsgSceneFile(void);
public:
	CString AliasName();
	void AliasName(CString val) { m_strAliasName = val; }
	COsgFile* OsgFile() const { return m_osgFile; }
	void OsgFile(COsgFile* val) { m_osgFile = val; }
};

