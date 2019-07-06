//credit


#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cc_num;
    cc_num = get_int("Type in a credit card number:  ");

        int digit = cc_num % 10;
        printf ("%d\n", digit);
        cc_num = cc_num - digit;
        //int cc_num1 = cc_num - digit;
        printf("%d\n", cc_num);

}


//take every digit, add to sum in a loop



//Final math, but with prints as tests

//credit

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long int cc_num;
    cc_num = get_long("Type in a credit card number:  ");

    int digit = 0;
    int singlesum = 0;
    int doublesum = 0;
    int extradigit = 0;

    while (cc_num > 0){
        digit = cc_num % 10;
        singlesum = singlesum + digit;
        cc_num = (cc_num - digit) / 10;
        //printf ("Digit:  %d\n", digit);
        //printf ("Singlesum:  %d\n", singlesum);
        //printf ("CC num:  %ld\n", cc_num);

        digit = cc_num % 10;
        digit = digit * 2;
        while (digit > 1){
            extradigit = digit % 10;
            digit = (digit - extradigit) / 10;
            doublesum = doublesum + digit + extradigit;
        }
        //doublesum = doublesum + 2 * digit;
        cc_num = (cc_num - digit) / 10;
        //printf ("Digit:  %d\n", digit);
        //printf ("Doublesum:  %d\n", doublesum);
        //printf ("CC num:  %ld\n", cc_num);

    }

    int totalsum = singlesum + doublesum;
    printf ("Totalsum: %d\n", totalsum);

    if (totalsum % 10 != 0){
        printf("INVALID\n");
    }
}


//AMEX\n or MASTERCARD\n or VISA\n or INVALID\n, nothing more, nothing less, and that main always return 0

//Adding the numbers instead of the single digits themselves