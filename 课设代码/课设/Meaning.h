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
/*  使用方式：
    在创建时自动读取所有标识符，在后续过程中 遇到声明填写类型和种类并申请地址，遇到赋值则对申请的地址进行赋值
    若赋值与声明同时进行，则一步填写
    若需要进行初始化 则直接使用
    地址问题未完成：需要使用 new指令申请空间，然后赋值给void指针
    数组表和结构体表还未完成（在写了在写了）*/

using namespace std;


stack<string> SEM;//语义栈
vector<Quaternion> QT;//存放所有四元式

//语义分析类
class Meaning
{
private:
    string str;  //当前识别token串
    int n = 0;  //token串在数组中的编号
    int flag = 0;  //标记位
    int err[30] = { 0 };  //标记错误

    int numt = 1; //记录临时变量t的名字

public:
    Meaning() {};  //构造函数
    void parse();  //语法分析函数
    void main_func(int flag);  //主函数
    void _func(); //函数
    void type_dec();  //类型说明
    void func_sta();  //函数语句
    void para_list();  //参数表
    void _sta();  //语句
    void comp_sta();  //复合语句
    void exp_sta();  //表达语句
    void ass_sta();  //赋值语句
    void if_exp();  //if语句
    void while_exp();  //while语句

    void declare();//声明语句

    void rela_exp();  //关系表达式
    void logic_exp();  //逻辑表达式
    void logic_e();  //逻辑项
    void _opd();  //操作对象
    void logic_v();  //逻辑量
    void arti_exp();  //算数表达式
    void item();  //项
    void factor();  //因子
    void arti_v();  //算数量
    void print_err();  //语法分析错误提示语句
    void get_back();  //回溯一个token串
    void get_next();  //取下一个token串
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

};

//语义分析类成员定义


    //语义动作函数

void Meaning::RLT(string w) {

}


void Meaning::IF() {

    Quaternion a("if", SEM.top(), "_", "_");
    QT.push_back(a);//存入qt
    SEM.pop();

}

void Meaning::EL() {

    Quaternion a("el", "_", "_", "_");
    QT.push_back(a);

}

void Meaning::IE() {
    Quaternion a("ie", "_", "_", "_");
    QT.push_back(a);

}

void Meaning::WH() {
    Quaternion a("wh", "_", "_", "_");
    QT.push_back(a);
}

void Meaning::DO() {
    Quaternion a("do", SEM.top(), "_", "_");
    QT.push_back(a);
    SEM.pop();
}

void Meaning::WE() {
    Quaternion a("we", "_", "_", "_");
    QT.push_back(a);
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
    Quaternion a(w, ob1, ob2, t);
    SEM.push(t);

}

void Meaning::OR() {
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    Quaternion a("||", ob1, ob2, t);
    SEM.push(t);
}

void Meaning::AND() {
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    Quaternion a("&&", ob1, ob2, t);
    SEM.push(t);
}

void Meaning::NOT() {
    string t = NEWT();
    string ob1 = SEM.top();
    SEM.pop();
    Quaternion a("!", ob1, "_", t);
    SEM.push(t);
}

void Meaning::PUSH(string i) {
    SEM.push(i);
}

void Meaning::ASSI()
{
    string t = SEM.top();
    SEM.pop();
    Quaternion a("=", t, "_", SEM.top());
    QT.push_back(a);
    SEM.pop();
}

void Meaning::ADD()
{
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    Quaternion a("+", ob1, ob2, t);
    SEM.push(t);
}

void Meaning::SUB()
{
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    Quaternion a("-", ob1, ob2, t);
    SEM.push(t);
}

void Meaning::MUL()
{
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    Quaternion a("*", ob1, ob2, t);
    SEM.push(t);
}

void Meaning::DIV()
{
    string t = NEWT();
    string ob2 = SEM.top();
    SEM.pop();
    string ob1 = SEM.top();
    SEM.pop();
    Quaternion a("/", ob1, ob2, t);
    SEM.push(t);
}

void Meaning::parse()  //语义分析函数
{
    flag = 1;
    get_next();
    main_func(flag);
    if (err[1] == 1)
        _func();
    if (str == "@")
        cout << "The result of parsing is correct!" << endl;
    else
        print_err();
}


void Meaning::declare() {   //声明语句
    type_dec();
    if (judge_IT()) {
        get_next();
        if (str == ";") {
            return;
        }
        else
            print_err();
    }
    else
        print_err();
}


void Meaning::main_func(int flag)  //主函数
{
    err[1] = 0;
    type_dec();
    if (str == "main")
        get_next();
    else
    {
        if (flag == 1)
        {
            err[1] = 1;
            return;
        }
        else
            print_err();
    }
    if (str == "(")
        get_next();
    else
        print_err();
    if (str == ")")
        get_next();
    else
        print_err();
    func_sta();
}

void Meaning::_func() //函数
{
    type_dec();
    if (judge_IT() == true)
        get_next();
    else
        print_err();
    para_list();
    func_sta();
}

void Meaning::type_dec()  //类型说明
{
    if (str == "void" || str == "char" || str == "int" || str == "float")
        get_next();
    else
        print_err();
}

void Meaning::func_sta()  //函数语句
{
    if (str == "{")
        get_next();
    else
        print_err();
    _sta();
    if (str == "return")
        get_next();
    else
        print_err();
    if (judge_IT() == true)
        get_next();
    else
        print_err();
    if (str == ";")
        get_next();
    else
        print_err();
    if (str == "}")
        get_next();
    else
        print_err();
}

void Meaning::para_list()  //参数表
{
    if (str == "(")
        get_next();
    else
        print_err();
    if (str == ")")
        get_next();
    else
    {
        get_back();
        while (str == "," || str == "(")
        {
            get_next();
            type_dec();
            if (judge_IT() == true)
                get_next();
            else
                print_err();
            if (str == ")")
            {
                get_next();
                return;
            }
            else
                get_next();
        }
    }
}

void Meaning::_sta()  //语句
{
    if (str == "void" || str == "char" || str == "int" || str == "float")
        type_dec();
    else if (str == "if")
        if_exp();
    else if (str == "while")
        while_exp();
    else
    {
        exp_sta();
        return;
    }
    if (str == ";")
    {
        get_next();
        _sta();
    }
    else
        print_err();
}

void Meaning::comp_sta()  //复合语句
{
    if (str == "{")
        get_next();
    else
    {
        _sta();
        if (str == "}")
            get_next();
        else
            print_err();
    }
}



void Meaning::ass_sta()  //赋值语句
{
    if (judge_IT() == true)
        get_next();
    else
        print_err();
    if (str == "=")
    {
        get_next();
        arti_exp();
        if (str == ";")
        {
            get_next();
            ASSI();
        }
        else
            print_err();
    }
    else
        print_err();
}

void Meaning::if_exp()  //if语句
{
    if (str == "if")
        get_next();

    else
        print_err();
    if (str == "(")
        get_next();
    else
        print_err();
    logic_exp();
    if (str == ")") {
        get_next();
        IF();
    }
    else
        print_err();


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
        print_err();
    if (str == "(")
        get_next();
    else
        print_err();
    logic_exp();
    if (str == ")") {
        DO();
        get_next();
    }
    else
        print_err();
    comp_sta();
    WE();
}



void Meaning::rela_exp()  //关系表达式
{
    string w;
    arti_exp();
    if (str == ">" || str == ">=" || str == "<" || str == "<=" || str == "==") {
        w = str;
        get_next();
    }
    else print_err();

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
        PUSH(str);
        get_next();
        return;
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
            print_err();
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
            print_err();
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
        print_err();
}

void Meaning::print_err()  //语法分析错误提示语句
{
    cout << "The result of parsing is incorrect!" << endl;
    exit(0);
}


void Meaning::get_back()  //回溯一个token串
{
    str = sequence[n--];
}

void Meaning::get_next()  //取下一个token串
{
    str = sequence[n++];
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





#endif // MEANING_H_INCLUDED
