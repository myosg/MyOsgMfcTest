#pragma once
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
class CPickEventHandle :
	public osgGA::GUIEventHandler
{
private:
	float m_mouseX;
	float m_mouseY;
public:
	CPickEventHandle(void);
	~CPickEventHandle(void);
	virtual bool handle( const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
	void Select(osgViewer::View* view, float mouseX, float mouseY);
};

