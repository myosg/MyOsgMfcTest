#include "stdafx.h"
#include "PickEventHandle.h"
#include <osgFX/Scribe>

CPickEventHandle::CPickEventHandle(void)
{
	m_mouseX=-1;
	m_mouseY=-1;
}


CPickEventHandle::~CPickEventHandle(void)
{
}

bool CPickEventHandle::handle( const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
	osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
	if (!view) return false;
	switch(ea.getEventType())
	{
		//鼠标按下
	case(osgGA::GUIEventAdapter::PUSH):
		{
			//更新鼠标位置
			m_mouseX = ea.getX();
			m_mouseY = ea.getY();
			//Select(view, ea.getX(), ea.getY());
			break;
		}
	case(osgGA::GUIEventAdapter::RELEASE):
		{
			if (m_mouseX==ea.getX() && m_mouseY==ea.getY())
			{
				//执行对象选取
				Select(view, ea.getX(), ea.getY());
			}
			break;
		}
	default:
		break;
	}
	return false;
}

void CPickEventHandle::Select( osgViewer::View* view, float mouseX, float mouseY )
{
	osg::ref_ptr<osg::Node> node = new osg::Node();
	osg::ref_ptr<osg::Group> parent = new osg::Group();
	//创建一个线段交集检测函数
	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (view->computeIntersections(mouseX, mouseY, intersections))
	{
		osgUtil::LineSegmentIntersector::Intersection intersection = *intersections.begin();
		osg::NodePath& nodePath = intersection.nodePath;
		//得到选择的物体
		node = (nodePath.size()>=1)?nodePath[nodePath.size()-1]:0;
		parent = (nodePath.size()>=2)?dynamic_cast<osg::Group*>(nodePath[nodePath.size()-2]):0;
	}       

	//用一种高亮显示来显示物体已经被选中
	if (parent.get() && node.get())
	{
		osg::ref_ptr<osgFX::Scribe> parentAsScribe = dynamic_cast<osgFX::Scribe*>(parent.get());
		if (!parentAsScribe)
		{
			//如果对象选择到，高亮显示
			osg::ref_ptr<osgFX::Scribe> scribe = new osgFX::Scribe();
			scribe->addChild(node.get());
			parent->replaceChild(node.get(),scribe.get());
		}
		else
		{
			//如果没有没有选择到，则移除高亮显示的对象
			osg::Node::ParentList parentList = parentAsScribe->getParents();
			for(osg::Node::ParentList::iterator itr=parentList.begin();
				itr!=parentList.end();
				++itr)
			{
				(*itr)->replaceChild(parentAsScribe.get(),node.get());
			}
		}
	}
}
