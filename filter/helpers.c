#include "helpers.h"
#include <math.h>
#include <cs50.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)//row
    {
        for (int j = 0; j < width; j++)//col
        {
            RGBTRIPLE pixel = image[i][j];
            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            image[i][j].rgbtRed =  image[i][j].rgbtGreen =  image[i][j].rgbtBlue = average;

        }
    }

}
//check if cap
int exeed(int value)
{
    return value > 255 ? 255 : value;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)//row
    {
        for (int j = 0; j < width; j++)//col
        {
            RGBTRIPLE pixel = image[i][j];
            int originalRed = pixel.rgbtRed;
            int originalGreen = pixel.rgbtGreen;
            int originalBlue = pixel.rgbtBlue;
            //converting to sepia
            image[i][j].rgbtRed = exeed(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            image[i][j].rgbtGreen = exeed(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            image[i][j].rgbtBlue = exeed(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));
        }
    }
}
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)//row
    {
        for (int j = 0; j < width / 2; j++)//col
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
   
}
bool validPixel(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

RGBTRIPLE GetblurPixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int red = 0;
    int green = 0;
    int blue = 0;
    int num_Validpixel = 0;
    
    for (int k = -1; k <= 1; k++)
    {
        for (int l = -1; l <= 1; l++)
        {
            int new_i = i + k;
            int new_j = j + l;
            if (validPixel(new_i, new_j, height, width))
            {
                num_Validpixel ++;
                red += image[new_i][new_j].rgbtRed; 
                green += image[new_i][new_j].rgbtGreen;
                blue += image[new_i][new_j].rgbtBlue;
            }
        }
    }
    RGBTRIPLE blurPixel;
    blurPixel.rgbtRed = round((float)red / num_Validpixel);
    blurPixel.rgbtGreen = round((float)green / num_Validpixel);
    blurPixel.rgbtBlue = round((float)blue / num_Validpixel);
    
    return blurPixel;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newImage[i][j] = GetblurPixel(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = newImage[i][j];
        }
    }
}
