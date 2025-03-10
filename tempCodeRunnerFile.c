#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1024
#define MAX_NUMBER 512

int adjust_numbers(int list[], int n);

int main(){
    char input[MAX_LINE_LENGTH];
    int numbers[MAX_NUMBER];
    int cnt=0;

    // 从键盘中获取输入
    while(fgets(input, sizeof(input), stdin)!=NULL)
    {
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
    for(int i=0;i<n;i++){
        if(list[i]%3==2)
        {
            temp[cnt++]=list[i];
        }
    }
    for(int i=0;i<n;i++){
        if(list[i]%3==0)
        {
            temp[cnt++]=list[i];
        }
    }
    for(int i=0;i<n;i++){
        if(list[i]%3==1)
        {
            temp[cnt++]=list[i];
        }
    }
    for(int i=0;i<n;i++){list[i]=temp[i];}
    return 0;
}