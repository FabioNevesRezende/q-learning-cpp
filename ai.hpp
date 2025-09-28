#pragma once

#include "utils.hpp"
using namespace utils;

namespace ai{

void train_q_map(int epochs, int num_states, vector<double_list>& Q, vector<int_list> R, double gamma, double alpha){

    // train the model based on the state using q-learning
    for(int i = 0; i<epochs; i++){
        auto current_state = std::rand()%num_states;
        int_list playable_actions; // array to hold possible actions I can go from current state
        
        // get the possible actions I can go from current state based on rewards:
        for(int j = 0; j<num_states; j++){
            if(R[current_state][j] > 0) playable_actions.push_back(j);
        }

        int next_state = playable_actions[std::rand()%playable_actions.size()]; // randomly selected next state

        // calculate temporal difference for next state based on current using Bellman equation
        double TD = R[current_state][next_state] + gamma*Q[next_state][utils::index_of_greatest(Q[next_state])] - Q[current_state][next_state];
        Q[current_state][next_state] = Q[current_state][next_state] + alpha*TD; 
    }
}

vector<char> route(vector<double_list> Q, location_to_state_map_t location_to_state, state_to_location_map_t state_to_location, char route_init, char route_end){
    vector<char> rota = {route_init};
    char next_location = route_init;
    while(next_location != route_end){
        int starting_state = location_to_state[route_init];
        int next_state = utils::index_of_greatest(Q[starting_state]);
        next_location = state_to_location[next_state];
        rota.push_back(next_location);
        route_init = next_location;
    }

    return rota;
}

}