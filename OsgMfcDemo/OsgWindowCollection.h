#pragma once
#include "OsgWindow.h"
#include <list>
#include "ICollection.h"
using namespace std;
//´°¿ÚÁÐ±í
class COsgWindowCollection:public ICollection<COsgWindow>
{
public:
	COsgWindowCollection(void);
	~COsgWindowCollection(void);
public:

};

