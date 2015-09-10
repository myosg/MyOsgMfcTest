#pragma once
#include <string>
using namespace std;
//申请空间
void* Malloc(int size);
//释放空间
void Free(void*p);
//如果p=NULL,将会调用Malloc，不为空则不调用
void ToChars(CString str,char*&p);
//转为string 类型
void ToString(CString str,string&cstr);
