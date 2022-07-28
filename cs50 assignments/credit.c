// credit.c checks if an inputted credit number is a valid credit card type. For specifications, view: https://cs50.harvard.edu/x/2022/psets/1/credit/


#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card = get_long("Number: ");
    int digits = 0;
    int prefix, remainder;
    int even = 0;
    int luhns = 0;

    // count digits in number
    do
    {
        remainder = card % 10;
        card = card / 10;
        digits++;

        // find card prefix
        if (card < 100 && card >= 10)
        {
            prefix = card;
        }

        // calculate Luhn's Algorithm p1
        if (digits % 2 == 0)
        {
            remainder = remainder * 2;
            remainder = remainder % 10 + remainder / 10;
            even = even + remainder;
        }

        // calculate Luhn's Algorithm p2
        else if (digits % 2 > 0)
        {
            luhns = luhns + remainder;
        }
    }
    while (card > 1);

    // find Luhn's #
    luhns = luhns + even;

    // What card is it
    if (luhns % 10 == 0)
    {
        // AMEX identifier
        if (digits == 15 && (prefix == 34 || prefix == 37))
        {
            //if (digits == 15)
            //{
                printf("AMEX\n");
            //}
            //else
            //{
                //printf("INVALID\n");
            //}
        }

        // MASTERCARD identifier
        else if (digits == 16 && (prefix >= 51 && prefix <= 55))
        {
            //if (digits == 16)
            //{
                printf("MASTERCARD\n");
            //}
            //else
            //{
                //printf("INVALID\n");
            //}
        }

        // VISA identifier
        else if ((digits == 13 || digits == 16) && (prefix >= 40 && prefix <= 49))
        {
            //if (digits == 13 || digits == 16)
            //{
                printf("VISA\n");
            //}
            //else
            //{
                //printf("INVALID\n");
            //}
        }

        // solves luhn's but not a card
        else
        {
            printf("INVALID\n");
        }
    }

    // not a card #
    else
    {
        printf("INVALID\n");
    }
}
