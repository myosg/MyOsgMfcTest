#pragma once
#include "OsgFile.h"
#include "osg\Node"
class COsgSceneFile
{
private:
	COsgFile*m_osgFile;
	CString m_strAliasName;
	osg::ref_ptr<osg::Node> m_osgNode;
private:
	osg::ref_ptr<osg::Node> DoReadOsgFile();
public:
	COsgSceneFile(COsgFile*osgFile);
	~COsgSceneFile(void);
public:
	CString AliasName();
	void AliasName(CString val) { m_strAliasName = val; }
	COsgFile* OsgFile() const { return m_osgFile; }
	osg::ref_ptr<osg::Node> OsgNode();
	void OsgFile(COsgFile* val) { m_osgFile = val; }
};

