#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    static unsigned int num,power;
    if(scanf("%d %d", &num, &power)!=2)
    {
        printf("Invalid input");
    }
    else
    {
        double result = pow(num, power );
        printf("%0.2lf",result);
 
    }
      
    

    


    return 0;
}
