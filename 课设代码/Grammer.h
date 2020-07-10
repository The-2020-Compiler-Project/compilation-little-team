#ifndef GRAMMER_H_INCLUDED
#define GRAMMER_H_INCLUDED

#include<iostream>



#include "Word.h"

using namespace std;

//语法分析类
class Syntax
{
	private:
        string str;  //当前识别token串
        int n=-1;  //token串在数组中的编号
        int flag=0;  //标记位
        int err[30]={0};  //标记错误
	public:
        Syntax() {};  //构造函数
        void parse();  //语法分析函数
        void declare();  //声明函数
	    void main_func();  //主函数
	    int _func(); //函数
	    void type_dec();  //类型说明
	    void func_sta();  //函数语句
	    void para_list();  //参数表
	    void _sta();  //语句
	    void comp_sta();  //复合语句
	    void exp_sta();  //表达语句
	    void ass_sta();  //赋值语句
	    void if_exp();  //if语句
	    void while_exp();  //while语句
	    void rela_ope();  //关系运算符
	    void logic_ope();  //逻辑运算符
	    void rela_exp();  //关系表达式
	    void logic_exp();  //逻辑表达式
	    void logic_e();  //逻辑表达
	    void _ope();  //操作数
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
        bool judge_CT();  //判断token串是否为常数
        bool judge_KT();  //判断token串是否为关键字
        void func_call();  //函数调用
        void iden_list();  //标识符表
        void return_sta();  //return语句
        void head_file();  //头文件语句

};

//语法分析类成员定义
void Syntax::parse()  //语义分析函数
{
    int flag=0;
    get_next();
    head_file();
    flag=_func();
    while(flag)
    {
        flag=_func();
    }
    main_func();
    if (str == "@")
        cout << "The result of parsing is correct!" << endl;
    else
        print_err();
}

void Syntax::head_file()  //头文件语句
{
    while(str=="#")
    {
        get_next();
        if(str=="include")
            get_next();
        else
            print_err();
        if(str=="<")
            get_next();
        else
            print_err();
        if(judge_KT())
            get_next();
        else
            print_err();
        if(str==">")
            get_next();
        else
            print_err();
    }
}

void Syntax::declare()  //声明语句
{
    type_dec();
    if (judge_IT())
    {
        get_next();
        if(str==";")
        {
            get_next();
            return;
        }
        else if(str == "=")
            get_next();
        else
            print_err();
        arti_exp();
        if(str==";")
            get_next();
        else
            print_err();
    }
    else
        print_err();
}

void Syntax::func_call()  //函数调用
{
    if(judge_IT())
    {
        get_next();
        iden_list();
    }
    else
        print_err();
    if(str==";")
        get_next();
    else
        print_err();
}

void Syntax::iden_list()  //标识符表
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
            if (judge_IT() == true)
                get_next();
            else
                print_err();
            if (str == ")")
            {
                get_next();
                return;
            }
        }
    }
}


void Syntax::main_func()  //主函数
{
    type_dec();
    if (str == "main")
        get_next();
    else
        print_err();
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

int Syntax::_func() //函数
{
    type_dec();
    if (judge_IT() == true)
        get_next();
    else
    {
        if(str=="main")
        {
            get_back();
            return 0;
        }
        else
            print_err();
    }
    para_list();
    func_sta();
    return 1;
}

void Syntax::type_dec()  //类型说明
{
    if (str == "void" || str == "char" || str == "int" || str == "float")
        get_next();
    else
        print_err();
}

void Syntax::func_sta()  //函数语句
{
    if (str == "{")
        get_next();
    else
        print_err();
    _sta();
    return_sta();
    if(str=="}")
        get_next();
    else
        print_err();
}

void Syntax::return_sta()  //return语句
{
    if(str=="return")
    {
        get_next();
        if(str==";")
            get_next();
        else if(judge_IT()||str=="0"||str=="1")
        {
            get_next();
            if(str==";")
                get_next();
            else
                print_err();
        }
        else
            print_err();
    }
    else
        print_err();
}

void Syntax::para_list()  //参数表
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
        }
    }
}

void Syntax::_sta()  //语句
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
        if(str=="=")
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
    if (str != "}"&&str !="return" )
        _sta();
    else
        return;
}

void Syntax::comp_sta()  //复合语句
{
    if (str == "{")
    {
        get_next();
        _sta();
        if(str=="}")
            get_next();
        else
            print_err();
    }
    else
        print_err();
}

void Syntax::ass_sta()  //赋值语句
{
    if (judge_IT() == true)
        get_next();
    else
        print_err();
    if (str == "=")
    {
        get_next();
        get_next();
        if(str=="(")
        {
            get_back();
            func_call();
        }
        else
        {
            get_back();
            arti_exp();
            if (str == ";")
                get_next();
            else
                print_err();
        }
    }
    else
        print_err();
}

void Syntax::if_exp()  //if语句
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
    if (str == ")")
        get_next();
    else
        print_err();
    comp_sta();
    if (str == "else")
        get_next();
    else
        return;
    comp_sta();
}

void Syntax::while_exp()  //while语句
{
    if (str == "while")
        get_next();
    else
        print_err();
    if (str == "(")
        get_next();
    else
        print_err();
    logic_exp();
    if (str == ")")
        get_next();
    else
        print_err();
    comp_sta();
}

void Syntax::rela_exp()  //关系表达式
{
    arti_exp();
    if (str == ">" || str == ">=" || str == "<" || str == "<=" || str == "==" || str =="!=")
        get_next();
    else
        print_err();
    arti_exp();
}

void Syntax::logic_exp() {  //逻辑表达式
    logic_e();
    while (1) {
        if (str == "||") {
            get_next();
            logic_e();
        }
        else if (str == "&&") {
            get_next();
            logic_e();
        }
        else
            return;
    }
}

void Syntax::logic_e()  //逻辑项
{
    if (judge_IT())
    {
        get_next();
        if (str == ">" || str == ">=" || str == "<" || str == "<=" || str == "==" || str == "!=")
        //为关系表达式时
        {
            get_back();
            rela_exp();
        }
        else //为标识符时
            return;
    }
    else if (str == "0") {
        get_next();
        return;
    }
    else if (str == "1") {
        get_next();
        return;
    }
    else if (str == "!") {
        get_next();
        logic_e();
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
        print_err();
}

void Syntax::arti_exp()  //算数表达式
{
    item();
    while (1)
    {
        if (str == "+")
        {
            get_next();
            item();
        }
        else if (str == "-")
        {
            get_next();
            item();
        }
        else
            return;
    }
}

void Syntax::item()  //项
{
    factor();
    while (1)
    {
        if (str == "*")
        {
            get_next();
            factor();
        }
        else if (str == "/")
        {
            get_next();
            factor();
        }
        else
            return;
    }
}

void Syntax::factor()  //因子
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

void Syntax::arti_v()  //算数量
{
    if (judge_IT() == true || judge_CT() == true)
        get_next();
    else
        print_err();
}

void Syntax::print_err()  //语法分析错误提示语句
{
    cout << "The result of parsing is incorrect!" << endl;
    exit(0);
}


void Syntax::get_back()  //回溯一个token串
{
    str = sequence[--n];
}

void Syntax::get_next()  //取下一个token串
{
    str = sequence[++n];
}

bool Syntax::judge_IT()  //判断token串是否为标识符
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

bool Syntax::judge_CT()  //判断token串是否为常数
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

bool Syntax::judge_KT()  //判断token串是否为关键字
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

#endif // GRAMMER_H_INCLUDED
