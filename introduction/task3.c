#include <stdio.h>
#include <stdlib.h>


void convert(unsigned char tempC)
{   
    float tempF = (tempC * 9.0/5.0 )+ 32;
    printf("Temp in F:  %0.2f \n",tempF);
}

int main()
{
    // Converting temp in Celius to Fahrenheit
    convert(25);
    return 0;
}