// 以int型元素为例
#include <stdio.h>
#define MaxSize 100
int N = 50;


int searchint(int list[], int n, int item);
int binarysearchint(int list[], int n, int item);
int insertint(int list[], int n, int i, int item);
int deleteint(int list[], int n, int i, int item);




int main(){
    return 0;
}


// 线性查找算法
int searchint(int list[], int n, int item){
    // 检索每一个item
    for(int i = 0;i < n;i++){
        if(list[i] == item){ // 检索是否为对应元素
            return i; // 找到了返回索引
        }
    }
    return -1; // 找不出返回-1
}

// 二分查找算法
int binarysearchint(int list[], int n, int item){
    int low = 0, high = n-1, mid; // 定义若干次循环中的量
    while(low <= high){ //循环条件
        mid = (high + low)/2;
        if(item < list[mid])
            high = mid - 1; //和循环呼应
        else if(item > list[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

// 插入算法
int insertint(int list[], int n, int i, int item){
    int k;
    if(N==MaxSize || i<0 || i>N) //这里不需要大于，因为初始化过
        return -1;
    for(k=N-1;k>=i;k--)
        list[k+1]=list[k];
    list[i]=item;
    N++;
    return 1;
}

// 删除算法
int deleteint(int list[], int n, int i, int item){
    int k; //定义一个循环变量
    if(i<0 || i>N) //判断是否越界
        return -1;
    for(k=i+1;k<N;k++)
        list[k-1]=list[k];
    N--;
    return 1;
}