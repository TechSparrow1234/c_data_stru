/*
【问题描述】

卷积神经网络（CNN）的核心操作是卷积和池化，池化操作需要定义池化窗口的大小与窗口移动的步长，然后在每个滑动窗口中选取所需要的统计量（如均值，最大值等）作为输出。

以一维的数据为例，窗口设置为3，移动步长设置为1，那么对于数据1 3 -1 -3 5 3 6 7来说，最大值池化后的输出应为3 3 5 5 6 7。

现在假定给入的数据是长度为n的2维数组，滑动窗口大小为k1*k2，步长为(t1,t2)，（t1是纵向移动步长，t2是横向移动步长）池化方法为最大值池化，设计算法运用队列进行池化运算。

说明：滑动窗口初始时其左上角与原数据的左上角重合，移动时先横向移动至末尾，再纵向移动并回到横向的起点，每个方向移动后要保证整个窗口与原数据重叠。


【输入形式】

三行数据，第一行为数组长度n，窗口宽度k1，k2和移动步长t1，t2

第二行和第三行是需要进行池化操作的二维数组



【输出形式】

池化后的输出，在一行内输出。


【样例输入】

5 2 2 1 2

1 2 3 4 5

5 4 3 2 1


【样例输出】

5 4*/

#include <stdio.h>
#include <stdlib.h>

// 函数用于查找给定窗口内的最大值
int findMax(int **matrix, int i, int j, int k1, int k2) {
    int max_val = matrix[i][j];
    for (int x = i; x < i + k1; x++) {
        for (int y = j; y < j + k2; y++) {
            if (matrix[x][y] > max_val) {
                max_val = matrix[x][y];
            }
        }
    }
    return max_val;
}

int main() {
    int n, k1, k2, t1, t2;
    // 读取输入的 n, k1, k2, t1, t2
    scanf("%d %d %d %d %d", &n, &k1, &k2, &t1, &t2);

    // 动态分配二维数组的内存
    int **matrix = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // 读取二维数组的数据
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int first = 1;
    // 遍历二维数组，进行最大值池化操作
    for (int i = 0; i <= 2 - k1; i += t1) {
        for (int j = 0; j <= n - k2; j += t2) {
            int max_val = findMax(matrix, i, j, k1, k2);
            if (!first) {
                printf(" ");
            }
            printf("%d", max_val);
            first = 0;
        }
    }
    printf("\n");

    for (int i = 0; i < 2; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}