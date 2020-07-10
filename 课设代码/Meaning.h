#ifndef MEANING_H_INCLUDED
#define MEANING_H_INCLUDED
#include <string>
#include<stack>
#include<vector>
#include <iostream>
#include "ConstTable.h"//常量表 使用方式 按token调用即可 如<N,4>即调用 ConstTable.getFloat(i)|getInt(i)
#include "MainTable.h"//符号表总表
#include "TypeList.h"
#include "PFINFL.h"
#include "ParameterTable.h"
#include "Word.h"

#include"TotalList.h"
/*  使用方式：
    在创建时自动读取所有标识符，在后续过程中 遇到声明填写类型和种类并申请地址，遇到赋值则对申请的地址进行赋值
    若赋值与声明同时进行，则一步填写
    若需要进行初始化 则直接使用
    地址问题未完成：需要使用 new指令申请空间，然后赋值给void指针
    数组表和结构体表还未完成（在写了在写了）*/

using namespace std;


Totallist List;//符号表


//函数表的计数器


stack<string> SEM;//语义栈
vector<Quaternion> QT;//存放所有四元式

//语义分析类
class Meaning
{
private:
    string str;  //当前识别token串
    int n = 0;  //token串在数组中的编号
    int err[30] = { 0 };  //标记错误
    int numF;
    int numt = 1; //记录临时变量t的名字

public:
    Meaning() {n=-1;numF=0;};  //构造函数
    void parse();  //语法分析函数
    void main_func();  //主函数
    int _func(); //函数
    void type_dec();  //类型说明
    void func_sta();  //函数语句
    void para_list();  //参数表
    void _sta();  //语句
    void comp_sta();  //复合语句

    void ass_sta();  //赋值语句
    void if_exp();  //if语句
    void while_exp();  //while语句

    void declare();//声明语句

    void iden_list();//标识符表

    void func_call();  //函数调用

    void rela_exp();  //关系表达式
    void logic_exp();  //逻辑表达式
    void logic_e();  //逻辑项
    void _opd();  //操作对象
    void logic_v();  //逻辑量
    void arti_exp();  //算数表达式
    void item();  //项
    void factor();  //因子
    void arti_v();  //算数量

    void head_file();//头文件语句
    void return_sta();//return语句

    void print_err();  //语法分析错误提示语句
    void get_back();  //回溯一个token串
    void get_next();  //取下一个token串

    bool judge_KT();
    bool judge_IT();  //判断token串是否为标识符
    bool judge_CT(); //判断token串是否为常数

    //if语句的语义动作
    void IF();
    void EL();
    void IE();

    //while语句的语义动作
    void WH();
    void DO();
    void WE();

    //逻辑表达式的语义动作
    string NEWT();
    void RLT(string w);
    void OR();
    void AND();
    void NOT();
    void PUSH(string i);

    //赋值表达式的语义动作
    void ASSI();

    //算术表达式的语义动作
    void ADD();
    void SUB();
    void MUL();
    void DIV();

    //函数调用语义动作
    void CALL(string fucname);
    void RETURN(string res);

};


//语义分析类成员定义


    //语义动作函数


void Meaning::RETURN(string res) {
    List.setEntry("return", "_", "_",res,numF);
}

void Meaning::IF() {
    List.setEntry("if", SEM.top(), "_", "_",numF);
    SEM.pop();
}

void Meaning::EL() {
     List.setEntry("el", "_", "_", "_",numF);
}

void Meaning::IE() {
    List.setEntry("ie", "_", "_", "_",numF);
}

void Meaning::WH() {
    List.setEntry("wh", "_", "_", "_",numF);
}

void Meaning::DO() {
    List.setEntry("do", SEM.top(), "_", "_",numF);
    SEM.pop();
}

void Meaning::WE() {
    List.setEntry("we", "_", "_", "_",numF);
}


string Meaning::NEWT() {
    string t = "t" + to_string(numt);
    numt++;
    return t;
}


void Meaning::RLT(string w) {
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    List.setEntry(w, ob1, ob2, t,numF);
    SEM.push(t);
}

void Meaning::OR() {
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    List.setEntry("||", ob1, ob2, t,numF);
    SEM.push(t);
}

void Meaning::AND() {
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    List.setEntry("&&", ob1, ob2, t,numF);
    SEM.push(t);
}

void Meaning::NOT() {
    string t = NEWT();
    string ob1 = SEM.top();
    SEM.pop();
    List.setEntry("!", ob1, "_", t,numF);
    SEM.push(t);
}

void Meaning::PUSH(string i) {
    SEM.push(i);
}

void Meaning::ASSI()
{
    string ob1 = SEM.top();
    SEM.pop();
    List.setEntry("=", ob1, "_", SEM.top(),numF);
    SEM.pop();
}

void Meaning::ADD()
{
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    List.setEntry("+", ob1, ob2, t,numF);
    SEM.push(t);
}

void Meaning::SUB()
{
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    List.setEntry("-", ob1, ob2, t,numF);
    SEM.push(t);
}

void Meaning::MUL()
{
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    List.setEntry("*", ob1, ob2, t,numF);
    SEM.push(t);
}

void Meaning::DIV()
{
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    List.setEntry("/", ob1, ob2, t,numF);
    SEM.push(t);
}

void Meaning::parse()  //语义分析函数
{
    int flag = 0;
    get_next();
    head_file();
    flag = _func();
    while (flag)
    {
        flag = _func();
    }
    main_func();
    if (str == "@")
        cout << "The result of parsing is correct!" << endl;
    else
        {cout<<"flag"<<endl;print_err();}
    List.showTable(0);
    List.outputMT();
}


void Meaning::head_file()  //头文件语句
{
    while (str == "#")
    {
        get_next();
        if (str == "include")
            get_next();
        else
            {cout<<"fl34ag"<<endl;print_err();}
        if (str == "<")
            get_next();
        else
            {cout<<"fl234ag"<<endl;print_err();}
        if (judge_KT())
            get_next();
        else
            {cout<<"fl324ag"<<endl;print_err();}
        if (str == ">")
            get_next();
        else
            {cout<<"f234lag"<<endl;print_err();}
    }
}


void Meaning::func_call()  //函数调用
{
    if (judge_IT())
    {
        PUSH(str);
        get_next();
        iden_list();
    }
    else
        {cout<<"fl324ag234"<<endl;print_err();}
    if (str == ";") {
        get_next();
    }
    else
        {cout<<"flag23423"<<endl;print_err();}
}

void Meaning::iden_list()  //标识符表
{
    if (str == "(")
        get_next();
    else
        {cout<<"flag"<<endl;print_err();}
    if (str == ")")
        get_next();
    else
    {
        get_back();
        while (str == "," || str == "(")
        {
            get_next();
            if (judge_IT() == true)
                get_next();
            else

                {cout<<"flag234"<<endl;print_err();}}
            if (str == ")")
            {
                get_next();
                return;
            }
        }
    }


void Meaning::declare()  //声明语句
{
    type_dec();
    if (judge_IT())
    {   PUSH(str);
        get_next();
        if (str == ";") {
            get_back(); get_back();//读取刚刚的类型说明
            TypeList*ty=new TypeList;//创建一个类型表
            char type;//记录类型表的类型
            if (str == "int") {
                type = 'I';
            }
            else if (str == "float") {
                type = 'R';
            }
            else if (str == "char") {
                type = 'C';
            }
            else
                {cout<<"flag23456"<<endl;print_err();}
            (*ty).setTypeNode(type, 0);//设置类型表
            get_next();//返回至标识符
            List.addGlobalVar(str,ty,v);//添加变量
            get_next();//返回至“;”
            get_next();
            return;
        }
        else if (str == "=") {
            get_back(); get_back();//读取刚刚的类型说明
            TypeList* ty = new TypeList;//创建一个类型表
            char type;//记录类型表的类型
            if (str == "int") {
                type = 'I';
            }
            else if (str == "float") {
                type = 'R';
            }
            else if (str == "char") {
                type = 'C';
            }
            else
                {cout<<"flag7898"<<endl;print_err();}
            (*ty).setTypeNode(type, 0);//设置类型表
            get_next();//返回至标识符
            List.addGlobalVar(str, ty, v);//添加变量
            get_next();//返回至“=”
            get_next();
        }
        else
            {cout<<"flag7978"<<endl;print_err();}
        arti_exp();
        ASSI();

        if (str == ";")
            get_next();
        else

            {cout<<"flag56765"<<endl;print_err();}
    }
    else
        {cout<<"flag"<<endl;print_err();}
}

void Meaning::return_sta()  //return语句
{
    if (str == "return")
    {
        get_next();
        if (str == ";") {
            RETURN("NULL");
            get_next();
        }
        else if (judge_IT() || str == "0" || str == "1")
        {
            RETURN(str);
            get_next();
            if (str == ";")
                get_next();
            else
                {cout<<"flag666"<<endl;print_err();}
        }
        else
            {cout<<"flag343444"<<endl;print_err();}
    }
    else
        {cout<<"flag3345"<<endl;print_err();}
}


void Meaning::main_func()  //主函数
{
    type_dec();
    if (str == "main")
        get_next();
    else
        {cout<<"flag34534"<<endl;print_err();}
    if (str == "(")
        get_next();
    else
        {cout<<"flag34534"<<endl;print_err();}
    if (str == ")") {
        get_next();
    }
    else
        {cout<<"flag34534534"<<endl;print_err();}
    func_sta();
}


int Meaning::_func() //函数
{
    type_dec();
    if (judge_IT() == true) {


    }
    else {

        if (str == "main") {
            get_back();
            return 0;
        }
        else
            {cout<<"flag"<<endl;print_err();}
    }
    get_back();//读取刚刚的类型说明
    TypeList* ty = new TypeList;//创建一个类型表
    char type;//记录类型表的类型
    if (str == "int") {
        type = 'I';
    }
    else if (str == "float") {
        type = 'R';
    }
    else if (str == "char") {
        type = 'C';
    }
    else if (str == "void") {
        type = 'I'; //这里我不知道要给类型表指向啥类型，所以就指向了i
    }
    else
        {cout<<"flag345345"<<endl;print_err();}

    (*ty).setTypeNode(type, 0);//设置类型表
    get_next();//返回至函数名
    List.addIdenfer(str, ty, f,numF);//添加函数表




    get_next();
    para_list();
    func_sta();

 //计数器加1
    return 1;
}

void Meaning::type_dec()  //类型说明
{
    if (str == "void" || str == "char" || str == "int" || str == "float")
        get_next();
    else
        {cout<<"flag3453"<<endl;print_err();}
}

void Meaning::func_sta()  //函数语句
{
    if (str == "{")
        get_next();
    else
        {cout<<"flag2133112"<<endl;print_err();}
    _sta();

    return_sta();

    if (str == "}")
        get_next();
    else
        {cout<<"flag31231"<<endl;print_err();}
}

void Meaning::para_list()  //参数表
{

    int nump = 0;//参数个数

    if (str == "(")
        get_next();
    else
        {cout<<"flag12331"<<endl;print_err();}
    if (str == ")") {
        List.setFuc(0,0,0,numF);//设置函数表的参数个数
        get_next();
        return;
    }
    else
    {
        get_back();
        while (str == "," || str == "(")
        {
            get_next();
            type_dec();

            if (judge_IT() == true) {

                get_back();//返回至类型
                TypeList* ty = new TypeList;//创建一个类型表
                char type;//记录类型表的类型
                if (str == "int") {
                    type = 'I';
                }
                else if (str == "float") {
                    type = 'R';
                }
                else if (str == "char") {
                    type = 'C';
                }
                else
                    {cout<<"flag2133"<<endl;print_err();}
                nump++;//参数个数加一
                (*ty).setTypeNode(type, 0);//设置类型表
                get_next();//返回至标识符
                List.addPara(str, ty, vf, numF);//添加参数
                get_next();//返回至","或“）”

            }
            else
                {cout<<"flag1231"<<endl;print_err();}
            if (str == ")")

            {
                List.setFuc(0, 0, nump, numF);//设置函数参数个数
                get_next();
                return;
            }

        }
    }
}

void Meaning::_sta()  //语句
{
    if (str == "void" || str == "char" || str == "int" || str == "float")
        declare();
    else if (str == "if")
        if_exp();
    else if (str == "while")
        while_exp();
    else
    {
        get_next();
        if (str == "=")
        {
            get_back();
            ass_sta();
        }
        else
        {
            get_back();
            func_call();
        }
    }
    if (str != "}" && str != "return")
        _sta();
    else
        return;
}

void Meaning::comp_sta()  //复合语句
{
    if (str == "{")
    {
        get_next();
        _sta();
        if (str == "}")
            get_next();
        else
            {cout<<"flag12313"<<endl;print_err();}
    }
    else
        {cout<<"flag123"<<endl;print_err();}
}



void Meaning::ass_sta()  //赋值语句
{
    if (judge_IT() == true){

        PUSH(str);
        get_next();
        }
    else
        {cout<<"flag121"<<endl;print_err();}
    if (str == "=")
    {
        get_next();
        get_next();
        if (str == "(")
        {
            get_back();
            func_call();
            ASSI();
        }

        else
        {
            get_back();
            arti_exp();
            if (str == ";") {
                ASSI();
                get_next();
            }
            else
                {cout<<"flag12"<<endl;print_err();}
        }
    }
    else
        {cout<<"flag11"<<endl;print_err();}
}

void Meaning::if_exp()  //if语句
{
    if (str == "if")
        get_next();

    else
        {cout<<"flag101"<<endl;print_err();}
    if (str == "(")
        get_next();
    else
        {cout<<"flag9"<<endl;print_err();}
    logic_exp();
    if (str == ")") {
        get_next();
        IF();
    }
    else
        {cout<<"flag8"<<endl;print_err();}


    comp_sta();
    if (str == "else") {
        get_next();
        EL();
    }
    else {
        IE();
        return;
    }


    comp_sta();
    IE();

}

void Meaning::while_exp()  //while语句
{
    if (str == "while") {
        WH();
        get_next();

    }
    else
        {cout<<"flag7"<<endl;print_err();}
    if (str == "(")
        get_next();
    else
        {cout<<"flag6"<<endl;print_err();}
    logic_exp();
    if (str == ")") {
        DO();
        get_next();
    }
    else
        {cout<<"flag5"<<endl;print_err();}
    comp_sta();
    WE();
}



void Meaning::rela_exp()  //关系表达式
{
    string w;
    arti_exp();
    if (str == ">" || str == ">=" || str == "<" || str == "<=" || str == "=="||str=="!=") {
        w = str;
        get_next();
    }
    else {cout<<"flag4"<<endl;print_err();}

    arti_exp();
    RLT(w);
}

void Meaning::logic_exp() {  //逻辑表达式
    logic_e();
    while (1) {
        if (str == "||") {
            get_next();
            logic_e();
            OR();
        }
        else if (str == "&&") {
            get_next();
            logic_e();
            AND();
        }
        else
            return;

    }
}

void Meaning::logic_e()  //逻辑项
{
    if (judge_IT()) {
        get_next();
        if(str == ">" || str == ">=" || str == "<" || str == "<=" || str == "==" || str == "!=") {
            get_back();
            rela_exp();
        }
        else {
            get_back();//返回至标识符
            PUSH(str);
            get_next();
            return;
        }
    }
    else if (str == "0") {
        PUSH(str);
        get_next();
        return;
    }
    else if (str == "1") {
        PUSH(str);
        get_next();
        return;
    }
    else if (str == "!") {
        get_next();
        logic_e();
        NOT();
    }
    else if (str == "(") {
        get_next();
        logic_exp();
        if (str == ")") {
            get_next();
            return;
        }
        else
            {cout<<"flag3"<<endl;print_err();}
    }
    else
        rela_exp();
}

void Meaning::arti_exp()  //算数表达式
{
    item();
    while (1)
    {
        if (str == "+")
        {
            get_next();
            item();
            ADD();
        }
        else if (str == "-")
        {
            get_next();
            item();
            SUB();
        }
        else
            return;
    }
}

void Meaning::item()  //项
{
    factor();
    while (1)
    {
        if (str == "*")
        {
            get_next();
            factor();
            MUL();
        }
        else if (str == "/")
        {
            get_next();
            factor();
            DIV();
        }
        else
            return;
    }
}

void Meaning::factor()  //因子
{
    if (str == "(")
    {
        get_next();
        arti_exp();
        if (str == ")") {
            get_next();
            return;
        }
        else
            {cout<<"flag2"<<endl;print_err();}
    }
    else
        arti_v();
}

void Meaning::arti_v()  //算数量
{
    if (judge_IT() == true || judge_CT() == true)
    {
        PUSH(str);
        get_next();
    }
    else
        {cout<<"flag1"<<endl;print_err();}
}

void Meaning::print_err()  //语法分析错误提示语句
{
    cout << "The result of parsing is incorrect!" << endl;
    exit(0);
}


void Meaning::get_back()  //回溯一个token串
{
    str = sequence[--n];
}

void Meaning::get_next()  //取下一个token串
{
    str = sequence[++n];
    cout<<str<<endl;
}

bool Meaning::judge_IT()  //判断token串是否为标识符
{
    string data;
    ifstream infile;
    infile.open("IT.txt");
    infile >> data;
    while (!infile.eof())
    {
        if (str == data)
            return true;
        else
            infile >> data;
    }
    infile.close();
    return false;
}

bool Meaning::judge_CT()  //判断token串是否为常数
{
    string data;
    ifstream infile;
    infile.open("CT.txt");
    infile >> data;
    while (!infile.eof())
    {
        if (str == data)
            return true;
        else
            infile >> data;
    }
    infile.close();
    return false;
}


bool Meaning::judge_KT()  //判断token串是否为关键字
{
    string data;
    ifstream infile;
    infile.open("KT.txt");
    infile >> data;
    while (!infile.eof())
    {
        if (str == data)
            return true;
        else
            infile >> data;
    }
    infile.close();
    return false;
}


#endif // MEANING_H_INCLUDED
