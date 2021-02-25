#include <stdio.h>
#include <cs50.h>

//Function to print the solid blocks of the pyramid
void print_pyramid(int line)
{

    for (int j = 0 ; j < line ; j++)
    {
        printf("#");
    }

}

int main(void)
{
    //Get height
    int height = 0;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //Pyramid loop
    for (int line = 1 ; line <= height ; line++)
    {

        //Count empty spaces to the left/right
        int empty = height - line;


        //Left side spaces
        for (int j = 0 ; j < empty ; j++)
        {
            printf(" ");
        }

        //Left side of pyramid
        print_pyramid(line);

        //Midle spaces
        printf("  ");

        //Right side of pyramid
        print_pyramid(line);

        //Line skip to be pretty
        printf("\n");
    }
}