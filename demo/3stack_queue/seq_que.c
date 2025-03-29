#define MAXSIZE 1000

int queue[MAXSIZE];
int Front=0, Rear=MAXSIZE-1,Count=0;

void initqueue()
{
    Front=0;
    Rear=MAXSIZE-1;
    Count=0;
}

int isEmpty()
{
    return Count==0;
}

int isFull()
{
    return Count==MAXSIZE;
}

void enqueue(int item)  // don't need to add queue cuz global
{
    if(isFull())
    {
        Error("full queue");
    }
    else
    {
        // use this exp to make it circular
        Rear=(Rear+1)%MAXSIZE;
        queue[Rear]=item;
        Count++;
    }
}

int dequeue()
{
    int item;
    if(isEmpty())
    {
        Error("empty queue");
    }
    else
    {
        item = queue[Front];
        Count--;
        // make it circular
        Front=(Front+1)%MAXSIZE;
        return item;
    }
}