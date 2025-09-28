#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "utils.hpp"
#include "ai.hpp"

using namespace utils;
using namespace ai;

int main(int argc, char* argv[]){

    // read command line arguments and store them in the variables
    params* p = new params;
    string states_file = argv[1];
    string rewards_map_file = argv[2];
    p->route_init = argv[3][0];
    p->route_priority = argv[4][0];
    p->route_end = argv[5][0];
    p->epochs = stoi(string(argv[6]));
    p->alpha = stod(string(argv[7]));
    p->gamma = stod(string(argv[8]));

    // use current time as seed for random number generator
    std::srand(std::time({})); 

    // read the states file and define the mappings between location and states
    read_states_file(p, states_file);

    // read the rewards matrix file and create a matrix for it
    p->R_init = read_rewards_matrix(rewards_map_file);

    // get route from point A to point B (p->route_init to p->route_end, prioritizing p->route_priority)
    auto rota = route_with_priority(p);

    // print the route from point A to point B
    cout << "Route from "  << p->route_init << " to " << p->route_end << " according to Q-learning:" << endl;
    for(char c : rota){
        cout << c << " ";
    }
    cout << endl;

    delete p;
    
    return 0;
}