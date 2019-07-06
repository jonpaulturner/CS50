// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember how much to scale image
    int n = atoi(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //
    // Create new info headers
    BITMAPFILEHEADER out_bf = bf;
    BITMAPINFOHEADER out_bi = bi;

    int WidthOld = bi.biWidth;
    int HeightOld = bi.biHeight;

    // determine padding for scanlines
    int padding_old = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    out_bi.biWidth = bi.biWidth*n;
    out_bi.biHeight = bi.biHeight*n;

    //determine new padding
    int padding_new = (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    out_bi.biSizeImage = ((sizeof(RGBTRIPLE) * (out_bi.biWidth)) + padding_new) * abs(out_bi.biHeight);  //Total size including pixels, padding, and headers in bytes

    out_bf.bfSize = out_bf.bfOffBits + out_bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int i = 0; i < abs(HeightOld); i++)
    {
        int j;
        // temporary storage
        RGBTRIPLE triple;
        //-----------------n-1 times Write pixels, padding to outfile---------------
        for (int h = 0; h < n-1; h++)
        {
            // iterate over pixels in scanline
            for (j = 0; j < WidthOld; j++)
            {
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // write pixels to outfile
                for (int s = 0; s < n; s++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add padding
            for (int k = 0; k < padding_new; k++)
            {
                fputc(0x00, outptr);
            }
            //------------Send infile cursor back--------------------------
            fseek(inptr, -1 * sizeof(RGBTRIPLE)*j ,SEEK_CUR);
        }

            //-----------------Last write pixels, padding to outfile---------------
            for (j = 0; j < WidthOld; j++)
                        {
                            // read RGB triple from infile
                            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                            // write pixels to outfile
                            for (int s = 0; s < n; s++)
                            {
                                // write RGB triple to outfile
                                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                            }
                        }
                        // add padding
                        for (int k = 0; k < padding_new; k++)
                        {
                            fputc(0x00, outptr);
                        }

        // skip over padding, if any
        fseek(inptr, padding_old, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
