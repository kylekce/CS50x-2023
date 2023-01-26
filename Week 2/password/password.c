// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool a, b, c, d;
    for (int i = 0; i < strlen(password); i++)
    {
        // checks for uppercase
        if (isupper(password[i]))
        {
            a = true;
        }
        // checks for lowercase
        if (islower(password[i]))
        {
            b = true;
        }
        // checks for number
        if (isdigit(password[i]))
        {
            c = true;
        }
        // checks for symbol
        if (password[i] == '!' || password[i] == '$' || password[i] == '#')
        {
            d = true;
        }
    }

    // checks all conditions
    if (a == true && b == true && c == true && d == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
