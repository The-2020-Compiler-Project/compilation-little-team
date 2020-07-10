#ifndef CONSTTABLE_H_INCLUDED
#define CONSTTABLE_H_INCLUDED
#include <fstream>
#include <string>

using namespace std;

class ConstTable//���������ڽ�ɨ�赽�ĳ������浽����ָ��ĵ�ַ����
{
public://ͨ���Բ�ͬ�����ĵ��ã������ַ���ת��Ϊ��ֵ���ַ����ַ������ؼ��� *****************
    ConstTable();//ֱ�Ӵ�CT���ж�ȡ
    float getfloat(int i);
    int getint(int i);//���߶��������ֵ ����һ��ȡ���в�ת��Ϊfloat ��һ��ȡ����
    string getstring(int i);
    char getchar(int i);
    void addconst(string a);
private:
    int k;
    string CT[100];//100�Ƿ��㹻��
                   //��Ϊʹ�������飬�ᵼ��ռ�ô��������ռ䣬����string�����������ֲ��䣬���Բ���Ҫ�Ķ����Ķ���Ҫ�ƶ��������ݣ�
};
ConstTable::ConstTable()//���캯�� ����������������Ҫ ���Ը�Ϊ��ʼ������
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
