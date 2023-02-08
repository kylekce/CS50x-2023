#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // if pixel is white turn to red
            if (image[i][j].rgbtRed == 0xff && image[i][j].rgbtGreen == 0xff && image[i][j].rgbtBlue == 0xff)
            {
                image[i][j].rgbtGreen = 0x00;
                image[i][j].rgbtBlue = 0x00;
            }
            // if pixel is black turn to yellow
            else if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                image[i][j].rgbtRed = 0xff;
                image[i][j].rgbtGreen = 0xff;
            }
        }
    }
}