#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0)
            {
                continue;
            }
            image[i][j].rgbtBlue = 90;
            image[i][j].rgbtRed = 29;
            image[i][j].rgbtGreen = 170;
        }
    }
}
