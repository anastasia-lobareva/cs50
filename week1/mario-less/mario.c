#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    for (int l = 0; l < h; l++)
    {
        // space
        for (int s = 0; s < (h - (l + 1)); s++)
        {
            printf(" ");
        }
        // pyramid
        for (int p = 0; p <= l; p++)
        {
            printf("#");
        }

        printf("\n");
    }
}




