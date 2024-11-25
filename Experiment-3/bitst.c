#include<stdio.h>
#include<string.h>
int main()
{
    char data[100],stuffed[200];
    int i,count=0,j=0;
    printf("enter the data");
    scanf("%s",data);
    for(int i=0;i<strlen(data);i++)
    {
        if(data[i]=='1')
        {
            count++;
            stuffed[j++]=data[i];
        }
        else
        {
            count=0;
            stuffed[j++]=data[i];
        }
        if(count==5)
        {
            count=0;
            stuffed[j++]='0';
        }
    }
    stuffed[j]='\0';
    printf("%s",stuffed);
    return 0;
    
}