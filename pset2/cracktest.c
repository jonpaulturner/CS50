//CrackTEST
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

//Take in a command line argument
int main(int argc, string argv[])
{
    //Check the input arguments to make sure there's only one
    if (argc != 2){
        exit(1);
    }
    char password[50];
    strcpy(password, crypt(argv[1], "t6"));
    printf("%s\n",password);

    char letter = 'a';

    for (int i = 0, a = 26; i < a; i++)
    {
        printf("%c", letter);
        letter = letter + 1;
    }
    printf("\n");

}
