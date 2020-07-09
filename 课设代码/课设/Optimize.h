#ifndef OPTIMIZE_H_INCLUDED
#define OPTIMIZE_H_INCLUDED

#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <map>
#include <stdlib.h>
using namespace std;
struct Four{
 string op;     // ������
 string data1;     // ��һ��������
 string data2;     // �ڶ���������
 string result;     // ���
 int stylenum;    // �������
 struct Four *next;   // ָ����һ��������ʼλ��
 struct Four *last;
 };   // ָ����һ��������ʼλ��      };
struct dagnode{
 string sign;     // ��ʶ��
 string var;     // ����ʶ��
 int flag;      // ���λ
 struct dagnode *lchild;  // ָ���ӵ�ָ��
 struct dagnode *rchild;  // ָ���Һ��ӵ�ָ��
 struct dagnode *next;
 }; // ָ����һ�����
Four *fhead;
dagnode *nhead;
std::list<dagnode*> listdag;
vector<string> inputs;

void do_input()
{
//��������
 inputs.push_back(" ,3.14, ,T0");
 inputs.push_back("*,2,T0,T1");
}
void four() // ������Ԫʽ�Ľṹ
{
 struct Four *fourTmp = new Four;
 fourTmp->last = NULL;
 fourTmp->next = NULL;

 for(int i=0;i< inputs.size();i++)
{
 struct Four *pp = new Four;
 pp->next = NULL;
 pp->last = fourTmp;
 fourTmp->next = pp;
  if(!pp)  //�ڴ����ʧ��
  {
    cout<<"Memory allocation failed!"<<endl;
    return;
  }
  //��Ԫʽ
   char op[10]={0};
   char data1[10]={0};
   char data2[10]={0};
   char result[10]={0};
    sscanf(inputs[i].c_str(),"%[^,],%[^,],%[^,],%[^\n]", op,data1,data2,result);
//sscanf()-��һ���ַ����ж�����ָ����ʽ���������
  pp->op=op;
  pp->data1=data1;
  pp->data2=data2;
  pp->result=result;
  if(pp->data2 == " ")
  if(pp->op == " ")
   //�ڶ���������Ϊ��,���Ҳ�����Ϊ�գ���Ϊ0����Ԫʽ
    pp->stylenum=0;
    else
   //�ڶ���������Ϊ��,���Ҳ��������գ���Ϊ1����Ԫʽ
    pp->stylenum=1;
    else
   //�ڶ�����������Ϊ�գ���Ϊ2����Ԫʽ
    pp->stylenum=2;
    fourTmp = pp;
}
    fhead = fourTmp;
}
void list_build() // ������������Ż�
{
     for(int i = 1; fhead->last != NULL; fhead = fhead->last) //�����һ����Ԫʽ��ʼ��������
 {
     //�����ڴ��ʼ��
        dagnode *tmp1 = new dagnode;
        dagnode *tmp2 = new dagnode;
        dagnode *tmpResult = new dagnode;
        tmp1->lchild = NULL;
        tmp1->rchild = NULL;
        tmp1->next = NULL;
        tmp2->lchild = NULL;
        tmp2->rchild = NULL;
        tmp2->next = NULL;
        tmpResult->lchild = NULL;
        tmpResult->rchild = NULL;
        tmpResult->next = NULL;
        nhead = new dagnode;
        nhead->next = NULL;
        nhead->lchild = NULL;
        nhead->rchild = NULL;
switch(fhead->stylenum)//�����ʹ���
{
    case 0:
    tmp1->sign = fhead->result;
    tmp1->var = fhead->data1;
    tmp1->flag = 0;
    tmp1->lchild = NULL;
    tmp1->rchild = NULL;
    tmp1->next = NULL;
    nhead->next = tmp1;
    listdag.push_back(nhead); // list�ĳ�Ա����push_back()��һ������ŵ�һ��list�ĺ���
   break;
   case 1:
   tmp1->sign = fhead->data1;
   tmp1->var = "";
   tmp1->flag = 0;
   tmp1->lchild = NULL;
   tmp1->rchild = NULL;
   tmp1->next = NULL;
   tmpResult->sign = fhead->result;
   tmpResult->var = fhead->op;
   tmpResult->flag = 0;
   tmpResult->lchild = tmp1;
   tmpResult->rchild = NULL;
   tmpResult->next = tmp1;
   nhead->next = tmpResult;
   listdag.push_back(nhead);
   break;
   case 2:
        tmp2->sign = fhead->data2;
        tmp2->var = "";
        tmp2->flag = 0;
        tmp2->lchild = NULL;
        tmp2->rchild = NULL;
        tmp2->next = NULL;
        tmp1->sign = fhead->data1;
        tmp1->var = "";
        tmp1->flag = 0;
        tmp1->lchild = NULL;
        tmp1->rchild = NULL;
        tmp1->next = tmp2;
        tmpResult->sign = fhead->result;
        tmpResult->var = fhead->op;
        tmpResult->flag = 0;
        tmpResult->lchild = tmp1;
        tmpResult->rchild = tmp2;
        tmpResult->next = tmp1;
        nhead->next = tmpResult;
        listdag.push_back(nhead);
        break;
        default:
   cout<<"���������Ԫʽ����0�͡�1�ͻ���2�͵ģ����������������͵���Ԫʽ��"<<endl;
   }
  }
}
void node_build()  // ����DAG���
{  dagnode *nhead_up = new dagnode;
   nhead_up->next = NULL;
   nhead_up->lchild = NULL;
   nhead_up->rchild = NULL;
   dagnode *nhead_down = new dagnode;
   nhead_down->next = NULL;
   nhead_down->lchild = NULL;
   nhead_down->rchild = NULL;
   std::list<dagnode*>::iterator iter1,iter2,iter3;

   if(!listdag.empty())//������
    {
  for(iter1 = listdag.begin(),iter3 = (--listdag.end()); iter1 != iter3; --iter3) //������ͷ����ʼɨ��
  {    nhead_down = (*iter3)->next;
  while(nhead_down != NULL)
   {
    iter2 = listdag.begin();
     while(iter3 != iter2)  //��������һ����㿪ʼɨ��
    {
     nhead_up = (*iter2)->next;
      while(nhead_up != NULL)
    {
        if(nhead_up->sign == nhead_down->sign || nhead_up->var == nhead_down->sign)
    {
        nhead_up->var = nhead_down->var;
      nhead_down->flag = 1;
       nhead_up->lchild = nhead_down->lchild;
            nhead_up->rchild = nhead_down->rchild;
              }
    nhead_up = nhead_up->next;
     }
      ++iter2;
       }
        nhead_down = nhead_down->next;
    }
    }
    }
    }
void paint_node(dagnode *node)// ����DAG���
{  string Tsign,Tvar;
Tsign = node->sign;
 if(node->var != "")
 {
    cout<<" "<<node->var<<"\t";
 }
 if(node->lchild != NULL)
 {
    cout<<" "<<node->lchild->sign<<"\t";
 }
 if(node->rchild != NULL)
 {
    cout<<" "<<node->rchild->sign<<"\t";
 }
else
{
    cout<<"  ���";
}
    cout<<""<<Tsign<<"\t\t";
    cout<<endl;
    node->flag = 2;
}
void paint(dagnode *node)  // ����DAGͼ
{  paint_node(node);
 if(node->lchild != NULL)
    paint(node->lchild);
 if(node->rchild != NULL)
    paint(node->rchild);
 else
return;
}
void paint_gap(dagnode *node) // ����DAGͼ�ķָ�����
{
    if(node->lchild != NULL)
        paint(node->lchild);
    if(node->rchild != NULL)
        paint(node->rchild);
    else
        return;
    }

int main(int datac, char* datav[ ])
{
    do_input();
    four();
    list_build();
    node_build();
    std::list<dagnode*>::iterator iter, iter_end;
    iter = listdag.begin();
    iter_end = listdag.end();
    if(listdag.empty())
{
    cout<<"����Ϊ�գ�"<<endl;
    return 0;
}
    else
    nhead = (*iter)->next;
    cout<<"�Ż������Ԫʽ����Ϊ��"<<endl;
    paint(nhead);  //����DAGͼ
    for(; iter != iter_end; iter++)
{
    nhead = (*iter)->next;
    if(nhead->flag != 1 && nhead->flag != 2)
 {
    paint_gap(nhead);
 }
}
    return 0;
}


#endif // OPTIMIZE_H_INCLUDED
