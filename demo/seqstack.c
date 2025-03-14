#define MAXSIZE 1000
int stack[MAXSIZE];
int Top;  // 需要共享，全局变量

void initstack();
int isEmpty();
int isFull();
void push(int stack[], int x);
int pop(int stack[]);


void initstack()
{
    Top=-1;
}

int isEmpty()
{
    return Top==-1;
}

int isFull()
{
    return Top==MAXSIZE-1;
}

void push(int stack[], int x)
{
    if(isFull())
    {
        printf("FULL STACK");
        exit(-1);
    }
    else
    {
        stack[++Top]=x;
    }
}

int pop(int stack[])
{
    if(isEmpty())
    {
        printf("EMPTY STACK");
        exit(-1);
    }
    else
    {
        // 返回弹出结果
        return stack[Top--];
    }
}