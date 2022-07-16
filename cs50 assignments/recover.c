// recover.c opens, reads, and writes files to recover photos from a given camera card.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// define new type BYTE
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // if user enters more than one argument, remind user of correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // opens argument file
    FILE *file = fopen(argv[1], "r");
    // if argument file cannot be read, inform user
    if (file == NULL)
    {
        printf("Forensic image cannot be opened for reading\n");
        return 1;
    }
    // create buffer to read argument file to
    BYTE buffer[512];
    // create new file for individual JPEG
    FILE *jpeg = NULL;
    char *jpeg_name = malloc(8);
    // counter of number of JPEGS in file
    int count = 0;
    // read data from argument file through end of file
    while (fread(buffer, 1, 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                // name new file
                sprintf(jpeg_name, "%03i.jpg", count);
                // open file to be written in
                jpeg = fopen(jpeg_name, "w");
                // write JPEG data to new file
                fwrite(buffer, 1, 512, jpeg);
                count++;
            }
            else
            {
                // close file
                fclose(jpeg);
                // name new file
                sprintf(jpeg_name, "%03i.jpg", count);
                // open file
                jpeg = fopen(jpeg_name, "w");
                // write into file
                fwrite(buffer, 1, 512, jpeg);
                count++;
            }
        }
        // if not new jpeg
        else
        {
            // keep writing into file
            if (count >= 1 && jpeg != NULL)
            {
                fwrite(buffer, 1, 512, jpeg);
            }
        }
    }
    // free memory
    free(jpeg_name);
    // close final JPEG
    fclose(jpeg);
}
