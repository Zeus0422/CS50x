#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = ((float)image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0;
            int average_rounded = round(average);

            image[i][j].rgbtRed = average_rounded;
            image[i][j].rgbtGreen = average_rounded;
            image[i][j].rgbtBlue = average_rounded;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int original_red = image[i][j].rgbtRed;
            int original_green = image[i][j].rgbtGreen;
            int original_blue = image[i][j].rgbtBlue;

            float new_red = ((float).393 * original_red + .769 * original_green + .189 * original_blue);
            int new_red_rounded = round(new_red);

            float new_green = ((float).349 * original_red + .686 * original_green + .168 * original_blue);
            int new_green_rounded = round(new_green);

            float new_blue = ((float).272 * original_red + .534 * original_green + .131 * original_blue);
            int new_blue_rounded = round(new_blue);

            if (new_red_rounded > 255)
            {
                new_red_rounded = 255;
            }
            if (new_green_rounded > 255)
            {
                new_green_rounded = 255;
            }
            if (new_blue_rounded > 255)
            {
                new_blue_rounded = 255;
            }

            image[i][j].rgbtRed = new_red_rounded;
            image[i][j].rgbtGreen = new_green_rounded;
            image[i][j].rgbtBlue = new_blue_rounded;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][width - j - 1];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
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
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += copy[ni][nj].rgbtRed;
                        sumGreen += copy[ni][nj].rgbtGreen;
                        sumBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = round((float)sumRed / count);
            image[i][j].rgbtGreen = round((float)sumGreen / count);
            image[i][j].rgbtBlue = round((float)sumBlue / count);
        }
    }
}
