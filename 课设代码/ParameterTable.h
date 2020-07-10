#ifndef PARAMETERTABLE_H_INCLUDED
#define PARAMETERTABLE_H_INCLUDED

using namespace std;

class ParameterNode//由MainNode引申而来 故而直接复制了大部分代码和全部数据结构
{
public:
    ParameterNode();
    char gettype();
    void setId(string id);
    void setType(TypeList *NewType,Cat NewCat);
    void setVar(void *Addr);//普通的set函数
    //void setVar(int var[],int n);//数组
    void showNode();//输出
    void dele();//奇怪的东西
    ~ParameterNode();
private:
    string ID;//参数名
    TypeList *Type;//连接类型表 决定万能指针指向的类型 （可修改）
    Cat aCat;//枚举类
    void *ADDR;//注意在参数表中的Addr符号表总表中地址的引用 不能提前删除
};

ParameterNode::ParameterNode()//构造函数
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
    void addPara(string id,TypeList *newType,Cat newCat);//不推荐使用
    void addPara(string id,TypeList *newType,Cat newCat,void *Addr);//增加参数 由于直接添加到了函数表主表内 可理解为不需要单独调用的工具函数
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
