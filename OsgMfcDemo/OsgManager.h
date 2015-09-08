#pragma once
#include "resource.h"
#include <list>
#include "OsgSceneCollection.h"
#include "OsgFileSource.h"
#include "FileSourceDlg.h"
#include "D3WindowsDlg.h"
#include "ScenesDlg.h"
#include "SceneLayersDlg.h"
using namespace std;
extern class CFileSourceDlg;
extern class CD3WindowsDlg;
extern class CScenesDlg;
extern class CSceneLayersDlg;
class COsgManager
{
private:
	COsgFileSource * m_fileSource;//文件列表
	COsgSceneCollection* m_sceneCollection;//场景集合

	CFileSourceDlg*m_fileSourceDlg;//文件窗口
	CD3WindowsDlg*m_d3WindowsDlg;//场景窗口
	CScenesDlg*m_scenesDlg;//场景列表窗口
	CSceneLayersDlg*m_sceneLayersDlg;//图层窗口
public:
	COsgManager(void);
	~COsgManager(void);
public:
	COsgFileSource * FileSource() const;
	COsgSceneCollection* SceneCollection()const;
	CFileSourceDlg* FileSourceDlg() const { return m_fileSourceDlg; }
	void FileSourceDlg(CFileSourceDlg* val) { m_fileSourceDlg = val; }
	CD3WindowsDlg* D3WindowsDlg() const { return m_d3WindowsDlg; }
	void D3WindowsDlg(CD3WindowsDlg* val) { m_d3WindowsDlg = val; }
	CScenesDlg* ScenesDlg() const { return m_scenesDlg; }
	void ScenesDlg(CScenesDlg* val) { m_scenesDlg = val; }
	CSceneLayersDlg* SceneLayersDlg() const { return m_sceneLayersDlg; }
	void SceneLayersDlg(CSceneLayersDlg* val) { m_sceneLayersDlg = val;}
};

