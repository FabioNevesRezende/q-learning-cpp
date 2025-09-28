# Q Learning algorithm example in C++

This is a simple project design to teach de Q Learning algorithm in C++

## Build and run

Clone this project, install Cmake and run ./build.sh
it will create a build folder and a binary QLearningCpp

you run it with:

    ./QLearningCpp states-file.txt rewards-file.txt origin-point destination-point

### for example:

     ./QLearningCpp ../states.txt ../rewards.txt E G

### it will calculate the Q table considering this states and print a route from point E to G