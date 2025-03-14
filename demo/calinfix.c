#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXSIZE 100

typedef int DataType;
enum symbol{NUM, OP, EQ, OTHER};
enum oper{EPT, ADD, MIN, MUL, DIV, LEFT, RIGHT};
int Pri[]={-1,0,0,1,1,2,2};
union sym
{
    DataType num;
    enum oper op;
};  // 符号值
DataType Num_stack[MAXSIZE];  // 数据栈
enum oper Op_stack[MAXSIZE];
int Ntop=-1;
int Otop=-1;

enum symbol getSym(union sym *item);
void operate(enum oper op);
void compute(enum oper op);
DataType popNum();
void pushOP(enum oper op);
enum oper popOp();
enum oper topOp();

int main()
{
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
    while(Otop>=0)  // 写到这里
    {
        compute(pushOP);
    }
}   