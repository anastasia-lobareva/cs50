#include <cs50.h>
#include <stdio.h>
#include <math.h>

long get_cardNumber(void);
int get_digitCount(long cardNumber);
int get_firstNumber(long cardNumber, int count);
int get_secondDigitSum(long cardNumber);
int get_firstDigitSum(long cardNumber);

int main(void)
{
    // get a card number
    long cardNumber = get_cardNumber();
    // Check if the card number is valid
    int secondDigitSum = get_secondDigitSum(cardNumber);
    int firstDigitSum = get_firstDigitSum(cardNumber);

    if ((firstDigitSum + secondDigitSum) % 10 == 0)
    {
        // check Amex and Master Card conditions using first two digits of the card number
        int digitCount = get_digitCount(cardNumber);
        int firstNumber = get_firstNumber(cardNumber, 2);

        if ((firstNumber == 34 || firstNumber == 37) && digitCount == 15)
        {
            printf("AMEX\n");
        }
        else if ((firstNumber > 50 && firstNumber < 56) && digitCount == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            //check Visa condition using first digit of the card number
            firstNumber = get_firstNumber(cardNumber, 1);

            if ((digitCount == 13 || digitCount == 16) && firstNumber == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}


long get_cardNumber(void)
{
    // get a card number from a user
    long cardNumber;
    do
    {
        cardNumber = get_long("Card number: ");
    }
    while (cardNumber < 1);
    return cardNumber;
}

int get_digitCount(long cardNumber)
{
    // counting number of digits in the card number
    int digitNumber = 0;

    do
    {
        cardNumber /= 10;
        digitNumber++;
    }
    while (cardNumber != 0);
    return digitNumber;
}

int get_firstNumber(long cardNumber, int count)
{
    // execute first one or two digits of card number
    int firstNumber;

    int numberLength = pow(10, count);

    do
    {
        firstNumber = cardNumber /= 10;
    }
    while (cardNumber >= numberLength);
    return firstNumber;
}

int get_firstDigitSum(long cardNumber)
{
    // getting sum of every other digit starting from the last
    int mod;

    int firstDigitSum = 0;

    do
    {
        mod = cardNumber % 10;
        firstDigitSum = firstDigitSum + mod;
        cardNumber = cardNumber / 100;
    }
    while (cardNumber > 0);
    return firstDigitSum;
}

int get_secondDigitSum(long cardNumber)
{
    // starting with the number’s second-to-last digit, multiply every other digit by 2, and then add those products’ digits together
    int mod;

    int secondDigitSum = 0;

    cardNumber = cardNumber / 10;

    do
    {
        mod = cardNumber % 10;
        if (mod * 2 < 9)
        {
            secondDigitSum = secondDigitSum + mod * 2;
        }
        else
        {
            secondDigitSum = secondDigitSum + ((mod * 2) - 9);
        }
        cardNumber = cardNumber / 100;
    }
    while (cardNumber > 0);
    return secondDigitSum;
}