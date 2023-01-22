#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks for a name
    string name;
    name = get_string("Hi! What's your name? ");

    // Print
    printf("Hello, %s!\n", name);
}