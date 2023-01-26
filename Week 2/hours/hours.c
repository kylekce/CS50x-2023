#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    // asks the number of hours of each week
    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    int total = 0; // variable for total hours
    if (output == 'T')
    {
        // calculate for total
        for (int i = 0; i < weeks; i++)
        {
            total += hours[i];
        }
        return total;
    }
    else
    {
        // calculate for average
        for (int i = 0; i < weeks; i++)
        {
            total += hours[i];
        }
        return total / (float)weeks;
    }
}