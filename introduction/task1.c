#include <stdio.h>
#include <stdlib.h>


int fun(int num1,int num2)
{
    return ((num1+num2)*3)-10;
}

int main()
{
    int x,y;
    
    scanf("%d %d",&x,&y);
    printf("%d",fun(x,y));
    return 0;
}