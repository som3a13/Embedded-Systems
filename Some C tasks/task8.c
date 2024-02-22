#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool perfectSqr(int num)
{
    double result = sqrt(num);
    return result == (int)result;
}

int main()
{

    printf("Is it Perfect ? %d \n",perfectSqr(4));
    return 0;
}

