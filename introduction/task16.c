#include <stdio.h>

int reverseNumber(int num) {
   int reversed = 0;
   while (num>0)
   {
    int digit = num%10;
    reversed = reversed * 10 + digit;
    num/=10;
   }
   return reversed;
}

int main() {
    static int num;
    printf("Please enter a number  to reverse = ");
    scanf("%d", &num);
    int result = reverseNumber(num);
    printf("Reversed number = %d \n",result);

}
