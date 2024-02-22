#include <stdio.h>

int digitCounter(int num) {
   int count = 0;
   if(num<0)
   {
    printf("Please enter positive number");
   }else if(num==0)
   {
    return 1;
   }
   while (num>0)
   {
    
    num/=10;
    count++;
   }
   return count;
}

int main() {
    static int num;
    printf("Please enter a number = ");
    scanf("%d", &num);
    int result = digitCounter(num);
    printf("Number of digits = %d \n",result);

}
