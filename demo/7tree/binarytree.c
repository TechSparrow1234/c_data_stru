#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *lchild, *rchild;    
};

typedef struct node BTNode;
typedef struct node *BTNodeptr;

void preorder(BTNodeptr t)
{
    if(t!=NULL)
    {
        VISIT(t);
        preorder(t->lchild);
        preorder(t->rchild);
    }
};

void postorder(BTNodeptr t)
{
    if(t!=NULL)
    {
        postorder(t->lchild);
        postorder(t->rchild);
        VISIT(t);
    }
}

void layerorder(BTNodeptr t)
{
    BTNodeptr queue[100], p;
    int front, rear;
    if(t!=NULL)
    {
        queue[0]=t;
        front=-1;
        rear=0;
        while(front<rear)
        {
            p=queue[++front];
            VISTI(p);
            if(p->lchild!=NULL)
            {
                queue[++rear]=p->lchild;
            }
            if(p->rchild!=NULL)
            {
                queue[++rear]=p->rchild;
            }
        }
    }
}