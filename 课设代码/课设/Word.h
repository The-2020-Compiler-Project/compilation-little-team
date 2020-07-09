#ifndef WORDWord_H_INCLUDED
#define WORDWord_H_INCLUDED
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
//含有WordMachine类，可以读取KT，PT，把源码转换为Word序列，并输出IT，CT（标识符表和常数表）
using namespace std;

int num=0;  //用来标记Token串序列的顺序
string sequence[500]={""};  //Token序列
void Addtoken(string s)//添加Token串函数
{
    sequence[num++]=s;
}

class wordnode
{
public:
    wordnode();
    void setnode(int Num);//设置节点序号
    int CompareTrans(char Char);//返回是否存在状态转移
    void AddTrans(char Char,int Num);//增加状态转移
    void shownode();//展示状态转移
    void setreturn(bool a,int n,char na);//设置返回类型与序号
    bool getable();
    int getnum();
    char getname();//获取是否可返回、类型、序号
private:
    int NodeNum;
    char CharTable[100]={0};
    int TransformTable[100]={0};
    int TransSum;
    bool returnable;
    int returnnum;
    char returnname;
};
bool wordnode::getable()
{
        return returnable;
}
int wordnode::getnum()
{
        return returnnum;
}
char wordnode::getname()
{
        return returnname;
}
void wordnode::setreturn(bool a,int n,char na)
{
    returnable=a;returnnum=n;returnname=na;
}
int wordnode::CompareTrans(char Char)//遍历状态转换表，若已存在目标节点则返回节点序号，反之则返回0
{
    for(int i=0;i<TransSum;i++)
    {
        if(CharTable[i]==Char)
        {
            if(TransformTable[i]!=0)
                return TransformTable[i];
        }
    }
    return 0;
}
void wordnode::AddTrans(char Char,int Num)//用于创造新的节点并将当前节点和新节点以当前字符连接，增加转移表行数
{
    CharTable[TransSum]=Char;
    TransformTable[TransSum]=Num;
    TransSum=TransSum+1;
    return;
}
void wordnode::shownode()//展示节点的序号和状态转移表
{
    cout<<NodeNum<<" "<<TransSum<<endl;
    for(int i=0;i<TransSum;i++)
    {
        cout<<CharTable[i]<<"->"<<TransformTable[i]<<endl;
    }
    cout<<returnable<<" "<<returnname<<" "<<returnnum<<endl;
}
void wordnode::setnode(int Num)//设置节点序号值
{
    NodeNum=Num;
}
wordnode::wordnode()//构造函数
{
    NodeNum=0;
    TransSum=0;
    for(int i;i<100;i++)
    {
        CharTable[i]='/0';
        TransformTable[i]=2000;
    }//初始化节点
    returnable=0;
    returnname='-1';
    returnnum=-1;
}
class Word{
public:
    Word();//构造函数
    void AddString(string str,int num);//读取字符串并转化为自动机，原用于读取文件中的关键字与符号并转化为自动机
    void Initialize();//初始化（构造由关键字与字符组成的自动机，打开待编译）
    void operate();//启动自动机
    void AddTrans(char Char,int Num);//用于构造自动机的辅助函数，若可转移则优先转移，否则创建新节点，构建新状态转移并转移到该节点
    bool AddStr(char name,int num);//用于一个一个读取字符并构造自动机
    void ReadTable();//读取关键字与字符表
    void shownode();//展示所有节点的状态转移
    void process();//从待编译文件中读取char并转移
    void wordreturn(char choice);//规约
    void Readstr();//字符串处理函数
    void Readchar();//字符处理函数
    void Readnum();//数字处理函数
    void Readki();//由于无法分别关键字与标识符，在同一个函数进行处理
    void Readp();//符号处理函数

private:
    ifstream input;//输入文件流
    ofstream ITout;
    ofstream CTout;
    ofstream output;//输出文件流
    char currentchar;//当前字符w
    wordnode WordNode[1024];//自动机
    int currentnode;//当前节点
    int nodesum;//节点数量
    int snum;
    int cnum;
    int inum;
    int nnum;
    int knum;
    int pnum;//各可规约项数量
    string str;//记录input中写入的字符串，用于输入到常数与标识符表
    string KT[100];
    string PT[100];//关键字与符号输出字符储存
    string IT[100];
    string CT[100];
    string name[4];//常量输出字符储存
};
void Word::shownode()//对所有节点进行状态转移展示
{
    for(int i=0;i<nodesum;i++)
       WordNode[i].shownode();
}
void Word::wordreturn(char choice)//规约处理
{
    if(choice==0)
    {
        choice=WordNode[currentnode].getname();
    }
    if(choice=='K')//输出
    {
        //cout<<"<K,"<<WordNode[currentnode].getnum()<<'>'<<endl;
        output<<"<K,"<<WordNode[currentnode].getnum()<<'>'<<endl;
        Addtoken(str);
        //cout<<<<KT[WordNode[currentnode].getnum()]<<" "<<str<<endl;
        //output<<KT[WordNode[currentnode].getnum()]<<" "<<str<<endl;
    }
    else if(choice=='P')
    {
        //cout<<"<P,"<<WordNode[currentnode].getnum()<<'>'<<endl;
        output<<"<P,"<<WordNode[currentnode].getnum()<<'>'<<endl;
        Addtoken(str);
        //cout<<PT[WordNode[currentnode].getnum()]<<" "<<str<<endl;
        //output<<PT[WordNode[currentnode].getnum()]<<" "<<str<<endl;
    }
    else if(choice=='I')//输出类别名与字符串str记录的值
    {
        bool k=1;
        //cout<<"<I,"<<inum<<'>'<<endl;
        output<<"<I,"<<inum<<'>'<<endl;
        Addtoken(str);
        //cout<<name[0]<<" "<<str<<endl;
        //output<<name[0]<<" "<<str<<endl;
        for(int i=0;i<inum;i++)
        {
            if(str==IT[i])
                k=0;
        }
        if(k)
        {
            IT[inum]=str;
            inum++;
            ITout<<str<<endl;
        }
    }
    else if(choice=='N')
    {
        int k=-1;
        for(int i=0;i<cnum;i++)
        {
            if(str==CT[i])
                k=i;
        }
        if(k==-1)
        {
            CT[cnum]=str;
            k=cnum;
            cnum++;
            nnum++;
            CTout<<str<<endl;
        }
        //cout<<"<N,"<<cnum<<'>'<<endl;
        output<<"<N,"<<k<<'>'<<endl;
        Addtoken(str);
    }
    else if(choice=='R')
    {
        int k=-1;
        for(int i=0;i<cnum;i++)
        {
            if(str==CT[i])
                k=i;
        }
        if(k==-1)
        {
            CT[cnum]=str;
            k=cnum;
            cnum++;
            nnum++;
            CTout<<str<<endl;
        }
        //cout<<"<N,"<<cnum<<'>'<<endl;
        output<<"<R,"<<k<<'>'<<endl;
        Addtoken(str);
    }
    else if(choice=='C')
    {
        int k=-1;
        for(int i=0;i<cnum;i++)
        {
            if(str==CT[i])
                k=i;
        }
        if(k==-1)
        {
            CT[cnum]=str;
            k=cnum;
            cnum++;
            nnum++;
            CTout<<str<<endl;
        }
        output<<"<C,"<<k<<'>'<<endl;
        Addtoken(str);
    }
    else if(choice=='S')
    {
        int k=-1;
        for(int i=0;i<cnum;i++)
        {
            if(str==CT[i])
                k=i;
        }
        if(k==-1)
        {
            CT[cnum]=str;
            k=cnum;
            cnum++;
            nnum++;
            CTout<<str<<endl;
        }
        //cout<<"<S,"<<cnum<<'>'<<endl;
        output<<"<S,"<<k<<'>'<<endl;
        Addtoken(str);
    }
    currentnode=0;//回到原点
    str.clear();//清空str
}
void Word::Readstr()
{
    //读取字符串
    str.clear();
    while(1)
    {
        input.get(currentchar);//读取字符串在“后的第一个char
        if(currentchar=='"')//若为”则结束
        {
            wordreturn('S');
            input.get(currentchar);
            return;
        }
        else
        {
            str+=currentchar;
        }
    }
}
void Word::Readchar()//处理字符
{
    str.clear();
    bool flag=1;//用来确保输入为一个字符
    while(1)
    {
        input.get(currentchar);
        if(currentchar==39)//若为‘则退出
        {
            wordreturn('C');
            input.get(currentchar);
            return;
        }
        else if(flag)//否则记录，
        {
            flag=0;
            str+=currentchar;
        }
        else//若’后不止跟一个字符则显示错误
        {
            //cout<<error<<endl;
        }
    }
}
void Word::Readnum()//读取数字，由于只有无符号整数，未对其他进行处理，若需要处理其他数，可在读取到.后跳转到其他函数
{
    str.clear();
    int num=0;
    bool flag=0;
    str+=currentchar;
    while(1)
    {
        input.get(currentchar);
        if(currentchar=='.'&&!flag)
        {
            str+=currentchar;
            flag=1;
        }
        else if(currentchar>'9'||currentchar<'0')
        {
            if(!flag)
                wordreturn('N');
            else
                wordreturn('R');
            return;
        }
        else if(currentchar<='9'&&currentchar>='0')
        {
            str+=currentchar;
        }
        else
        {
            cout<<"error";
            break;
        }
    }
}
void Word::Readki()//读取关键字与标识符
{
    str.clear();
    while(1)
    {
        if(WordNode[WordNode[0].CompareTrans(currentchar)].getname()=='P'||currentchar==' ')//若读取到末尾（读入符号或空格）
        {
            if(!WordNode[currentnode].getable())//若不可返回则为标识符，设置表示符节点返回并，返回
            {
                WordNode[currentnode].setreturn(1,inum,'I');
                inum++;
                wordreturn('I');
                return;
            }
            wordreturn(0);
            return;
        }
        else//若有状态转移则转移，否则建立新节点并转移
        {
            int k=WordNode[currentnode].CompareTrans(currentchar);
            if(k!=0)
            {
                currentnode=k;
            }
            else
            {
                WordNode[currentnode].AddTrans(currentchar,nodesum);
                currentnode=nodesum;
                nodesum++;
            }
            str+=currentchar;
            input.get(currentchar);
        }
    }
}
void Word::Readp()//读取符号，只需要一步查询是否可返回并返回，
{
    str.clear();
    str+=currentchar;
    currentnode=WordNode[currentnode].CompareTrans(currentchar);
    input.get(currentchar);
    int k=WordNode[currentnode].CompareTrans(currentchar);
    while(k!=0)
    {
        currentnode=k;
        str+=currentchar;
        input.get(currentchar);
        k=WordNode[currentnode].CompareTrans(currentchar);
    }
    wordreturn('P');
}
void Word::process()//自动机分支，即根据currentchar判断下个符号属于什么类型并分配任务
{
    input.get(currentchar);
    while(1)
    {
        int i;
        while(currentchar=='\n'||currentchar==' ')//跳过换行
        {
            input.get(currentchar);
            continue;
        }
        if(input.eof())//返回
        {
            return;
        }
        //cin>>i;
        if(currentchar=='"')//为’则读取字符串
            Readstr();
        else if(currentchar==39)//为‘则读取字符
            Readchar();
        else if(currentchar<='9'&&currentchar>='0')//读取数字
            Readnum();
        else if(currentchar=='_'||
                currentchar<='z'&&currentchar>='a'||
                currentchar<='Z'&&currentchar>='A')//读取关键字或标识符
            Readki();
        else if(WordNode[WordNode[0].CompareTrans(currentchar)].getname()=='P')//读取符号
            Readp();
        else
            cout<<"error";
    }
}
void Word::operate()
{
    Initialize();//初始化程序,包括读入关键字表和界符表，打开input文件
    //shownode();//显示状态转移
    process();//处理
    return;
}
void Word::AddString(string str,int num)//读取关键词表或符号表中的字符并构造自动机
{
    char name;
    currentchar=str[0];
    if(currentchar=='_'||
                currentchar<='z'&&currentchar>='a'||
                currentchar<='Z'&&currentchar>='A')//若为这些字符开头则为k
        name='K';
    else
        name='P';//否则为p
    for(int i=0;i<str.size();i++)//以读取完字符为总结
    {
        currentchar=str[i];//读取字符
        AddTrans(currentchar,nodesum);//若是其他字符则查看当前节点是否存在对应字符的转移函数，若无则创建新节点且转移，如有则转移
    }
    WordNode[currentnode].setreturn(1,num,name);//设置返回
    currentnode=0;//返回原点
}
void Word::ReadTable()//读入关键字表和界符表
{
    string word,name;
    ifstream WordInput;
    WordInput.open("KT.txt",ios::binary);
    while(!WordInput.eof())
    {
        WordInput>>word;
        WordInput>>name;
        AddString(word,knum);
        KT[knum]=name;
        knum++;
    }
    WordInput.close();
    WordInput.open("PT.txt",ios::binary);
    while(!WordInput.eof())
    {
        WordInput>>word;
        WordInput>>name;
        AddString(word,pnum);
        PT[pnum]=name;
        pnum++;
    }

}
Word::Word()//构造函数
{
    name[0]="IDENFR";
    name[1]="INTCON";
    name[2]="CHARCON";
    name[3]="STRCON";
    nodesum=1;
    currentchar=0;
    inum=cnum=0;
    for(int i=0;i<1024;i++)
    {
        WordNode[i].setnode(i);//unfinished
    }
    WordNode[0].AddTrans(' ',0);
    currentnode=0;
    output.open("word.txt");//初始化
    snum=nnum=inum=cnum=knum=pnum=0;
}
bool Word::AddStr(char name,int num)//通过字符串建立从原点开始识别该字符串的自动机
{
    for(int i=0;i<1024;i++)//设置极限值以免陷入死循环
    {
        input.get(currentchar);
        if(currentchar=='\n')
            continue;
        str+=currentchar;
        int j;
        if(input.eof())
        {
            return 0;
        }
        else if(currentchar==' ')
        {
            WordNode[currentnode].setreturn(1,num,name);
            currentnode=0;
            return 1;
        }
        else
            AddTrans(currentchar,nodesum);
            //若是其他字符则查看当前节点是否存在对应字符的转移函数，若无则创建新节点且转移，如有则转移
    }
            cout<<"error"<<endl;//若无法正常退出则显示错误
    return 0;
}
void Word::Initialize()//初始化程序块
{
    ReadTable();
    input.open("code.txt");
    ITout.open("IT.txt",ios::binary);
    CTout.open("CT.txt",ios::binary);
    currentnode=0;
}
void Word::AddTrans(char Char,int Num)//创建状态转移函数
{
    int k;
    k=WordNode[currentnode].CompareTrans(Char);
    if(k==0)
    {
        WordNode[currentnode].AddTrans(Char,Num);
        currentnode=nodesum;
        nodesum=nodesum+1;
        return;
    }
    currentnode=k;
    return;
}

#endif // WORDWord_H_INCLUDED
