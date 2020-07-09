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
 string op;     // 操作符
 string data1;     // 第一个操作数
 string data2;     // 第二个操作数
 string result;     // 结果
 int stylenum;    // 结点类型
 struct Four *next;   // 指向下一条语句的起始位置
 struct Four *last;
 };   // 指向上一条语句的起始位置      };
struct dagnode{
 string sign;     // 标识符
 string var;     // 副标识符
 int flag;      // 标记位
 struct dagnode *lchild;  // 指向孩子的指针
 struct dagnode *rchild;  // 指向右孩子的指针
 struct dagnode *next;
 }; // 指向下一个结点
Four *fhead;
dagnode *nhead;
std::list<dagnode*> listdag;
vector<string> inputs;

void do_input()
{
//测试用例
 inputs.push_back(" ,3.14, ,T0");
 inputs.push_back("*,2,T0,T1");
}
void four() // 建立四元式的结构
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
  if(!pp)  //内存分配失败
  {
    cout<<"Memory allocation failed!"<<endl;
    return;
  }
  //四元式
   char op[10]={0};
   char data1[10]={0};
   char data2[10]={0};
   char result[10]={0};
    sscanf(inputs[i].c_str(),"%[^,],%[^,],%[^,],%[^\n]", op,data1,data2,result);
//sscanf()-从一个字符串中读进与指定格式相符的数据
  pp->op=op;
  pp->data1=data1;
  pp->data2=data2;
  pp->result=result;
  if(pp->data2 == " ")
  if(pp->op == " ")
   //第二个操作数为空,并且操作符为空，则为0型四元式
    pp->stylenum=0;
    else
   //第二个操作数为空,并且操作符不空，则为1型四元式
    pp->stylenum=1;
    else
   //第二个操作数不为空，则为2型四元式
    pp->stylenum=2;
    fourTmp = pp;
}
    fhead = fourTmp;
}
void list_build() // 建立链表进行优化
{
     for(int i = 1; fhead->last != NULL; fhead = fhead->last) //从最后一个四元式开始构造链表
 {
     //分配内存初始化
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
switch(fhead->stylenum)//分类型处理
{
    case 0:
    tmp1->sign = fhead->result;
    tmp1->var = fhead->data1;
    tmp1->flag = 0;
    tmp1->lchild = NULL;
    tmp1->rchild = NULL;
    tmp1->next = NULL;
    nhead->next = tmp1;
    listdag.push_back(nhead); // list的成员函数push_back()把一个对象放到一个list的后面
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
   cout<<"您输入的四元式不是0型、1型或者2型的，请输入这三种类型的四元式："<<endl;
   }
  }
}
void node_build()  // 建立DAG结点
{  dagnode *nhead_up = new dagnode;
   nhead_up->next = NULL;
   nhead_up->lchild = NULL;
   nhead_up->rchild = NULL;
   dagnode *nhead_down = new dagnode;
   nhead_down->next = NULL;
   nhead_down->lchild = NULL;
   nhead_down->rchild = NULL;
   std::list<dagnode*>::iterator iter1,iter2,iter3;

   if(!listdag.empty())//链表不空
    {
  for(iter1 = listdag.begin(),iter3 = (--listdag.end()); iter1 != iter3; --iter3) //从链表头部开始扫描
  {    nhead_down = (*iter3)->next;
  while(nhead_down != NULL)
   {
    iter2 = listdag.begin();
     while(iter3 != iter2)  //从链表下一个结点开始扫描
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
void paint_node(dagnode *node)// 画出DAG结点
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
    cout<<"  结点";
}
    cout<<""<<Tsign<<"\t\t";
    cout<<endl;
    node->flag = 2;
}
void paint(dagnode *node)  // 绘制DAG图
{  paint_node(node);
 if(node->lchild != NULL)
    paint(node->lchild);
 if(node->rchild != NULL)
    paint(node->rchild);
 else
return;
}
void paint_gap(dagnode *node) // 绘制DAG图的分隔部分
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
    cout<<"链表为空！"<<endl;
    return 0;
}
    else
    nhead = (*iter)->next;
    cout<<"优化后的四元式序列为："<<endl;
    paint(nhead);  //画出DAG图
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
