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

#include"TotalList.h"
/*  ʹ�÷�ʽ��
    �ڴ���ʱ�Զ���ȡ���б�ʶ�����ں��������� ����������д���ͺ����ಢ�����ַ��������ֵ�������ĵ�ַ���и�ֵ
    ����ֵ������ͬʱ���У���һ����д
    ����Ҫ���г�ʼ�� ��ֱ��ʹ��
    ��ַ����δ��ɣ���Ҫʹ�� newָ������ռ䣬Ȼ��ֵ��voidָ��
    �����ͽṹ���δ��ɣ���д����д�ˣ�*/

using namespace std;


Totallist List;//���ű�


//������ļ�����


stack<string> SEM;//����ջ
vector<Quaternion> QT;//���������Ԫʽ

//���������
class Meaning
{
private:
    string str;  //��ǰʶ��token��
    int n = 0;  //token���������еı��
    int err[30] = { 0 };  //��Ǵ���
    int numF;
    int numt = 1; //��¼��ʱ����t������

public:
    Meaning() {n=-1;numF=0;};  //���캯��
    void parse();  //�﷨��������
    void main_func();  //������
    int _func(); //����
    void type_dec();  //����˵��
    void func_sta();  //�������
    void para_list();  //������
    void _sta();  //���
    void comp_sta();  //�������

    void ass_sta();  //��ֵ���
    void if_exp();  //if���
    void while_exp();  //while���

    void declare();//�������

    void iden_list();//��ʶ����

    void func_call();  //��������

    void rela_exp();  //��ϵ���ʽ
    void logic_exp();  //�߼����ʽ
    void logic_e();  //�߼���
    void _opd();  //��������
    void logic_v();  //�߼���
    void arti_exp();  //�������ʽ
    void item();  //��
    void factor();  //����
    void arti_v();  //������

    void head_file();//ͷ�ļ����
    void return_sta();//return���

    void print_err();  //�﷨����������ʾ���
    void get_back();  //����һ��token��
    void get_next();  //ȡ��һ��token��

    bool judge_KT();
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

    //�����������嶯��
    void CALL(string fucname);
    void RETURN(string res);

};


//����������Ա����


    //���嶯������


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

void Meaning::parse()  //�����������
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


void Meaning::head_file()  //ͷ�ļ����
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


void Meaning::func_call()  //��������
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

void Meaning::iden_list()  //��ʶ����
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


void Meaning::declare()  //�������
{
    type_dec();
    if (judge_IT())
    {   PUSH(str);
        get_next();
        if (str == ";") {
            get_back(); get_back();//��ȡ�ոյ�����˵��
            TypeList*ty=new TypeList;//����һ�����ͱ�
            char type;//��¼���ͱ������
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
            (*ty).setTypeNode(type, 0);//�������ͱ�
            get_next();//��������ʶ��
            List.addGlobalVar(str,ty,v);//��ӱ���
            get_next();//��������;��
            get_next();
            return;
        }
        else if (str == "=") {
            get_back(); get_back();//��ȡ�ոյ�����˵��
            TypeList* ty = new TypeList;//����һ�����ͱ�
            char type;//��¼���ͱ������
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
            (*ty).setTypeNode(type, 0);//�������ͱ�
            get_next();//��������ʶ��
            List.addGlobalVar(str, ty, v);//��ӱ���
            get_next();//��������=��
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

void Meaning::return_sta()  //return���
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


void Meaning::main_func()  //������
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


int Meaning::_func() //����
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
    get_back();//��ȡ�ոյ�����˵��
    TypeList* ty = new TypeList;//����һ�����ͱ�
    char type;//��¼���ͱ������
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
        type = 'I'; //�����Ҳ�֪��Ҫ�����ͱ�ָ��ɶ���ͣ����Ծ�ָ����i
    }
    else
        {cout<<"flag345345"<<endl;print_err();}

    (*ty).setTypeNode(type, 0);//�������ͱ�
    get_next();//������������
    List.addIdenfer(str, ty, f,numF);//��Ӻ�����




    get_next();
    para_list();
    func_sta();

 //��������1
    return 1;
}

void Meaning::type_dec()  //����˵��
{
    if (str == "void" || str == "char" || str == "int" || str == "float")
        get_next();
    else
        {cout<<"flag3453"<<endl;print_err();}
}

void Meaning::func_sta()  //�������
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

void Meaning::para_list()  //������
{

    int nump = 0;//��������

    if (str == "(")
        get_next();
    else
        {cout<<"flag12331"<<endl;print_err();}
    if (str == ")") {
        List.setFuc(0,0,0,numF);//���ú�����Ĳ�������
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

                get_back();//����������
                TypeList* ty = new TypeList;//����һ�����ͱ�
                char type;//��¼���ͱ������
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
                nump++;//����������һ
                (*ty).setTypeNode(type, 0);//�������ͱ�
                get_next();//��������ʶ��
                List.addPara(str, ty, vf, numF);//��Ӳ���
                get_next();//������","�򡰣���

            }
            else
                {cout<<"flag1231"<<endl;print_err();}
            if (str == ")")

            {
                List.setFuc(0, 0, nump, numF);//���ú�����������
                get_next();
                return;
            }

        }
    }
}

void Meaning::_sta()  //���
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

void Meaning::comp_sta()  //�������
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



void Meaning::ass_sta()  //��ֵ���
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

void Meaning::if_exp()  //if���
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

void Meaning::while_exp()  //while���
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



void Meaning::rela_exp()  //��ϵ���ʽ
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
        get_next();
        if(str == ">" || str == ">=" || str == "<" || str == "<=" || str == "==" || str == "!=") {
            get_back();
            rela_exp();
        }
        else {
            get_back();//��������ʶ��
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
            {cout<<"flag2"<<endl;print_err();}
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
        {cout<<"flag1"<<endl;print_err();}
}

void Meaning::print_err()  //�﷨����������ʾ���
{
    cout << "The result of parsing is incorrect!" << endl;
    exit(0);
}


void Meaning::get_back()  //����һ��token��
{
    str = sequence[--n];
}

void Meaning::get_next()  //ȡ��һ��token��
{
    str = sequence[++n];
    cout<<str<<endl;
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


bool Meaning::judge_KT()  //�ж�token���Ƿ�Ϊ�ؼ���
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
