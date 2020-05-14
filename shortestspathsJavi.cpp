//
//  shortestspathsJavi.cpp
//  
//
//  Created by Javier Diaz on 11/30/19.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
#include <vector>
#include <cstdlib>

using namespace std;

//allow for infinity to be represented as a variable
long infinity = numeric_limits<long>::max();


void print_matrix(long** arr, long n){
    for(long i = 0; i < n; ++i){
        for (long j = 0; j < n; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Computes the floyd algorithm on an inputted array and the number of vertices on the graphs
// Returns the path matrix if found
long** floyd(long** arr, long n){
    long** distance_matrix = arr;
    
    for(long k = 0; k < n; ++k){
        for(long i = 0; i < n; ++i){
            for(long j = 0; j < n; ++j){
                if(distance_matrix[i][k] != infinity && distance_matrix[k][j] != infinity){
                    distance_matrix[i][j] = min(distance_matrix[i][j], distance_matrix[i][k] + distance_matrix[k][j]);
                }
            }
        }
    }
    return distance_matrix;
}

char** intermediate(long** arr, char** arr2, long n){
    long** distance_matrix = arr;
    char** intermediate_matrix = arr2;
    
    for(long k = 0; k < n; ++k){
        for(long i = 0; i < n; ++i){
            for(long j = 0; j < n; ++j){
                if(distance_matrix[i][k] != infinity && distance_matrix[k][j] != infinity){
                    if(distance_matrix[i][j] > distance_matrix[i][k] + distance_matrix[k][j])
                        distance_matrix[i][j] = min(distance_matrix[i][j], distance_matrix[i][k] + distance_matrix[k][j]);
                }
            }
        }
    }
    return distance_matrix;
}

//long** create_matrix(long n) {
//    // Create a 2d array filled with
//    long **array = new long*[n];
//    // For each row, make an array of line_number longs.
//    for (long i = 0; i < n; ++i) {
//        array[i] = new long[n];
//    }
//    //Fill all elements with 0 unless they are on the diagonal (i == j)
//    for (long i = 0; i < n; ++i) {
//        for (long j = 0; j < n; ++j) {
//            if (i != j) {
//                array[i][j] = infinity;
//            }
//            else {
//                array[i][j] = 0;
//            }
//        }
//    }
//    return array;
//}
//
//void delete_matrix(long **array, long n){
//    for(long i = 0; i < init; i++){
//           delete [] array[i];
//       }
//       delete [] array;
//}

void display_table(long** const matrix, const string &label, int num_vertices, const bool use_letters = false){
    cout << label << endl;
    long max_val = 0;
    for(int i = 0; i < num_vertices; i++){
        for(int j = 0; j < num_vertices; j++){
            long cell = matrix[i][j];
            if(cell < inf && cell > max_val){
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? to_string(max_val).length() : to_string(max(static_cast<long>(num_vertices), max_val)).length();
    cout << ' ';
    for(int j = 0; j < num_vertices; j++){
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for(int i = 0; i < num_vertices; i++){
        cout << static_cast<char>(i + 'A');
        for(int j = 0; j < num_vertices; j++){
            cout << " " << setw(max_cell_width);
            if(matrix[i][j] == inf){
                cout << "-";
            }else if(use_letters){
                cout << static_cast<char>(matrix[i][j] + 'A');
            }else{
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char * const argv[]){
    
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
//    // Add read errors to the list of exceptions the ifstream will handle.
//    input_file.exceptions(ifstream::badbit);
//    string line;
//    try {
//        unsigned int line_number = 1;
//        // Use getline to read in a line.
//        // See http://www.cplusplus.com/reference/string/string/getline/
//        while (getline(input_file, line)) {
//            cout << line_number << ":\t" << line << endl;
//            ++line_number;
//        }
//        // Don't forget to close the file.
//        input_file.close();
//    } catch (const ifstream::failure &f) {
//        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
//        return 1;
//    }
//        return 0;
    
    
    string line;
    getline(input_file, line);
    istringstream temp_Number(line);
    istringstream temp_String(line);
    
    unsigned int line_number;
    string element_String;
    
    temp_Number>>line_number //element represented as an int
    temp_String>>element_String //element represented as a string
    
    //First make sure the input is correct before building the three arrays
    
    //The number of vertices is not an integer between 1 and 26.
    if ((line_number <= 0 || line_number > 26) && strcmp(to_string(line_number), element_String) == 0) {
        cerr << "Error: Invalid number of vertices '" << line_number << "' on line 1." << endl;
        return 1;
    }
    
    //Next, create three matrices: Distance, Paths, and Intermediate
    
    // Distance matrix
    long **distance_matrix = new long*[line_number];
    // For each row, make an array of line_number longs.
    for (long i = 0; i < line_number; ++i) {
        distance_matrix[i] = new long[line_number];
    }
    //Fill all elements with 0 unless they are on the diagonal (i == j)
    for (long i = 0; i < line_number; ++i) {
        for (long j = 0; j < line_number; ++j) {
            if (i != j) {
                distance_matrix[i][j] = infinity;
            }
            else {
                distance_matrix[i][j] = 0;
            }
        }
    }
    
    // Path Lengths
    // Floyd function will be applied to this array
    long **paths_matrix = new long*[line_number];
    // For each row, make an array of line_number longs.
    for (long i = 0; i < line_number; ++i) {
        paths_matrix[i] = new long[line_number];
    }
    //Fill all elements with 0 unless they are on the diagonal (i == j)
    for (long i = 0; i < line_number; ++i) {
        for (long j = 0; j < line_number; ++j) {
            if (i != j) {
                paths_matrix[i][j] = infinity;
            }
            else {
                paths_matrix[i][j] = 0;
            }
        }
    }
    
    // Array used for intermediates
    // Declare a 2-dimensional array with line_number rows.
    char **intermediates_matrix = new char*[line_number];

    // For each row, make an array of line_number chars.
    for (long i = 0; i < line_number; ++i) {
        intermediates_matrix[i] = new char[line_number];
        // Fill the array with "-".
        fill(intermediates_matrix[i], intermediates_matrix[i] + line_number, "-");
    }
    
    //Lastly, parse through the input and compute the shortest path possible
    
    //Add 64 to the element number in order to find the correct ascii character
    char end_vertex = line_number + 64;
    //line number
    int row_counter = 1;
    
    //read input
    while(getline(inFile, line)){
        row_counter++;
        
        string vertex1, vertex2, edge;
        istringstream
    }
    
}


