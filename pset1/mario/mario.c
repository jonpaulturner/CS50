//mario

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask the user for the number of blocks
    int height;
    do
    {
        height = get_int("How tall do you want the pyramid: ");
    }
    while (height < 0 || height > 23);

//Create a rows variable and loop through each row until the height is reached
    for (int rows = 1; rows < height+1; rows++) //Make a number of rows
        {
           //Print left hand spaces
           for (int space1 = 0; space1 < (height-rows); space1++)
            {
                printf(" ");
            }
            //Print left hand blocks
            for (int block1 = 0; block1 < rows; block1++)
            {
                printf("#");
            }

            //Print center spaces
            printf("  ");

            //Print right hand blocks
            for (int block1 = 0; block1 < rows; block1++)
            {
                printf("#");
            }

            //Return to new row
            printf("\n");

        }
}
