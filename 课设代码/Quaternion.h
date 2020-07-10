//��Ԫʽ

#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include<iostream>
#include<string>
#include<stack>

using namespace std;




class Quaternion{
public:
    Quaternion();
    Quaternion(string a, string b, string c, string d);
    

    string showQuaternion();//��ӡ��Ԫʽ
    void setOperator(string opt);//�������
    void setObject1(string obj);//���ö���1
    void setObject2(string obj);//���ö���2
    void setResult(string result);//���ý��

    string member[4];//�����Ԫʽ�����������󡢽��

    string getOperator();
    string getObject1();
    string getObject2();
    string getResult();

private:
    
};

Quaternion::Quaternion(){
    member[0]="_";
    member[1]="_";
    member[2]="_";
    member[3]="_";
}

Quaternion::Quaternion(string a, string b, string c, string d){
    member[0] = a;
    member[1] = b;
    member[2] = c;
    member[3] = d;
}


string Quaternion::showQuaternion() {
    string str;
    str = member[0] + " " + member[1] + " " + member[2] + " " + member[3];
    return str;
}

 void Quaternion::setOperator(string opt){
     member[0]=opt;
 }
void Quaternion::setObject1(string obj){
    member[1]=obj;
}

void Quaternion::setObject2(string obj){
    member[2]=obj;
}

void Quaternion::setResult(string result){
    member[3]=result;
}

string Quaternion::getOperator(){
    return member[0];
}

string Quaternion::getObject1(){
    return member[1];
}

string Quaternion::getObject2(){
    return member[2];
}

string Quaternion::getResult(){
    return member[3];
}

#endif // QUATERNION_H_INCLUDED
