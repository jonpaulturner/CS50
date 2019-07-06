//Recover
//pset4

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: file\n");
        return 1;
    }

    //Open memory card file to char array data
    FILE *file = fopen(argv[1], "r");

    //Check to ensure that fopen is working properly
    if (file == NULL)
    {
        fprintf(stderr, "Please include valid raw camera data\n");
        fclose(file);
        return 1;
    }

    //Declare first jpeg number
    int jpegnumber = 0;
    //Declare that we havent found a jpeg yet
    int jpegfound = 0;
    //Create buffer
    unsigned char buffer[512];
    //Create the filename
    char filename[8];

    FILE* img = NULL;

    //Declare a counter for the variable above
    int i = 0;
        //Start parsing through the data file one chunk at a time

    //OLD METHOD
    //while((fread(buffer, 512, 1, file) == 1))
    while((fread(buffer, sizeof(buffer), 1, file) == 1))
    {

        if (jpegfound == 0)
        {
        //Check if the block of data called is a JPEG
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0)
                {
                    //Open our first JPEG
                    sprintf(filename, "%03i.jpg", jpegnumber);
                    //FILE *img = fopen(filename, "w");
                    //alt
                    img = fopen(filename, "w");

                    //Write the block to the first JPEG
                    fwrite(buffer, 512, 1, img);

                    //Tell the program that we are now in the JPEG section
                    jpegfound = 1;
                }
        }

        //Once we've found the first jpeg
        //Read through and write the remaining blocks to the file
        //Create new files and close old files as headers arise
        else{
        if (jpegfound == 1)
        {
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0)
                {
                    //Close the current file
                    fclose(img);
                    //Move to the next file name
                    jpegnumber++;
                    //Open our next JPEG
                    sprintf(filename, "%03i.jpg", jpegnumber);
                    //FILE *img = fopen(filename, "w");
                    //ALT
                    img = fopen(filename, "w");
                    //Write the block to the next JPEG
                    fwrite(buffer, 512, 1, img);
                }
            else {
                fwrite(&buffer, 512, 1, img);
            }
        }
        }
    }
    fclose(file);
    fclose(img);

    return 0;

}

