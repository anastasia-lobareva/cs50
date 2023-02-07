#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;
// block size to read
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover filename.raw\n");
        return 1;
    }

    // Open input file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    // create an array for buffer
    BYTE buffer[BLOCK_SIZE];

    // set image counter
    int fileNumber = 0;

    // set outfile pointer
    FILE *newJPEG = NULL;

    // lock memory to hold file name
    char fileName[8];

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (newJPEG != NULL)
            {
                fclose(newJPEG);
            }
            sprintf(fileName, "%03i.jpg", fileNumber);
            newJPEG = fopen(fileName, "w");
            fileNumber++;
        }

        if (newJPEG != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, newJPEG);
        }
    }
    fclose(newJPEG);
    fclose(file);

    return 0;
}