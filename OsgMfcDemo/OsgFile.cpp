#include "stdafx.h"
#include "OsgFile.h"


COsgFile::COsgFile(void):
	m_filePathName(_T(""))
{
}

COsgFile::COsgFile(CString filePathName)
{
	FilePathName(filePathName);
}


COsgFile::~COsgFile(void)
{
}

CString COsgFile::FilePathName() const
{
	return m_filePathName;
}

void COsgFile::FilePathName(CString val)
{
	m_filePathName = val;
}
BOOL COsgFile::EqualByFilePathName(const COsgFile &file) const
{
	return (this->m_filePathName.CompareNoCase(file.FilePathName()) == 0);
}

BOOL COsgFile::EqualByReference(const COsgFile&file) const
{
	return this == &file;
}

BOOL COsgFile::operator==( const COsgFile&file ) const
{
	return EqualByReference(file);
}
