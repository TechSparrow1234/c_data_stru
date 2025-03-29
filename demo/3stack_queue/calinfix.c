#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXSIZE 100

typedef int DataType;
// define an enum type for symbol
enum symbol{NUM, OP, EQ, OTHER};
// defin an enum type for operator
enum oper{EPT, ADD, MIN, MUL, DIV, LEFT, RIGHT};
// define priority first
int Pri[]={-1,0,0,1,1,2,2};
// a symble can only be num or op so use union
union sym
{
    DataType num;
    enum oper op;
};  // 符号值
// data_**seq**_stack, that's why we don't use Node
DataType Num_stack[MAXSIZE]; 
// op_seq_stack
enum oper Op_stack[MAXSIZE];
int Ntop=-1;  // top only eq -1 ,the stack is empty
int Otop=-1;

enum symbol getSym(union sym *item);
void operate(enum oper op);
void compute(enum oper op);
DataType popNum();
void pushOP(enum oper op);
enum oper popOp();
enum oper topOp();

int main()
{   // object
    union sym item;
    enum symbol s;
    while((s=getSym(&item))!=EQ)
    {
        if(s==NUM)
            pushNum(item.num);
        else if(s==OP)
            operate(item.op);
        else
        {
            printf("error in expresion");
            return 1;
        }
    }
    while(Otop>=0)  // pop every item in stack
    {
        compute(pushOP);
    }
    if(Ntop==0)
        printf("%d\n",popNum());
    else
        printf("error in expression\n");
    return 0;
}

enum symbol getsymbol(union sym *item)
{
    int c,n;
    while((c = getchar())!='=')
    {
        if(c>='0'&&c<='9')
        {
            for(n=0;c>='0'&&c<='9';c=getchar())
            {
                // to get the number but don't use int
                n=n*10+c-'0';
            }
            // push the c back to stdin
            ungetc(c, stdin);
            item->num=n;
            return NUM;
        }
        else
        {
            switch(c)
            {
                case '+':item->op=ADD;return OP;
                case '-':item->op=MIN;return OP;
                case '*':item->op=MUL;return OP;
                case '/':item->op=DIV;return OP;
                case '(':item->op=LEFT;return OP;
                case ')':item->op=RIGHT;return OP;
                case ' ':
                case '\t':
                case 'n':
                    break;
                default:return OTHER;
            }
        }
    }
    return EQ;
}

void operate(enum oper op)
{
    enum oper t;
    if(op!=RIGHT)
    {
        // use the enumtype to show the num to compare
        while(Pri[op]<=Pri[topOp()] && topOp()!=LEFT)
        {
            compute(popOp());
        }
        pushOP(op);
    }
    else
    {
        while(t=popOp()!=LEFT)
        {
            compute(t);
        }
    }
}

void compute(enum oper op){
    DataType tmp;
    switch(op)
    {
        case ADD:
            pushNum(popNum()+popNum());break;
        case MIN:
            tmp = popNum();
            pushNum(popNum()-tmp);break;
        case MUL:
            pushNum(popNum()*popNum());break;
        case DIV:
            tmp = popNum();
            pushNum(popNum()/tmp);break;
    }
}

void pushNum(DataType num)
{
    if(Ntop==MAXSIZE-1)
    {
        printf("Datastack is full!\n");
        exit(1);
    }
    Num_stack[++Otop] = num;
}

DataType popNum()
{
    if(Ntop==-1)
    {
        printf("error in the expression");
        exit(1);
    }
    return Num_stack[Ntop--];
}

void pushOP(enum oper op)
{
    if(Ntop==MAXSIZE-1)
    {
        printf("operator stack is full!");
        exit(1);
    }
    Op_stack[++Otop] = op;
}

enum oper popOp()
{
    if(Otop!=-1)
    {
        return Op_stack[Otop--];
    }
    return EPT;
}


enum oper topOp()
{
    if(Otop!=-1)
    {
        return Op_stack[Otop];
    }
    else
        return EPT;
}