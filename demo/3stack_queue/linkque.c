#include<stdio.h>

struct node
{
    int data;
    struct node *link;
};
typedef struct node Qnode;
typedef Qnode *Qnodeptr;

Qnodeptr Front, Rear;
void init()
{
    Front=NULL;
    Rear=NULL;
}

int isEmpty()
{
    return Front==NULL;
}
/*
if you want to ceate a void node
you can just use list->link=Front=Rear;
*/

void enLQueue(int item)
{
    Qnodeptr p;
    if ((p==(Qnodeptr)malloc(sizeof(Qnode)))==NULL)
    {
        Error("No memory");
    }
    p->data=item;
    p->link=NULL;
    if(Front==NULL)
        Front=p;
    else
        Rear->link=p;
    Rear=p;
}

int deLQueue()
{
    Qnodeptr p;
    int item;
    if(isEmpty())
    {
        Error("empty queue");
    }
    else
    {
        p=Front;
        Front=Front->link;
        item=p->data;
        free(p);
        return item;
    }
}

void destroyQueue()
{
    while(Front!=NULL)
    {
        Front=Front->link;
        free(Front);
    }
}