#pragma once
#include "OsgFile.h"
#include <list>
#include "ICollection.h"
using namespace std;
//文件列表
class COsgFileSource:public ICollection<COsgFile>
{
public:
	COsgFileSource(void);
	~COsgFileSource(void);
public:
	BOOL Contains(CString fileName);
};

