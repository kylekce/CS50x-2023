#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask user for the height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // print
    for (int row = 1; row <= height; row++)
    {
        // print spaces
        for (int col2_space = height - row; col2_space > 0; col2_space--)
        {
            printf(" ");
        }

        // print hashes
        for (int col = 1; col <= 2; col++)
        {
            for (int col2 = 0; col2 != row; col2++)
            {
                printf("#");
            }
            if (col == 1)
            {
                printf("  ");
            }
        }

        // print newline
        printf("\n");
    }
}