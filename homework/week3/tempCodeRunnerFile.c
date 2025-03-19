/*
【问题描述】
 输入一个中缀表达式，表达式中有+、-、*、/、<、>、%七种运算，表达式中的其他符号为大写的字母。实现一个算法，得到相应的后缀表达式。

【输入形式】
 一个式子的中缀表达式，以=结束

【输出形式】
 相应的后缀表达式 
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct node
{
    char data;
    struct node *link;
};
typedef struct node Node;
typedef Node *Nodeptr;
Nodeptr Top = NULL;
// 全局变量Top，不用每一个都传入 



void changeinfix(char *ch);
int isEmpty();
char pop();
void push(char ch);
int get_precedence(char op);

int main()
{
    char c;
    char temp;
    while((c=getchar())!='=')
    {
        changeinfix(&c);
    }
    while(isEmpty()==1)
    {
        temp = pop();
        printf("%c",temp);
    }
    return 0;
}

void changeinfix(char *ch)
{
    char temp;
    if(isalpha(*ch))
    {
        printf("%c",*ch);
    }
    else if(*ch==')')
    {
        while((temp=pop())!='(')
        {
            temp=pop();
            printf("%c",temp);
        }
    }
    else
    {
        while(isEmpty() && Top->data != '(' && get_precedence(Top->data) >= get_precedence(*ch))
        {
            temp = pop();
            printf("%c",temp);
        }
        push(*ch);
    }
}

int isEmpty()
{
    return Top==NULL;
}

char pop()
{
    char temp;
    if(isEmpty())
    {
        return -1;
    }
    else
    {
        Nodeptr p;
        p=Top;
        temp=p->data;
        Top=p->link;
        free(p);
        return temp;
    }
}

void push(char ch)
{
    Nodeptr p = (Nodeptr)malloc(sizeof(Node));
    p->data = ch;
    p->link = Top;
    Top = p;
}

int get_precedence(char op)
{
    switch(op)
    {
        case '>':
        case '<':
            return 0;

        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
        case '%':
            return 2;
        
        case '(':
        case ')':
            return 3;
    }
}