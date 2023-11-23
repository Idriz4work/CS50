#include "helpers.h"
#include "math.h"
#include "stdio.h"
#include "unistd.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for loop to get each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculating and rounding the average of the 3 values
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // each color gets the same value
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
    // set the minimum and the maximum
    int min = 0;
    int max = 255;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Sepiaformel for red, green and blue
            int SepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int SepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int SepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +  .131 * image[i][j].rgbtBlue);

            // fmax and fmin is in "math.h" "more comfortable"
            image[i][j].rgbtRed = fmin(max, SepiaRed);
            image[i][j].rgbtGreen = fmin(max, SepiaGreen);
            image[i][j].rgbtBlue = fmin(max, SepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temper is a copy of image[height][width] so we can store the reflected image
    RGBTRIPLE copy;
    for (int i = 0; i < height; i++)
    {
        int reflect = 0;
        // j gets the first numbers while reflect gets the numbers till the end
        // because of that we swab the image to the other side
        for (int j = 0; j < width / 2; j++, reflect++)
        {
            copy = image[i][j];
            image[i][j] = image[i][width - i -1];
            image[i][width - i -1] = copy;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy of image[height][width]
    RGBTRIPLE updated_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0 ; j < width; j++)
        {
            updated_image[i][j] = image[i][j];
        }
    }

   for (int i = 0; i < height ; i++)
   {
        for(int j = 0; j < width; j++)
        {
            int Red, Blue, Green;
            Red = Blue = Green = 0;
            float checker = 0.00;


            for (int sor = -1; sor < 2 ; sor++)
            {
                for(int core = -1; core < 2; core++)
                {
                int position1 = i + sor;
                int position2 = j + core;

                    if (position1 < 0 || position1 > (height-1) || position2 < 0 || position2 > (width-1))
                    {
                        continue;
                    }

                    Red += image[position1][position2].rgbtRed;
                    Blue += image[position1][position2].rgbtBlue;
                    Green += image[position1][position2].rgbtGreen;

                    checker++;
                }

                    updated_image[i][j].rgbtRed = round(Red / checker);
                    updated_image[i][j].rgbtGreen = round(Green / checker);
                    updated_image[i][j].rgbtBlue = round(Blue / checker);
            }
        }
   }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
                image[i][j].rgbtRed = updated_image[i][j].rgbtRed;
                image[i][j].rgbtGreen = updated_image[i][j].rgbtGreen;
                image[i][j].rgbtBlue = updated_image[i][j].rgbtBlue;
        }
    }
    return;
}
