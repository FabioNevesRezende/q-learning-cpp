
#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <sstream>
#include <string>

namespace utils{

using std::cout, 
std::endl, 
std::map, 
std::vector, 
std::string, 
std::ifstream,
std::tuple,
std::get;

typedef vector<int> int_list;
typedef vector<double> double_list;
typedef map<char, int> location_to_state_map_t;
typedef map<int, char> state_to_location_map_t;

int index_of_greatest(double_list l){
    int greatest = 0;
    int size = l.size();

    for(int i = 0; i<size; i++){
        if(l[i] > l[greatest])
            greatest = i;
    }

    return greatest;
}


vector<double_list> get_initial_q_list(int num_states){
    vector<double_list> ret;
    for(int i=0; i<num_states; i++){
        ret.push_back(double_list(num_states));
    }

    return ret;
}

tuple<location_to_state_map_t, state_to_location_map_t, int_list> read_states_file(const string& filename){
    ifstream f(filename);
    location_to_state_map_t ret1;
    state_to_location_map_t ret2;
    int_list actions;
    string temp;
    int count=0;

    while (getline(f,temp)){
        char current_state = temp.c_str()[0];
        ret1[current_state] = count;
        ret2[count] = current_state;
        actions.push_back(count);
        count++;
    }
    return std::make_tuple(ret1, ret2, actions);
}

void print_states(location_to_state_map_t s){
    for(auto it=s.begin(); it!=s.end(); ++it){
        cout << it->first << ": " << it->second << endl;
    }
}

void print_int_list(int_list l){
    for(auto it=l.begin(); it!=l.end(); ++it)
        cout << *it << " ";
}

void print_q_map(vector<double_list> q){
    for(auto it=q.begin(); it!=q.end(); ++it){
        for(auto jt=it->begin(); jt!=it->end(); ++jt)
            cout << *jt << " ";
        cout << endl;
    }
}

// provided by chatGpt, reads the rewards matrix file
vector<int_list> read_rewards_matrix(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    string line;
    vector<int_list> matrix;

    // Skip the first line (column headers)
    if (!getline(file, line)) {
        throw std::runtime_error("File is empty or invalid format.");
    }

    // Read remaining lines
    while (getline(file, line)) {
        // Remove everything after '#'
        if (auto pos = line.find('#'); pos != string::npos) {
            line = line.substr(0, pos);
        }

        std::istringstream iss(line);
        int_list row;
        int value;

        // Extract integers from the line
        while (iss >> value) {
            row.push_back(value);
        }

        if (!row.empty()) {
            matrix.push_back(std::move(row));
        }
    }

    return matrix;
}


}