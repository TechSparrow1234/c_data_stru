#include<stdio.h>
#include<stdlib.h>

// 定义链表结构
struct node{
    int data;
    struct node *link;
};
//继续定义链表，方便后续表示
typedef struct node Node;
typedef struct node *Nodeptr;

Nodeptr creatlist(int n);  //创建一个n个节点的链表

int getLength(Nodeptr list);  //获取链表的长度

Nodeptr insertFirst(Nodeptr list,int item);  //在表头插入元素

void insertNode(Nodeptr p, int item);  //在p之后插入元素

void insertNode1(Nodeptr list, int n, int item);  // 在第n个节点后插入

Nodeptr insertNode2(Nodeptr list, int elem);  // 在增序链表里插入

Nodeptr deleteNode1(Nodeptr list, Nodeptr r, Nodeptr p);  // 删除p指向的节点，且给出p的前驱节点r

Nodeptr deleteNode2(Nodeptr list, Nodeptr p);  // 删除p指向的节点，但不给出前驱节点

Nodeptr creatlist(int n)
{
    Nodeptr list=NULL, p, q; //list为头指针，p是最终节点，q是临时节点
    for(int i=0; i<n; i++){
        q=(Nodeptr)malloc(sizeof(Node));  //先对临时节点分配内存。并填充数据
        q->data=read();
        q->link=NULL;
        if(list==NULL){
            list=p=q;
        }
        else{
            p->link=q;
        }
        p=q; //此时结尾已经不是p，所以要更新
    }
    return list;
}

int getLength(Nodeptr list)
{
    Nodeptr p;  //为遍历链表的指针,不应该对头指针修改
    int n=0;
    for(p=list;p!=NULL;p=p->link)
    {
        n++;
    }
    return n;
}

Nodeptr insertFirst(Nodeptr list,int item)
{
    Nodeptr p=(Nodeptr)malloc(sizeof(Node));
    p->data=item;
    p->link=list;
    return p;  //建议这样调用 list = insertFirst(list, item);
}

void insertNode(Nodeptr p, int item)
{
    Nodeptr q=(Nodeptr)malloc(sizeof(Node));
    q->data=item;
    q->link=p->link;
    p->link=q;
}

void insertNode1(Nodeptr list, int n, int item)
{
    Nodeptr p=list;
    for(int i=0;i<n;i++)
    {
        p=p->link;  // 这里没有考虑到n超出边界的情况，最好考虑
    }
    insertNode(p, item);
}

Nodeptr insertNode2(Nodeptr list, int elem)
{
    Nodeptr p,q,r; //观察到对链表的操作都是对三个元素操作的，所以此处设置三个变量
    r->data=elem, r->link=NULL;
    if(list == NULL)  //如果链表是一个空表，那么直接插入
    {
        return r;  //用list=insertNode2(list, elem)调用
    }
    for(p=list;elem>p->data && p!=NULL;q=p,p=p->link);  //获取插入位置
    if(p==list){  // 一次都没有执行，需要插入在头位置
        r->link=p;
        return r;
    }
    else
    {
        r->link = p;
        q->link = r;
    }
    return list;
}

Nodeptr deleteNode1(Nodeptr list, Nodeptr r, Nodeptr p)
{
    if(p==list)
    {
        list=p->link;
    }
    else
    {
        r->link=p->link;  //把节点接上
    }
    free(p);
    return list;
}

Nodeptr deleteNode2(Nodeptr list, Nodeptr p)
{
    /*类似可以给出双指针做法，可以极大优化时间复杂度和空间复杂度*/
    Nodeptr r;
    if(p==list)
    {
        list=p->link;
        free(p);
        return list;
    }
    for(r=list;r->link!=p && r->link!=NULL;r=r->link);  //只需要检索对应的节点即可，不需要操作
    r->link=p->link;  //也可以写成r->link=r->link->link;
    free(p);
    return list;
}