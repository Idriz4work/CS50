#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

string get_input(string text);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
double coleman_index(int letters, int sentences, int words);

int main(void)
{
    // propmt user for text
    string text = get_string("Text: ");

    // count letters
    int letters = count_letters(text);

    // count words
    int words = count_words(text);

    // count sentences
    int sentences = count_sentences(text);

    // calculating the index
    int index = coleman_index(letters, sentences, words);

    // print grade level of the text
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int letters = 0;
    {
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            if (islower(text[i]))
            {
                letters++;
            }
            else if (isupper(text[i]))
            {
                letters++;
            }
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    {
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            if (isblank(text[i]))
            {
                words++;
            }
        }
        words += 1;
    }

    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    {
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            //indicater for a sentence
            if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            {
                sentences++;
            }
        }
    }
    return sentences;
}

double coleman_index(int letters, int sentences, int words)
{
    float L = (float) letters / (float) words * 100;   // L = avereage letters per 100 words
    float S = (float) sentences / (float) words * 100; // S = avereage sentences per 100 words
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}