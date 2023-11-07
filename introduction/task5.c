
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void printASCII(unsigned char userInput)
{
    printf("%u",userInput);
}

int main()
{
    static unsigned char userInput;
    scanf("%c",&userInput);
    while(1)
    {
        if(isalpha(userInput))
    {
        printASCII(userInput);
        break;
    }
        else
    {
        scanf("%c",&userInput);
    }
    }
    
    
    return 0;



}