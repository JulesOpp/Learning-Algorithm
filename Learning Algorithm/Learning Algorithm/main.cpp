//
//  main.cpp
//  Learning Algorithm
//
//  Created by Jules on 2/28/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[])
{
    // Ahhhhh, the joys of returning to C++
    
    std::cout << "Hello, World!\n";
    return 0;
}


// This program will create a new language, interpret the language, have an AI that uses the language to attempt to spell new words
// This program is based upon the work at http://www.primaryobjects.com/CMS/Article149
// These languages are wonderful http://en.wikipedia.org/wiki/Esoteric_programming_language


/* 
New language (similar to BrainFuck) - using a linked list

    :)  - Increment Data Pointer
    :(  - Decrement Data Pointer
 
    ;)  - Increment Pointer
    ;(  - Decrement Pointer
 
    :O  - Output the data
    :D  - Input data
 
    :p  - Begin while loop (while not zero)
    :d  - End while loop
 
    Anything else that is useful...

*/

/*
    To create words from the data, characters are mapped to numbers in this order starting at 1 and going up
 
    ' etaoinshtdlcumwfgypbvkjxqz' (note the space)
 
*/

/*
    The AI will generate a random set of sequences using the new language.
 
    The AI will then run the sequence through an interpretter and depending how similar it is to the desired output, will be rewarded.

    The AI will then evolve: keep some of the sequence depending on how much it is rewarded for similarity and mutate accordingly.
 
    It will run through generations until sufficiently close to the desired output.
 
*/