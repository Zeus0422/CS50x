#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text;

    text = get_string("Text: ");

    int number_of_letters = count_letters(text);
    //printf("%d letters\n", number_of_letters);

    int number_of_words = count_words(text);
    //printf("%d words\n", number_of_words);

    int number_of_sentences = count_sentences(text);
    //printf("%d sentences\n", number_of_sentences);

    float L = ((float) number_of_letters / number_of_words) * 100;
    float S = ((float) number_of_sentences / number_of_words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    int grade = round(index);

    if (grade>=16)
    {
        printf("Grade 16+\n");
    }
    else if(grade<1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }

    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isblank(text[i]))
        {
            count++;
        }
    }

    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }

    return count;
}