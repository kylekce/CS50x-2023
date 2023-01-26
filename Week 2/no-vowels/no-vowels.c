// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string str);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        printf("%s\n", replace(argv[1]));
    }
    else
    {
        printf("Error: None or more than one command-line arguent was given.");
        return 1;
    }
}

string replace(string str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'a')      // a turns to 6
        {
            str[i] = '6';
        }
        else if (str[i] == 'e') // e turns to 3
        {
            str[i] = '3';
        }
        else if (str[i] == 'i') // i turns to 1
        {
            str[i] = '1';
        }
        else if (str[i] == 'o') // o turns to 0
        {
            str[i] = '0';
        }
    }
    return str;
}