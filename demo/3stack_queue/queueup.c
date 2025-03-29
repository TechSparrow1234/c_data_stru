#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 200
#define THRESHOLD 7
#define MAXSVR 5
#define MINSVR 3

typedef struct
{
    int id;
    int wtime;
}CustType;
CustType Cqueue[MAXSIZE];
int Cfront=0, Crear=-1,Cnum=0;

int Winnum=MINSVR;
void updataCustqueue();
void enCustqueue();
CustType deCustqueue();
int isFull();
int isEmpty();
void arriveCust();
int service();


int main()
{
    int clock, simulationtime;
    scanf("%d",&simulationtime);
    for(clock=1;;clock++)
    {
        updataCustqueue();
        if(clock<=simulationtime)
            arriveCust();
        if(service()==0 && clock>simulationtime)
            break;
    }
    return 0;
}

void arriveCust()
{
    int i,n;
    static int count=0;
    CustType c;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        c.id = count++;
        c.wtime=0;
        enCustqueue(c);
    }
    while((getCustnum()/Winnum)>=THRESHOLD && Winnum<MAXSVR)
    {Winnum++;}
}

int service()
{
    int i;
    CustType c;
    for(i=0;i<Winnum;i++)
    {
        if(isEmpty()) return 0;
        else
        {
            c=deCustqueue();
            printf("%d:%d\n",c.id, c.wtime);
        }
        if((getCustnum()/Winnum)<THRESHOLD && Winnum>MINSVR)
            {Winnum--;}
        return 1;
    }
}