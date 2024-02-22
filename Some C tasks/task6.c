
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void comp(int num1,int num2)
{   
    int max=num1;
    if(num1==num2)
    {
        printf(" Number 1 = Number 2 \n");

    }
    else if (num1 != num2)
    {
        printf(" Number 1 != Number 2 \n");
        if (num2>max)
    {
        max=num2;
        printf("Max number = %d \n",max);
    }
    }
}

int main()
{

    comp(2,10);
    
    return 0;



}