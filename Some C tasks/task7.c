#include <stdlib.h>
#include <stdio.h>

void comp(int num1,int num2,int num3)
{   
    int min=num1;
    if(num2<min && num2<num3)
    {
        min=num2;
        printf("Mini number = %d \n",min);    }
    else if( num3<min && num3 < num2 )
    {
        min=num3;
        printf("Mini number = %d \n",min);
    }
    else
    {
        min=num1;
        printf("Mini number = %d \n",min);
    }
}

int compAscending(const void*a ,const void *b)
{
    int e1=*((int*)a);
    int e2=*((int*)b);
    return e1-e2;
}
int main()
{

    comp(100,2,1);
    //Using qsort
    int numbers[]={10,20,40,60,-1,-2,-4,60};
    int size= sizeof(numbers)/sizeof(numbers[0]);
    qsort(numbers, size, sizeof(int), compAscending);
    int mini = numbers[0];
    printf("Minimum number = %d \n ",mini);


    return 0;



}