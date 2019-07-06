//Caesar -

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include <stdlib.h>

//Take in a command line argument
int main(int argc, string argv[])
{
    //Check the input arguments to make sure there's only one
    if (argc != 2){
        exit(1);
    }

    //Convert the input argument from a string to an integer.
    int n = atoi(argv[1]);

    //Get plaintext and start cypher
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    //Loop through and print the cipher text
    //Print each character individually
    for (int i = 0, s = strlen(plaintext); i < s ;i++)
      {
          if (isalpha(plaintext[i]))
            {
                if(isupper(plaintext[i]))
                    {
                        int alphabetindex = plaintext[i] - 65;
                        int ciphertext = (alphabetindex + n) % 26;
                        char ciphertextASCII = ciphertext + 65;
                        printf("%c",ciphertextASCII);
                    }
                if(islower(plaintext[i]))
                    {
                        int alphabetindex = plaintext[i] - 97;
                        int ciphertext = (alphabetindex + n) % 26;
                        char ciphertextASCII = ciphertext + 97;
                        printf("%c",ciphertextASCII);
                    }
            }
            else
            {
                printf("%c",plaintext[i]);
            }

          //char ciphertext = plaintext[i] + n;
          //printf("%c",ciphertext);

          //Debugg:  printf("%c\n", plaintext[i]);
      }
     printf("\n");
     return 0;
}