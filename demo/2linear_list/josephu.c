#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *link;
};
typedef struct node Node;
typedef Node* Nodeptr;

void Josephu(int n, int k, int m);

int main()
{
    int n,k,m;
    printf("\nInput n k m:");
    scanf("%d %d %d",&n,&k,&m);
    Josephu(n,k,m);
    return 0;
}

void Josephu(int n, int k, int m)
{
    // 因为只在这个函数运行，所以可以在内部定义链表
    Nodeptr list, p,r;  
    int i;
    list = NULL;
    // 先创建一个**循环**链表
    for(i=0;i<n;i++)
    {
        // r是新增节点，p是过渡节点
        r=(Nodeptr)malloc(sizeof(Node));
        r->data=i+1;
        // 先考虑初始化的情况
        if(list==NULL)
        {
            list=p=r;
        }
        else
        {
            p->link=r;
            p=p->link;
        }
    }
    p->link=list;  // 建立起循环列表
    r=p;  // 相当于首节点的前置节点
    // 先找到第一个节点
    for(p=list,i=0;i<k-1;i++,r=p,p=p->link);
    while(p->link!=p)  //只要不是只剩一个节点
    {
        // 找到该节点后的第m个节点
        for(i=0;i<m-1;i++)
        {
            r=p;
            p=p->link;
        }
        // 删除p节点
        r->link=p->link;
        free(p);
        p=r->link;
        
    }
    printf("%3d",p->data); // 最后一个节点
}