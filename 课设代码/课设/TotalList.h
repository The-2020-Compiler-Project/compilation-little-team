#ifndef TOTALLIST_H_INCLUDED
#define TOTALLIST_H_INCLUDED

class Totallist
{
private:
    MainTable Var;
    MainTable Fuc[100];
public:
    Totallist();
    void addGlobalVar(string id,TypeList *newType,Cat newCat);//���ӱ���
    void addIdenfer(string id,TypeList *newType,Cat newCat,int order);//���ӱ�ʶ����������
    void setFuc(int Level,int Off,int Fn,int order);//���ú�����ɶ
    void setEntry(string a,string b,string c,string d,int order);//��Ҫ������Ԫʽ�� ������Ԫʽ�� ���������棨��Ϊ��Ҳ������
    void addPara(string id,TypeList *newType,Cat newCat,int order);//���Ӳ���
    void addPara(int orderM,int orderT);//���Ӳ��� ����� ��<I,9>Ϊ������ addPara(9);
    ParameterTable* retParaList(int order);//���ز���
    //CodeList *retCodeList();//���ش���
    void showTable(int order);//��������Ѿ���ֵ�ı�
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
