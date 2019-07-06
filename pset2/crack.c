//Crack

//Include libraries
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

//find the salt
string salt[2];
salt[0] = argv[0];
salt[1] = argv[1];

printf("%s\n", salt);

//define max password length
int passlength = 4;
char guess[4] = {'\0'};

//for loop that iterates through one character passwords, then two, etc...
for (int i = 0; i < passlength; i++)
    {
    //generate characters in the corresponding string places
    for (int j = passlength; j < i; j++)
        {

        }

    }

}