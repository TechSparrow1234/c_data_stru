/*
双向循环链表
【问题描述】
在一个多道程序运行的计算机系统中，几个程序同时进驻内存，且不同的程序所需要内存空间大小不同。
当又有程序申请内存空间时，系统必须分配大小合适、连续的一块内存单元。
另一方面，当某个程序结束运行后，又需要将所占用的内存空间归还操作系统，以供其他程序使用。
内存的空白区组织成一个链表形式，分配内存空间时，每次从头空白区开始同时向两侧查找空白区，如果空白区大小满足需求，则从空白区的末尾分配一块空间，并修改空白区大小（如果同时在两侧遇到满足需求的空白区，优先选择左侧的空白区）；否则寻找下一块空白区。
如果没有合适的空白区，但总的空白空间足够，系统可以进行内存浮动，将所有的空白区合并到一起，并分配内存。
假设所有的程序运行时间无限。
【输入形式】
第一行是初始的内存空白区；
后续N行则是N次需要分配内存的程序所需内存的大小
【输出形式】
若成功分配内存，输出最后修改的空白区的剩余内存的大小；
若内存不足，则输出“memory out”
【样例输入】
10 9 12 13
13
8
13
14
【样例输出】
0
2
10
memory out
*/


/*
思路，第一次获取输入，构建一个双向循环链表，**初始化链表**（这次构建一个有头结点的链表）
之后每一次读取一个数，**查找**，**修改并输出**，**合并**

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1024
#define MAX_NUMBER 256

struct node
{
    int mem;
    struct node *link;
    struct node *pre;
};
typedef struct node Node;
typedef Node *Nodeptr;

Nodeptr initNode(Nodeptr list, int *numbers, int cnt);
int memalloc(Nodeptr list, int num);
void reshape(Nodeptr list, int tolmem, int num);
void deleteNode(Nodeptr p);
int main(){
    char input[MAX_LINE_LENGTH];
    int cnt=0;
    Nodeptr list = (Nodeptr)malloc(sizeof(Node));
    list->mem = -1;
    // 从键盘中获取初始化的内存数据
    if(fgets(input, sizeof(input), stdin)!=NULL)
    {
        int numbers[MAX_NUMBER];
        int num = 0;
        char *token = strtok(input, " \n");
        while(token!=NULL)
        {
            num = atoi(token);
            numbers[cnt++]=num;
            token = strtok(NULL, " \n");
        }
        // 初始化内存
        list = initNode(list, numbers, cnt);
    }
    

    // 从键盘中获取多行输入
    while(fgets(input, sizeof(input), stdin)!=NULL)
    {
        if(input[0]=='\n'){break;}
        int num = 0;
        num = atoi(input);
        if(num==0){continue;}
        int flag = memalloc(list, num);
        if(!flag){break;}
    }
    printf("\n");
    return 0;
}

Nodeptr initNode(Nodeptr list, int *numbers, int cnt)
{
    // 设置新节点的前驱p
    Nodeptr p = list;
    for(int i=0; i<cnt; i++)
    {
        // 设置新节点q
        Nodeptr q = (Nodeptr)malloc(sizeof(Node));
        q->mem = numbers[i];
        p->link = q;
        q->pre = p;
        p = q;
    }
    p->link = list;
    list->pre = p;
    return list;
}

int memalloc(Nodeptr list, int num)
{
    // 设置首节点，此时不是list
    Nodeptr p1 = list->link;
    Nodeptr q1=list;
    Nodeptr p2 = list->pre;
    Nodeptr q2 = list;
    int tolmem = 0;
    int flag = 0;
    // 遍历节点，检查是否有内存或者是否可能有内存
    for(;p1!=list || p2!=list;p1=p1->link, p2=p2->pre)
    {
        // 先判断左边
        if(p2->mem>=num)
        {
            p2->mem -= num;
            flag = 1;
            printf("%d\n", p2->mem);
            return flag;
        }
        else if(p1->mem>=num)
        {
            p1->mem -= num;
            flag = 1;
            printf("%d\n", p1->mem);
            if(p1->mem==0){deleteNode(q1);}
            return flag;
        }
        else
        {
            tolmem += p1->mem;
        }
        q1=p1;
    }
    if(tolmem>=num){flag=1;}
    if(flag){reshape(list,tolmem,num);}
    else{printf("memory out");}
    return flag;
}

void reshape(Nodeptr list, int tolmem, int num)
{
    Nodeptr p = list->link;
    p->mem = tolmem-num;
    printf("%d\n", p->mem);
    p=p->link;
    for(;p!=list;p=p->link)
    {
        p->mem=0;
    }
}

void deleteNode(Nodeptr p)
{
    Nodeptr q = p->link;
    // 如果是尾节点
    if(!(q->link)){
        free(q);
        p->link = NULL;
    }
    // 如果是中间节点
    else{
        p->link = q->link;
        free(q);
    }
}