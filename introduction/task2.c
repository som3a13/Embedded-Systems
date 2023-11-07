#include <stdio.h>
#include <stdlib.h>


void print(char name[],unsigned char age)
{
    printf("Name: %s | Age:  %u \n",name,age);
}

int main()
{
    char name[] = "Mohamed Ismail";
    unsigned char age = 23;
    print(name,age);
    return 0;
}