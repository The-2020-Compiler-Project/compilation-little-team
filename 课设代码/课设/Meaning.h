#ifndef MEANING_H_INCLUDED
#define MEANING_H_INCLUDED
#include <string>
#include<stack>
#include<vector>
#include <iostream>
#include "ConstTable.h"//������ ʹ�÷�ʽ ��token���ü��� ��<N,4>������ ConstTable.getFloat(i)|getInt(i)
#include "MainTable.h"//���ű��ܱ�
#include "TypeList.h"
#include "PFINFL.h"
#include "ParameterTable.h"
#include "Word.h"
/*  ʹ�÷�ʽ��
    �ڴ���ʱ�Զ���ȡ���б�ʶ�����ں��������� ����������д���ͺ����ಢ�����ַ��������ֵ�������ĵ�ַ���и�ֵ
    ����ֵ������ͬʱ���У���һ����д
    ����Ҫ���г�ʼ�� ��ֱ��ʹ��
    ��ַ����δ��ɣ���Ҫʹ�� newָ������ռ䣬Ȼ��ֵ��voidָ��
    �����ͽṹ���δ��ɣ���д����д�ˣ�*/

using namespace std;


stack<string> SEM;//����ջ
vector<Quaternion> QT;//���������Ԫʽ

//���������
class Meaning
{
private:
    string str;  //��ǰʶ��token��
    int n = 0;  //token���������еı��
    int flag = 0;  //���λ
    int err[30] = { 0 };  //��Ǵ���

    int numt = 1; //��¼��ʱ����t������

public:
    Meaning() {};  //���캯��
    void parse();  //�﷨��������
    void main_func(int flag);  //������
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

    void declare();//�������

    void rela_exp();  //��ϵ���ʽ
    void logic_exp();  //�߼����ʽ
    void logic_e();  //�߼���
    void _opd();  //��������
    void logic_v();  //�߼���
    void arti_exp();  //�������ʽ
    void item();  //��
    void factor();  //����
    void arti_v();  //������
    void print_err();  //�﷨����������ʾ���
    void get_back();  //����һ��token��
    void get_next();  //ȡ��һ��token��
    bool judge_IT();  //�ж�token���Ƿ�Ϊ��ʶ��
    bool judge_CT(); //�ж�token���Ƿ�Ϊ����

    //if�������嶯��
    void IF();
    void EL();
    void IE();

    //while�������嶯��
    void WH();
    void DO();
    void WE();

    //�߼����ʽ�����嶯��
    string NEWT();
    void RLT(string w);
    void OR();
    void AND();
    void NOT();
    void PUSH(string i);

    //��ֵ���ʽ�����嶯��
    void ASSI();

    //�������ʽ�����嶯��
    void ADD();
    void SUB();
    void MUL();
    void DIV();

};

//����������Ա����


    //���嶯������

void Meaning::RLT(string w) {

}


void Meaning::IF() {

    Quaternion a("if", SEM.top(), "_", "_");
    QT.push_back(a);//����qt
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

void Meaning::parse()  //�����������
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


void Meaning::declare() {   //�������
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


void Meaning::main_func(int flag)  //������
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

void Meaning::_func() //����
{
    type_dec();
    if (judge_IT() == true)
        get_next();
    else
        print_err();
    para_list();
    func_sta();
}

void Meaning::type_dec()  //����˵��
{
    if (str == "void" || str == "char" || str == "int" || str == "float")
        get_next();
    else
        print_err();
}

void Meaning::func_sta()  //�������
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

void Meaning::para_list()  //������
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

void Meaning::_sta()  //���
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

void Meaning::comp_sta()  //�������
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



void Meaning::ass_sta()  //��ֵ���
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

void Meaning::if_exp()  //if���
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

void Meaning::while_exp()  //while���
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



void Meaning::rela_exp()  //��ϵ���ʽ
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

void Meaning::logic_exp() {  //�߼����ʽ
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

void Meaning::logic_e()  //�߼���
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

void Meaning::arti_exp()  //�������ʽ
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

void Meaning::item()  //��
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

void Meaning::factor()  //����
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

void Meaning::arti_v()  //������
{
    if (judge_IT() == true || judge_CT() == true)
    {
        PUSH(str);
        get_next();
    }
    else
        print_err();
}

void Meaning::print_err()  //�﷨����������ʾ���
{
    cout << "The result of parsing is incorrect!" << endl;
    exit(0);
}


void Meaning::get_back()  //����һ��token��
{
    str = sequence[n--];
}

void Meaning::get_next()  //ȡ��һ��token��
{
    str = sequence[n++];
}

bool Meaning::judge_IT()  //�ж�token���Ƿ�Ϊ��ʶ��
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

bool Meaning::judge_CT()  //�ж�token���Ƿ�Ϊ����
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
