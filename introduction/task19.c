#include <stdlib.h>
#include <stdio.h>

// half pyramid
void printPyramid()
{
    for(int i=1;i<=5;i++)
    {
        for(int j=i;j<=5;j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

int main()
{

    printPyramid();
    return 0;
}