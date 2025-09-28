# Q Learning algorithm example in C++

This is a simple project design to teach de Q Learning algorithm in C++

## Build and run

Clone this project, install Cmake and run ./build.sh
it will create a build folder and a binary QLearningCpp

you run it with:

    ./QLearningCpp states-file.txt rewards-file.txt origin-point priority-point destination-point num-epochs-to-train alpha gamma

### for example:

     ./QLearningCpp ../states.txt ../rewards.txt E F G 1000 0.9 0.75

it will train:
 - by 1000 epochs, 
 - calculate the Q table considering the states.txt and rewards.txt files
 - with learning rate (alpha) 0.9 and discount factor (gamma) of 0.75
 - print a route from point E to G prioritizing passing through point F

You can tweak the epochs, learning rate and gamma to see the different Q table results and routes