#include "helpers.h"
#include <math.h>


float min (float num1, float num2) {
//Function to evaluate a minimum value between 2 floats

    if (num1 < num2)
    {
        return num1;
    }
    else
    {
        return num2;
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Iterate through the whole picture
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Get blue, red and green values
            float blue = image[h][w].rgbtBlue;
            float red = image[h][w].rgbtRed;
            float green = image[h][w].rgbtGreen;

            //Calculate grayscale value
            int gray = round((blue+red+green)/3.0);

            //Set values to grayscale value.
            image[h][w].rgbtBlue=gray;
            image[h][w].rgbtRed=gray;
            image[h][w].rgbtGreen=gray;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Iterate through the whole picture
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Get blue, red and green values
            float blue = image[h][w].rgbtBlue;
            float red = image[h][w].rgbtRed;
            float green = image[h][w].rgbtGreen;

            //Calculate sepia filter values
            int sepia_red=round(min(0.393*red + 0.769*green + 0.189*blue,255));
            int sepia_green=round(min(0.349*red + 0.686*green + 0.168*blue,255));
            int sepia_blue=round(min(0.272*red + 0.534*green + 0.131*blue,255));

            //Set values to sepia value.
            image[h][w].rgbtBlue=sepia_blue;
            image[h][w].rgbtRed=sepia_red;
            image[h][w].rgbtGreen=sepia_green;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Get the midpoint
    int mid = width/2;

    //Iterate through all lines of pixels
    for (int h = 0; h < height; h++)
    {
        //Iterate through HALF of pixels
        for (int w = 0; w < mid; w++)
        {
            //Store image[h][w] in a temp variable
            RGBTRIPLE temp = image[h][w];

            //Swap image[h][w] with image[h][(width-1)-w]
            image[h][w]=image[h][(width-1)-w];
            image[h][(width-1)-w]=temp;


            // //Position of the "mirrored" pixel
            // int mirror = (width-1)-w;

            // //Temporary RGBTRIPLE to store values
            // RGBTRIPLE temp = image[h][w];

            // //Only mirror if mirror != w (mirror == w in the midpoint of a picture with an even number of pixels)

            // //Copy color values from the right-side equivalent
            // copyrgbt(image[h][mirror],&image[h][w]);

            // //Copy color values from temp to the right side
            // copyrgbt(temp,&image[h][mirror]);


        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Make a copy of  image
    RGBTRIPLE copy[height][width];

    for (int h = 0; h < height; h++)
        for (int w = 0; w < width; w++)
            copy[h][w]=image[h][w];

    //Apply blur filter
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Variables to count total red, green and blue amounts
            float red = 0, green = 0, blue = 0;

            //Count how many pixels were used in the average
            float counter = 0;

            //Iterate through neighbors
            for (int i = -1; i <= 1; i++)
            {

                for (int j = -1; j <= 1; j++)
                {
                    //Check for valid row
                    if (h + i < 0 || h + i > (height -1))
                    {
                        continue; //Don't do anything, invalid pixel
                    }

                    //Check for valid column
                    if (w + j < 0 || w + j > (width-1))
                    {
                        continue; //Same
                    }

                    blue += copy[h+i][j+w].rgbtBlue;
                    red += copy[h+i][j+w].rgbtRed;
                    green += copy[h+i][j+w].rgbtGreen;
                    counter++;
                }
            }

            //Assign averages
            image[h][w].rgbtBlue=round(blue/counter);
            image[h][w].rgbtRed=round(red/counter);
            image[h][w].rgbtGreen=round(green/counter);
        }
    }
    return;
}
