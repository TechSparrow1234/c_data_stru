#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int equal(char s1[], char s2[])
{
    int i=0;
    for(i=0;s1[i]!='\0' && s2[i]!='\0';i++)
    {
        if(s1[i]!=s2[i])
        {
            // not equal return 0
            return 0;
        }
    }
    if(s1[i]=='\0' && s2[i]=='\0')
    {
        // make sure same length
        return 1;
    }
}

int insert(char s[], char t[], int n)
{
    // n show the insert position
    int i=0, j=0;
    char *p;
    p=(char*)malloc(strlen(s)+1);
    for(i=0;s[i+n]!='\0';i++)
    {
        // conserve the sec part of s
        p[i]=s[i+n];
    }
    for(i=n,j=0;t[j]!='\0';i++,j++)
    {
        // update the sec part of s
        s[i]=t[j];
    }
    for(j=0;p[j]!='\0';i++,j++)
    {
        // add p to s
        // don't need to change i
        s[i]=p[j];
    }
    free(p);
    return n;
}

int insert1(char s[], char t[], int n)
{
    // add the sec part of s to t
    strcat(t, s+n);
    s[n]='\0';
    // add t to s
    strcat(s, t);
    return n;
}

int index(char s[], char t[])
{
    int i, j, k;
    for(i=0;s[i]!='\0';i++)
    {
        for(j=i,k=0;t[k]!='\0'&& s[j]==t[k];j++,k++);
        if(t[k]=='\0')
        {
            // the for loop end cuz t[k]='\0
            // so the i is index
            return i;
        }
    }
    return -1;
}

int index1(char s[], char t[])
{
    int i,j,k,m,n;
    n=strlen(s);
    m=strlen(t);
    for(i=0;n-i>=m;i++)  // reduce some unnecessary situation
    {
        for(j=i,k=0;t[k]!='\0' && s[j]==t[k];j++,k++);
        if(t[k]=='\0')
        {
            return i;
        }
    }
    return -1;
}

