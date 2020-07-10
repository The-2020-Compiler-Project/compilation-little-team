#ifndef TYPELIST_H_INCLUDED
#define TYPELIST_H_INCLUDED

class TypeList
{
public:
    void setTypeNode(char NewType,void *NewAddr);//
    char getType();
private:
    char Type;
    void *Addr;// 是否需要新建结构体类（包含结构体和数组的）
};
void TypeList::setTypeNode(char NewType,void *NewAddr)
{
    Type=NewType;
    if(Type=='I'||Type=='R'||Type=='C'||Type=='B')
        Addr=0;
    else
        ;//若需要使用结构体和数组 必须进行修改
}
char TypeList::getType()
{
    return Type;
}

#endif // TYPELIST_H_INCLUDED
