#include <stdlib.h>
#include <stdio.h>

long long factorial(int num)
{
    if (num == 0 || num == 1) {
        return 1; 
    }
    else
    {
        return num * factorial(num - 1); 
    }
    
}
int main()
{
    static int num;
    printf("Please enter positive int : ");
    if(scanf("%d", &num)!=1)
    {
        printf("Invalid input.\n");
        
    }   
    if(num<0)
    {
        printf("Factorial is not defined for negative numbers.\n");
        return 1;
    }
    long long result= factorial(num);
       printf("Result = %lld\n",result );

       return 0 ;
}
