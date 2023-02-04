// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first for items to the menu array
void add_items(void)
{
    string itemArr[] = {"Burger", "Vegan Burger", "Hot Dog", "Cheese Dog", "Fries", "Cheese Fries", "Cold Pressed Juice", "Cold Brew", "Water", "Soda"};
    float priceArr[] = {9.50, 11.00, 5.00, 7.00, 5.00, 6.00, 7.00, 3.00, 2.00, 2.00};

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        menu[i].item = itemArr[i];
        menu[i].price = priceArr[i];
    }
    return;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    // corrects the case
    for (int i = 0; i < strlen(item); i++)
    {
        if (i == 0)
        {
            item[i] = toupper(item[i]);
        }
        else if (isspace(item[i - 1]))
        {
            item[i] = toupper(item[i]);
        }
        else
        {
            item[i] = tolower(item[i]);
        }
    }

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (strcmp(item, menu[i].item) == 0)
        {
            return menu[i].price;
        }
    }
    return 0.0;
}
