#ifndef FINALSTEP_H_INCLUDED
#define FINALSTEP_H_INCLUDED
/*  首先申请空间（数据段） 需要顺便把符号表填了
    segment dseg
    读符号表 int：
             char：
             real：
             bool：
    声明堆栈段（可忽略）
    代码段 首先翻译主程序
cseg：start： ……
              end
    翻译其他程序
      proc    name
              endp
      end starts*/
/*  翻译算法方面
    return 语句 翻译为 ST FUCNAMEVAL
    加减乘除 见ppt
    赋值语句 见ppt
    条件语句 见ppt
    循环语句 见ppt
    tips:
    把函数的调用也当作基本块结束的标志 （保存寄存器内的数据）
    接口格式为：
    MainList.txt
    格式为
    main
    dfs //包含所有函数的名字和所有全局变量的总表
    fucname.txt //此处的文件名为任意函数名
    格式为
    main itp f
    a    itp v //变量 参数表和变量名都包含在变量表内所以可以不用给出
    +,3,3,t1
    +,2,t1,t2//四元式
    */
string numtostring(int num)
{
    string a;
    int k=100000;
    int yushu;
    int shan;
    for(int i=0;k!=1;i++)
    {
        shan=num/k;
        num-=k*shan;
        if(shan!=0)
        {
            a+=(char)(shan+48);
        }
        k/=10;
    }
    a+=char(num+48);
    return a;
}
class symbolList
{
public:
    symbolList();
    void setIsActive();
    void addglobalvar(string newId,char newChar,Cat newCat);
    void addSymbol(string newId,char newChar,Cat newCat);
    void reclear();
    void showSymbolList();
    int getsize();
    int getIsActive(string obj,int type,int q);
    char gettype(string obj);
    void setbytype();
private:
    string Id[200];
    char type[200];
    Cat aCat[200];
    int isActive[200];
    int globalvarNum;
    int symbolListLength;
};
void symbolList::setbytype()
{
    for(int i=0;i<symbolListLength;i++)
    {
        if(aCat[i]==n)
        {
            isActive[i]=-1;
        }
        else
        {
            isActive[i]=-2;
        }
    }
}
void symbolList::addglobalvar(string newId,char newChar,Cat newCat)
{
    Id[globalvarNum]=newId;
    type[globalvarNum]=newChar;
    aCat[globalvarNum]=newCat;
    isActive[globalvarNum]=-2;
    globalvarNum++;
    symbolListLength++;
}
void symbolList::showSymbolList()
{
    for(int i=0;i<symbolListLength;i++)
    {
        cout<<Id[i]<<' '<<type[i]<<' '<<aCat[i]<<' '<<isActive[i]<<endl;
    }
}
char symbolList::gettype(string obj)
{
    for(int i=0;i<symbolListLength;i++)
    {
        if(Id[i]==obj)
            return type[i];
    }
}
void symbolList::addSymbol(string newId,char newChar,Cat newCat)
{
    Id[symbolListLength]=newId;
    type[symbolListLength]=newChar;
    aCat[symbolListLength]=newCat;
    if(newCat==n)
    {
        isActive[symbolListLength]=-1;
    }
    else
    {
        isActive[symbolListLength]=-2;
    }
    symbolListLength++;
}
void symbolList::reclear()
{
    for(int i=0;i<symbolListLength;i++)
    {
        Id[i].clear();
        type[i]='0';
        aCat[i]=n;
        isActive[i]=-1;
    }
    symbolListLength=globalvarNum;
}
symbolList::symbolList()
{
    symbolListLength=0;
}
int symbolList::getIsActive(string obj,int type,int q)
{
    for(int i=0;i<symbolListLength;i++)
    {
        if(Id[i]==obj)
        {
            int temp=isActive[i];
            if(type==0)
            {
                isActive[i]=q;
            }
            else
            {
                isActive[i]=-1;
            }
            return temp;
        }
    }
    return -3;
}
class RDL
{
public:
    RDL();
    string getdata(int i);
    int locr(string object);
    int getAvailable();
    int getAvailableNum();
    int getRegNum();
    int getisactive(int i);
    void setReg(string object,int isActive,int i);
    void clearReg(string obj);
    void showReg();
private:
    int regNum;
    string REG[4];
    int isactive[4];
};
int RDL::getisactive(int i)
{
    return isactive[i];
}
RDL::RDL()
{
    regNum=4;
}
void RDL::showReg()
{
    for(int i=0;i<regNum;i++)
    {
        if(REG[i].size()!=0)
            cout<<"Reg"<<i<<":"<<REG[i]<<endl;
        else
            cout<<"Reg"<<i<<":NULL"<<endl;
    }
}
int RDL::getRegNum()
{
    return regNum;
}
int RDL::getAvailableNum()
{
    int sum=0;
    for(int i=0;i<regNum;i++)
    {
        if(REG[i].size()==0)
            sum++;
    }
    return sum;
}
int RDL::getAvailable()
{
    for(int i=0;i<regNum;i++)
    {
        if(REG[i].size()==0)
            return i;
    }
    return -1;
}
string RDL::getdata(int i)
{
    if(i<regNum)
        return REG[i];
    else
        cout<<"error"<<endl;
}
int RDL::locr(string object)
{
    for(int i=0;i<regNum;i++)
    {
        if(REG[i]==object)
            return i;
    }
    return -1;
}
void RDL::setReg(string object,int isActive,int i)
{
    if(locr(object)!=-1)
    {
        isactive[locr(object)]=-1;
        REG[locr(object)].clear();
    }
    if(i<=regNum)
    {
        REG[i]=object;
        isactive[i]=isActive;
    }
    else
        cout<<"error"<<endl;
}
void RDL::clearReg(string obj)
{
    for(int i=0;i<regNum;i++)
    {
        if(obj==REG[i])
        {
            REG[i].clear();
        }
    }
}
class finalstep
{
public:
    finalstep();
    bool getSeg();//获取一段基本块 若遇到while for dowhile if else return则结束获取 bool型是因为需要确认是否取到下个代码段
    void transSeg();//转换基本块内四元式为目标代码。
    void mainControl();
    //主要函数
    void setIsActive();//生成活跃信息
    bool getNext();//获取下一个四元式 并判断是否为基本块末尾 返回是（1）或不是（0）。
    bool transfuc();//获取下一个函数的变量和所有四元式
    void transCode();//处理当前四元式并生成目标代码
    void addToObj(string a,string b,string c,string d);
    void storeAll();
    void showobj();
    void showvar();
    void showfourac();
    void showseg();
    void fileoutput();
    void update();
    void popstack();
    //辅助函数
    void returnSentence();
    void setVarSentence();
    void ifSentence();
    void elseSentence();
    void ieSentence();
    void whileSentence();
    void doSentence();
    void weSentence();
    void addSentence();
    void subSentence();
    void mulSentence();
    void divSentence();
    void grtSentence();
    void letSentence();
    void greSentence();//>=
    void leeSentence();//<=
    void equSentence();//==
    void andSentence();//&&
    void orSentence();//||
    //对不同语句的转化函数
private:
    int pointer;
    int objpointer;
    int midpointer;
    int vsn;
    int fournum;
    int sem[100][2];
    int semtop;
    int isActive[1000][4];
    char vartype[100];
    int stepcheck;
    int fucvarnum;
    symbolList sList;
    RDL rList;
    string fucname;
    string regname[4];
    string four[1000][4];
    string obj[1000][4];
    string varstored[100];
    string fucvar[100];
    ifstream Midcode;
    ofstream finalcode;
    //符号表 symbollist id，类型，种类，活跃信息
    //寄存器描述表 rdl 寄存器状态，
    //寻址函数 locr 若在寄存器内未找到 则在内存中
};
void finalstep::popstack()
{
    for(int i=fucvarnum-1;i>=0;i--)
    {
        addToObj("POP",fucvar[i],"","");
        fucvarnum--;
    }
}
void finalstep::update()
{
    for(int i=0;i<4;i++)
    {
        if(rList.locr(four[pointer][i])!=-1)
        {
            rList.setReg(four[pointer][i],isActive[pointer][i],rList.locr(four[pointer][i]));
        }
    }
}
void finalstep::fileoutput()
{
    finalcode.open("FinalCode.txt",ios::binary);
    finalcode<<"SEGMENT DSEG"<<endl;
    string s[vsn];
    char st[vsn];
    int sp=0;
    int k;
    for(int i=0;i<vsn;i++)
    {
        k=1;
        for(int j=0;j<vsn;j++)
        {
            if(varstored[i]==s[j])
            {
                k=0;
                break;
            }
        }
        if(k)
        {
            s[sp]=varstored[i];
            st[sp]=vartype[i];
            sp++;
        }
    }
    for(int i=0;i<sp;i++)
    {

        finalcode<<s[i]<<' ';
        finalcode<<"DB 4 DUP(0)"<<endl;
    }
    for(int i=0;i<objpointer;i++)
    {
        finalcode<<obj[i][0]<<' '<<obj[i][1]<<' '<<obj[i][2]<<' '<<obj[i][3]<<endl;
    }
    finalcode.close();
}
void finalstep::showseg()
{
    for(int i=pointer;i<midpointer;i++)
    {
        cout<<i<<' '<<four[i][0]<<' '<<four[i][1]<<' '<<four[i][2]<<' '<<four[i][3]<<endl;
    }
}
bool finalstep::transfuc()
{
    fucvarnum=0;
    for(int i=0;i<100;i++)
    {
        fucvar[i].clear();
    }
    for(int i=0;i<fournum;i++)
    {
        four[i][0].clear();
        four[i][1].clear();
        four[i][2].clear();
        four[i][3].clear();
    }
    fournum=0;
    midpointer=pointer=0;
    string var[4];
    int fn=0;
    while(1)
    {
        Midcode>>var[0];
        if(var[0]=="code")
        {
            break;
        }
        if(fn==1)
        {
            fucvar[fucvarnum]=var[0];
            varstored[vsn]=var[0];
            vsn++;
            fucvarnum++;
            addToObj("PUSH",var[0],"","");
        }
        if(fn==0)
        {
            fucname=var[0];
            if(fucname=="main")
            {
                addToObj("START:","MOV","AX","DS");
                addToObj("MOV","DS","AX","");
                fn=2;
            }
            else
            {
                addToObj(var[0],"PROC","","");
                fn=1;
            }
        }
        Midcode>>var[1]>>var[2];
        sList.addSymbol(var[0],var[1][0],v);
    }
    while(1)
    {
        Midcode>>var[0];
        if(Midcode.eof())
        {
            return 0;
        }
        else if(var[0]=="Fuc:")
        {
            return 1;
        }
        Midcode>>var[1]>>var[2]>>var[3];
        four[fournum][0]=var[0];
        four[fournum][1]=var[1];
        four[fournum][2]=var[2];
        four[fournum][3]=var[3];
        fournum++;
    }
}
bool finalstep::getSeg()
{
    if(pointer==fournum)
    {
        return 0;
    }
    for(int i=midpointer;i<fournum;i++)
    {
        if(four[i][0]=="if"||four[i][0]=="el"||four[i][0]=="do"||four[i][0]=="we")
        {
            midpointer++;
            return 1;
        }
        midpointer++;
    }
}
void finalstep::showfourac()
{
    for(int i=0;i<fournum;i++)
    {
        cout<<i<<' ';
        cout<<four[i][0]<<',';
        cout<<four[i][1];
        if(four[i][1]!="_")
        {
            cout<<'(';
            if(isActive[i][1]<0)
            {
                if(isActive[i][1]==-1)
                {
                    cout<<'n';
                }
                else
                {
                    cout<<'y';
                }
            }
            else
                cout<<isActive[i][1];
            cout<<"),";
        }
        else
            cout<<',';
        cout<<four[i][2];
        if(four[i][2]!="_")
        {
            cout<<'(';
            if(isActive[i][2]<0)
            {
                if(isActive[i][2]==-1)
                {
                    cout<<'n';
                }
                else
                {
                    cout<<'y';
                }
            }
            else
                cout<<isActive[i][2];
            cout<<"),";
        }
        else
            cout<<',';
        cout<<four[i][3];
        if(four[i][3]!="_")
        {
            cout<<'(';
            if(isActive[i][3]<0)
            {
                if(isActive[i][3]==-1)
                {
                    cout<<'n';
                }
                else
                {
                    cout<<'y';
                }
            }
            else
                cout<<isActive[i][3];
            cout<<")."<<endl;
        }
        else
            cout<<'.'<<endl;
    }
}
void finalstep::setIsActive()
{
    sList.setbytype();
    for(int i=midpointer-1;i>=pointer;i--)
    {
        int k;
        k=sList.getIsActive(four[i][1],0,i);
        if(k!=-3)
            isActive[i][1]=k;
        else if(four[i][1].at(0)=='t')
        {
            sList.addSymbol(four[i][1],'I',n);
            k=sList.getIsActive(four[i][1],0,i);
            isActive[i][1]=k;
        }
        k=sList.getIsActive(four[i][2],0,i);
        if(k!=-3)
            isActive[i][2]=k;
        else if(four[i][2].at(0)=='t')
        {
            sList.addSymbol(four[i][2],'I',n);
            k=sList.getIsActive(four[i][2],0,i);
            isActive[i][2]=k;
        }
        k=sList.getIsActive(four[i][3],1,i);
        if(k!=-3)
            isActive[i][3]=k;
        else if(four[i][3].at(0)=='t')
        {
            sList.addSymbol(four[i][3],'I',n);
            k=sList.getIsActive(four[i][3],0,i);
            isActive[i][3]=k;
        }
    }
}
void finalstep::showvar()
{
    cout<<"SEGMENT DSEG"<<endl;
    string s[vsn];
    char st[vsn];
    bool k=1;
    int sp=0;
    for(int i=0;i<vsn;i++)
    {
        k=1;
        for(int j=0;j<vsn;j++)
        {
            if(varstored[i]==s[j])
            {
                k=0;
                break;
            }
        }
        if(k)
        {
            s[sp]=varstored[i];
            st[sp]=vartype[i];
            sp++;
        }
    }
    for(int i=0;i<sp;i++)
    {

        cout<<s[i]<<' ';
        cout<<"DB 4 DUP(0)"<<endl;
    }
    cout<<"END DSEG"<<endl;
}
void finalstep::returnSentence()
{
    storeAll();
    //cout<<"RETP"<<endl;
    if(fucname=="main")
    {
        addToObj("MOV","AX","004CH","");
        addToObj("INT","21H","","");
    }
    else
    {
        popstack();
        addToObj("RETP","","","");
    }
}
bool finalstep::getNext()
{
    if(pointer<midpointer)
    {
        pointer++;
        return 1;
    }
    return 0;
}
void finalstep::showobj()
{
    for(int i=0;i<objpointer;i++)
    {
        cout<<i<<' ';
        cout<<obj[i][0]<<' '<<obj[i][1]<<' '<<obj[i][2]<<' '<<obj[i][3]<<endl;
    }
}
finalstep::finalstep()
{
    pointer=0;
    vsn=0;
    objpointer=0;
    semtop=0;
    stepcheck=1;
    regname[0]="AX";
    regname[1]="BX";
    regname[2]="CX";
    regname[3]="DX";
}
void finalstep::addToObj(string a,string b,string c,string d)
{
    obj[objpointer][0]=a;
    obj[objpointer][1]=b;
    obj[objpointer][2]=c;
    obj[objpointer][3]=d;
    objpointer++;
}
void finalstep::mainControl()
{
    string kkk;
    Midcode.open("MTO.txt",ios::binary);
    getline(Midcode,kkk);
    string var[4];
    bool k=0;
    while(1)
    {
        Midcode>>var[0];
        if(var[0]=="Fuc:")
        {
            break;
        }
        Midcode>>var[1]>>var[2];
        sList.addglobalvar(var[0],var[1][0],v);
    }
    addToObj("SEGMENT","CSEG","","");
    addToObj("ASSUME","DS:DSEG,CS:CSEG","","");
    while(transfuc())
    {
        pointer=0;
        midpointer=0;
        while(getSeg())
        {
            setIsActive();
            transCode();
            update();
            while(getNext())
            {
                transCode();
                update();
            }
        }
        storeAll();
        if(fucname!="main")
        {
            popstack();
            addToObj(fucname,"ENDP","","");
        }
    }
    pointer=0;
    midpointer=0;
    while(getSeg())
    {
        setIsActive();
        transCode();
        update();
        while(getNext())
        {
            transCode();
            update();
        }
    }
    storeAll();
    if(fucname!="main")
        {
            popstack();
            addToObj(fucname,"ENDP","","");
        }
    addToObj("CSEG","ENDS","","");
    addToObj("END","START","","");
    showvar();
    showobj();
    fileoutput();
}
void finalstep::transCode()
{
    if(stepcheck==pointer)
    {
        pointer++;
    }
    if(four[pointer][0]=="+")
    {
        addSentence();
    }
    else if(four[pointer][0]=="-")
    {
        subSentence();
    }
    else if(four[pointer][0]=="*")
    {
        mulSentence();
    }
    else if(four[pointer][0]=="/")
    {
        divSentence();
    }
    else if(four[pointer][0]=="=")
    {
        setVarSentence();
    }
    else if(four[pointer][0]==">=")
    {
        greSentence();
    }
    else if(four[pointer][0]=="<=")
    {
        leeSentence();
    }
    else if(four[pointer][0]=="<")
    {
        letSentence();
    }
    else if(four[pointer][0]==">")
    {
        grtSentence();
    }
    else if(four[pointer][0]=="wh")
    {
        whileSentence();
    }
    else if(four[pointer][0]=="we")
    {
        weSentence();
    }
    else if(four[pointer][0]=="do")
    {
        doSentence();
    }
    else if(four[pointer][0]=="if")
    {
        ifSentence();
    }
    else if(four[pointer][0]=="el")
    {
        elseSentence();
    }
    else if(four[pointer][0]=="ie")
    {
        ieSentence();
    }
    else if(four[pointer][0]=="return")
    {
        returnSentence();
    }
    stepcheck=pointer;
}
void finalstep::whileSentence()
{
    sem[semtop][0]=objpointer;
    sem[semtop][1]=1;//压栈
    semtop++;
}
void finalstep::doSentence()
{
    if(rList.locr(four[pointer][1])!=-1)//若找到了if的参数
    {
        int k=rList.locr(four[pointer][1]);
        if(sList.getIsActive(four[pointer][1],0,pointer)!=-1)
        {
            //cout<<"ST "<<regname[k]<<",B"<<endl;
            addToObj("ST",regname[k],","+four[pointer][1]," ");
        }
        //cout<<"FJ "<<regname[k]<<",_"<<endl;
        addToObj("CMP",regname[k],",0","");
        addToObj("JNZ","","","");
        sem[semtop][0]=objpointer-1;
        sem[semtop][1]=2;
        semtop++;
        //以它为参数进行语句转换 把代填地址压入语义栈
    }
    else if(rList.getAvailableNum()!=0)//若找不到if的参数但是有可用的寄存器 则LD到寄存器总并执行第一步操作
    {
        int k=rList.getAvailable();
        //cout<<"LD "<<regname[k]<<",B"<<endl;
        addToObj("MOV",regname[k],","+four[pointer][1],"");
        rList.setReg(four[pointer][1],isActive[pointer][1],k);
        //cout<<"FJ "<<regname[k]<<",_"<<endl;
        addToObj("CMP",regname[k],",0","");
        addToObj("JNZ","","","");
        sem[semtop][0]=objpointer-1;
        sem[semtop][1]=2;
        semtop++;
    }
    else//找不到参数也没有可用的寄存器
    {
        storeAll();
        int k=rList.getAvailable();
        //cout<<"LD "<<regname[k]<<",B"<<endl;
        addToObj("MOV",regname[k],","+four[pointer][1]," ");
        rList.setReg(four[pointer][1],isActive[pointer][1],k);
        //cout<<"FJ "<<regname[k]<<",_"<<endl;
        addToObj("CMP",regname[k],",0","");
        addToObj("JNZ","","","");
        sem[semtop][0]=objpointer-1;
        sem[semtop][1]=2;
        semtop++;
        //把寄存器内全部变量存入储存空间
        //执行上一个可能的操作即可
    }
}
void finalstep::weSentence()
{
    storeAll();
    string k;
    k=numtostring(objpointer+1);
    //k+=(char)objpointer+49;
    obj[sem[semtop-1][0]][sem[semtop-1][1]]=k;
    semtop--;
    k.clear();
    k=numtostring(sem[semtop-1][0]);
    semtop--;
    addToObj("JMP",k,"","");
}
void finalstep::setVarSentence()
{
    rList.clearReg(four[pointer][3]);
    if(rList.locr(four[pointer][1])!=-1)
    {
        cout<<four[pointer][1]<<':'<<sList.getIsActive(four[pointer][1],0,pointer)<<endl;
        if(sList.getIsActive(four[pointer][1],0,pointer)!=-1)
        {
            addToObj("ST",regname[rList.locr(four[pointer][1])],four[pointer][1],"");
            //cout<<"ST "<<regname[rList.getAvailable()]<<",B"<<endl;
            varstored[vsn]=four[pointer][1];
            vsn++;
        }
        rList.setReg(four[pointer][3],isActive[pointer][3],rList.locr(four[pointer][1]));
    }
    else if(rList.getAvailableNum()!=0)
    {
        int k=rList.getAvailable();
        addToObj("MOV",regname[rList.getAvailable()],","+four[pointer][1],"");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);
        //cout<<"LD "<<regname[rList.getAvailable()]<<",B"<<endl;
    }
    else
    {
        storeAll();
        //cout<<"LD "<<regname[rList.getAvailable()]<<",B"<<endl;
        int k=rList.getAvailable();
        addToObj("MOV",regname[rList.getAvailable()],","+four[pointer][1]," ");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);
    }
}
void finalstep::ifSentence()//if指令转化
{
    /*
    CMP [1],0
    JNZ K
    */
    if(rList.getAvailableNum()<2)
    {
        storeAll();
        int k=rList.getAvailable();
        int u=rList.getAvailable();
        //cout<<"LD "<<regname[k]<<",B"<<endl;
        addToObj("MOV",regname[k],","+four[pointer][1]," ");
        //cout<<"FJ "<<regname[k]<<",_"<<endl;
        addToObj("MOV",regname[u],",0","");
        addToObj("ADD",regname[u]+",","","");
        sem[semtop][0]=objpointer-1;
        sem[semtop][1]=2;
        semtop++;
        addToObj("CMP",regname[k],",0","");
        addToObj("JNZ","","","");
    }
    else if(rList.locr(four[pointer][1])!=-1)//若找到了if的参数
    {
        int k=rList.locr(four[pointer][1]);
        int u=rList.getAvailable();
        if(sList.getIsActive(four[pointer][1],0,pointer)!=-1)
        {
            //cout<<"ST "<<regname[k]<<",B"<<endl;
            addToObj("ST",regname[k],","+four[pointer][1]," ");
        }
        //cout<<"FJ "<<regname[k]<<",_"<<endl;
        addToObj("MOV",regname[u],",0","");
        addToObj("ADD",regname[u]+",","","");
        sem[semtop][0]=objpointer-1;
        sem[semtop][1]=2;
        semtop++;
        addToObj("CMP",regname[k],",0","");
        addToObj("JNZ",regname[u],"","");
        //以它为参数进行语句转换 把代填地址压入语义栈
    }
    else if(rList.getAvailableNum()!=0)//若找不到if的参数但是有可用的寄存器 则LD到寄存器总并执行第一步操作
    {
        int k=rList.getAvailable();
        int u=rList.getAvailable();
        //cout<<"LD "<<regname[k]<<",B"<<endl;
        addToObj("MOV",regname[k],","+four[pointer][1]," ");
        //cout<<"FJ "<<regname[k]<<",_"<<endl;
        addToObj("MOV",regname[u],",0","");
        addToObj("ADD",regname[u]+",","","");
        sem[semtop][0]=objpointer-1;
        sem[semtop][1]=2;
        semtop++;
        addToObj("CMP",regname[k],",0","");
        addToObj("JNZ","","","");
    }
    else//找不到参数也没有可用的寄存器
    {
        storeAll();
        int k=rList.getAvailable();
        int u=rList.getAvailable();
        //cout<<"LD "<<regname[k]<<",B"<<endl;
        addToObj("MOV",regname[k],","+four[pointer][1]," ");
        //cout<<"FJ "<<regname[k]<<",_"<<endl;
        addToObj("MOV",regname[u],",0","");
        addToObj("ADD",regname[u]+",","","");
        sem[semtop][0]=objpointer-1;
        sem[semtop][1]=2;
        semtop++;
        addToObj("CMP",regname[k],",0","");
        addToObj("JNZ","","","");
        //把寄存器内全部变量存入储存空间
        //执行上一个可能的操作即可
    }
    storeAll();
}
void finalstep::elseSentence()
{
    storeAll();
    int u=rList.getAvailable();
    addToObj("MOV",regname[u],",0","");
    addToObj("ADD",regname[u]+",","","");
    string k;
    k=numtostring(objpointer+1);
    obj[sem[semtop-1][0]][sem[semtop-1][1]]=k;
    semtop--;
    sem[semtop][0]=objpointer-1;
    sem[semtop][1]=2;
    semtop++;
    //cout<<"JMP "<<endl;
    addToObj("JMP",regname[u],"","");
}
void finalstep::ieSentence()
{
    storeAll();
    string k;
    k=numtostring(objpointer);
    obj[sem[semtop-1][0]][sem[semtop-1][1]]=k;
    semtop--;
}
void finalstep::storeAll()
{
    string a;
    update();
    for(int i=0;i<rList.getRegNum();i++)
    {
        a=rList.getdata(i);
        if(a.size()!=0&&rList.getisactive(i)!=-1)
        {
            //cout<<"MOV "<<regname[i]<<','<<a<<endl;
            addToObj("ST",regname[i],","+rList.getdata(i),"");
            varstored[vsn]=rList.getdata(i);
            vartype[vsn]=sList.gettype(a);
            vsn++;
        }
        rList.clearReg(a);
    }
}
void finalstep::addSentence()
{
    if(rList.locr(four[pointer][3])!=-1)
    {
        int k=rList.locr(four[pointer][0]);
        addToObj("MOV",regname[k],","+four[pointer][1]," ");//将第一个参数存入
        addToObj("ADD",regname[k],","+four[pointer][2],"");//加法命令
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][1])!=-1)//若参数在寄存器中
    {
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][1])],","+four[pointer][1],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        //cout<<"ADD "<<regname[rList.locr("b")]<<",C"<<endl;
        addToObj("ADD",regname[rList.locr(four[pointer][1])],","+four[pointer][2],"");//加法命令
        rList.setReg(four[pointer][3],isActive[pointer][3],rList.locr(four[pointer][1]));//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][2])!=-1)//第二个参数在寄存器中 同理
    {
        if(isActive[pointer][2]!=-1)//若活跃
        {
            //cout<<"ST "<<regname[rList.locr("c")]<<",c"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][2])],","+four[pointer][2],"");
            varstored[vsn]=four[pointer][2];
            vsn++;//保存
        }
        //cout<<"ADD "<<regname[rList.locr("c")]<<",B"<<endl;
        addToObj("ADD",regname[rList.locr(four[pointer][2])],","+four[pointer][1],"");
        rList.setReg(four[pointer][3],isActive[pointer][3],rList.locr(four[pointer][2]));//加法和保存 改变寄存器内容
    }
    else if(rList.getAvailableNum()!=0)//若还有未使用的寄存器
    {
        int k=rList.getAvailable();//取得该寄存器的位置
        //cout<<"LD "<<regname[k]<<",B"<<endl;
        addToObj("MOV",regname[k],","+four[pointer][1]," ");//将第一个参数存入
        //cout<<"ADD "<<regname[k]<<",C"<<endl;
        addToObj("ADD",regname[k],","+four[pointer][2]," ");//加上第二个参数
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//寄存器设为结果变量
    }
    else//若没有未使用的寄存器
    {
        storeAll();//保存所有寄存器中的变量 然后执行有可用寄存器时的操作
        int k=rList.getAvailable();
        //cout<<"LD "<<regname[k]<<",B"<<endl;
        addToObj("MOV",regname[k],","+four[pointer][1]," ");
        //cout<<"ADD "<<regname[k]<<",C"<<endl;
        addToObj("ADD",regname[k],","+four[pointer][2]," ");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);
    }
}
void finalstep::subSentence()
{
    if(rList.locr(four[pointer][3])!=-1)
    {
        int k=rList.locr(four[pointer][0]);
        addToObj("MOV",regname[k],","+four[pointer][1]," ");//将第一个参数存入
        addToObj("SUB",regname[k],","+four[pointer][2],"");//加法命令
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][1])!=-1)//若参数在寄存器中
    {
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][1])],","+four[pointer][1],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        //cout<<"ADD "<<regname[rList.locr("b")]<<",C"<<endl;
        addToObj("SUB",regname[rList.locr(four[pointer][1])],","+four[pointer][2],"");//加法命令
        rList.setReg(four[pointer][3],isActive[pointer][3],rList.locr(four[pointer][1]));//将寄存器内储存的内容换为结果变量
    }
    else if(rList.getAvailableNum()!=0)//若还有未使用的寄存器
    {
        int k=rList.getAvailable();//取得该寄存器的位置
        //cout<<"LD "<<regname[k]<<",B"<<endl;
        addToObj("MOV",regname[k],","+four[pointer][1]," ");//将第一个参数存入
        //cout<<"ADD "<<regname[k]<<",C"<<endl;
        addToObj("SUB",regname[k],","+four[pointer][2]," ");//加上第二个参数
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//寄存器设为结果变量
    }
    else//若没有未使用的寄存器
    {
        storeAll();//保存所有寄存器中的变量 然后执行有可用寄存器时的操作
        int k=rList.getAvailable();
        //cout<<"LD "<<regname[k]<<",B"<<endl;
        addToObj("MOV",regname[k],","+four[pointer][1]," ");
        //cout<<"ADD "<<regname[k]<<",C"<<endl;
        addToObj("SUB",regname[k],","+four[pointer][2]," ");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);
    }
}
void finalstep::mulSentence()
{
    if(rList.locr(four[pointer][1])!=0)
    {
        storeAll();
        addToObj("MOV",regname[0],","+four[pointer][1],"");
        addToObj("MUL",four[pointer][1],"","");
        rList.setReg(four[pointer][3],isActive[pointer][3],0);
    }
    else
    {
        addToObj("MUL",four[pointer][1],"","");
        rList.setReg(four[pointer][3],isActive[pointer][3],0);
    }
}
void finalstep::divSentence()
{
    if(rList.locr(four[pointer][1])!=0)
    {
        storeAll();
        addToObj("MOV",regname[0],","+four[pointer][1],"");
        addToObj("DIV",four[pointer][1],"","");
        rList.setReg(four[pointer][3],isActive[pointer][3],0);
    }
    else
    {
        addToObj("DIV",four[pointer][1],"","");
        rList.setReg(four[pointer][3],isActive[pointer][3],0);
    }
}
void finalstep::grtSentence()
{
    /*
        MOV AX,[1]
        CMP AX,[2]
        JA OBJP+2
        MOV AX,0
        JMP OBJP+1
        MOV AX,1
    */
    if(rList.locr(four[pointer][3])!=-1)
    {
        int k=rList.locr(four[pointer][0]);
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JA",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][1])!=-1)//若参数在寄存器中
    {
        int k=rList.locr(four[pointer][1]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][1])],","+four[pointer][1],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JA",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][2])!=-1)//第二个参数在寄存器中 同理
    {
        int k=rList.locr(four[pointer][2]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[k],","+four[pointer][2],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][1],"");
        addToObj("JBE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.getAvailableNum()!=0)//若还有未使用的寄存器
    {
        int k=rList.getAvailable();//取得该寄存器的位置
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JA",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else//若没有未使用的寄存器
    {
        storeAll();//保存所有寄存器中的变量 然后执行有可用寄存器时的操作
        int k=rList.getAvailable();
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JA",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
}
void finalstep::greSentence()
{
    /*
        MOV AX,[1]
        CMP AX,[2]
        JAE OBJP+2
        MOV AX,0
        JMP OBJP+1
        MOV AX,1
    */
    if(rList.locr(four[pointer][3])!=-1)
    {
        int k=rList.locr(four[pointer][0]);
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JAE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][1])!=-1)//若参数在寄存器中
    {
        int k=rList.locr(four[pointer][1]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][1])],","+four[pointer][1],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JAE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][2])!=-1)//第二个参数在寄存器中 同理
    {
        int k=rList.locr(four[pointer][2]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[k],","+four[pointer][2],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][1],"");
        addToObj("JB",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.getAvailableNum()!=0)//若还有未使用的寄存器
    {
        int k=rList.getAvailable();//取得该寄存器的位置
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JAE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else//若没有未使用的寄存器
    {
        storeAll();//保存所有寄存器中的变量 然后执行有可用寄存器时的操作
        int k=rList.getAvailable();
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JAE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
}
void finalstep::letSentence()
{
    /*
        MOV AX,[1]
        CMP AX,[2]
        JB OBJP+2
        MOV AX,0
        JMP OBJP+1
        MOV AX,1
    */
    if(rList.locr(four[pointer][3])!=-1)
    {
        int k=rList.locr(four[pointer][0]);
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JB",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][1])!=-1)//若参数在寄存器中
    {
        int k=rList.locr(four[pointer][1]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][1])],","+four[pointer][1],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JB",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][2])!=-1)//第二个参数在寄存器中 同理
    {
        int k=rList.locr(four[pointer][2]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[k],","+four[pointer][2],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][1],"");
        addToObj("JAE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.getAvailableNum()!=0)//若还有未使用的寄存器
    {
        int k=rList.getAvailable();//取得该寄存器的位置
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JB",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else//若没有未使用的寄存器
    {
        storeAll();//保存所有寄存器中的变量 然后执行有可用寄存器时的操作
        int k=rList.getAvailable();
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JB",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
}
void finalstep::leeSentence()
{
    /*
        MOV AX,[1]
        CMP AX,[2]
        JBE OBJP+2
        MOV AX,0
        JMP OBJP+1
        MOV AX,1
    */
    if(rList.locr(four[pointer][3])!=-1)
    {
        int k=rList.locr(four[pointer][0]);
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JBE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][1])!=-1)//若参数在寄存器中
    {
        int k=rList.locr(four[pointer][1]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][1])],","+four[pointer][1],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JBE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][2])!=-1)//第二个参数在寄存器中 同理
    {
        int k=rList.locr(four[pointer][2]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[k],","+four[pointer][2],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][1],"");
        addToObj("JA",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.getAvailableNum()!=0)//若还有未使用的寄存器
    {
        int k=rList.getAvailable();//取得该寄存器的位置
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JBE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else//若没有未使用的寄存器
    {
        storeAll();//保存所有寄存器中的变量 然后执行有可用寄存器时的操作
        int k=rList.getAvailable();
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JBE",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
}
void finalstep::equSentence()
{
    /*
    MOV AX,[1]
    CMP AX,[2]
    JF OBJP+2
    MOV AX,1
    JMP OBJP+1
    MOV AX,0
    */
    if(rList.locr(four[pointer][3])!=-1)
    {
        int k=rList.locr(four[pointer][0]);
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][1])!=-1)//若参数在寄存器中
    {
        int k=rList.locr(four[pointer][1]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][1])],","+four[pointer][1],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][2])!=-1)//第二个参数在寄存器中 同理
    {
        int k=rList.locr(four[pointer][2]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[k],","+four[pointer][2],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],","+four[pointer][1],"");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.getAvailableNum()!=0)//若还有未使用的寄存器
    {
        int k=rList.getAvailable();//取得该寄存器的位置
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else//若没有未使用的寄存器
    {
        storeAll();//保存所有寄存器中的变量 然后执行有可用寄存器时的操作
        int k=rList.getAvailable();
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],","+four[pointer][2],"");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
}
void finalstep::andSentence()
{
    /*
    MOV AX,[1]
    CMP AX,0;
    JF  K //OBJ+5
    MOV AX,[2]
    CMP AX,0
    JF  K //OBJP+2
    MOV AX,1
    JMP M //OBJ+1
    MOV AX,0
    */
    if(rList.locr(four[pointer][3])!=-1)
    {
        int k=rList.locr(four[pointer][0]);
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][2],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][1])!=-1)//若参数在寄存器中
    {
        int k=rList.locr(four[pointer][1]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][1])],four[pointer][1],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][2],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][2])!=-1)//第二个参数在寄存器中 同理
    {
        int k=rList.locr(four[pointer][2]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[k],","+four[pointer][2],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][1],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.getAvailableNum()!=0)//若还有未使用的寄存器
    {
        int k=rList.getAvailable();//取得该寄存器的位置
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][2],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else//若没有未使用的寄存器
    {
        storeAll();//保存所有寄存器中的变量 然后执行有可用寄存器时的操作
        int k=rList.getAvailable();
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][2],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",1","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",0","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
}
void finalstep::orSentence()
{
    /*
    MOV AX,[1]
    CMP AX,0
    JNF  K //OBJ+5
    MOV AX,[2]
    CMP AX,0
    JNF  K
    MOV AX,0
    JMP M //OBJ+1
    MOV AX,1
    */
    if(rList.locr(four[pointer][3])!=-1)
    {
        int k=rList.locr(four[pointer][0]);
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][2],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][1])!=-1)//若参数在寄存器中
    {
        int k=rList.locr(four[pointer][1]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[rList.locr(four[pointer][1])],","+four[pointer][1],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][2],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.locr(four[pointer][2])!=-1)//第二个参数在寄存器中 同理
    {
        int k=rList.locr(four[pointer][2]);
        if(isActive[pointer][1]!=-1)//若它是个活跃变量
        {
            //cout<<"ST "<<regname[rList.locr("b")]<<",B"<<endl;
            addToObj("ST",regname[k],","+four[pointer][2],"");//储存
            varstored[vsn]=four[pointer][1];
            vsn++;//增加使用过的变量
        }
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][1],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else if(rList.getAvailableNum()!=0)//若还有未使用的寄存器
    {
        int k=rList.getAvailable();//取得该寄存器的位置
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][2],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
    else//若没有未使用的寄存器
    {
        storeAll();//保存所有寄存器中的变量 然后执行有可用寄存器时的操作
        int k=rList.getAvailable();
        addToObj("MOV",regname[k],","+four[pointer][1],"");//将第一个参数存入
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+6),"","");
        addToObj("MOV",regname[k],","+four[pointer][2],"");
        addToObj("CMP",regname[k],",0","");
        addToObj("JNF",numtostring(objpointer+3),"","");
        addToObj("MOV",regname[k],",0","");
        addToObj("JMP",numtostring(objpointer+2),"","");
        addToObj("MOV",regname[k],",1","");
        rList.setReg(four[pointer][3],isActive[pointer][3],k);//将寄存器内储存的内容换为结果变量
    }
}
#endif // FINALSTEP_H_INCLUDED
