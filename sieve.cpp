/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Javier Diaz
 * Date        : September 11, 2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;


private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
    
    
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout << "\n" << "Number of primes found: " <<  count_num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    
    const int max_prime_width = num_digits(max_prime_);
    int primes_per_row = 80 / (max_prime_width + 1);
    
    //Prime Counter
    int num_primes = 0;
    
    for (int i = 2; i <= limit_; ++i) {
        //Checks if the element in the array is false
        if(is_prime_[i] == false){
            //Last number in the row, add indent after
            if (num_primes == (primes_per_row - 1)) {
                cout << setw(max_prime_width) << i << endl;
                num_primes = 0;
            }
            //Prints the final prime number
            else if(i == max_prime_){
                cout << setw(max_prime_width) << i;
            }
            //Prints the primes that do not loop around
            else if(count_num_primes() <= primes_per_row){
                cout << i << " ";
                num_primes++;
            }
            //Prints any number that is the not the final prime or last number in a row.
            else{
                cout << setw(max_prime_width) << i << " ";
                num_primes++;
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int prime_counter = 0;
    for (int i = 2; i <= limit_; ++i) {
        if (is_prime_[i] == false) {
            prime_counter++;
        }
    }
    return prime_counter;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    int temp = 0;
    for (int i = 2; i <= sqrt(limit_); ++i) {
        if (is_prime_[i] == false) {
            for (int j = 0; (pow(i,2) + j*i) <= limit_; ++j) {
                temp = (pow(i,2) + j*i);
                is_prime_[temp] = true;
            }
        }
    }
    
    for (int c = 0; c <= limit_; ++c) {
        if (is_prime_[c] == false){
            max_prime_ = c;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int num_count = 1;
    while (num > 10) {
        num = num/10;
        num_count++;
    }
    return num_count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve primes(limit);
    primes.display_primes();
    //delete [] primes;
    return 0;
}
