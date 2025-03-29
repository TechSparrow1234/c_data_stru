#include<stdio.h>
#include<stdlib.h>

// 定义链表结构
struct node{
    int data;
    struct node *link;
};

// 定义双向链表
struct dnode
{
    int data;
    struct dnode *rlink, *llink;
};
typedef struct dnode Dnode;
typedef Dnode *Dnodeptr;
Dnodeptr list = NULL;


//继续定义链表，方便后续表示
typedef struct node Node;
typedef struct node *Nodeptr;

//创建一个n个节点的链表
Nodeptr creatlist(int n);  
//获取链表的长度
int getLength(Nodeptr list);  
//在表头插入元素
Nodeptr insertFirst(Nodeptr list,int item);  
//在p之后插入元素
void insertNode(Nodeptr p, int item);  
// 在第n个节点后插入
void insertNode1(Nodeptr list, int n, int item);  
// 在增序链表里插入
Nodeptr insertNode2(Nodeptr list, int elem);  
// 删除p指向的节点，且给出p的前驱节点r
Nodeptr deleteNode1(Nodeptr list, Nodeptr r, Nodeptr p);  
// 删除p指向的节点，但不给出前驱节点
Nodeptr deleteNode2(Nodeptr list, Nodeptr p);  
// 双向非空循环链表插入
int insertDnode(Dnodeptr list, int x, int item);
// 带头结点的双向非空循环链表删除
int deleteDnode(Dnodeptr list, int x);


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

int insertDnode(Dnodeptr list, int x, int item)
{
    Dnodeptr p,q;
    // 先寻找满足条件的链节点
    for(q=list->rlink;q!=NULL && q->data!=x;q=q->rlink);
    if(q==list)return -1;
    p=(Dnodeptr)malloc(sizeof(Dnode));
    p->data=item;
    p->llink=q;  // p的前驱节点指向q
    p->rlink=q->rlink;  // p的后继节点指向q的后继
    q->rlink->llink=p;  // q的下一个的上一个指向p
    q->rlink=p;  // q的下一个是p
    return 1;
}

int deleteDnode(Dnodeptr list, int x)
{
    Dnodeptr q;
    for(q=list->rlink;q!=NULL && q->data!=x;q=q->rlink);
    if(q==list);
        return -1;
    q->llink->rlink=q->rlink; // q的上一个的下一个应该指向q的下一个
    q->rlink->llink=q->llink;
    free(q);
    return 1;
}