#ifndef CONSTTABLE_H_INCLUDED
#define CONSTTABLE_H_INCLUDED
#include <fstream>
#include <string>

using namespace std;

class ConstTable//常数表，用于将扫描到的常数储存到变量指向的地址里面
{
public://通过对不同函数的调用，来将字符串转化为数值，字符或字符串返回即可 *****************
    ConstTable();//直接打开CT进行读取
    float getfloat(int i);
    int getint(int i);//两者都是针对数值 但是一个取所有并转化为float 另一个取整数
    string getstring(int i);
    char getchar(int i);
    void addconst(string a);
private:
    int k;
    string CT[100];//100是否足够？
                   //因为使用了数组，会导致占用大量连续空间，但是string（常量）保持不变，所以不需要改动（改动需要移动大量数据）
};
ConstTable::ConstTable()//构造函数 若后续还有其他需要 可以改为初始化函数
{
    k=0;
    ifstream CTin;
    string input;
    CTin.open("CT.txt",ios::binary);
    while(!CTin.eof())
    {
        getline(CTin,input);
        addconst(input);
    }
    CTin.close();
}

float ConstTable::getfloat(int i)
{
    string floatstring;
    floatstring=CT[i];
    float floatreturn=0;
    float counter=0.1;
    char achar;
    int aint;
    bool flag=0;
    for(int j=0;j<floatstring.size();j++)
    {
        achar=floatstring.at(j);
        if(achar=='.')
        {
            flag=1;
            continue;
        }
        aint=achar-48;
        if(!flag)
        {
            floatreturn=floatreturn*10+aint;
        }
        else
        {
            floatreturn=floatreturn+aint*counter;
            counter/=10;
        }
    }
    return floatreturn;
}
int ConstTable::getint(int i)
{
    string intstring;
    intstring=CT[i];
    int intreturn=0;
    for(int j=0;j<intstring.size();j++)
        intreturn=intreturn*10+(int(intstring.at(j))-48);
    return intreturn;
}
string ConstTable::getstring(int i)
{
    return CT[i];
}
char ConstTable::getchar(int i)
{
    return (CT[i].at(0));
}
void ConstTable::addconst(string a)
{
    CT[k]=a;
    k++;
}
#endif // CONSTTABLE_H_INCLUDED
