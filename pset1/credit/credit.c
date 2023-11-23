#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long get_cc_number(void);
long calculate_digits(long ccn);
int check_lenght(long ccn, long digitsum);
//string print_cc_type();

int main (void)
{
    // getting card number / prompt user for number
    long ccn = get_cc_number();

    //calculate checksum
    int digitsum = calculate_digits(ccn);

    // checking lenght for creditcard type
    int length = check_lenght(ccn,digitsum);

    // printing the credit-card-type
    //string printf_cc_type();

}
long get_cc_number(void)
{
    long ccn;
    do
    {
        ccn = get_long("Enter your creditcard number: ");
    }
    while(ccn < 1000000000000000 || ccn > 9999999999999999);
    return ccn;
}
long calculate_digits(long ccn) //
{
    long digitsum;
    long digits_1 ;
    long digits_2 ;
    int ccn1, ccn2, ccn3, ccn4, ccn5, ccn6, ccn7, ccn8;
    int ccn_b1, ccn_b2, ccn_b3, ccn_b4, ccn_b5, ccn_b6, ccn_b7, ccn_b8;
    {
    // multiplying every second digit by 2
    ccn1 = ((ccn % 100)/10)*2;
    ccn2 = ((ccn % 10000)/1000*2);
    ccn3 = ((ccn % 1000000)/100000*2);
    ccn4 = ((ccn % 100000000)/100000000*2);
    ccn5 = ((ccn % 10000000000)/10000000000*2);
    ccn6 = ((ccn % 1000000000000)/1000000000000*2);
    ccn7 = ((ccn % 100000000000000)/10000000000000*2);
    ccn8 = ((ccn % 10000000000000000)/100000000000000*2);
     // now seperate the digits from the product

    ccn1 = (ccn1 % 100/10) + (ccn1 % 10);
    ccn2 = (ccn2 % 100/10) + (ccn2 % 10);
    ccn3 = (ccn3 % 100/10) + (ccn3 % 10);
    ccn4 = (ccn4 % 100/10) + (ccn4 % 10);
    ccn5 = (ccn5 % 100/10) + (ccn5 % 10);
    ccn6 = (ccn6 % 100/10) + (ccn6 % 10);
    ccn7 = (ccn7 % 100/10) + (ccn7 % 10);
    ccn8 = (ccn8 % 100/10) + (ccn8 % 10);
    digits_1 = ccn1 + ccn2 + ccn3 + ccn4 + ccn5 + ccn6 + ccn7 + ccn8;
    }

    // get the digits that are not multiplied by 2
    {
    ccn_b1 = (ccn % 10);
    ccn_b2 = ((ccn % 1000)/100);
    ccn_b3 = ((ccn % 100000)/10000);
    ccn_b4 = ((ccn % 10000000)/1000000);
    ccn_b5 = ((ccn % 1000000000)/100000000);
    ccn_b6 = ((ccn % 100000000000)/10000000000);
    ccn_b7 = ((ccn % 10000000000000)/1000000000000);
    ccn_b8 = ((ccn % 1000000000000000)/10000000000000);
    digits_2 = ccn_b1 + ccn_b2 + ccn_b3 + ccn_b4 + ccn_b5 + ccn_b6 + ccn_b7 + ccn_b8;
    }
        {
        // Add the digits that werent multiplied by 2 and those which did together by starting from the end
        digitsum = digits_1 + digits_2;
        }
        if((digitsum % 10)!=0)
    {
        printf("%li", digitsum);
        return 0;
    }
    return ccn;
}

int check_lenght(long ccn, long digitsum) //
{
    long amex = ccn;
    long visa = ccn;
    long mastercard = ccn;
    int length = 0;

    if((digitsum % 10)!=0)
    {
        printf("%li", digitsum);
        return 0;
    }
    return ccn;

    while(visa >= 10)
    {
        visa = visa/10;
    }
    if(visa == 4 && (length == 13 || length == 16))
    {
        printf("VISA");
    }
    else
    {
        printf("INVALID");
    }
    return visa;
    while(amex <= 100000000000000 )

    return amex;

}