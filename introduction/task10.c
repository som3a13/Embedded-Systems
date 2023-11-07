#include <stdlib.h>
#include <stdio.h>

int main()
{
    float num1, num2;
    char sign;
    printf("Please enter two numbers: ");
    scanf("%f %f", &num1, &num2);

    printf("Please enter the operation sign : ");
    scanf(" %c", &sign);
    float result=0 ;
switch (sign)
{   
    case '+':
        result = num1+num2;
        printf("Result= %0.2lf \n",result);
        break;
    case '-':
        result = num1-num2;
        printf("Result= %0.2lf \n",result);
        break;
    case '*':
        result = num1*num2;
        printf("Result= %0.2lf \n",result);
        break;
    case '/':
        if(num2!=0)
        {
            result = num1/num2;
        printf("Result= %0.2lf \n",result);
        }
        else {
                printf("Division by zero is not allowed.\n");
               
        }
        
        break;

default:
    printf("Please enter Correct sign. ");
    break;
}

 return 0;
}