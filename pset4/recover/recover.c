#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Number of bytes in a block
const int BLOCK_SIZE = 512;

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover file.raw\n");
        return 1;
    }

    // Open file
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    //Variable to check end of card (fread returns < BLOCK_SIZE)
    int end_check=BLOCK_SIZE;

    //Count how many jpgs have been recovered
    int jpg_count=0;

    //Filename
    char filename[10];

    //Pointer to file
    FILE *img = NULL;

    //Create a buffer
    BYTE buffer[BLOCK_SIZE];

    //Iterate through memory card
    while (1)
    {
        //Read file
        end_check = fread(&buffer, sizeof(BYTE), BLOCK_SIZE,raw_file);

        //Check for end of file
        if (end_check != BLOCK_SIZE)
        {
            break; //Quit
        }
        //Check for jpg file
        if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (jpg_count>0)
            {
                //After the first jpg has already been found
                //Close previously opened file
                fclose(img);
            }

            //Create new filename
            sprintf(filename,"%03i.jpg",jpg_count);

            //Open new file
            img = fopen(filename,"w");

            //Write content to file
            fwrite(&buffer,sizeof(BYTE),BLOCK_SIZE,img);

            //Increment jpg count (found a jpg)
            jpg_count++;

        }
        else
        {
            //Not the start of a jpg file; must be part of one!
            if (jpg_count > 0)
            {
                //Keep writing only after finding the first jpg!
                fwrite(&buffer,sizeof(BYTE),BLOCK_SIZE,img);
            }
        }

    }

    fclose(raw_file);
    fclose(img);

    return 0;
}