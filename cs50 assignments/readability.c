// readability.c utilizes the Coleman-Liau equation for calculating the grade-level of an inputted text. For specifications, view: https://cs50.harvard.edu/x/2022/psets/2/readability/


#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);

int count_words(string text);

int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    // Coleman-Liau calculation
    float L = 100 * ((float)count_letters(text) / count_words(text));
    float S = 100 * ((float)count_sentences(text) / count_words(text));
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // round Coleman-Liau to nearest whole #
    int grade = round(index);

    // print readability
    if (grade >= 1 && grade <= 15)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

// count letters
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
        else
        {
            letters += 0;
        }
    }
    return letters;
}

// count words
int count_words(string text)
{
    int words = 1;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == ' ')
        {
            words += 1;
        }
        else
        {
            words += 0;
        }
    }
    return words;
}


// count sentences
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == '.' | text[i] == '!' | text[i] == '?')
        {
            sentences += 1;
        }
        else
        {
            sentences += 0;
        }
    }
    return sentences;
}
