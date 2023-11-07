#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Circle {
    float radius; // Changed the data type to float
};

int main() {
    struct Circle c1;
    struct Circle *ptr = &c1;
    ptr->radius = 4.0; // Use a floating-point value for the radius
    float pi = 3.14;
    double area = pi * pow(ptr->radius, 2);
//gcc task4.c -o task4 -lm

    printf("%0.2lf", area);

    return 0;
}
