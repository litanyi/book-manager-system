#include "c_Book.h"
#include<fstream>

c_Book::c_Book()
{
}


c_Book::c_Book(string cName, string cIsbn, string cPrice, string cAuthor)
    :m_cName(cName),m_cIsbn(cIsbn),m_cPrice(cPrice),m_cAuthor(cAuthor)
{

}

c_Book::~c_Book()
{
}

string c_Book::GetName()
{
    return m_cName;
}

void c_Book::SetName(string cName)
{
    m_cName = cName;
}
string c_Book::GetIsbn()
{
    return m_cIsbn;
}
void c_Book::SetIsbn(string cIsbn)
{
    m_cIsbn = cIsbn;
}
string c_Book::GetPrice()
{
    return m_cPrice;
}
void c_Book::SetPrice(string cPrice)
{
    m_cPrice = cPrice;
}
string c_Book::GetAuthor()
{
    return m_cAuthor;
}


void c_Book::SetAuthor()
{
    m_cAuthor = m_cAuthor;
}

//将数据写入文件中
void c_Book::WriteData()                
{
    ofstream oFile;
    oFile.open("book.txt", ios::binary|ios::app);
    try
    {
        oFile.write(m_cName.c_str(),NUM1);
        oFile.write(m_cIsbn.c_str(), NUM1);
        oFile.write(m_cPrice.c_str(), NUM2);
        oFile.write(m_cAuthor.c_str(), NUM2);
    }
    catch(...)
    {
        throw("file error occurred!");
        oFile.close();
    }
    oFile.close();
}

//从文件中删除数据，创建一个临时的文件，把不删除的部分放在临时文件
void c_Book::DeleteData(int iCount)
{
    long resPos;
    int iDataCount = 0;
    char tempBuf[NUM1*2+NUM2*2];
    fstream file("book.txt",ios::binary|ios::in|ios::out);
    fstream tempFile("temp.txt",ios::binary|ios::in|ios::out|ios::trunc);
    ofstream oFile;
    file.seekg(0,ios::end);
    resPos = file.tellg();
    iDataCount = resPos / (NUM1 * 2 + NUM2 * 2);
    if (iDataCount < 0 || iDataCount < iCount)
    {
        throw "input number error";
    }
    else
    {
        file.seekg(iCount*(NUM1 * 2 + NUM2 * 2), ios::beg);
        for (int i = 0; i < (iDataCount - iCount);i++)
        {
            memset(tempBuf,0, NUM1 * 2 + NUM2 * 2);
            file.read(tempBuf, NUM1 * 2 + NUM2 * 2);
            tempFile.write(tempBuf, NUM1 * 2 + NUM2 * 2);
        }
        file.close();
        tempFile.seekg(0,ios::beg);
        oFile.open("book.txt");
        oFile.seekp((iCount-1)*(NUM1 * 2 + NUM2 * 2),ios::beg);
        for (int i = 0; i < (iDataCount-iCount); i++)
        {
            memset(tempBuf, 0, NUM1 * 2 + NUM2 * 2);
            tempFile.read(tempBuf, NUM1 * 2 + NUM2 * 2);
            oFile.write(tempBuf, NUM1 * 2 + NUM2 * 2);
        }
    }
    tempFile.close();
    oFile.close();
    remove("temp.txt");
}

//获取文件中的数据
void c_Book::GetBookFromFile(int iCount)
{
    char cName[NUM1];
    char cIsbn[NUM1];
    char cPrice[NUM2];
    char cAuthor[NUM2];
    ifstream iFile("book.txt", ios::binary);
    try
    {
        iFile.seekg(iCount*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
        iFile.read(cName, NUM1);
        if (iFile.tellg() > 0)
        {
            m_cName = cName;
        }
        iFile.read(cIsbn, NUM1);
        if (iFile.tellg() > 0)
        {
            m_cIsbn = cIsbn;
        }
        iFile.read(cPrice, NUM2);
        if (iFile.tellg() > 0)
        {
            m_cPrice = cPrice;
        }
        iFile.read(cAuthor, NUM2);
        if (iFile.tellg() > 0)
        {
            m_cAuthor = cAuthor;
        }
    }
    catch (...)
    {
        throw("file error occurred!");
        iFile.close();
    }
    iFile.close();
}
