#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DEFLINES 10
#define MAXLEN 81
struct node{
    char *line;
    struct node *next;
};
typedef struct node Node;
typedef struct node* Nodeptr;

int main(int argc, char *argv[])
{
    char curline[MAXLEN], filename;
    int n=DEFLINES, i;
    Nodeptr first, ptr;
    FILE *fp;
    // 获取参数
    if(argc==3 && argv[1][0]=='-')
    {
        n=atoi(argv[1]+1);
        filename=argv[2];
    }
    else if(argc==2)
    {
        filename=argv[1];
    }
    else
    {
        printf("Usage: tail [-n] filename\n");
        return 1;
    }
    // 读取文件
    if((fp=fopen(filename, "r"))==NULL)
    {
        printf("can't open file");
        return -1;
    }
    // 初始化节点
    first=ptr=(Nodeptr)malloc(sizeof(Node));
    first->line=NULL;
    for(i=1;i<n;i++)  // 因为以及设置了一个节点，只需要循环n-1次
    {
        // 在申请时只为line指针分配空间
        Nodeptr q = (Nodeptr)malloc(sizeof(Node));
        q = ptr->next;
        ptr = ptr->next;
        ptr->line = NULL;
    }
    ptr->next = first;  // 知道长度可以先全部读入再封尾
    ptr = first;

    //开始读取文件，修改链表
    while(fgets(curline, MAXLEN, fp)!=NULL)
    {
        if(ptr->line!=NULL)
        {
            free(ptr->line);  // 为了代码一致性，同时节省内存下面会重新分配内存
        }
        ptr->line = (char*)malloc(strlen(curline)+1);
        strcpy(ptr->line, curline);
        ptr = ptr->next;
    }
    // 输出结果
    for(i=0;i<n;i++)
    {
        if(ptr->line!=NULL)
        {
            printf("%s", ptr->line);
        }
        ptr=ptr->next;
    }
    // 为什么不释放链表
    fclose(fp);
    return 0;
}
