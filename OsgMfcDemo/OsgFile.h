#pragma once
class COsgFile
{
private:
    CString m_filePathName;//文件名称路径
public:
    COsgFile(void);
    COsgFile(CString filePathName);
    ~COsgFile(void);
public:
    CString FilePathName() const;//获取路径
    void FilePathName(CString val);//设置路径
	CString FileName();
public:
    BOOL EqualByFilePathName(const COsgFile&file) const;//通过文件名比较
    BOOL EqualByReference(const COsgFile&file) const;//引用比较
    BOOL operator==(const COsgFile&file) const;
};

