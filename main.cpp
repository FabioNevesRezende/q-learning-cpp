#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "utils.hpp"

using namespace utils;

int main(int argc, char* argv[]){

    string states_file = argv[1];
    string rewards_map_file = argv[2];
    char route_init = argv[3][0];
    char route_end = argv[4][0];

    auto gamma = 0.75;
    auto alpha = 0.9;
    int epochs = 1000;

    std::srand(std::time({})); // use current time as seed for random generator

    auto maps = read_states_file(states_file);
    location_to_state_map_t location_to_state = get<0>(maps);
    state_to_location_map_t state_to_location = get<1>(maps);
    int_list actions = get<2>(maps);

    int num_states = location_to_state.size();

    vector<int_list> R = read_rewards_matrix(rewards_map_file);
    
    auto Q = get_initial_q_list(num_states);

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
        double TD = R[current_state][next_state] + gamma*Q[next_state][index_of_greatest(Q[next_state])] - Q[current_state][next_state];
        Q[current_state][next_state] = Q[current_state][next_state] + alpha*TD; 
    }

    //print_q_map(Q);

    // get route from point A to point B
    vector<char> rota = {route_init};
    char next_location = route_init;
    while(next_location != route_end){
        int starting_state = location_to_state[route_init];
        int next_state = index_of_greatest(Q[starting_state]);
        next_location = state_to_location[next_state];
        rota.push_back(next_location);
        route_init = next_location;
    }

    cout << "Rota de acordo com o Q-learning:" << endl;
    for(char c : rota){
        cout << c << " ";
    }
    
    return 0;
}