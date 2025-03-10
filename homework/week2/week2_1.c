/*
1. 线性链表：第k大数字
【问题描述】

构建一个线性链表，读取并存储每行的输入数据，每行数据由定位数字k和不定数量的整数构成，定位数字k表明需要输出当前行及当前行之前的所有行中的第k大（不包括定位数字）的整数。

整数若重复视作相同排名，定位数字不会超过整数数量之和。
【输入形式】

若干行整数，长度不固定，由空格隔开
【输出形式】

每行输入对应的一个整数输出
【样例输入】

2 7 9 10 4 8

4 10 -1 0 4 9

2 7 6 5 3 1 9 12
【样例输出】

9

7

10
【样例说明】

第一行需要存储7 9 10 4 8,并输出第2大的数字；

第二行需要在第一行的基础上存储10 -1 0 4 9，并输出第4大的数字；

以此类推...

数据读取方式参考作业1。
【评分标准】
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE_LENGTH 100
#define MAX_NUMBERS 100

struct node
{
    int data;
    struct node *link;
};
typedef struct node Node;
typedef struct node* Nodeptr;
Node *list = NULL;
/*
获取一行输入，将第一个输入作为定位数字，其他数字**插入**链表中,同时要保持有序性（**先获取索引**），从大到小
之后返回数字

两个问题，一个插入函数或者查找函数有问题，不能返回想要
*/
int  get_input(int *numbers, int cnt, int *index);
Nodeptr insertnum(int num, Node *list);
Nodeptr searchindex(int num, Node *list, int *flag);
void pirnt_ans(Nodeptr list, int index);

int main(){
    char input[MAX_LINE_LENGTH];
    int numbers[MAX_NUMBERS];
    int ans[MAX_NUMBERS];
    int cnt=0;
    int len_ans = 0;

    // 从键盘中获取输入
    while(fgets(input, sizeof(input), stdin)!=NULL)
    {
        len_ans++;
        int index = 0;
        if(input[0]=='\n'){break;}
        int num = 0;
        char *token = strtok(input, " \n");

        while(token!=NULL)
        {
            num = atoi(token);
            numbers[cnt++]=num;;
            token = strtok(NULL, " \n");
        }
        get_input(numbers, cnt, &index);

        pirnt_ans(list, index);
    }
    printf("\n");
    return 0;
}

int  get_input(int *numbers, int cnt, int *index)
{
    *index = numbers[0];
    for(int i=1;i<cnt;i++){
        list = insertnum(numbers[i], list);  
    } 
    return 0;
}

Nodeptr insertnum(int num, Node *list)
{
    Nodeptr p=(Nodeptr)malloc(sizeof(Node));
    if (list == NULL){
        p->data=num;
        list=p;
        return list;
    }
    Nodeptr q;
    int flag=0;
    q=searchindex(num, list, &flag);
    if (q==list && flag==1)
    {
        p->data=num;
        p->link=list;
        list=p;
    }
    else if (flag==1)
    {
        p->data=num;
        p->link=q->link;
        q->link=p;
    }
    else
    {
        free(p);
    }
    return list;
}

Nodeptr searchindex(int num, Node *list, int *flag)
{
    Nodeptr p=NULL;
    Nodeptr q=(Nodeptr)malloc(sizeof(Node));
    q->link=list;
    for(p=list;p!=NULL;p=p->link)
    {
        if(p->data>num)
        {
            q=p;
        }
        else if(p->data<num)
        {
            *flag=1;
            return q;
        }
        else
        {
            *flag=0;
            return q;
        }
    }
    q->link=NULL;
    return q;  // 如果最后还不行，就在最后一个地方往后插入 
}

void pirnt_ans(Nodeptr list, int index)
{
    Nodeptr p=list;
    for(int i=1;i<index;i++,p=p->link);
    printf("%d\n", p->data);
}