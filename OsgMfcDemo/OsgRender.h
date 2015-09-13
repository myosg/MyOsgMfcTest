#pragma once

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/Group>
#include <string>
class CRenderingThread;
class COsgRender
{
private:
	CRenderingThread* m_thread;
public:
    COsgRender(HWND hWnd);
    ~COsgRender();

    void InitOSG();
	int StartGrahics();
	void RefreshGrahics();
    void InitManipulators(void);
    void AddNode(osg::ref_ptr<osg::Node> node);
	void RemoveNode(osg::ref_ptr<osg::Node> node);
    void InitCameraConfig(void);
    void SetupWindow(void);
    void SetupCamera(void);
    void PreFrameUpdate(void);
    void PostFrameUpdate(void);
    void Done(bool value) { mDone = value; }
    bool Done(void) { return mDone; }
    //static void Render(void* ptr);

    osgViewer::Viewer* getViewer() { return mViewer; }

private:
    bool mDone;
    std::string m_ModelName;
    HWND m_hWnd;
    osgViewer::Viewer* mViewer;
    osg::ref_ptr<osg::Group> mRoot;
    //osg::ref_ptr<osg::Node> mModel;
    osg::ref_ptr<osgGA::TrackballManipulator> trackball;
    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator;
};

class CRenderingThread : public OpenThreads::Thread
{
public:
    CRenderingThread( COsgRender* ptr );
    virtual ~CRenderingThread();

    virtual void run();

protected:
    COsgRender* _ptr;
    bool _done;
};
