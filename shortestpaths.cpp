/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Javier Diaz and Valentina Bustamante
 * Version     : 1.0
 * Date        : December 5, 2019
 * Description : Floyd Algorithm implemented in code - All Pairs Shortest Path
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <limits>
#include <iomanip> 

using namespace std;
long INF = numeric_limits<long>::max();
long const HYPHEN = 45;
long const A = 65;

//Fills a matrix with 0s and infinities
long** fill_matrix(long** array, long int_rep) {
       for(long row = 0; row < int_rep; row++){
           array[row] = new long[int_rep];
           for(long col = 0; col < int_rep; col++){
               //zeroes for the major diagnol
               if(row!=col){
                   array[row][col] = INF;
               }else{
                   array[row][col] = 0;
               }
           }
       }
    return array;
}

/**
* Displays the matrix on the screen formatted as a table. */
void display_table(long** const matrix, const string &label, int num_vertices, const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;

    for (int row = 0; row < num_vertices; row++) {
        for (int col = 0; col < num_vertices; col++) {
            long cell = matrix[row][col];
            if (cell < INF && cell > max_val) {
                max_val = matrix[row][col];
            }
        }
    }
    int max_cell_width = use_letters ? to_string(max_val).length() : to_string(max(static_cast<long>(num_vertices), max_val)).length();
    cout << ' ';
    for (int c = 0; c < num_vertices; c++) {
        cout << (use_letters ? setw(max_cell_width) : setw(max_cell_width + 1)) << static_cast<char>(c + A);
    }
    cout << endl;
    for (int row = 0; row < num_vertices; row++) {
        cout << static_cast<char>(row + A);
        for (int col = 0; col < num_vertices; col++) { cout << " " << setw(max_cell_width);
            if (use_letters){
                cout << setw(max_cell_width - 1);
            }
            if (matrix[row][col] == INF) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix[row][col]);
            } else {
                cout << matrix[row][col];
            }
        }
        cout << endl;
    }
    cout << endl;
}

//definition of floyds algorithm from the textbook implemented
long** compute_floyd(long** distance, long int_rep){
    long** result = distance;
    for(long diag = 0; diag < int_rep; diag++){
        for(long row = 0; row < int_rep; row++){
            for(long col = 0; col < int_rep; col++){
                if(result[row][diag] != INF && result[diag][col] != INF){
                    result[row][col] = min(result[row][col], result[row][diag] + result[diag][col]);
                }
            }
        }
    }
    return result;
}

//Computes the intermediates of all vertex pair that may have any.
long** compute_intermediate(long** distance, long** intermediates, long int_rep){
    long** dist = distance;
    long** result = intermediates;

    for(long diag = 0; diag < int_rep; diag++){
        for(long row = 0; row < int_rep; row++){
            for(long col = 0; col < int_rep; col++){
                if(dist[row][diag] != INF && dist[diag][col] != INF && row != col){
                    if(dist[row][diag] + dist[diag][col] < dist[row][col]){
                        dist[row][col] = dist[row][diag] + dist[diag][col];
                        result[row][col] = diag + A;
                    }
                }
            }
        }
    }
    return result;
}


//Displays the path in which the vertices go
void path_display(long** distances, long** intermediates, long int_rep) {
    for(long row = 0; row < int_rep; row++){
         char print_row = static_cast<char>(row + A);
        for(long col = 0; col < int_rep; col++){
            
               char print_col = static_cast<char>(col + A);
               long outer_count = row;
               
               if(distances[row][col] == INF){
                   cout << print_row << " -> " << print_col <<  ", distance: infinity, path: none";
               }
               else{
                    cout << print_row << " -> " << print_col <<  ", distance: " << distances[row][col] << ", path: " << print_row;
               }
            
               while(intermediates[outer_count][col] != HYPHEN && distances[row][col] != INF) {
                   
                   for(long i = 1; i < int_rep; i++) {
                       if(intermediates[outer_count][intermediates[outer_count][col] - A] == HYPHEN) {
                           cout << " -> " << static_cast<char>(intermediates[outer_count][col]);
                           break;
                       }
                       else {
                           intermediates[outer_count][col] = intermediates[outer_count][intermediates[outer_count][col]-A];
                       }
                   }
                   outer_count = intermediates[outer_count][col] - A;
              
               }
               
               if(intermediates[outer_count][col] == HYPHEN && distances[row][col] != 0 && distances[row][col] != INF){
                   cout << " -> " << print_col;
               }
               cout << endl;
        }
    }
}


//Used at the end of the main to free up the memory space being used by the matrices
void deleteMatrix(long** matrix, long int_rep){
    for(int i = 0; i < int_rep; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
}

int main(int argc, const char *argv[]) {
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
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);

    //Read lines from a file
    string line;
    getline(input_file, line);
    
    istringstream int_temp (line);
    istringstream string_temp(line);
    int int_rep;
    string string_rep;
    
    int_temp>>int_rep;     //integer representation
    string_temp>>string_rep;    //string representation

    //The number of vertices is not an integer between 1 and 26
    if(!(int_rep>0 && int_rep<=26) && to_string(int_rep) == string_rep){
        //integer
        cerr << "Error: Invalid number of vertices '" << int_rep << "' on line 1." << endl;
        return 1;
    }
    
    if(int_rep == 0){
            //string
            cerr << "Error: Invalid number of vertices '" << string_rep << "' on line 1." << endl;
            return 1;
    }  
    
    //Distance Matrix
    long** distances = new long*[int_rep];
    //call to fill function
    distances = fill_matrix(distances, int_rep);
    //Paths Matrix
    long** paths = new long*[int_rep];
    //fill
    paths = fill_matrix(paths, int_rep);
    
    // Declare a 2-dimensional array with 'some_size' rows.
    long** intermediates = new long*[int_rep];
    // For each row, make an array of 'some_other_size' booleans.
    for (int i = 0; i < int_rep; ++i) {
        intermediates[i] = new long[int_rep];
        // Fill the array with zeros.
        fill(intermediates[i], intermediates[i] + int_rep, HYPHEN);
    }

    try {
         unsigned int line_number = 2;
         char letter_range = int_rep + 64;
         
         // Use getline to read in a line.
         // See http://www.cplusplus.com/reference/string/string/getline/
         while (getline(input_file, line)) {
             istringstream inputs(line);
        
             string first, second, edge_string;
             inputs >> first >> second >> edge_string;
         
             stringstream temp(edge_string);
             int edge_num = 0;
             temp >> edge_num;

             //Each line should have three components
             if(edge_string.size() == 0){
                 cerr << "Error: Invalid edge data '" << first << " " << second << "' on line " << line_number << "." << endl;
                 return 1;
             }

            //The starting vertex must be in range.
             if(!(first[0] >=65 && first[0]<=letter_range) || !(second[0] >=65 && second[0] <= letter_range)){
                 cerr << "Error: "<< (!(first[0] >=65 && first[0]<=letter_range) ? "Starting" : "Ending") << " vertex '" << ( !(first[0] >=65 && first[0]<=letter_range) ? first : second) << "' on line " << line_number << " is not among valid values A-" << letter_range << "." << endl;
                 return 1;
                 
             }
                 
            //The starting vertex must be in range.
            if(first.size() != 1 || second.size() != 1){
                cerr << "Error: " << ((first.size() != 1) ? "Starting" : "Ending") << " vertex '" << ((first.size() != 1) ? first : second) << "' on line " << line_number << " is not among valid values A-" << letter_range << "." << endl;
                return 1;
            }
         
            //The ending vertex must be in range.
             if(!(second[0] >=65 && second[0] <= letter_range)){
                 cerr << "Error: Ending vertex '" << second << "' on line " << line_number << " is not among valid values A-" << letter_range << "." << endl;
                 return 1;
             }
                 
            //Each line should have three components.
            if(edge_num <= 0){
                cerr << "Error: Invalid edge weight '" << ((to_string(edge_num) != edge_string) ? edge_string : to_string(edge_num) ) << "' on line " << line_number << "." << endl;
                return 1;
            }
        
             //Input values into the distances and paths matrices
             distances[first[0] - A][second[0]- A] = edge_num;
             paths[first[0] - A][second[0]- A] = edge_num;
             
             //cout << line_number << ":\t" << line << endl;
             ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    //Distance Matrix
    display_table(distances, "Distance matrix:", int_rep, false);
    //Paths Matrix
    display_table(compute_floyd(distances, int_rep), "Path lengths:", int_rep, false);
    //Intermediate Matrix
    display_table(compute_intermediate(paths, intermediates, int_rep), "Intermediate vertices:", int_rep, true);
    
    //Display the path
    path_display(distances, intermediates, int_rep);

    //Delete Distance Matrix
    deleteMatrix(distances, int_rep);
    //Delete Paths Matrix
    deleteMatrix(paths, int_rep);
    //Delete Intermediates Matrix
    deleteMatrix(intermediates, int_rep);

    return 0;
}
