#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    // Asks for the min number
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    // Asks for the max number
    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    // Checks if its prime
    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // TODO
    // For 1 and below
    if (number <= 1)
    {
        return false;
    }

    // For 2 and above
    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}
