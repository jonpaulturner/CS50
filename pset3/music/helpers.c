// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //1/8, 1/4, 3/8, 1/2, 1/1

    int numer;
    int denom;

    numer = fraction[0] - '0';
    denom = fraction[2] - '0';

    if (denom == 1){
        numer = numer * 8;
        return numer;
    }
    else if (denom == 2){
        numer = numer *4;
        return numer;
    }
    else if (denom == 4){
        numer = numer * 2;
        return numer;
    }
    else if (denom ==8){
        return numer;
    }
    else{
        return 1;
    }

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
//declare offset values and value of starting frequency
    int A4freq = 440;
    int offset = 0;

    int accidental = 0;
    int octave = 0;
    int noteletter = 0;

    int semioffset = 0;
    int accidentaloffset =0;


    //check for accidentals
    if (strlen(note) == 3){
        noteletter = note[0];
        accidental = note[1];
        octave = note[2];

    }
    else if (strlen(note) == 2){
        noteletter = note[0];
        octave = note[1];
        accidental = 0;
    }
    else {
        return 1;
    }

     //adjust semitones based on note

    if (noteletter == 'B'){
        semioffset = 2;
    }
    else if (noteletter == 'A'){
        semioffset = 0;
    }
    else if (noteletter == 'G'){
        semioffset = -2;
    }
    else if (noteletter == 'F'){
       semioffset = -4;
    }
    else if (noteletter == 'E'){
        semioffset = -5;
    }
    else if (noteletter == 'D'){
        semioffset = -7;
    }
    else if (noteletter == 'C'){
       semioffset =-9;
    }
    else{
        return 1;
    }

    if (accidental == '#'){
        accidentaloffset = 1;
        offset = offset+1;
    }
    else if (accidental == 'b'){
        accidentaloffset = -1;
        offset = offset-1;
    }
    else{
        accidentaloffset = 0;
    }

    offset = offset + semioffset; //accidentaloffset;

    //adjust offset for octave
    //THIS COULD BE AN ISSUE FOR OTHER OCTAVES
    //CONSIDER GOING BACK TO -'0' THEN -4
    offset = offset + 12*((octave-'4'));

    return round(A4freq * pow(2, offset/12.0));
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // "" represents a rest in the text notation of music here

    if (strcmp(s, "") == 0){
        return true;
    }
        return false;
}
