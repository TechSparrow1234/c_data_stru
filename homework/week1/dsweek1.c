/*
1. 数据排列
【问题描述】

已知顺序表中的每个数据元素为互不相等的整数，设计算法将其调整为三部分，使得左边的所有元素除以3余2，中间的所有元素被3整除，右边的所有元素除以3余1
【输入形式】

一行整数，由空格隔开
【输出形式】

一行整数，由空格隔开
【样例输入】

1 2 3 4 5
【样例输出】

5 2 3 4 1
【样例说明】
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1024
#define MAX_NUMBER 256

int adjust_numbers(int list[], int n);

int main(){
    char input[MAX_LINE_LENGTH];
    int numbers[MAX_NUMBER];
    int cnt=0;

    // 从键盘中获取输入
    while(fgets(input, sizeof(input), stdin)!=NULL)
    {
        if(input[0]=='\n'){break;}
        int num = 0;
        char *token = strtok(input, " \n");

        while(token!=NULL)
        {
            num = atoi(token);
            numbers[cnt++]=num;;
            token = strtok(NULL, " \n");
        }
    

        adjust_numbers(numbers, cnt);
        //打印输出列表
        for(int i=0;i<cnt;i++)
        {
            printf("%d", numbers[i]);
            if(i < cnt-1)
                printf(" ");
        }
    }
    printf("\n");
    return 0;
}

int adjust_numbers(int list[], int n){
    int temp[n];
    int cnt=0;
    if(n <= 0 || n > MAX_NUMBER){
        printf("输入错误");
        return -1;
    }
    for(int i=0;i<n;i++){
        if((list[i]%3+3)%3==2)
        {
            temp[cnt++]=list[i];
        }
    }
    for(int i=0;i<n;i++){
        if((list[i]%3+3)%3==0)
        {
            temp[cnt++]=list[i];
        }
    }
    for(int i=0;i<n;i++){
        if((list[i]%3+3)%3==1)
        {
            temp[cnt++]=list[i];
        }
    }
    for(int i=0;i<n;i++){list[i]=temp[i];}
    return 0;
}