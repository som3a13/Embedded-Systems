#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
bool isPrime(int num)
{
    if (num <=1 ) {
        return false; 
    }
    else if( num <=3)
    {
        return true; 
    }
    else if (num %2 ==0 || num % 3==0)
    {
        return false;
    }
    //    for (int i = 5; i * i <= num; i += 6) {
    //     if (num % i == 0 || num % (i + 2) == 0) {
    //         return false;  // Numbers divisible by i or i+2 are not prime
    //     }
    // }

    return true;
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
        printf("Please enter positive number.\n");
        return 1;
    }
    if (isPrime(num))
    {

        printf("%d is a prime number.\n", num);
    } else {
        printf("%d is not a prime number.\n", num);
    }

       return 0 ;
}
