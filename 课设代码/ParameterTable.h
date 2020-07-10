#ifndef PARAMETERTABLE_H_INCLUDED
#define PARAMETERTABLE_H_INCLUDED

using namespace std;

class ParameterNode//��MainNode������� �ʶ�ֱ�Ӹ����˴󲿷ִ����ȫ�����ݽṹ
{
public:
    ParameterNode();
    char gettype();
    void setId(string id);
    void setType(TypeList *NewType,Cat NewCat);
    void setVar(void *Addr);//��ͨ��set����
    //void setVar(int var[],int n);//����
    void showNode();//���
    void dele();//��ֵĶ���
    ~ParameterNode();
private:
    string ID;//������
    TypeList *Type;//�������ͱ� ��������ָ��ָ������� �����޸ģ�
    Cat aCat;//ö����
    void *ADDR;//ע���ڲ������е�Addr���ű��ܱ��е�ַ������ ������ǰɾ��
};

ParameterNode::ParameterNode()//���캯��
{
    ID="NULL";
    Type=0;
    aCat=n;
    ADDR=0;
}
void ParameterNode::setVar(void *Addr)
{
    ADDR=Addr;
    return;
}
char ParameterNode::gettype()
{
    return Type->getType();
}
void ParameterNode::setId(string id)
{
    ID=id;
}
void ParameterNode::setType(TypeList *NewType,Cat NewCat)
{
    Type=NewType;
    aCat=Cat(NewCat);
    return;
}
void ParameterNode::showNode()
{
    if(ID!="NULL")
    cout<<ID<<' '<<Type->getType()<<' '<<aCat<<' '<<*(int*)ADDR<<endl;
}
ParameterNode::~ParameterNode()
{
    delete Type;
}

class ParameterTable
{
public:
    ParameterTable();
    void setId(string id,int order);
    void setType(TypeList *newType,Cat newCat,int order);
    void addPara(string id,TypeList *newType,Cat newCat);//���Ƽ�ʹ��
    void addPara(string id,TypeList *newType,Cat newCat,void *Addr);//���Ӳ��� ����ֱ����ӵ��˺����������� �����Ϊ����Ҫ�������õĹ��ߺ���
    char gettype(int order);
    void showTable();
    ~ParameterTable();
private:
    int ParaNum;
    ParameterNode ParameterT[20];
};
void ParameterTable::addPara(string id,TypeList *newType,Cat newCat)
{
    ParameterT[ParaNum].setId(id);
    ParameterT[ParaNum].setType(newType,newCat);
    ParaNum=ParaNum+1;
}
void ParameterTable::addPara(string id,TypeList *newType,Cat newCat,void *Addr)
{
    ParameterT[ParaNum].setId(id);
    ParameterT[ParaNum].setType(newType,newCat);
    ParameterT[ParaNum].setVar(Addr);
    ParaNum=ParaNum+1;
}
void ParameterTable::setId(string id,int order)
{
    ParameterT[order].setId(id);
}
char ParameterTable::gettype(int order)
{
    return ParameterT[order].gettype();
}
ParameterTable::ParameterTable()
{
    ParaNum=0;
}
ParameterTable::~ParameterTable()
{
    for(int i=0;i<20;i++)
        delete &ParameterT[i];
}
void ParameterTable::setType(TypeList *newType,Cat newCat,int order)
{
    ParameterT[order].setType(newType,newCat);
}
void ParameterTable::showTable()
{
    for(int i=0;i<ParaNum;i++)
    {
        ParameterT[i].showNode();
    }
}
#endif // PARAMETERTABLE_H_INCLUDED
