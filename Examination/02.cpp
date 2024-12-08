#include <cstring>
#include <iostream>

// 1
// 为下面的类加上赋值相关操作

class CMyString
{
public:

    CMyString(char *pData = nullptr);
    ~CMyString(void);

    // Copy sematics
    CMyString(const CMyString &str);
    CMyString &operator=(const CMyString &_lhs);

    void       print() { std::cout << m_pData << std::endl; }

private:

    char *m_pData;
};

CMyString::CMyString(char *pData)
{
    if (pData == nullptr)
    {
        m_pData    = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int len = strlen(pData);
        m_pData = new char[len + 1];
        memcpy(m_pData, pData, len * sizeof(char));
    }
}

CMyString::~CMyString() { delete[] m_pData; }

CMyString::CMyString(const CMyString &str)
{
    int len = strlen(str.m_pData);
    m_pData = new char[len + 1];
    memcpy(m_pData, str.m_pData, len);
}

CMyString &CMyString::operator=(const CMyString &_lhs)
{
    if (this == &_lhs)
        return *this;

    CMyString tmp{_lhs};
    // Shallow copy
    char     *tempptr = tmp.m_pData;
    tmp.m_pData       = this->m_pData;
    this->m_pData     = tempptr;

    return *this;
}

int main()
{

    char *str = "Hello World.\n";

    std::cout << "Test Copy:" << std::endl;
    CMyString cstr1{str};
    CMyString cstr2{cstr1};
    cstr1           = cstr1;
    CMyString cstr3 = cstr2 = cstr1;

    cstr1.print();
    cstr2.print();
    cstr3.print();

    return 0;
}