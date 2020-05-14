/*******************************************************************************
 * Name    : student.cpp
 * Author  : Javier Diaz
 * Version : 1.0
 * Date    : September 6, 2019
 * Description : Prints the gpa of passing and/or failing students
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student {
public:
    
    //Constructor that uses an initializer list
    Student(string first, string last, float gpa, int id) :
    first_{first}, last_{last}, gpa_{gpa}, id_{id} { }
    
    //Accessor for first name
    string get_first_name () const {
        return first_;
    }
    
    //Accessor for last name
    string get_last_name () const {
        return last_;
    }
    
    //Accessor for gpa
    float get_gpa () const {
        return gpa_;
    }
    
    //Accessor for id
    int get_id () const {
        return id_;
    }
    
    //Accessor for full name
    string full_name () const {
        return get_first_name() + " " + get_last_name();
    }
    
    //Print out the full name, gpa, and id of a single student.
    void print_info () const {
        cout << full_name() << ", GPA: " << fixed << setprecision(2) << get_gpa() << ", ID: " << get_id() << endl;
    }
    
    
private:
    //Private Variables
    string first_, last_;
    float gpa_;
    int id_;
};

/**
 * Takes a vector of Student objects, and returns a new vector
 * with all Students whose GPA is < 1.0.
 */
vector<Student> find_failing_students(const vector<Student> &students) {
    vector<Student> failing_students;
    // Iterates through the students vector, appending each student whose gpa is
    // less than 1.0 to the failing_students vector.
    
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].get_gpa() < 1.0) {
            failing_students.push_back(students[i]);
        }
    }
    return failing_students;
}

/**
 * Takes a vector of Student objects and prints them to the screen.
 */
void print_students(const vector<Student> &students) {
    // Iterates through the students vector, calling print_info() for each student.
    for (auto it = students.cbegin(); it != students.cend(); ++it) {
        it->print_info();
    }
}

/**
 * Allows the user to enter information for multiple students, then
 * find those students whose GPA is below 1.0 and prints them to the
 * screen.
 */
int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;
    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl << "Failing students:";
    // TODO
    // Print a space and the word 'None' on the same line if no students are
    // failing.
    // Otherwise, print each failing student on a separate line.
    if (find_failing_students(students).empty()) {
        cout << " None";
    }
    else{
        cout << "\n";
        print_students(find_failing_students(students));
    }
    
    return 0;
}
