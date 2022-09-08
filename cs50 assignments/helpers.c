#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // take average of RBG values
            float average = (image[h][w].rgbtRed + image[h][w].rgbtBlue + image[h][w].rgbtGreen) / 3.0;
            average = round(average);
            // set all RBG values to average to convert to greyscale
            image[h][w].rgbtRed = average;
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels for left half of image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            // store pixel in temporary variable
            RGBTRIPLE temp = image[h][w];
            // swap pixels with pixel on mirrored side
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create temp image to store blurred pixels
    RGBTRIPLE temp[height][width];
    // Loop through all pixels
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // create arrays (max 9) to store RGB values used to calculate blurred average
            int red[9];
            int blue[9];
            int green[9];
            int fill = 0;
            // float to divide by number of valid pixels
            float count = 0;
            // loop through each 3x3 square within 1 row and 1 column of original pixel
            for (int h_loop = 0; h_loop < 3; h_loop++)
            {
                for (int w_loop = 0; w_loop < 3; w_loop++)
                {
                    // start from upper right pixel in 3x3
                    int x = h + 1 - h_loop;
                    int y = w + 1 - w_loop;
                    // if pixels are within image height and width bounds, add RGB values to arrays
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        red[fill] = image[x][y].rgbtRed;
                        blue[fill] = image[x][y].rgbtBlue;
                        green[fill] = image[x][y].rgbtGreen;
                        fill++;
                        count++;
                    }
                    // if pixel is outside of image border, set all RGB values to 0
                    else
                    {
                        red[fill] = 0;
                        blue[fill] = 0;
                        green[fill] = 0;
                        fill++;
                    }
                }
            }
            // calculate average blurred values and store in temporary image
            float avg_red = (red[0] + red[1] + red[2] + red[3] + red[4] + red[5] + red[6] + red[7] + red[8]) / count;
            avg_red = round(avg_red);
            temp[h][w].rgbtRed = avg_red;
            float avg_blue = (blue[0] + blue[1] + blue[2] + blue[3] + blue[4] + blue[5] + blue[6] + blue[7] + blue[8]) / count;
            avg_blue = round(avg_blue);
            temp[h][w].rgbtBlue = avg_blue;
            float avg_green = (green[0] + green[1] + green[2] + green[3] + green[4] + green[5] + green[6] + green[7] + green[8]) / count;
            avg_green = round(avg_green);
            temp[h][w].rgbtGreen = avg_green;
        }
    }
    // move stored blurred image to original
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = temp[h][w];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create temp image to store blurred pixels
    RGBTRIPLE temp[height][width];
    // create arrays (max 9) to store RGB values used to calculate blurred average
    int redX[9];
    int blueX[9];
    int greenX[9];
    int redY[9];
    int blueY[9];
    int greenY[9];
    // Loop through all pixels
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int fill = 0;
            for (int h_loop = 0; h_loop < 3; h_loop++)
            {
                for (int w_loop = 0; w_loop < 3; w_loop++)
                {
                    // start from upper right pixel in 3x3
                    int x = h + 1 - h_loop;
                    int y = w + 1 - w_loop;
                    if (fill > 8)
                    {
                        break;
                    }
                    // if pixels are within image height and width bounds
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        // multiply kernels depending on location of pixel in 3x3
                        if (fill == 0)
                        {
                            redX[fill] = image[x][y].rgbtRed;
                            redY[fill] = image[x][y].rgbtRed * -1;
                            blueX[fill] = image[x][y].rgbtBlue;
                            blueY[fill] = image[x][y].rgbtBlue * -1;
                            greenX[fill] = image[x][y].rgbtGreen;
                            greenY[fill] = image[x][y].rgbtGreen * -1;
                            fill++;
                        }
                        else if (fill == 1)
                        {
                            redX[fill] = 0;
                            redY[fill] = image[x][y].rgbtRed * -2;
                            blueX[fill] = 0;
                            blueY[fill] = image[x][y].rgbtBlue * -2;
                            greenX[fill] = 0;
                            greenY[fill] = image[x][y].rgbtGreen * -2;
                            fill++;
                        }
                        else if (fill == 2)
                        {
                            redX[fill] = image[x][y].rgbtRed * -1;
                            redY[fill] = image[x][y].rgbtRed * -1;
                            blueX[fill] = image[x][y].rgbtBlue * -1;
                            blueY[fill] = image[x][y].rgbtBlue * -1;
                            greenX[fill] = image[x][y].rgbtGreen * -1;
                            greenY[fill] = image[x][y].rgbtGreen * -1;
                            fill++;
                        }
                        else if (fill == 3)
                        {
                            redX[fill] = image[x][y].rgbtRed * 2;
                            redY[fill] = 0;
                            blueX[fill] = image[x][y].rgbtBlue * 2;
                            blueY[fill] = 0;
                            greenX[fill] = image[x][y].rgbtGreen * 2;
                            greenY[fill] = 0;
                            fill++;
                        }
                        else if (fill == 4)
                        {
                            redX[fill] = 0;
                            redY[fill] = 0;
                            blueX[fill] = 0;
                            blueY[fill] = 0;
                            greenX[fill] = 0;
                            greenY[fill] = 0;
                            fill++;
                        }
                        else if (fill == 5)
                        {
                            redX[fill] = image[x][y].rgbtRed * -2;
                            redY[fill] = 0;
                            blueX[fill] = image[x][y].rgbtBlue * -2;
                            blueY[fill] = 0;
                            greenX[fill] = image[x][y].rgbtGreen * -2;
                            greenY[fill] = 0;
                            fill++;
                        }
                        else if (fill == 6)
                        {
                            redX[fill] = image[x][y].rgbtRed * 1;
                            redY[fill] = image[x][y].rgbtRed * 1;
                            blueX[fill] = image[x][y].rgbtBlue * 1;
                            blueY[fill] = image[x][y].rgbtBlue * 1;
                            greenX[fill] = image[x][y].rgbtGreen * 1;
                            greenY[fill] = image[x][y].rgbtGreen * 1;
                            fill++;
                        }
                        else if (fill == 7)
                        {
                            redX[fill] = 0;
                            redY[fill] = image[x][y].rgbtRed * 2;
                            blueX[fill] = 0;
                            blueY[fill] = image[x][y].rgbtBlue * 2;
                            greenX[fill] = 0;
                            greenY[fill] = image[x][y].rgbtGreen * 2;
                            fill++;
                        }
                        else if (fill == 8)
                        {
                            redX[fill] = image[x][y].rgbtRed * -1;
                            redY[fill] = image[x][y].rgbtRed * 1;
                            blueX[fill] = image[x][y].rgbtBlue * -1;
                            blueY[fill] = image[x][y].rgbtBlue * 1;
                            greenX[fill] = image[x][y].rgbtGreen * -1;
                            greenY[fill] = image[x][y].rgbtGreen * 1;
                            fill++;
                        }
                    }
                    // if pixel is outside of image border, set all RGB values to 0
                    else
                    {
                        redX[fill] = 0;
                        blueX[fill] = 0;
                        greenX[fill] = 0;
                        redY[fill] = 0;
                        blueY[fill] = 0;
                        greenY[fill] = 0;
                        fill++;
                    }
                }
            }
            // calculate red value
            int red_Gx = (redX[0] + redX[1] + redX[2] + redX[3] + redX[4] + redX[5] + redX[6] + redX[7] + redX[8]);
            int red_Gy = (redY[0] + redY[1] + redY[2] + redY[3] + redY[4] + redY[5] + redY[6] + redY[7] + redY[8]);
            int SobelR = round(sqrt(pow(red_Gx, 2) + pow(red_Gy, 2)));
            // set channel value limit
            if (SobelR > 255)
            {
                SobelR = 255;
            }
            temp[h][w].rgbtRed = SobelR;
            // calculate blue value
            int blue_Gx = (blueX[0] + blueX[1] + blueX[2] + blueX[3] + blueX[4] + blueX[5] + blueX[6] + blueX[7] + blueX[8]);
            int blue_Gy = (blueY[0] + blueY[1] + blueY[2] + blueY[3] + blueY[4] + blueY[5] + blueY[6] + blueY[7] + blueY[8]);
            int SobelB = round(sqrt(pow(blue_Gx, 2) + pow(blue_Gy, 2)));
            // set channel value limit
            if (SobelB > 255)
            {
                SobelB = 255;
            }
            temp[h][w].rgbtBlue = SobelB;
            // calculate green value
            int green_Gx = (greenX[0] + greenX[1] + greenX[2] + greenX[3] + greenX[4] + greenX[5] + greenX[6] + greenX[7] + greenX[8]);
            int green_Gy = (greenY[0] + greenY[1] + greenY[2] + greenY[3] + greenY[4] + greenY[5] + greenY[6] + greenY[7] + greenY[8]);
            int SobelG = round(sqrt(pow(green_Gx, 2) + pow(green_Gy, 2)));
            // set channel value limit
            if (SobelG > 255)
            {
                SobelG = 255;
            }
            temp[h][w].rgbtGreen = SobelG;
        }
    }
    // move stored image with edges to original
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = temp[h][w];
        }
    }
    return;
}