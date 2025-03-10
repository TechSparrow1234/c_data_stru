#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXWORD 32
#define MAXSIZE 1024

struct Inode{
    char word[MAXWORD];
    int count;
};

typedef struct Inode Inode;
/*
思路应该是，获取单词，查找单词，如果有那么+1，否则插入该单词
*/
int getWord(FILE *bfp, char *w);  //从文件中读取但单词
int searchWord(Inode list[], char *w);
int insert(Inode list[], int pos, char *w);
int N=0;

int main()
{
    Inode wordlist[ MAXSIZE];  //在主文件里定义单词表
    char filename[MAXWORD],word[MAXWORD];
    FILE *bfp;

    scanf("%s", filename);
    if((bfp=fopen(filename, "r"))==NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);
        return -1;
    }
    while(getWord(bfp, word)!=EOF)
    {
        if(searchWord(wordlist, word)==-1)
        {
            fprintf(stderr, "wordlist is full!\n");
            return -1;
        }
    }
    for(int i=0;i<N;i++)  // 遍历输出单词表的结果
    {
        printf("%s %d\n", wordlist[i].word, wordlist[i].count);
    }
    return 0;
}

int getWord(FILE *bfp, char *w) 
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
int searchWord(Inode list[], char *w)
{
    int low=0, high=N-1, mid=0;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(strcmp(w,list[mid].word)<0)
        {
            high=mid-1;
        }
        else if(strcmp(w,list[mid].word)>0)
        {
            low=mid+1;
        }
        else
        {
            list[mid].count++;
            return 0;
        }
        return insertWord(list,low,w);
    }
}
int insert(Inode list[], int pos, char *w)
{
    /*
    因为是线性表的结构，所以要对元素移动
    */
    int i;
    if(N==MAXSIZE)
    {
        printf("wordlist is full!");
        return -1;
    }
    for(i=N-1;i>=pos;i--)
    {
        strcpy(list[i+1].word, list[i].word);
        list[i+1].count=list[i].count;  //移动线性表，腾位置
    }
    list[pos].count=1;
    N++;  //设置全局变量的好处
    return 1;
}