// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t TWOBYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // // Copy header from input file to output file
    // BYTE header[HEADER_SIZE];
    // fread(&header,  sizeof(BYTE), HEADER_SIZE, input);
    // fwrite(&header, sizeof(BYTE), HEADER_SIZE, output);

    // //Read samples from input file and write updated data to output file
    // //Note that the cursor is already at the proper position from the previous read
    // // TWOBYTE buffer;
    // // int count=0; //Count how many TWOBYTES we have gone through
    // // while (fread(&buffer,sizeof(TWOBYTE),1,input))
    // // {
    // //     if (count > HEADER_SIZE/2)
    // //     {
    // //         buffer *= factor; //Multiply by scaling factor
    // //     }
    // //     fwrite(&buffer,sizeof(TWOBYTE),1,input);
    // //     count++;
    // // }

    // Copy source to destination, one BYTE at a time
    TWOBYTE buffer;
    long count=0;
    while (fread(&buffer, sizeof(TWOBYTE), 1, input))
    {
        if (count>22){
            buffer *= factor;
        }
        fwrite(&buffer, sizeof(TWOBYTE), 1, output);
        count++;
    }

    // Close files
    fclose(input);
    fclose(output);
}
