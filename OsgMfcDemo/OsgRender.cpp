// COsgRender.cpp : implementation of the COsgRender class
//
#include "stdafx.h"
#include "OsgRender.h"
#include "PickEventHandle.h"

COsgRender::COsgRender(HWND hWnd) :
    m_hWnd(hWnd)
{
    mRoot=NULL;
    m_thread=NULL;
    mViewer=NULL;
}

COsgRender::~COsgRender()
{
	if (m_thread)
	{
		delete m_thread;
		Sleep(500);
	}
    if (mViewer)
    {
        mViewer->setDone(true);
		Sleep(500);
        mViewer->stopThreading();
        delete mViewer;
    }
}

void COsgRender::InitOSG()
{
    //return;
    // Store the name of the model to load
    if (mRoot)
        return;
    mRoot=new osg::Group();
    // Init different parts of OSG
    InitManipulators();
    //InitSceneGraph();
    InitCameraConfig();
}

void COsgRender::InitManipulators(void)
{
    // Create a trackball manipulator
    trackball = new osgGA::TrackballManipulator();

    // Create a Manipulator Switcher
    keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

    // Add our trackball manipulator to the switcher
    keyswitchManipulator->addMatrixManipulator( '1', "Trackball", trackball.get());

    // Init the switcher to the first manipulator (in this case the only manipulator)
    keyswitchManipulator->selectMatrixManipulator(0);  // Zero based index Value
}

void COsgRender::InitCameraConfig(void)
{
    // Local Variable to hold window size data
    RECT rect;

    // Create the viewer for this window
    mViewer = new osgViewer::Viewer();

    // Get the current window size
    ::GetWindowRect(m_hWnd, &rect);

    // Init the GraphicsContext Traits
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

    // Init the Windata Variable that holds the handle for the Window to display OSG in.
    osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);
    traits->x = 0;
    traits->y = 0;
    traits->width = rect.right - rect.left;
    traits->height = rect.bottom - rect.top;
    // Setup the traits parameters
    traits->windowDecoration = false;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;
    traits->setInheritedWindowPixelFormat = true;
    traits->inheritedWindowData = windata;

    // Create the Graphics Context
    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

    // Init Master Camera for this View
    osg::ref_ptr<osg::Camera> camera = mViewer->getCamera();

    // Assign Graphics Context to the Camera
    camera->setGraphicsContext(gc.get());

    // Set the viewport for the Camera
    //camera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));
    camera->setViewport(new osg::Viewport(0, 0, rect.right - rect.left, rect.bottom - rect.top));

    // Set projection matrix and camera attribtues
    camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0, 1000.0);
    // Add the Camera to the Viewer
    //mViewer->addSlave(camera.get());
    mViewer->setCamera(camera.get());

    // Add the Camera Manipulator to the Viewer
    mViewer->setCameraManipulator(keyswitchManipulator.get());

    // Set the Scene Data
    mViewer->setSceneData(mRoot.get());

    // Add a Stats Handler to the viewer
    mViewer->addEventHandler(new osgViewer::StatsHandler);
	mViewer->addEventHandler(new CPickEventHandle());
    // Realize the Viewer
    mViewer->realize();

    // Correct aspect ratio
    /*double fovy,aspectRatio,z1,z2;
    mViewer->getCamera()->getProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);
    aspectRatio=double(traits->width)/double(traits->height);
    mViewer->getCamera()->setProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);*/
}

void COsgRender::AddNode(osg::ref_ptr<osg::Node> node)
{
    if (!mRoot)
        return;
    // Optimize the model
    osgUtil::Optimizer optimizer;
    optimizer.optimize(node.get());
    optimizer.reset();
    // Add the model to the scene
    if (!mRoot->containsNode(node.get()))
        mRoot->addChild(node.get());
}

void COsgRender::RemoveNode( osg::ref_ptr<osg::Node> node )
{
    if (mRoot)
        mRoot->removeChild(node.get());
}


void COsgRender::PreFrameUpdate()
{
    // Due any preframe updates in this routine
}

void COsgRender::PostFrameUpdate()
{
    // Due any postframe updates in this routine
}

int COsgRender::StartGrahics()
{
    if (!mRoot||!mViewer)
        return -1;

    if (!m_thread)
    {
        m_thread = new CRenderingThread(this);
        int i= m_thread->start();
        if (i!=0)
        {
            delete m_thread;
            m_thread=NULL;
        }
        return i;
    }
    return 0;
}

void COsgRender::RefreshGrahics()
{
    if (mViewer)
	{
        mViewer->setSceneData(mRoot.get());
	}
}




/*void cOSG::Render(void* ptr)
{
    cOSG* osg = (cOSG*)ptr;

    osgViewer::Viewer* viewer = osg->getViewer();

    // You have two options for the main viewer loop
    //      viewer->run()   or
    //      while(!viewer->done()) { viewer->frame(); }

    //viewer->run();
    while(!viewer->done())
    {
        osg->PreFrameUpdate();
        viewer->frame();
        osg->PostFrameUpdate();
        //Sleep(10);         // Use this command if you need to allow other processes to have cpu time
    }

    // For some reason this has to be here to avoid issue:
    // if you have multiple OSG windows up
    // and you exit one then all stop rendering
    AfxMessageBox("Exit Rendering Thread");

    _endthread();
}*/

CRenderingThread::CRenderingThread( COsgRender *ptr )
    :   OpenThreads::Thread(), _ptr(ptr), _done(false)
{
}

CRenderingThread::~CRenderingThread()
{
    _done = true;
    if (isRunning())
    {
        cancel();
        join();
    }
}

void CRenderingThread::run()
{
    if ( !_ptr )
    {
        _done = true;
        return;
    }

    osgViewer::Viewer *viewer = _ptr->getViewer();
    do
    {
        _ptr->PreFrameUpdate();
        viewer->frame();
        _ptr->PostFrameUpdate();
        this->microSleep(100);
    }
    while ( !testCancel() && !viewer->done() && !_done );
}
