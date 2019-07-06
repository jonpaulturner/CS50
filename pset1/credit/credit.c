//credit

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long int cc_num;
    cc_num = get_long("Type in a credit card number:  ");

    long int cc_type;
    cc_type = cc_num;


//Specify all variables needed to run Luhn's algorithm
    int digit = 0;
    int singlesum = 0;
    int doublesum = 0;
    int extradigit = 0;
//Run the loop for Luhn's algorithm
    while (cc_num > 0){
        //For each digit that is not multiplied, add to the single sum and move to the next digit
        digit = cc_num % 10;
        singlesum = singlesum + digit;
        cc_num = (cc_num - digit) / 10;

        //For each digit that needs to be doubled:
        digit = 2* (cc_num % 10);
        //Seperate product into two seperate digits
        while (digit > 10){
            //move to the correct digit, store the two product digits in seperate variables, then add to the double sum
            extradigit = digit % 10;
            digit = (digit - extradigit) / 10;
            doublesum = doublesum + digit + extradigit;
        }

        cc_num = (cc_num - digit) / 10;

    }

    //Check if CC is valid with Luhn's algorithm
    int totalsum = singlesum + doublesum;
    //printf ("Totalsum: %d\n", totalsum);

    int totalsumcheck = totalsum % 10;
    //printf("Totalsumcheck: %d\n", totalsumcheck);

    int firsttwodigits;
    int firstdigit;

    long int thirteen_digit = 100000000000;
    long int fourteen_digit = 1000000000000;
    long int fifteen_digit = 10000000000000;
    long int sixteen_digit = 100000000000000;
    long int seventeen_digit = 1000000000000000;


    while (cc_type > 10){

    if (totalsum % 10 != 0){
        printf("INVALID\n");
        break;
    }
    //----------------------------------PROGRAM CORRECT ABOVE THIS LINE---------------------------------------

    else if (cc_type / fifteen_digit == 34 || cc_type / fifteen_digit == 37){
        printf("AMEX\n");
        break;
    }
    else if (cc_type / sixteen_digit == 51 || cc_type / sixteen_digit == 52 || cc_type / sixteen_digit == 53 || cc_type / sixteen_digit == 54 || cc_type / sixteen_digit == 55){
        printf("MASTERCARD\n");
        break;
    }
    else if (cc_type / seventeen_digit == 4 || cc_type / fourteen_digit == 4 ){
        printf("VISA\n");
        break;
    }
    else{
        //printf("UNKNOWN or NOT WORKING\n");
        printf("INVALID\n");
        break;
    }
}
}