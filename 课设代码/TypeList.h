#ifndef TYPELIST_H_INCLUDED
#define TYPELIST_H_INCLUDED

class TypeList
{
public:
    void setTypeNode(char NewType,void *NewAddr);//
    char getType();
private:
    char Type;
    void *Addr;// �Ƿ���Ҫ�½��ṹ���ࣨ�����ṹ�������ģ�
};
void TypeList::setTypeNode(char NewType,void *NewAddr)
{
    Type=NewType;
    if(Type=='I'||Type=='R'||Type=='C'||Type=='B')
        Addr=0;
    else
        ;//����Ҫʹ�ýṹ������� ��������޸�
}
char TypeList::getType()
{
    return Type;
}

#endif // TYPELIST_H_INCLUDED
