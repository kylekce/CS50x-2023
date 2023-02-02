#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input, int len);

int main(void)
{
    // inputs a string of positive integer
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input, strlen(input)));
}

int convert(string input, int len)
{
    // TODO
    // base case
    if (len == 0)
    {
        return 0;
    }

    int num = input[len - 1] - '0';
    return num + 10 * convert(input, len - 1);
}