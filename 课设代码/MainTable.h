#ifndef MAINTABLE_H_INCLUDED
#define MAINTABLE_H_INCLUDED
enum Cat{n,f,c,t,d,v,vn,vf};//����ö���� �ֱ�Ϊ �գ����������������ͣ��������������βΣ���
#include <fstream>
#include "TypeList.h"
#include "PFINFL.h"
using namespace std;


class MainNode
{
public:
    MainNode();
    void setId(string id);//���ڵ����ʶ��
    void setType(TypeList *NewType,int NewCat);//����ʱ����
    void setVar(void *Addr,int num);//��ֵʱ���� ʹ�ô�Ĭ�ϲ���ֵ�ĺ���
    void setVar(int var);
    void setVar(float var);
    void setVar(char var);
    void setVar(bool var);//��ͬ���͵����ظ�ֵ����
    int returnI();
    float returnF();
    char returnC();
    bool returnB();
    //void setVar(int var[],int n);//����
    //void setVar(PFINFL *FucList);
    string getId();
    TypeList* getTypeList();
    Cat getCat();
    void* getAddr();
    void showNode();//��ȡ�ڵ����� ����Ӱ���װ ��ΪMainTable ��������Ӧ�����ɷ��ص�ַ
    void output(ofstream MTO);

    char gettype();//��ֵ��ò����ĺ���
    ~MainNode();
private:
    string ID;//��ʶ������
    TypeList *Type;//�������ͱ� ��������ָ��ָ��378 394 367������ �����޸ģ�
    Cat aCat;//ö����
    void *ADDR;//����ָ�� ʹ��ʱ���ת��
};
void MainNode::output(ofstream MTO)
{
    if(aCat!=n)
        MTO<<ID<<' '<<Type->getType()<<' '<<aCat<<endl;
}
int MainNode::returnI()
{
    int temp;
    temp=*(int*)ADDR;
    return temp;
}
float MainNode::returnF()
{
    float temp;
    temp=*(float*)ADDR;
    return temp;
}
char MainNode::returnC()
{
    char temp;
    temp=*(char*)ADDR;
    return temp;
}
bool MainNode::returnB()
{
    bool temp;
    temp=*(bool*)ADDR;
    return temp;
}
string MainNode::getId()//���ر�ʶ����
{
    return ID;
}
TypeList* MainNode::getTypeList()//�������ͱ� ָ��
{
    return Type;
}
Cat MainNode::getCat()//��������
{
    return aCat;
}
void* MainNode::getAddr()//���أ����棩��ַ
{
    return ADDR;
}
MainNode::MainNode()//��ʼ��
{
    ID="NULL";
    Type=0;
    aCat=n;
    ADDR=0;
}
char MainNode::gettype()
{
    return Type->getType();
}
void MainNode::setId(string id)
{
    ID=id;
}
void MainNode::setType(TypeList *NewType,int NewCat)//�������ͣ����ಢ����ռ�
{
    Type=NewType;
    aCat=Cat(NewCat);
    if(aCat=='t')//�ṹ�������
    {
        ;
    }
    else if(Type->getType()=='I')
    {
        ADDR=new int(0);
    }
    else if(Type->getType()=='R')
    {
        ADDR=new float(0);
    }
    else if(Type->getType()=='C')
    {
        ADDR=new char(0);
    }
    else if(Type->getType()=='B')
    {
        ADDR=new bool(0);
    }
    /*else if(Type->GetType()=='A')
    {
        int ArraySize=1;;
        //������������� �۳� �˻����������ʹ�С ����ռ� ����ֵ
    }
    else if(Type->GetType()=='S')
    {
        //�ṹ�� ����������
    }*/
    return;
}
void MainNode::setVar(int var)
{
    *(int*)ADDR=var;
}
void MainNode::setVar(float var)
{
    *(float*)ADDR=var;
}
void MainNode::setVar(char var)
{
    *(char*)ADDR=var;
}
void MainNode::setVar(bool var)
{
    *(bool*)ADDR=var;
}
//��ͬ���͵ĸ�ֵ���� ����Ӵ�����
//�ṹ�������ûд
void MainNode::showNode()
{
    cout<<ID<<' '<<Type->getType()<<' '<<aCat<<' '<<*(int*)ADDR<<endl;
}//չʾ�ڵ�
MainNode::~MainNode()//�ͷ�����Ŀռ� ���ڽڵ����ܴ�ʱ�б�Ҫ��
{
    if(Type==0)
    {
        return;
    }
    else if(Type->getType()=='I')
    {
        delete (int*)ADDR;
    }
    else if(Type->getType()=='R')
    {
        delete (float*)ADDR;
    }
    else if(Type->getType()=='C')
    {
        delete (char*)ADDR;
    }
    else if(Type->getType()=='B')
    {
        delete (bool*)ADDR;
    }
    else if(Type->getType()=='A')
    {
        ;
    }
    else if(Type->getType()=='S')
    {
        ;
    }

    return;
}
class MainTable//���ű��ܱ���
{
public:
    MainTable();//���캯��
    void addIdenfer(string id,TypeList *newType,Cat newCat);//���ӱ�ʶ����������
    void setFuc(int Level,int Off,int Fn);//���ú�����ɶ
    void setEntry(string a,string b,string c,string d);//��Ҫ������Ԫʽ�� ������Ԫʽ�� ���������棨��Ϊ��Ҳ������
    
    void setEntry(Quaternion q);


    void addPara(string id,TypeList *newType,Cat newCat);//���Ӳ���
    void addPara(int order);//���Ӳ��� ����� ��<I,9>Ϊ������ addPara(9);
    ParameterTable* retParaList();//���ز���
    //CodeList *retCodeList();
    void showTable();//��������Ѿ���ֵ�ı�
    void outputMT();
    bool getIsused();
    string getFucName();
    ~MainTable();

    //ǰ�ڲ��Ժ���
    void setId(string id);
    void setType(TypeList *newType,Cat newCat,int order);//�������� order���������
    char gettype(int order);//���ض�Ӧ��ŵ�����
    //sb���µ���Ч���� ���������Ϻ�ɾ��
    void setVar(int var,int order);
    void setVar(float var,int order);
    void setVar(char var,int order);
    void setVar(bool var,int order);//��ֵ���غ���
    int returnI(int order);
    float returnR(int order);
    char returnC(int order);
    bool returnB(int order);//����ֵ���� ��Ӧ��ͬ���͵��ò�ͬ���� �������

private:
    int Inum;
    bool usable[200];//��¼�Ƿ��Ѹ�ֵ ����֪���Ƿ������Ҫ��
    PFINFL FucList;//���ű��ܱ��Ӧ�ĺ��� �ĺ�����
    MainNode MainT[200];//������ ��ʼ��ʱ�������б�ʶ����
};
string MainTable::getFucName()
{
    return MainT[0].getId();
}
bool MainTable::getIsused()
{
    bool k=(MainT[0].getCat()!=n);
    return k;
}
void MainTable::outputMT()
{
    ofstream MTO;
    MTO.open("MTO.txt", ios::app);
    for (int i = 0; i < 200; i++)
    {
        if (usable[i])
            MTO << MainT[i].getId() << ' ' << MainT[i].gettype() << ' ' << MainT[i].getCat() << endl;
    }
    MTO << "code" << endl;
    for (int i = 0; i < FucList.Entry.size(); i++) {

        MTO << FucList.Entry[i].showQuaternion() << endl;
    }
}
void MainTable::addIdenfer(string id,TypeList* newType,Cat aCat)
{
    MainT[Inum].setId(id);
    MainT[Inum].setType(newType,aCat);
    usable[Inum]=1;
    Inum++;
}
void MainTable::setEntry(string a,string b,string c,string d)
{
    FucList.setEntry(a,b,c,d);
}

void MainTable::setEntry(Quaternion q) {
    FucList.setEntry(q);
}

int MainTable::returnI(int order)
{
    return MainT[order].returnI();
}
float MainTable::returnR(int order)
{
    return MainT[order].returnF();
}
char MainTable::returnC(int order)
{
    return MainT[order].returnC();
}
bool MainTable::returnB(int order)
{
    return MainT[order].returnB();
}
ParameterTable* MainTable::retParaList() //���ز������ַ ʹ�ò����� �������¼
{
    return FucList.getParam();
}
void MainTable::addPara(string id,TypeList *newType,Cat newCat)//���Ƽ�ʹ�ý��
{
    FucList.addParam(id,newType,newCat);
}
void MainTable::addPara(int order)
{
    string id=MainT[order].getId();
    TypeList *Type=MainT[order].getTypeList();
    Cat newCat=MainT[order].getCat();
    void *Addr=MainT[order].getAddr();
    FucList.addParam(id,Type,newCat,Addr);
}//��ӷ��ű��ܱ��ڲ��ı�����Ϊ����
void MainTable::setFuc(int Level=0,int Off=0,int Fn=0)
{
    FucList.setLevel(Level);
    FucList.setOff(Off);
    FucList.setFn(Fn);
}//���ú���ֵ
char MainTable::gettype(int order)//��ȡ����
{
    return MainT[order].gettype();
}
MainTable::MainTable()//���캯��
{
    Inum=0;
    /*ifstream ITin;
    string Instring;
    int TableNum=0;
    ITin.open("IT.txt",ios::binary);
    while(!ITin.eof())
    {
        getline(ITin,Instring);
        MainT[TableNum].setId(Instring);
        TableNum++;
    }
    ITin.close();//��ȡ����IT*/ //��    void setFuc(int Level,int Off,int Fn);//���ú�����ɶ����ȶ
}
MainTable::~MainTable()
{
    for(int i=0;i<200;i++)
        delete &MainT[i];
}//�������� ���������ռ��ռ��
void MainTable::setType(TypeList *newType,Cat newCat,int order)
{
    MainT[order].setType(newType,newCat);
    usable[order]=1;
}//�������࣬���� ��Ӧ����������
void MainTable::setVar(int var,int order)
{
    MainT[order].setVar(var);
}
void MainTable::setVar(float var,int order)
{
    MainT[order].setVar(var);
}
void MainTable::setVar(char var,int order)
{
    MainT[order].setVar(var);
}
void MainTable::setVar(bool var,int order)
{
    MainT[order].setVar(var);
}//��ֵ
void MainTable::showTable()
{
    for(int i=0;i<200;i++)
    {
        if(usable[i])
            MainT[i].showNode();
    }
}//չʾ�����������ı���
#endif // MAINTABLE_H_INCLUDED
