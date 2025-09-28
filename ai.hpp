#pragma once

#include "utils.hpp"
using namespace utils;

namespace ai{

void train_q_map(params* p){

    int num_states = p->location_to_state.size();

    // set the initial Q matrix filled with zeroes
    p->Q = get_initial_q_list(num_states);

    // train the model based on the state using q-learning
    for(int i = 0; i<p->epochs; i++){
        auto current_state = std::rand()%num_states;
        int_list playable_actions; // array to hold possible actions I can go from current state
        
        // get the possible actions I can go from current state based on rewards:
        for(int j = 0; j<num_states; j++){
            if(p->R[current_state][j] > 0) playable_actions.push_back(j);
        }

        int next_state = playable_actions[std::rand()%playable_actions.size()]; // randomly selected next state

        // calculate temporal difference for next state based on current using Bellman equation
        double TD = p->R[current_state][next_state] + p->gamma*p->Q[next_state][utils::index_of_greatest(p->Q[next_state])] - p->Q[current_state][next_state];
        p->Q[current_state][next_state] = p->Q[current_state][next_state] + p->alpha*TD; 
    }

    // prints the Q map
    cout << "Q map now:" << endl;
    print_q_map(p->Q);
}

vector<char> route(params* p, char route_init, char route_end){

    // restart the rewards matrix from the initial
    p->R = p->R_init;

    // update the rewards matrix to make the destination state reward higher than any other
    int destination_state = p->location_to_state[route_end];
    p->R[destination_state][destination_state] = 1000;

    // train the model filling the Q matrix with the rewards for each step
    train_q_map(p);

    vector<char> rota = {route_init};
    char next_location = route_init;
    while(next_location != route_end){
        int starting_state = p->location_to_state[route_init];
        int next_state = utils::index_of_greatest(p->Q[starting_state]);
        next_location = p->state_to_location[next_state];
        rota.push_back(next_location);
        route_init = next_location;
    }

    return rota;
}

vector<char> route_with_priority(params *p){
    auto v1 = route(p, p->route_init, p->route_priority);
    auto v2 = route(p, p->route_priority, p->route_end);

    // concatenate the two routes, +1 to remove the first element from second route since it is equal the last from the first route
    v1.insert(v1.end(), v2.begin()+1, v2.end()); 

    return  v1; 

}

}