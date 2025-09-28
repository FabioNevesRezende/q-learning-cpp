# Q Learning algorithm example in C++

This is a simple project design to teach de Q Learning algorithm in C++

## Build and run

Clone this project, install Cmake and run ./build.sh
it will create a build folder and a binary QLearningCpp

you run it with:

    ./QLearningCpp states-file.txt rewards-file.txt origin-point destination-point num-epochs-to-train alpha gamma

### for example:

     ./QLearningCpp ../states.txt ../rewards.txt E G 1000 0.9 0.75

it will train it by 1000 epochs, calculate the Q table considering this states with learning rate 0.9 and gamma of 0.75 and print a route from point E to G

You can tweak the epochs, learning rate and gamma to see the different Q table results and routes