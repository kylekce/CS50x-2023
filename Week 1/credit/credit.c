#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

bool isValid(long n, string type);
string getType(long n);
int extract(long n, int place);
int getN(long n);
bool checksum(long n);

int main(void)
{
    string type;
    long n;

    // ask for the number
    n = get_long("Number: ");

    // figures what type of card
    type = getType(n);

    if (strcmp(type, "INVALID") == 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // is it valid?
        if (isValid(n, type))
        {
            printf("%s\n", type);
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

// checks the validity through n length and numcheck
bool isValid(long n, string type)
{
    if (strcmp(type, "VISA") == 0 && (getN(n) == 13 || getN(n) == 16))
    {
        return true;
    }
    else if (strcmp(type, "AMEX") == 0 && getN(n) == 15)
    {
        return true;
    }
    else if (strcmp(type, "MASTERCARD") == 0 && getN(n) == 16)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// gets what type of card
// visa, amex, or mastercard
string getType(long n)
{
    // visa check
    if (extract(n, 10) == 4 && checksum(n))
    {
        return "VISA";
    }
    // amex check
    else if ((extract(n, 100) == 34 || extract(n, 100) == 37) && checksum(n))
    {
        return "AMEX";
    }
    // mastercard check
    else if ((extract(n, 100) >= 51 && extract(n, 100) <= 55) && checksum(n))
    {
        return "MASTERCARD";
    }
    else
    {
        return "INVALID";
    }
}

// gets the specific number
// 10 == first digit, 100 == first 2 digits
int extract(long n, int place)
{
    while (n >= place)
    {
        n = n / 10;
    }
    return (int)n;
}

// gets the n length
int getN(long n)
{
    return log10(n) + 1;
}

// luhn's algorithm
bool checksum(long n)
{
    int sum = 0;
    int num_digits = 0;
    int parity = 0;
    long digits = n;

    while (digits > 0)
    {
        // checks if the current digit is in an odd position or an even position.
        if (parity == 1)
        {
            int digit = digits % 10;
            digit = digit * 2;
            if (digit > 9)
            {
                digit = digit - 9;
            }
            sum += digit;
        }
        else
        {
            sum += digits % 10;
        }
        digits /= 10;
        num_digits++;
        parity = 1 - parity;
    }

    if ((sum % 10) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}