#ifndef WORDWord_H_INCLUDED
#define WORDWord_H_INCLUDED
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
//����WordMachine�࣬���Զ�ȡKT��PT����Դ��ת��ΪWord���У������IT��CT����ʶ����ͳ�����
using namespace std;

int num=0;  //�������Token�����е�˳��
string sequence[500]={""};  //Token����
void Addtoken(string s)//���Token������
{
    sequence[num++]=s;
}

class wordnode
{
public:
    wordnode();
    void setnode(int Num);//���ýڵ����
    int CompareTrans(char Char);//�����Ƿ����״̬ת��
    void AddTrans(char Char,int Num);//����״̬ת��
    void shownode();//չʾ״̬ת��
    void setreturn(bool a,int n,char na);//���÷������������
    bool getable();
    int getnum();
    char getname();//��ȡ�Ƿ�ɷ��ء����͡����
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
int wordnode::CompareTrans(char Char)//����״̬ת�������Ѵ���Ŀ��ڵ��򷵻ؽڵ���ţ���֮�򷵻�0
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
void wordnode::AddTrans(char Char,int Num)//���ڴ����µĽڵ㲢����ǰ�ڵ���½ڵ��Ե�ǰ�ַ����ӣ�����ת�Ʊ�����
{
    CharTable[TransSum]=Char;
    TransformTable[TransSum]=Num;
    TransSum=TransSum+1;
    return;
}
void wordnode::shownode()//չʾ�ڵ����ź�״̬ת�Ʊ�
{
    cout<<NodeNum<<" "<<TransSum<<endl;
    for(int i=0;i<TransSum;i++)
    {
        cout<<CharTable[i]<<"->"<<TransformTable[i]<<endl;
    }
    cout<<returnable<<" "<<returnname<<" "<<returnnum<<endl;
}
void wordnode::setnode(int Num)//���ýڵ����ֵ
{
    NodeNum=Num;
}
wordnode::wordnode()//���캯��
{
    NodeNum=0;
    TransSum=0;
    for(int i;i<100;i++)
    {
        CharTable[i]='/0';
        TransformTable[i]=2000;
    }//��ʼ���ڵ�
    returnable=0;
    returnname='-1';
    returnnum=-1;
}
class Word{
public:
    Word();//���캯��
    void AddString(string str,int num);//��ȡ�ַ�����ת��Ϊ�Զ�����ԭ���ڶ�ȡ�ļ��еĹؼ�������Ų�ת��Ϊ�Զ���
    void Initialize();//��ʼ���������ɹؼ������ַ���ɵ��Զ������򿪴����룩
    void operate();//�����Զ���
    void AddTrans(char Char,int Num);//���ڹ����Զ����ĸ�������������ת��������ת�ƣ����򴴽��½ڵ㣬������״̬ת�Ʋ�ת�Ƶ��ýڵ�
    bool AddStr(char name,int num);//����һ��һ����ȡ�ַ��������Զ���
    void ReadTable();//��ȡ�ؼ������ַ���
    void shownode();//չʾ���нڵ��״̬ת��
    void process();//�Ӵ������ļ��ж�ȡchar��ת��
    void wordreturn(char choice);//��Լ
    void Readstr();//�ַ���������
    void Readchar();//�ַ�������
    void Readnum();//���ִ�����
    void Readki();//�����޷��ֱ�ؼ������ʶ������ͬһ���������д���
    void Readp();//���Ŵ�����

private:
    ifstream input;//�����ļ���
    ofstream ITout;
    ofstream CTout;
    ofstream output;//����ļ���
    char currentchar;//��ǰ�ַ�w
    wordnode WordNode[1024];//�Զ���
    int currentnode;//��ǰ�ڵ�
    int nodesum;//�ڵ�����
    int snum;
    int cnum;
    int inum;
    int nnum;
    int knum;
    int pnum;//���ɹ�Լ������
    string str;//��¼input��д����ַ������������뵽�������ʶ����
    string KT[100];
    string PT[100];//�ؼ������������ַ�����
    string IT[100];
    string CT[100];
    string name[4];//��������ַ�����
};
void Word::shownode()//�����нڵ����״̬ת��չʾ
{
    for(int i=0;i<nodesum;i++)
       WordNode[i].shownode();
}
void Word::wordreturn(char choice)//��Լ����
{
    if(choice==0)
    {
        choice=WordNode[currentnode].getname();
    }
    if(choice=='K')//���
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
    else if(choice=='I')//�����������ַ���str��¼��ֵ
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
    currentnode=0;//�ص�ԭ��
    str.clear();//���str
}
void Word::Readstr()
{
    //��ȡ�ַ���
    str.clear();
    while(1)
    {
        input.get(currentchar);//��ȡ�ַ����ڡ���ĵ�һ��char
        if(currentchar=='"')//��Ϊ�������
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
void Word::Readchar()//�����ַ�
{
    str.clear();
    bool flag=1;//����ȷ������Ϊһ���ַ�
    while(1)
    {
        input.get(currentchar);
        if(currentchar==39)//��Ϊ�����˳�
        {
            wordreturn('C');
            input.get(currentchar);
            return;
        }
        else if(flag)//�����¼��
        {
            flag=0;
            str+=currentchar;
        }
        else//������ֹ��һ���ַ�����ʾ����
        {
            //cout<<error<<endl;
        }
    }
}
void Word::Readnum()//��ȡ���֣�����ֻ���޷���������δ���������д�������Ҫ���������������ڶ�ȡ��.����ת����������
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
void Word::Readki()//��ȡ�ؼ������ʶ��
{
    str.clear();
    while(1)
    {
        if(WordNode[WordNode[0].CompareTrans(currentchar)].getname()=='P'||currentchar==' ')//����ȡ��ĩβ��������Ż�ո�
        {
            if(!WordNode[currentnode].getable())//�����ɷ�����Ϊ��ʶ�������ñ�ʾ���ڵ㷵�ز�������
            {
                WordNode[currentnode].setreturn(1,inum,'I');
                inum++;
                wordreturn('I');
                return;
            }
            wordreturn(0);
            return;
        }
        else//����״̬ת����ת�ƣ��������½ڵ㲢ת��
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
void Word::Readp()//��ȡ���ţ�ֻ��Ҫһ����ѯ�Ƿ�ɷ��ز����أ�
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
void Word::process()//�Զ�����֧��������currentchar�ж��¸���������ʲô���Ͳ���������
{
    input.get(currentchar);
    while(1)
    {
        int i;
        while(currentchar=='\n'||currentchar==' ')//��������
        {
            input.get(currentchar);
            continue;
        }
        if(input.eof())//����
        {
            return;
        }
        //cin>>i;
        if(currentchar=='"')//Ϊ�����ȡ�ַ���
            Readstr();
        else if(currentchar==39)//Ϊ�����ȡ�ַ�
            Readchar();
        else if(currentchar<='9'&&currentchar>='0')//��ȡ����
            Readnum();
        else if(currentchar=='_'||
                currentchar<='z'&&currentchar>='a'||
                currentchar<='Z'&&currentchar>='A')//��ȡ�ؼ��ֻ��ʶ��
            Readki();
        else if(WordNode[WordNode[0].CompareTrans(currentchar)].getname()=='P')//��ȡ����
            Readp();
        else
            cout<<"error";
    }
}
void Word::operate()
{
    Initialize();//��ʼ������,��������ؼ��ֱ�ͽ������input�ļ�
    //shownode();//��ʾ״̬ת��
    process();//����
    return;
}
void Word::AddString(string str,int num)//��ȡ�ؼ��ʱ����ű��е��ַ��������Զ���
{
    char name;
    currentchar=str[0];
    if(currentchar=='_'||
                currentchar<='z'&&currentchar>='a'||
                currentchar<='Z'&&currentchar>='A')//��Ϊ��Щ�ַ���ͷ��Ϊk
        name='K';
    else
        name='P';//����Ϊp
    for(int i=0;i<str.size();i++)//�Զ�ȡ���ַ�Ϊ�ܽ�
    {
        currentchar=str[i];//��ȡ�ַ�
        AddTrans(currentchar,nodesum);//���������ַ���鿴��ǰ�ڵ��Ƿ���ڶ�Ӧ�ַ���ת�ƺ����������򴴽��½ڵ���ת�ƣ�������ת��
    }
    WordNode[currentnode].setreturn(1,num,name);//���÷���
    currentnode=0;//����ԭ��
}
void Word::ReadTable()//����ؼ��ֱ�ͽ����
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
Word::Word()//���캯��
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
    output.open("word.txt");//��ʼ��
    snum=nnum=inum=cnum=knum=pnum=0;
}
bool Word::AddStr(char name,int num)//ͨ���ַ���������ԭ�㿪ʼʶ����ַ������Զ���
{
    for(int i=0;i<1024;i++)//���ü���ֵ����������ѭ��
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
            //���������ַ���鿴��ǰ�ڵ��Ƿ���ڶ�Ӧ�ַ���ת�ƺ����������򴴽��½ڵ���ת�ƣ�������ת��
    }
            cout<<"error"<<endl;//���޷������˳�����ʾ����
    return 0;
}
void Word::Initialize()//��ʼ�������
{
    ReadTable();
    input.open("code.txt");
    ITout.open("IT.txt",ios::binary);
    CTout.open("CT.txt",ios::binary);
    currentnode=0;
}
void Word::AddTrans(char Char,int Num)//����״̬ת�ƺ���
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
