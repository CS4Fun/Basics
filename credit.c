/*
    Bad Credit
    
    Checks if a given credit card number is valid and then returns
    the credit company name or INVALID.
    
    - American Express uses 15-digit numbers
    - MasterCard uses 16-digit numbers
    - Visa uses 13- and 16-digit numbers
    And those are decimal numbers (0 through 9)
    
    - American Express numbers all start with 34 or 37
    - MasterCard numbers all start with 51, 52, 53, 54, or 55
    - Visa numbers all start with 4
    
    Credit card numbers also have a "checksum" built into them:
    1) Multiply every other digit by 2, starting with the number’s
        second-to-last digit, and then add those products' digits together.
    2) Add the sum to the sum of the digits that weren’t multiplied by 2.
    3) If the total’s last digit is 0 (or, put more formally,
        if the total modulo 10 is congruent to 0), the number is valid!
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int sum = 0, sum_odd = 0, temp;
    printf("Enter credit card number: ");
    long long card_num = GetLongLong();
    long long card_num_truc;
    
    /*
        1. Multiply every other digit by 2, starting with the number’s
            second-to-last digit, and then add those products' digits together.
        2. Add the sum to the sum of the digits that weren’t multiplied by 2.
        3. If the total’s last digit is 0 (or, put more formally, if the total
            modulo 10 is congruent to 0), the number is valid!
    */

    /* At most 16 digit number. Multiple 2 for digit at place:
        16th, 14th, 12th, 10th, 8th, 6th, 4th, and 2nd. */
    
    card_num_truc = card_num % 10000000000000000;
    long long divisor = 1000000000000000;
    while (divisor > 0)
    {
        temp = card_num_truc/divisor * 2;
        
        /* Double of a single digit is at most 18 (or a 2-digit product) */
        sum += temp/10 + temp%10;
        card_num_truc %= (divisor/10);
        divisor /= 100;
    }

    card_num_truc = card_num % 10000000000000000;
    divisor = 100000000000000;
    while (divisor > 1)
    {
        sum_odd += card_num_truc/divisor;
        card_num_truc %= (divisor/10);
        divisor /= 100;
    }
    sum_odd += card_num_truc/divisor;

    if (((sum + sum_odd)%10) == 0)
    {
        /* AMEX card use 15-digit number and starts with 34 or 37. */
        if ((card_num/10000000000000 == 34) || (card_num/10000000000000 == 37))
            printf("AMEX\n");
        /* MasterCard use 16-digit number and starts with 51-55. */
        else if ((card_num/100000000000000 >= 51) && (card_num/100000000000000 <= 55))
            printf("MASTERCARD\n");
        /* VISA card use 13 or 16-digit number and starts with 4. */
        else if ((card_num/1000000000000 == 4) || (card_num/1000000000000000 == 4))
            printf("VISA\n");
        else
            printf("INVALID\n");
    }
    else
    {
        printf("INVALID\n");
    }
    
}
