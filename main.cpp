#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "utils.hpp"
#include "ai.hpp"

using namespace utils;
using namespace ai;

int main(int argc, char* argv[]){

    string states_file = argv[1];
    string rewards_map_file = argv[2];
    char route_init = argv[3][0];
    char route_priority = argv[4][0];
    char route_end = argv[5][0];
    int epochs = stoi(string(argv[6]));
    double alpha = stod(string(argv[7]));
    double gamma = stod(string(argv[8]));

    std::srand(std::time({})); // use current time as seed for random generator

    // read the states file and define the mappings between location and states
    auto maps = read_states_file(states_file);
    location_to_state_map_t location_to_state = get<0>(maps);
    state_to_location_map_t state_to_location = get<1>(maps);

    int num_states = location_to_state.size();

    // read the rewards matrix file and create a matrix for it
    vector<int_list> R = read_rewards_matrix(rewards_map_file);

    // update the rewards matrix to make the destination state reward higher than any other
    // and to make the priority state a little higher so it has more chances to pass there
    int destination_state = location_to_state[route_end];
    int priority_state = location_to_state[route_priority];
    R[priority_state][priority_state] = 500;
    R[destination_state][destination_state] = 1000;
    
    // set the initial Q matrix filled with zeroes
    auto Q = get_initial_q_list(num_states);

    // train the model filling the Q matrix with the rewards for each step
    train_q_map(epochs, num_states, Q, R, gamma, alpha);

    // prints the Q map
    print_q_map(Q);

    // get route from point A to point B
    auto rota = route(Q, location_to_state, state_to_location, route_init, route_end);

    // print the route from point A to point B
    cout << "Route from "  << route_init << " to " << route_end << " according to Q-learning:" << endl;
    for(char c : rota){
        cout << c << " ";
    }
    cout << endl;
    
    return 0;
}