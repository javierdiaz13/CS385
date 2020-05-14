/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Javier Diaz
 * Version     : 1.0
 * Date        : October 23rd, 2019
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long inversion_count = 0;
    for (int i = 0; i < length; ++i) {
        for (int j = i + 1; j < length; ++j) {
            if (array[i] > array[j]) {
                inversion_count++;
            }
        }
    }
    return inversion_count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int *scratch = new int[length];
    long inversion_count = mergesort(array,scratch,0,length-1);
    delete[] scratch;
    return inversion_count;
}

//MERGESORT(A, low, high)
// 1. if low < high then
// 2.     mid = low + (high - low) / 2
// 3.     MERGESORT(A, low, mid)
// 4.     MERGESORT(A, mid+1, high)
// 5.     L = low
// 6.     H = mid + 1
// 7.     for k <- low to high
// 8.         do if L <= mid and (H > high or A[L] <= A[H])
// 9.             then scratch[k] = A[L]
//10.                  L <- L + 1
//11.             else scratch[k] = A[H]
//12.                  H <- H + 1
//13.     for k <- low to high
//14.         do A[k] <- scratch[k]


static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    int L,H,mid;
    
    //if left marker is less than the right marker perform MergeSort
    //if false return 0
    if (low < high) {
        mid = low + (high - low)/2;
        long inversion_count = 0;
        //Call mergesort recursively on the left half of the array and return inversion_count
        inversion_count += mergesort(array,scratch,low,mid);
        //Call mergesort recursively on the right half of the array and return inversion_count
        inversion_count += mergesort(array,scratch,mid+1,high);
        L = low;
        H = mid + 1;
        
        //Adds elements to the scratch array
        for (int i = low; i <= high; ++i) {
            //if true add element at position L
            if (L <= mid && (H > high || array[L] <= array[H])) {
                scratch[i] = array[L];
                L++;
            }
            //if false add element at position H
            else {
                scratch[i] = array[H];
                H++;
                inversion_count += mid-L+1;
            }
        }
        //Transfer elements from scratch to array
        //Update the array while returning recursively
        for (int j = low; j <= high; ++j) {
            array[j] = scratch[j];
        }
        return inversion_count;
    }
    return 0;
    
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    
    //Too many arguments
    if (argc > 2) {
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 0;
    }
    
    //first argument is not slow
    if (argc == 2){
        if (strcmp(argv[1],"slow")) {
            cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
            return 0;
        }
    }
    
    cout << "Enter sequence of integers, each followed by a space: " << flush;
    
    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    
    //No integers passed as args
    if (values.size() == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 0;
    }
    
    //if true run the program using the slow function
    if (argc == 2) {
        cout << "Number of inversions: " << count_inversions_slow(&values[0],values.size()) << endl;
    }
    //if false run the program using the fast function
    else {
        cout << "Number of inversions: " << count_inversions_fast(&values[0],values.size()) << endl;
    }
    return 0;
}
