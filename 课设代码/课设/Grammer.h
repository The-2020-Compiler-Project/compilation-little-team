#ifndef GRAMMER_H_INCLUDED
#define GRAMMER_H_INCLUDED
#include <bits/stdc++.h>
#include "Word.h"

using namespace std;

//�﷨������
class Syntax
{
	private:
        string str;  //��ǰʶ��token��
        int n=0;  //token���������еı��
        int flag=0;  //���λ
        int err[30]={0};  //��Ǵ���
	public:
        Syntax() {};  //���캯��
        void parse();  //�﷨��������
	    void main_func();  //������
	    void _func(); //����
	    void type_dec();  //����˵��
	    void func_sta();  //�������
	    void para_list();  //������
	    void _sta();  //���
	    void comp_sta();  //�������
	    void exp_sta();  //������
	    void ass_sta();  //��ֵ���
	    void if_exp();  //if���
	    void while_exp();  //while���
	    void rela_ope();  //��ϵ�����
	    void logic_ope();  //�߼������
	    void rela_exp();  //��ϵ���ʽ
	    void logic_exp();  //�߼����ʽ
	    void logic_e();  //�߼����
	    void _ope();  //������
	    void _opd();  //��������
	    void logic_v();  //�߼���
	    void arti_exp();  //�������ʽ
	    void item();  //��
	    void factor();  //����
	    void arti_v();  //������
	    void print_err();  //�﷨����������ʾ���
	    void get_next();  //ȡ��һ��token��
	    bool judge_IT();  //�ж�token���Ƿ�Ϊ��ʶ��

};

//�﷨�������Ա����
void Syntax::parse()  //�����������
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


void Syntax::declare() {   //�������
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


void Syntax::main_func(int flag)  //������
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

void Syntax::_func() //����
{
    type_dec();
    if (judge_IT() == true)
        get_next();
    else
        print_err();
    para_list();
    func_sta();
}

void Syntax::type_dec()  //����˵��
{
    if (str == "void" || str == "char" || str == "int" || str == "float")
        get_next();
    else
        print_err();
}

void Syntax::func_sta()  //�������
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

void Syntax::para_list()  //������
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

void Syntax::_sta()  //���
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

void Syntax::comp_sta()  //�������
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



void Syntax::ass_sta()  //��ֵ���
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
        }
        else
            print_err();
    }
    else
        print_err();
}

void Syntax::if_exp()  //if���
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
    }
    else
        print_err();


    comp_sta();
    if (str == "else") {
        get_next();
    }
    else {
        return;
    }


    comp_sta();
}

void Syntax::while_exp()  //while���
{
    if (str == "while") {
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
        get_next();
    }
    else
        print_err();
    comp_sta();
}



void Syntax::rela_exp()  //��ϵ���ʽ
{
    string w;
    arti_exp();
    if (str == ">" || str == ">=" || str == "<" || str == "<=" || str == "==") {
        w = str;
        get_next();
    }
    else print_err();

    arti_exp();
}

void Syntax::logic_exp() {  //�߼����ʽ
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

void Syntax::logic_e()  //�߼���
{
    if (judge_IT()) {
        get_next();
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
        rela_exp();
}

void Syntax::arti_exp()  //�������ʽ
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

void Syntax::item()  //��
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

void Syntax::factor()  //����
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

void Syntax::arti_v()  //������
{
    if (judge_IT() == true || judge_CT() == true)
    {
        get_next();
    }
    else
        print_err();
}

void Syntax::print_err()  //�﷨����������ʾ���
{
    cout << "The result of parsing is incorrect!" << endl;
    exit(0);
}


void Syntax::get_back()  //����һ��token��
{
    str = sequence[n--];
}

void Syntax::get_next()  //ȡ��һ��token��
{
    str = sequence[n++];
}

bool Syntax::judge_IT()  //�ж�token���Ƿ�Ϊ��ʶ��
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

bool Syntax::judge_CT()  //�ж�token���Ƿ�Ϊ����
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


#endif // GRAMMER_H_INCLUDED
