#ifndef MAINTABLE_H_INCLUDED
#define MAINTABLE_H_INCLUDED
enum Cat{n,f,c,t,d,v,vn,vf};//种类枚举类 分别为 空，函数，常量，类型，域名，变量，形参（）
#include <fstream>
#include "TypeList.h"
#include "PFINFL.h"
using namespace std;


class MainNode
{
public:
    MainNode();
    void setId(string id);//用于导入标识符
    void setType(TypeList *NewType,int NewCat);//声明时设置
    void setVar(void *Addr,int num);//赋值时设置 使用带默认参数值的函数
    void setVar(int var);
    void setVar(float var);
    void setVar(char var);
    void setVar(bool var);//不同类型的重载赋值函数
    int returnI();
    float returnF();
    char returnC();
    bool returnB();
    //void setVar(int var[],int n);//数组
    //void setVar(PFINFL *FucList);
    string getId();
    TypeList* getTypeList();
    Cat getCat();
    void* getAddr();
    void showNode();//获取节点数据 并不影响封装 因为MainTable 并不含相应函数可返回地址
    void output(ofstream MTO);

    char gettype();//奇怪的用不到的函数
    ~MainNode();
private:
    string ID;//标识符名称
    TypeList *Type;//连接类型表 决定万能指针指向378 394 367的类型 （可修改）
    Cat aCat;//枚举类
    void *ADDR;//万能指针 使用时最好转化
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
string MainNode::getId()//返回标识符名
{
    return ID;
}
TypeList* MainNode::getTypeList()//返回类型表 指针
{
    return Type;
}
Cat MainNode::getCat()//返回种类
{
    return aCat;
}
void* MainNode::getAddr()//返回（储存）地址
{
    return ADDR;
}
MainNode::MainNode()//初始化
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
void MainNode::setType(TypeList *NewType,int NewCat)//设置类型，种类并申请空间
{
    Type=NewType;
    aCat=Cat(NewCat);
    if(aCat=='t')//结构体和数组
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
        //遍历所有数组表 累乘 乘基本数据类型大小 申请空间 赋初值
    }
    else if(Type->GetType()=='S')
    {
        //结构体 类似于数组
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
//不同类型的赋值函数 可添加错误检测
//结构体和数组没写
void MainNode::showNode()
{
    cout<<ID<<' '<<Type->getType()<<' '<<aCat<<' '<<*(int*)ADDR<<endl;
}//展示节点
MainNode::~MainNode()//释放申请的空间 （在节点数很大时有必要）
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
class MainTable//符号表总表类
{
public:
    MainTable();//构造函数
    void addIdenfer(string id,TypeList *newType,Cat newCat);//增加标识符（变量）
    void setFuc(int Level,int Off,int Fn);//设置函数那啥
    void setEntry(string a,string b,string c,string d);//需要整合四元式表 输入四元式表 不懂问焯奇（因为我也不懂）
    
    void setEntry(Quaternion q);


    void addPara(string id,TypeList *newType,Cat newCat);//增加参数
    void addPara(int order);//增加参数 用序号 如<I,9>为参数则 addPara(9);
    ParameterTable* retParaList();//返回参数
    //CodeList *retCodeList();
    void showTable();//输出所有已经赋值的表
    void outputMT();
    bool getIsused();
    string getFucName();
    ~MainTable();

    //前期测试函数
    void setId(string id);
    void setType(TypeList *newType,Cat newCat,int order);//设置类型 order是数组序号
    char gettype(int order);//返回对应序号的类型
    //sb导致的无效函数 可以在整合后删除
    void setVar(int var,int order);
    void setVar(float var,int order);
    void setVar(char var,int order);
    void setVar(bool var,int order);//赋值重载函数
    int returnI(int order);
    float returnR(int order);
    char returnC(int order);
    bool returnB(int order);//返回值函数 对应不同类型调用不同函数 输入序号

private:
    int Inum;
    bool usable[200];//记录是否已赋值 （不知道是否真的需要）
    PFINFL FucList;//符号表总表对应的函数 的函数表
    MainNode MainT[200];//变量表 初始化时输入所有标识符名
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
ParameterTable* MainTable::retParaList() //返回参数表地址 使用参数表 构建活动记录
{
    return FucList.getParam();
}
void MainTable::addPara(string id,TypeList *newType,Cat newCat)//不推荐使用介个
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
}//添加符号表总表内部的变量作为参数
void MainTable::setFuc(int Level=0,int Off=0,int Fn=0)
{
    FucList.setLevel(Level);
    FucList.setOff(Off);
    FucList.setFn(Fn);
}//设置函数值
char MainTable::gettype(int order)//获取类型
{
    return MainT[order].gettype();
}
MainTable::MainTable()//构造函数
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
    ITin.close();//读取所有IT*/ //有    void setFuc(int Level,int Off,int Fn);//设置函数那啥待商榷
}
MainTable::~MainTable()
{
    for(int i=0;i<200;i++)
        delete &MainT[i];
}//析构函数 解除对申请空间的占用
void MainTable::setType(TypeList *newType,Cat newCat,int order)
{
    MainT[order].setType(newType,newCat);
    usable[order]=1;
}//设置种类，类型 对应函数的声明
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
}//赋值
void MainTable::showTable()
{
    for(int i=0;i<200;i++)
    {
        if(usable[i])
            MainT[i].showNode();
    }
}//展示所有已声明的变量
#endif // MAINTABLE_H_INCLUDED
