#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // asks for a line of text
    string text = get_string("Text: ");

    // gets the number of letters, words, and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // average number of letters per 100 words
    double l = (letters / (double)words) * 100;

    // average number of sentences per 100 words
    double s = (sentences / (double)words) * 100;

    // Coleman-Liau index
    double index = 0.0588 * l - 0.296 * s - 15.8;

    // prints the grade reading level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 0 && index < 16)
    {
        printf("Grade %i\n", (int)round(index));
    }
    else
    {
        printf("Grade 16+\n");
    }
}

// counts the letters
int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// counts the words
int count_words(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    return count + 1;
}

// counts the sentences
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i]) == '.' || (text[i]) == '!' || (text[i]) == '?')
        {
            count++;
        }
    }
    return count;
}