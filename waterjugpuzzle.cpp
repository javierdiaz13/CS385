/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Valentina Bustamante and Javier Diaz
 * Date        : October 14, 2019
 * Description : Water Jug Problem
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <cmath> 

using namespace std;

struct State {
    int a, b, c;
    string directions;
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

};
queue <State> queue_bfs;
vector <string> directions_vector;
vector<vector<State>> matrix;

void fill_matrix(int capA, int capB){
    State trash(-1, -1, -1);
    
    for(int i = 0; i < capA + 1; i++){
        vector<State> temp;
        matrix.push_back(temp);
        for(int j = 0; j <= capB ; j++){
            matrix[i].push_back(trash);
        }
    } 
}
bool is_equal(State &current, State &goal){
    if(current.a == goal.a && current.b == goal.b && current.c == goal.c){
        return true;
    }
    return false;
}

void pour(State &current, int current_from, int current_to, int same_amount, const int cap_to, string &direction){

    int available_to = cap_to - current_to;
    State temp(-1,-1,-1);
    
    if(available_to > 0 &&  current_from > 0){
        
        for(int i = available_to; i > 0 && current_from > 0; i--){
            current_to++;
            current_from--;
        }
        if(direction.compare("CtoA") == 0){
            State to_from(current_to, same_amount, current_from);
            if(is_equal(matrix[to_from.a][to_from.b], temp)){
                queue_bfs.push(to_from);
                matrix[to_from.a][to_from.b] = current;
            }
        }
        else if(direction.compare("BtoA") == 0){
            State to_from(current_to, current_from, same_amount);
            if(is_equal(matrix[to_from.a][to_from.b], temp)){
                queue_bfs.push(to_from);
                matrix[to_from.a][to_from.b] = current;
            }
        }
        else if(direction.compare("CtoB") == 0){
            State to_from(same_amount, current_to, current_from);
            if(is_equal(matrix[to_from.a][to_from.b], temp)){
                queue_bfs.push(to_from);
                matrix[to_from.a][to_from.b] = current;
            }
        }
        else if(direction.compare("AtoB") == 0){
            State to_from(current_from, current_to, same_amount);
            if(is_equal(matrix[to_from.a][to_from.b], temp)){
                queue_bfs.push(to_from);
                matrix[to_from.a][to_from.b] = current;
            }
        }
        else if(direction.compare("BtoC") == 0){
            State to_from(same_amount, current_from, current_to);
            if(is_equal(matrix[to_from.a][to_from.b], temp)){
                queue_bfs.push(to_from);
                matrix[to_from.a][to_from.b] = current;
            }
        }
        else if(direction.compare("AtoC") == 0){
            State to_from(current_from, same_amount, current_to);
            if(is_equal(matrix[to_from.a][to_from.b], temp)){
                queue_bfs.push(to_from);
                matrix[to_from.a][to_from.b] = current;
            }
        }
    }
}
void display_path(State &goal){
    vector<string> path;
    string enter = "";

    if(!(goal.a == 0 && goal.b == 0)){
        if(goal.a != matrix[goal.a][goal.b].a){
            //means that jug A and B were changed
            if(goal.b != matrix[goal.a][goal.b].b){
                //if the a from the previous state is less than the goal a that means that we poured from a
                if(matrix[goal.a][goal.b].a < goal.a){
                    if(abs(goal.b - matrix[goal.a][goal.b].b) == 1){
                        enter = "Pour " + to_string(abs(goal.b - matrix[goal.a][goal.b].b)) + " gallon from B to A. " + goal.to_string();
                    }else{
                        enter = "Pour " + to_string(abs(goal.b - matrix[goal.a][goal.b].b)) + " gallons from B to A. " + goal.to_string();
                    }  
                    path.push_back(enter);
                }
                //if the a from the previous state is greater than the goal a that means that its the To jug
                else{
                    if(abs(goal.a - matrix[goal.a][goal.b].a) == 1){
                        enter = "Pour " + to_string(abs(goal.a - matrix[goal.a][goal.b].a)) + " gallon from A to B. " + goal.to_string();
                    }else{
                        enter = "Pour " + to_string(abs(goal.a - matrix[goal.a][goal.b].a)) + " gallons from A to B. " + goal.to_string();
                    }
                    path.push_back(enter);
                }
                display_path(matrix[goal.a][goal.b]);
            }
            //means that jug A and C were changed
            else{
                if(matrix[goal.a][goal.b].a < goal.a){
                    if(abs(goal.c - matrix[goal.a][goal.b].c) == 1){
                        enter = "Pour " + to_string(abs(goal.c - matrix[goal.a][goal.b].c)) + " gallon from C to A. " + goal.to_string();
                    }
                    else{
                        enter = "Pour " + to_string(abs(goal.c - matrix[goal.a][goal.b].c)) + " gallons from C to A. " + goal.to_string();
                    }
                    path.push_back(enter);
                }
                //if the a from the previous state is greater than the goal a that means that its the To jug
                else{
                    if(abs(matrix[goal.a][goal.b].a - goal.a) == 1){
                        enter = "Pour " + to_string(abs(matrix[goal.a][goal.b].a - goal.a)) + " gallon from A to C. " + goal.to_string();
                    }
                    else{
                        enter = "Pour " + to_string(abs(matrix[goal.a][goal.b].a - goal.a)) + " gallons from A to C. " + goal.to_string();
                    }
                    
                    path.push_back(enter);
                }
                display_path(matrix[goal.a][goal.b]);
            }
        }
        //means that jug B and C were changed
        else if(goal.b != matrix[goal.a][goal.b].b){

             if(matrix[goal.a][goal.b].b < goal.b){
                 if(abs(goal.b - matrix[goal.a][goal.b].b) == 1){
                    enter = "Pour " + to_string(abs(goal.b - matrix[goal.a][goal.b].b)) + " gallon from C to B. " + goal.to_string();
                 }else{
                    enter = "Pour " + to_string(abs(goal.b - matrix[goal.a][goal.b].b)) + " gallons from C to B. " + goal.to_string();
                 }
                path.push_back(enter);
            }
                //if the a from the previous state is greater than the goal a that means that its the To jug
            else{
                if(abs(matrix[goal.a][goal.b].c - goal.c) == 1){
                    enter = "Pour " + to_string(abs(matrix[goal.a][goal.b].c - goal.c)) + " gallon from B to C. " + goal.to_string();
                }else{
                    enter = "Pour " + to_string(abs(matrix[goal.a][goal.b].c - goal.c)) + " gallons from B to C. " + goal.to_string();
                }
                path.push_back(enter);
            }
            display_path(matrix[goal.a][goal.b]);
        }
    }
    if(goal.a == 0 && goal.b == 0){
        cout << "Initial state. " << goal.to_string() << endl;
    }
    for(uint i = 0; i < path.size(); i++){
        cout << path[i] << endl;
    }
}
void bfs(const int capA, const int capB, const int capC, int goalA, int goalB, int goalC){
    State current(0, 0, capC);
    State goal_state(goalA, goalB, goalC);
    queue_bfs.push(current);
    string direction = "";
    bool no_solution = false;
    fill_matrix(capA, capB);
    State initial_holder(0,0,0);
    matrix[current.a][current.b] = initial_holder;
    
    while(!is_equal(queue_bfs.front(), goal_state)){
         if(queue_bfs.empty() == true){
            cout << "No solution." << endl;
            no_solution = true;
            break;
        }
        current = queue_bfs.front();
        queue_bfs.pop();
    
            direction = "CtoA";
            pour(current, current.c, current.a, current.b, capA, direction);
            direction = "BtoA";
            pour(current, current.b, current.a, current.c, capA, direction);
            direction = "CtoB";
            pour(current, current.c, current.b, current.a, capB, direction);
            direction = "AtoB";
            pour(current, current.a, current.b, current.c, capB, direction);
            direction = "BtoC";
            pour(current, current.b, current.c, current.a, capC, direction);
            direction = "AtoC";
            pour(current, current.a, current.c, current.b, capC, direction);
    }
    if(!no_solution){
        display_path(queue_bfs.front());
    }
}
int main(int argc, char * const argv[]) {
    int m;
    istringstream iss;
    
    if(argc != 7){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    vector<char> jug_names = {'A', 'B', 'C'};
    vector<int> input;
    int goal_sum_ = 0;

    for(int i = 1; i < argc; i++){
        iss.str(argv[i]);
        if(i < 4){
            if(!(iss >> m) || m <= 0){
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jug_names[i-1] << ".";
                return 1;
            }
        }
        else if(!(iss >> m) || m < 0){
            cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jug_names[i-4] << ".";
            return 1;
        }
        input.push_back(m);
        iss.clear();
    }
    for(uint i = 3; i < input.size(); i++){
        if(input[i-3] < input[i]){
                cerr << "Error: Goal cannot exceed capacity of jug " << jug_names[i-3] << ".";
                return 1;
        }
        goal_sum_ += input[i];
    }
    if(input[2] != goal_sum_){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
        return 1;
    }
    bfs(input[0],input[1], input[2], input[3], input[4],input[5]);
    return 0;
}
