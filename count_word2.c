#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXWORD 32
// 用链表一般就不用定义链表长度
struct node{
    char word[MAXWORD];
    int count;
    struct node *link;
};
typedef struct node Node;
Node *Wordlist = NULL;  // 设置链表头节点为NULL，且表头是一个全局变量
// 因为表头可能发生变化，且不确定会改变多少次，设置全局变量
// 方便修改
/*
构造一个空字符表，**从文件中读取单词**，**检索单词是否在单词表中**，
如果在则直接加数，**否则插入**
*/
int getWord(FILE *bfp, char *word); //从文件中获取单词
int searchWord(char *w);  // 寻找是否有这个单词
int insertWord(Node *p, char *w);  // 在特定位置后插入单词_



int main()
{
    char filename[32], word[MAXWORD];
    FILE *bfp;
    Node *p;
    scanf("%s", filename);
    if((bfp=fopen(filename, "r"))==NULL)
    {
        fprintf(stderr, "can't open %s\n",filename);
        return -1;
    }
    while(getWord(bfp, word)!=EOF)
    {
        if(searchWord(word)==-1){
            fprintf(stderr, "Memory error!");
            return -1;
        }
    }
    // 输出遍历单词表
    for(p=Wordlist; p!=NULL; p=p->link)
    {
        printf("%s, %d\n", p->word, p->count);
    }
    return 0;
}

int getWord(FILE *bfp, char *w)// 这个函数不一定对
{
    int c;
    while(!isalpha(c=fgetc(bfp)))  // 自动跳过各种不计数的空白符
    {
        if(c==EOF)return c; //这里和main程序对应上了
        else continue;
    }
    do
    {
        *w++=tolower(c);
    }
    while(isalpha(c=fgetc(bfp)));
    *w='\0';  //因为是w++,所以这里直接赋值就可以了
    return 1;  // 可以联系main中的内容理解这个返回值
}

int searchWord(char *w)
{
    Node *p, *q=NULL;  //将q作为p的前驱节点
    for(p=Wordlist; p!=NULL; q=p, p=p->link)
    {
        if(strcmp(w, p->word)<0)  // 这里的小于号没问题，因为和插入位置有关
        {
            break;
        }
        else if(strcmp(w, p->word)==0)
        {
            p->count++;
            return 0;
        }
    }
    return insertWord(p, w);
}

int insertWord(Node *p, char *w)
{
    Node *q;  // 先定一个一个q节点存储元素
    q=(Node*)malloc(sizeof(Node));
    if(q==NULL)return -1;  //没有内存空间
    strcpy(q->word, w);
    q->count=1;
    q->link=NULL;
    if(Wordlist==NULL)
    {
        Wordlist=q;
    }
    else if(p==NULL)
    {
        q->link=Wordlist;
        Wordlist=q;
    }
    else
    {
        q->link=p->link;
        p->link=q;
    }
    return 0;
}