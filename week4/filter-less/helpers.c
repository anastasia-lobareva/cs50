#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average  = round(((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0));
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = fmin(sepiaBlue, 255);
            image[i][j].rgbtGreen = fmin(sepiaGreen, 255);
            image[i][j].rgbtRed = fmin(sepiaRed, 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE swap = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float count = 0.0;
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;

            for (int m = (i - 1); m <= (i + 1); m++)
            {
                for (int n = (j - 1); n <= (j + 1); n++)
                {
                    if (m < 0 || m >= height || n < 0 || n >= width)
                    {
                        continue;
                    }
                    sumBlue += copy[m][n].rgbtBlue;
                    sumGreen += copy[m][n].rgbtGreen;
                    sumRed += copy[m][n].rgbtRed;
                    count++;
                }
            }
            image[i][j].rgbtBlue = round(sumBlue / count);
            image[i][j].rgbtGreen = round(sumGreen / count);
            image[i][j].rgbtRed = round(sumRed / count);
        }
    }
    return;
}