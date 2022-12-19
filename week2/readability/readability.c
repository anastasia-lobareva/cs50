#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int count_grade(int letters, int words, int sentences);

int main(void)
{
    // get text from the user
    string text = get_string("Text: ");

    // counting letters in the text
    int letters = count_letters(text);

    // counting words in the text
    int words = count_words(text);

    // counting sentences in the text
    int sentences = count_sentences(text);

    // getting grade by calculating Coleman-Liau index
    int grade = count_grade(letters, words, sentences);

    // print grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

int count_letters(string text)
{
    int length = strlen(text);

    int lettersCount;

    int letters = 0;

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            lettersCount = 1;
        }
        else
        {
            lettersCount = 0;
        }
        letters = letters + lettersCount;
    }
    return letters;
}

int count_words(string text)
{
    int length = strlen(text);

    int wordCount;

    int words = 1;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            wordCount = 1;
        }
        else
        {
            wordCount = 0;
        }
        words = words + wordCount;
    }
    return words;
}

int count_sentences(string text)
{
    int length = strlen(text);

    int sentencesCount;

    int sentences = 0;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentencesCount = 1;
        }
        else
        {
            sentencesCount = 0;
        }
        sentences = sentences + sentencesCount;
    }
    return sentences;
}

int count_grade(int letters, int words, int sentences)
{
    int grade = round(0.0588 * ((float)letters / words * 100) - 0.296 * ((float)sentences / words * 100) - 15.8);

    return grade;
}