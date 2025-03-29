#include<stdio.h>

struct node
{
    int data;
    struct node *link;
};
typedef struct node Node;
typedef struct node *Nodeptr;
Nodeptr Top;

void initStack();
int isEmpty();
void push(int item);
int pop();


void initStack()
{
    Top = NULL;
}

int isEmpty()
{
    return Top==NULL;
}

void push(int item)
{
    Nodeptr p;
    if((p=(Nodeptr)malloc(sizeof(Node)))==NULL)
    {
        printf("No memory!");
    }
    else
    {
        p->data=item;
        p->link=Top;  // 是在链表头插入
        Top=p;
    }
}

int pop()
{
    Nodeptr p;  // 此处就不用申请空间
    int item;
    if(isEmpty())
    {
        printf("EMPTY STACK!");
        exit(-1);
    }
    else
    {
        p=Top;
        item = Top->data;
        Top=Top->link;
        free(p);
        return item;
    }
}