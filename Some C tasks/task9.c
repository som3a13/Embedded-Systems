#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
void mark(int grade)
{
    if(grade>=85)
    {
        printf("Grade equals %d you got EXCELLENT ",grade);
    }
    else if (grade >=75 && grade <85) {
        printf("Grade equals %d you got Very GOOD ",grade);
    }
    else if (grade >=65 && grade < 75 ) {
        printf("Grade equals %d you got GOOD ",grade);
    }
    else if (grade <65 && grade >=50 ) {
        printf("Grade equals %d you PASSED ",grade);
    }
    else
    {
        printf("Grade equals %d you failed ",grade);
    }
}

int main()
{

   mark(75);
    return 0;
}

