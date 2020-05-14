/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Javier Diaz
 * Date        : September 29, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector< vector<int> > ways;
    vector< vector<int> > result;
    //Check if the number of stairs is less than or equal to zero
    //Return an empty vector if true
    //Recurse through the loop if false
    if (num_stairs <= 0) {
        ways.push_back(vector<int>());
    }
    else {
        //Outer Loop
        for (int i = 1; i <= 3; ++i) {
            //Check if the number of stairs is greater than or equal to the outer loop
            if (num_stairs >= i){
                //Recursively call the function with on less stair
                result = get_ways(num_stairs - i);
                //Inner loop
                for (unsigned int j = 0; j < result.size(); ++j) {
                    //Add the outer loop value to the vector result at the inner loop position
                    result[j].insert(result[j].cbegin(), i);
                    //Add inner loop element at position j to the vector ways
                    ways.push_back(result[j]);
                }
            }
        }
    }
    //Return the different combinations
    return ways;
}

int num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    // Copied from Sieve program
    //Used for seeting the width of numbers during display
    int num_count = 1;
    while (num > 9) {
        num = num/10;
        num_count++;
    }
    return num_count;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    
    //the maximum number of stair combinations, used to set width
    const int max_width = num_digits(ways.size());
    //the number of stairs
    const int stair_count = (int)(ways[0].size());
    //Return the singular version of the outputed statement if true
    //Return the plural version of the outputed statement if false
    if (stair_count == 1){
        cout << ways.size() << " way to climb " << stair_count << " stair.";
    }
    else{
        cout << ways.size() << " ways to climb " << stair_count << " stairs.";
    }
    cout << endl;
    //Outer Loop
    for (unsigned int i = 0; i <= ways.size(); ++i) {
        //Set width size and print combination number
        cout << setw(max_width) << i+1 << ". [";
        //Inner Loop
        for (unsigned int j = 0; j < ways[i].size()-1; ++j){
            //Print the vector combinations except the last one
            cout << ways[i][j] << ", ";
        }
        //Print the last one to restrain from printing an extra comma and space
        cout << ways[i][ways[i].size()-1];
        //Print closing bracket
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    int m;
    istringstream iss;
    
    //Checks for the correct number of inputs
    if (argc != 2) {
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    //Creates the argument into a string
    iss.str(argv[1]);
    //Checks if m is a positive number
    //Return error if true
    //Return display if not
    if(!(iss >> m) || m < 0) {
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    else {
        display_ways(get_ways(m));
    }
}
