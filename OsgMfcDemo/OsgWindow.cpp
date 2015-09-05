#include "stdafx.h"
#include "OsgWindow.h"


COsgWindow::COsgWindow(HWND hwnd,COsgScene*scene)
{
	OpenScene(scene);
}

COsgWindow::~COsgWindow(void)
{
}

BOOL COsgWindow::OpenScene( COsgScene*scene )
{
	if (m_Scene!=NULL)
	{
		CloseScene();
	}
	m_Scene=scene;
	return TRUE;
}

BOOL COsgWindow::CloseScene()
{
	m_Scene=NULL;
	return TRUE;
}
