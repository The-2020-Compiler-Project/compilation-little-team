//函数表
#ifndef PFINFL_H_INCLUDED
#define PFINFL_H_INCLUDED
#include "ParameterTable.h"
#include"Quaternion.h"
#include<vector>

using namespace std;

class PFINFL{
public:
    PFINFL();
    void setLevel(int level);
    void setOff(int off);
    void setFn(int fn);//普通的set函数
    void setParam(ParameterTable pram);//不推荐使用 需要将所有那啥那啥 且有被提前删除风险
    void addParam(string id,TypeList *newType,Cat newCat);//不带地址 是前期的测试用函数
    void addParam(string id,TypeList *newType,Cat newCat,void *Addr);//带地址 将参数表和符号表总表内的内容联系起来


    void setEntry(string a,string b,string c,string d);//需要整合四元式表
    void setEntry(Quaternion q);

    int getSize();//返回函数四元式的长度

    void showEntry();//打印函数的四元式

    int getLevel();
    int getOff();
    int getFn();
    ParameterTable* getParam();//普普通通的get函数

    vector<Quaternion> Entry;//入口地址,是一组四元式
    ~PFINFL();
 private:
    int Level;//层次号
    int Off;//区距
    int Fn;//参数个数
    ParameterTable *Param ;//指向参数表
   

};
void PFINFL::addParam(string id,TypeList *newType,Cat newCat)
{
    Param->addPara(id,newType,newCat);
}
void PFINFL::addParam(string id,TypeList *newType,Cat newCat,void *Addr)
{
    Param->addPara(id,newType,newCat,Addr);
}
PFINFL::PFINFL(){
    Level=0;
    Off=0;
    int fn=0;
    Param=new ParameterTable;
    Entry.clear();
}

void PFINFL::setLevel(int level){
    Level=level;
}

void PFINFL::setOff(int off){
    Off=off;
}

void PFINFL::setFn(int fn){
    Fn=fn;
}

/*void PFINFL::setParam(ParameterTable* param){
    Param=param;
}*/

void PFINFL::setEntry(string a,string b,string c,string d){
    Quaternion q(a, b, c, d);
    Entry.push_back(q);
}

void PFINFL::setEntry(Quaternion q) {
    Entry.push_back(q);
}


int PFINFL::getLevel(){
    return Level;
}

int PFINFL::getOff(){
    return Off;
}

int PFINFL::getFn(){
    return Fn;
}

ParameterTable* PFINFL::getParam(){
    return Param;
}

int PFINFL::getSize() {
    return Entry.size();
}

void PFINFL::showEntry() {
    for (int i = 0; i < Entry.size(); i++) {
        Entry[i].showQuaternion();
    }
}

PFINFL::~PFINFL()
{
    delete Param;
}

#endif //PFINFL_H_INCLUDED
