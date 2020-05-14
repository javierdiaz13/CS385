/*****************************************************************************
 * Name    : gcd.cpp
 * Author  : Javier Diaz
 * Version : 1.0
 * Date    : August 30, 2019
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ****************************************************************************/
#include <iostream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int gcd_recursive(int m, int n) {
    
    if (m == 0){
        return n;
    }
    else if (n == 0){
        return m;
    }
    return abs(gcd_recursive(n, m % n));
}

int gcd_iterative(int m, int n) {
    m = abs(m);
    n = abs(n);
    int gcd = 0;
    
    if (n > m) {
        int temp = n;
        n = m;
        m = temp;
    }
    
    for (int c = 1; c <= m; ++c) {
        if(m % c == 0 && n % c == 0){
            gcd = c;
        }
    }
    return gcd;
}

int main(int argc, char* const argv[]) {
    int m, n;
    istringstream iss;
    
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer." << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer." << endl;
        return 1;
    }
    
    cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(n,m) << endl;
    cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(n,m) << endl;
    return 0;
}
