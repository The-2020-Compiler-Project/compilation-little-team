#ifndef TOTALLIST_H_INCLUDED
#define TOTALLIST_H_INCLUDED

class Totallist
{
private:
    MainTable Var;
    MainTable Fuc[100];
public:
    Totallist();
    void addGlobalVar(string id,TypeList *newType,Cat newCat);//增加变量
    void addIdenfer(string id,TypeList *newType,Cat newCat,int order);//增加标识符（变量）
    void setFuc(int Level,int Off,int Fn,int order);//设置函数那啥
    void setEntry(string a,string b,string c,string d,int order);//需要整合四元式表 输入四元式表 不懂问焯奇（因为我也不懂）
    void addPara(string id,TypeList *newType,Cat newCat,int order);//增加参数
    void addPara(int orderM,int orderT);//增加参数 用序号 如<I,9>为参数则 addPara(9);
    ParameterTable* retParaList(int order);//返回参数
    //CodeList *retCodeList();//返回代码
    void showTable(int order);//输出所有已经赋值的表
    void outputMT();
};
Totallist::Totallist()
{
    ofstream k;
    k.open("MTO.txt",ios::binary);
    k.close();
}
void Totallist::addGlobalVar(string id,TypeList* newType,Cat newCat)
{
    Var.addIdenfer(id,newType,newCat);
}
void Totallist::addIdenfer(string id,TypeList *newType,Cat newCat,int order)
{
    Fuc[order].addIdenfer(id,newType,newCat);
}
void Totallist::setFuc(int Level,int Off,int Fn,int order)
{
    Fuc[order].setFuc(Level,Off,Fn);
}
void Totallist::setEntry(string a,string b,string c,string d,int order)
{
    Fuc[order].setEntry(a,b,c,d);
}
void Totallist::addPara(int orderM,int orderT)
{
    Fuc[orderT].addPara(orderM);
}
void Totallist::addPara(string id,TypeList* newType,Cat newCat,int order)
{
    Fuc[order].addPara(id,newType,newCat);
}
ParameterTable* Totallist::retParaList(int order)
{
    Fuc[order].retParaList();
}
void Totallist::showTable(int order)
{
    Fuc[order].showTable();
}
void Totallist::outputMT()
{
    ofstream k;
    k.open("MTO.txt",ios::app);
    k<<"Global Var:"<<endl;
    k.close();
    Var.outputMT();
    for(int i=0;Fuc[i].getIsused();i++)
    {
        k.open("MTO.txt",ios::app);
        k<<"Fuc:"<<endl;
        k.close();
        Fuc[i].outputMT();
    }
}
#endif // TOTALLIST_H_INCLUDED
