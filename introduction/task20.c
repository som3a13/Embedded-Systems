#include <stdlib.h>
#include <stdio.h>

int main()
{

for (int i = 1; i <=5; i++)
{
        // space b4 asterisk
        for(int x=1;x<=5-i;x++)
        {
            printf(" ");
        }
    // print asterisks
        for(int j = 1; j<=2*i-1;j++)
        {
            printf("*");
        }

    printf("\n");
}
   return 0;
}