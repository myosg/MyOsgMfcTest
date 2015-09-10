#include "stdafx.h"
#include "Common.h"

void* Malloc( int size )
{
	void*p=malloc(size);
	return p;
}

void Free( void*p )
{
	if (p)
	{
		free(p);
	}
}

void ToChars( CString str,char*&p )
{
	if (p==NULL)
	{
		p=(char*)Malloc(str.GetLength()+1);
	}
	WideCharToMultiByte(CP_ACP,0,str.GetBuffer(),-1,p,str.GetLength()+1,NULL,NULL);
}
void ToString(CString str,string&cstr)
{
	char*p=NULL;
	ToChars(str,p);
	cstr = p;
	Free(p);
}



