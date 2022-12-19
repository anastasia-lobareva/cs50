#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    const int SPACE = 2;

    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    for (int l = 0; l < h; l++)
    {
        // left spaces
        for (int ls = 0; ls < (h - (l + 1)); ls++)
        {
            printf(" ");
        }

        // left pyramid
        for (int lp = 0; lp <= l; lp++)
        {
            printf("#");
        }

        // middle spaces
        for (int ms = 0; ms < SPACE; ms++)
        {
            printf(" ");
        }

        // right pyramid
        for (int rp = 0; rp <= l; rp++)
        {
            printf("#");
        }

        printf("\n");
    }
}