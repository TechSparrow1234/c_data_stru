# include<stdio.h>

void magic(int **a, int n)
{
    int i, j, num;
    for(i=0; i<n;i++)
    {
        for(j=0; j<n; j++)
        {
            // initialize
            a[i][j]=0;
        }
    }
    i=0;
    j=n/2;
    for(num=1;num<=n*n;num++)
    {
        if(i<0 && j<0 || a[i][j]!=0)
        {
            i+=2;
            j++;
        }
        a[i--][j--]=num;
        if(i<0 && j>=0)
        {
            i=n-1;
        }
        if(j<0 && i>=0)
        {
            j=n-1;
        }
    }
}