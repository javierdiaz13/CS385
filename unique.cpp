/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Javier Diaz
 * Date        : September 20, 2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>


using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for(char c: s){
        //Checks if the char c is lowercase
        if(c < 97 || c > 122) {
            //c is uppercase
            return false;
        }
    }
    //c is lowercase
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    unsigned int storage = 0;
    //Finds how many positions you will shift the to the left
    int difference = 0;
    //Goes through all characters in the string
    for (char c: s) {
        
        //How many spaces the char will be shifted to on the unsigned int
        // to match the position on the alphabet
        difference = c - 'a';
        
        //Checks for duplicates, if true return false because the char has already been seen
        if(storage & (1 << difference)){
            //Dupicate has been found
            return false;
        }
        //if false then update the unsigned int to recognize that the char has already been seen once
        else {
            //Updates the char position in storage
            storage = storage | 1 << difference;
        }
    }
    //No duplicates found
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <string>" << endl;
    }
    else {
        if (is_all_lowercase(argv[1])) {
            
            if (all_unique_letters(argv[1])) {
                cout << "All letters are unique." << endl;
            }
            else {
                cout << "Duplicate letters found." << endl;
            }
            
    }
        else{
            cerr << "Error: String must contain only lowercase letters." << endl;
        }
    }
}
    
   

