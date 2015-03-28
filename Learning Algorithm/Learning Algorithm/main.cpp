//
//  main.cpp
//  Learning Algorithm
//
//  Created by Jules on 2/28/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

struct node {
    int     data;
    node    *next;
    node    *prev;
};

string RunSeq(string seq);
double GetFit(string res, string des);
string MutSeq(string seq, double fit);
int ComRes(string res[20], string des);
string print(node* root);
string RanGen();

int main(int argc, const char * argv[])
{
    // Ahhhhh, the joys of returning to C++
    
    srand(time(0));
    
    printf("Hello World!");
    printf("\n");
    printf("Welcome to the Evolution-Based Learning Algorithm");
    printf("\n\n");
    
    string pop[20];     // The strings of the population
    string res[20];     // The result of the sequence interpretted
    double fit[20];     // The fitness of the population
    
    string des;         // Desired string for the algorithm to learn
    
    //string seq;         // The sequence in language for the AI to use
    //string res;         // Result of the sequence when interpretted
    //double fit;         // The fitness of the res compared to des
    int    gen;         // Number of generations
    
    string bef;         // The previous sequence
    
    des = "Hello World";
    //seq = ":):):):p:(;):):);(";
    //seq = "";
    
    for (int i=0; i<20; i++) {
        pop[i] = "";
        for (int j=0; j<8; j++) {
            pop[i].append(RanGen());
        }
    }
        
        //seq.append(RanGen());
    
    //bef = seq;
    gen = 1;
      
    for (int i=0; i<20; i++) {
        res[i] = RunSeq(pop[i]);
        fit[i] = GetFit(res[i], des);
        printf("Individ: \t%d\nSequence: \t%s\nResult: \t%s\n",i,pop[i].c_str(),res[i].c_str());
    }
    
    //res = RunSeq(seq);
    //fit = GetFit(res, des);
        
    //printf("Sequence: \t%s \nResult: \t%s\nDesired: \t%s\nFitness: \t%f\nGener: \t\t%d\n\n",seq.c_str(),res.c_str(),des.c_str(),fit,gen);
    
    while (true)
    {
        printf("Gen: \t%d\t%s\n",gen,res[0].c_str());

        if (gen > 1000000)
            break;
        gen += 1;
        
        if (ComRes(res, des) != -1)
            break;
        
        for (int i=0; i<20; i++) {
            // Run each individual, check fitness, mutate
            pop[i] = MutSeq(pop[i], fit[i]);
            res[i] = RunSeq(pop[i]);
            fit[i] = GetFit(res[i], des);
        }
        
        for (int i=0; i<20; i++) {
            // Crossover rate, choose random other good-fitness individual and crossover
            for (int j=i; j<20; j++) {
                if (fit[i] < fit[j]) {
                    double tmp = fit[i];
                    fit[i] = fit[j];
                    fit[j] = tmp;
                    
                    string tmp2 = pop[i];
                    pop[i] = pop[j];
                    pop[j] = tmp2;
                }
            }
        }
        
        for (int i=10; i<20; i++) {
            // Cross over
            if (rand()%6 == 1) {
                // 12.5% chance of crossing over
                int tmp = rand()%10;
                int tmp2;
                do {
                    tmp2 = rand()%10;
                } while (tmp == tmp2);
                int pos = rand()%min(pop[tmp].length(),pop[tmp2].length());
                
                pop[i] = "";
                pop[i].append(pop[tmp].substr(0,pos));
                pop[i].append(pop[tmp2].substr(pos,pop[tmp2].length()-pos));
            }
        }
        
        //for (int i=0; i<20; i++)
        //  printf("Individ:%d Fit:%f",i,fit[i]);
        //printf("\n");
        
        
        /*seq = MutSeq(seq, fit);
        gen += 1;
        
        res = RunSeq(seq);
        fit = GetFit(res, des);

        if (GetFit(bef, des) > fit)
        {
            seq = bef;
            res = RunSeq(seq);
            fit = GetFit(res, des);
            
            printf("Using before: fit %f\n",fit);
        }
        else {
            bef = seq;
        }

        
        //printf("Sequence: \t%s \nResult: \t%s\nDesired: \t%s\nFitness: \t%f\nGener: \t\t%d\n\n",seq.c_str(),res.c_str(),des.c_str(),fit,gen);
        printf("%d\n",gen);             */

    }
    
    //printf("Sequence: \t%s \nResult: \t%s\nDesired: \t%s\nFitness: \t%f\nGener: \t\t%d\n\n",seq.c_str(),res.c_str(),des.c_str(),fit,gen);
    
    //for (int i=0; i<20; i++)
      //  printf("Individ: \t%d\nSequence: \t%s\nResult: \t%s\n\n",i,pop[i].c_str(),res[i].c_str());
    
    printf("Sequence: \t%s\nResult: \t%s\n",pop[ComRes(res, des)].c_str(), res[ComRes(res, des)].c_str());
    
    return 0;
}

string RunSeq(string seq)
{   // Interpret the sequence from the AI
    
    node* root;
    node* conductor;
    
    root = new node;
    root->next = NULL;
    root->prev = NULL;
    root->data = 0;

    conductor = root;
    
    int count = 0;
    
    // Interpret sequence
    for (int i=0; i<seq.length()/2; i++)
    {
        count++; 
        if (count > 200) break;
        
        if (seq[i*2] == ':')
        {
            if (seq[i*2+1] == ')') {
                // Increment data
                conductor->data += 1;
            }
            else if (seq[i*2+1] == '(') {
                // Decrement data
                conductor->data -= 1;
            }
            else if (seq[i*2+1] == 'O') {
                // Output
                printf("%d",conductor->data);
            }
            else if (seq[i*2+1] == 'D') {
                // Input
                // Do nothing right now
            }
            else if (seq[i*2+1] == 'p') {
                // Begin while
                if (conductor->data == 0) {
                    // go to end while
                    while (i<seq.length()/2 && seq[i*2] != ':' && seq[i*2+1] != 'd') {
                        i++;
                    }
                }
            }
            else if (seq[i*2+1] == 'd') {
                // End while
                if (conductor->data != 0) {
                    // go to begin while
                    int tmp = i;
                    while (i>0 && !(seq[i*2] == ':' && seq[i*2+1] == 'p'))
                        i--;
                    if (i==0 && seq[1] == 'p')
                        i = tmp;
                }
            }
        }
        else if (seq[i*2] == ';')
        {
            if (seq[i*2+1] == ')') {
                // Increment pointer
                if (conductor->next != NULL)
                    conductor = conductor->next;
                else {
                    node* tmp = new node;
                    conductor->next = tmp;
                    tmp->prev = conductor;
                    tmp->next = NULL;
                    tmp->data = 0;
                    conductor = tmp;
                }
            }
            else if (seq[i*2+1] == '(') {
                // Decrement pointer
                if (conductor->prev != NULL)
                    conductor = conductor->prev;
                else {
                    node* tmp = new node;
                    conductor->prev = tmp;
                    tmp->next = conductor;
                    tmp->prev = NULL;
                    tmp->data = 0;
                    conductor = tmp;
                }
            }
        }
    }
    
    return print(root);
}

string print(node* root)
{
    node* conductor;
    
    conductor = root;
    string res = "";
    
    while ( conductor->prev != NULL ) {
        conductor = conductor->prev;
    }
    
    while ( conductor != NULL ) {        
        //char buffer[128];
        //snprintf(buffer, sizeof(buffer), "%d", conductor->data);
        //res += buffer;
        
        char tmp = conductor->data + 'a';
        res += tmp;
        conductor = conductor->next;
    }
    
    return res;
}

double GetFit(string res, string des)
{   // Get the fitness of the sequence from the AI
    
    int fit = 0;
    
    for (int i=0; i<min(res.length(), des.length()); i++)
        fit += 256 - abs(res[i] - des[i]);
    
    return fit;
}

// Give an equal probability of selecting any of the characters
// Given that characters, either change to any of the 6, delete, or add one
string MutSeq(string seq, double fit)
{   // Mutate the sequence according to its fitness
    
    
    // CHANGE MUTATION TO THE OTHER GUYS
    // Loop through each character, if mutation rate then
    // 1/3 insertion (50-50 up or down), 1/3 deletion, 1/3 replacement
    
    int i = rand()%3;
    
    switch (i) {
        case 0: {
            // Insertion
            int j = rand()%(seq.length()/2);
            j *= 2;
            
            int z = rand()%2;
            
            if (z == 0) {
                // Add up
                seq.replace(i,2,seq.substr(i,2).append(RanGen()));
            }
            else {
                // Add down
                seq.replace(i,2,RanGen().append(seq.substr(i,2)));
            }
            
            break; }
        case 1: {
            // Deletion
            int j = rand()%(seq.length()/2);
            j *= 2;
            
            if (seq.length() > 2)
                seq.replace(i,2,"");
            
            break; }
        case 2: {
            // Replacement
            int j = rand()%(seq.length()/2);
            j *= 2;
            
            seq.replace(i,2,RanGen());
            
            break; }
        default:
            break;
    }
    
    //int i = rand()%(seq.length()/2);
    //i *= 2;
    
    /*switch (rand()%8) {
        case 0:
            seq.replace(i,2,":)");
            //seq += ":)";
            break;
        case 1:
            seq.replace(i,2,":(");
            //seq += ":(";
            break;
        case 2:
            seq.replace(i,2,";)");
            //seq += ";)";
            break;
        case 3:
            seq.replace(i,2,";(");
            //seq += ";(";
            break;
        case 4: {
            if (seq.length() > 2) {
                int j = i;
                while (i == j) { j = rand()%(seq.length()/2); j*=2; }
                seq.replace(min(i,j),2,":p");
                seq.replace(max(i,j),2,":d"); 
            }
            //seq += ":p";
            break; }
        case 5:
            if (seq.length() > 40) {
                seq.replace(i, 2, "");
            }
            //seq.replace(i,2,RanGen().append(seq.substr(i,2)));
            //seq.replace(i,2,":d");
            //seq += ":d";
            break;
        case 6:
            if (seq.length() > 2)
                seq.replace(i,2,"");
            //if (seq.length() > 2) seq = seq.substr(0,seq.length()-2);
            break;
        case 7:
            seq.replace(i,2,RanGen().append(seq.substr(i,2)));
            break;
        default:
            break;
    }*/
    
    return seq;
}

string RanGen()
{
    switch (rand()%6) {
        case 0: return ":)";
        case 1: return ":(";
        case 2: return ";)";
        case 3: return ";(";
        case 4: return ":p";
        case 5: return ":d";            
        default: break;
    }
    
    return "";
}

int ComRes(string res[20], string des)
{   // Check if the AI result contain the desired result
    
    bool tmp = true;
    int tmp2 = -1;

    for (int i=0; i<20; i++) {
    
        if (res[i].length() < des.length())
            tmp = false;
    
        for (int j=0; j<des.length(); j++) {
            if (res[i][j] != des[j]) {
                tmp = false;
            }
        }
        
        if (tmp == true) tmp2 = i;
        tmp = true;
    }
            
    return tmp2;
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