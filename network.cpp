#include "network.h"

Network::Network(unsigned long int numberOfNodes){

}

unsigned long int Network::GetRandomDegree(){
    double val;
    std::srand(unsigned(time(NULL)));
    val = double(std::rand())/RAND_MAX;
    return static_cast<unsigned long>(val);
}
