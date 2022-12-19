#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // compute and return score for string
    int length = strlen(word);

    int indexValue;

    int score = 0;

    for (int i = 0; i < length; i++)
    {
        // check if char is letter
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))
        {
            if (isupper(word[i]))
            {
                indexValue = word[i] - 65;
                indexValue = POINTS[indexValue];
            }
            else
            {
                indexValue = word[i] - 97;
                indexValue = POINTS[indexValue];
            }
        }
        else
        {
            indexValue = 0;
        }
        score = score + indexValue;
    }
    return score;
}