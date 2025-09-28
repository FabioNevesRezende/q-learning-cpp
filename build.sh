mkdir build
cd build
cmake ..
make
./QLearningCpp ../states.txt ../rewards.txt E F G 100000 0.75 0.9